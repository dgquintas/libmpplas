/* TRANSLATOR com_uwyn_qtunit::GuiMainwindow */
/*
 *  $Id: s.GuiMainwindow.cpp 1.5 02/09/05 15:03:05+02:00 gbevin@willow.uwyn.office $
 *
 *  This file is part of QtUnit.
 *
 *  QtUnit is a unit testing framework for c++ which compiles into a shared
 *  library. It uses the Qt 3.x library for platform independence.
 *
 *  Copyright (C) 2002, G.Bevin
 * 
 *  gbevin@uwyn.com
 *  http://www.uwyn.com/projects/qtunit
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "GuiMainwindow.h"

#include <qaction.h>
#include <qfiledialog.h>
#include <qlabel.h>
#include <qlistview.h>
#include <qmessagebox.h>
#include <qmenubar.h>
#include <qprocess.h>
#include <qprogressbar.h>
#include <qpushbutton.h>
#include <qregexp.h>
#include <qstatusbar.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qtextstream.h>
#include <qwizard.h>
#include <iostream>

#include "TestBase.h"
#include "TestDescription.h"
#include "TestModule.h"
#include "TestProject.h"
#include "TestProjectParser.h"
#include "TestSuite.h"
#include "GuiErrorListItem.h"
#include "GuiProjectWizard.h"
#include "GuiTestMethodListItem.h"
#include "GuiTestRunner.h"

using namespace com_uwyn_qtunit;

GuiMainwindow::GuiMainwindow(GuiTestRunner* pTestRunner, QWidget* pParent, const char* pName , WFlags flags) :
	GuiMainwindowBase(pParent, pName, flags),
	mpProject(0),
	mpTestRunner(pTestRunner),
	mTestClasses(),
	mTestsToRun(),
	mRunRegisteredTests(*this),
	mStopped(false),
	mpErrorListToolTip(0),
	mConfig(),
	mPreferencesDialog(this),
	mProjectPropertiesDialog(this),
	mAutoRunExecuted(false)
{
	if (true == rConfig().rememberProject() &&
		rConfig().rememberedProject().length() > 0)
	{
		projectOpen(rConfig().rememberedProject());
	}

	mpMenubar->insertSeparator(2);
	mpErrorListToolTip = new GuiErrorListToolTip(mpErrorsListview);
}

GuiMainwindow::~GuiMainwindow()
{
	delete mpErrorListToolTip;
	mpErrorListToolTip = 0;

	delete mpProject;
	mpProject = 0;
}

const TestProject* const GuiMainwindow::project() const
{
	return mpProject;
}

void GuiMainwindow::project(TestProject& rProject)
{
	if (0 != mpProject)
	{
		if (mpProject != &rProject)
		{
			disconnect(mpProject, SIGNAL(modificationStateChanged(bool)), this, SLOT(projectModified(bool)));

			delete mpProject;
			mpProject = 0;
			
			mpProject = &rProject;
			connect(mpProject, SIGNAL(modificationStateChanged(bool)), this, SLOT(projectModified(bool)));
		}
	}
	else
	{
		mpProject = &rProject;
		connect(mpProject, SIGNAL(modificationStateChanged(bool)), this, SLOT(projectModified(bool)));
	}

	projectModified(mpProject->modified());

	rebuildProjectTests();
	refreshTestListview();
	
	mpRunButton->setEnabled(true);

	mpProjectNew->setEnabled(true);
	mpProjectOpen->setEnabled(true);
	mpProjectClose->setEnabled(true);
	mpProjectProperties->setEnabled(true);
	mpProjectSave->setEnabled(true);

	resetStats();
}

void GuiMainwindow::rebuildProjectTests()
{
	mpTestRunner->clear();

	QPtrListIterator<TestModule> modules_it(*mpProject->modules());
	TestModule* p_module = 0;
	TestSuite* p_testsuite = 0;
	while (0 != (p_module = modules_it.current()))
	{
		++modules_it;
		p_testsuite = p_module->testSuite();
		if (0 != p_testsuite)
		{
			mpTestRunner->add(*p_testsuite, p_module->sourcePath());
		}
		else
		{
			QMessageBox::warning(this, trUtf8("Module couldn't be found ..."), trUtf8("The module file '%1' could not be found.").arg(p_module->filePath()), QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
		}
	}
}

bool GuiMainwindow::savedProjectInsurance()
{
	if (0 != mpProject)
	{
		if (true == mpProject->modified())
		{
			int result = QMessageBox::warning(this, trUtf8("Project has been modified ..."), 
				trUtf8("The current project has been modified but hasn't been saved yet.\nAre you sure you want to close it and thus lose the modifications?"), QMessageBox::No, QMessageBox::Yes, QMessageBox::NoButton);

			if (QMessageBox::No == result ||
				0 == result)
			{
				return false;
			}
		}
	}

	return true;
}

void GuiMainwindow::resetButtons()
{
	mpRunButton->setEnabled(false);
	mpRunselectedButton->setEnabled(false);
	mpStopButton->setEnabled(false);
}

void GuiMainwindow::resetStats()
{
	mpErrorsListview->clear();
	mpProgressbar->reset();
	mpProgressbar->setProgress(0);
	mpRunsStats->setText(QString::number(0));
	mpFailuresStats->setText(QString::number(0));
	mpErrorsStats->setText(QString::number(0));
}

void GuiMainwindow::show()
{
	applyConfig();
	GuiMainwindowBase::show();
}

GuiSettings& GuiMainwindow::rConfig()
{
	return mConfig;
}

void GuiMainwindow::applyConfig()
{
	if(true == rConfig().sortTests())
	{
		mpTestsListview->setSorting(0);
	}
	else
	{
		mpTestsListview->setSorting(-1);
	}

	refreshTestListview();

	mpErrorsListview->repaintContents(mpErrorsListview->contentsX(), mpErrorsListview->contentsY(), mpErrorsListview->contentsWidth(), mpErrorsListview->contentsHeight());
}

void GuiMainwindow::refreshTestListview()
{
	mTestClasses.clear();
	mpTestsListview->clear();
	QPtrListIterator<TestBase> it(mpTestRunner->tests());
	TestBase* p_current_test = 0;
	GuiTestClassListItem* p_last_classlistitem = 0;
	GuiTestClassListItem* p_current_classlistitem = 0;
	GuiTestMethodListItem* p_last_methodlistitem = 0;
	while (0 != (p_current_test = it.current()))
	{
		p_current_classlistitem = (GuiTestClassListItem*)mTestClasses.find(p_current_test->testClassname());
		if (0 == p_current_classlistitem)
		{
			p_current_classlistitem = new GuiTestClassListItem(mpTestsListview, *p_current_test, p_last_classlistitem);
			mTestClasses.insert(p_current_test->testClassname(), p_current_classlistitem);
			p_last_classlistitem = p_current_classlistitem;
			p_last_methodlistitem = 0;
		}
		if (0 != p_current_classlistitem)
		{
			p_last_methodlistitem = new GuiTestMethodListItem(p_current_classlistitem, *p_current_test, p_last_methodlistitem);
		}
		++it;
	}
}

void GuiMainwindow::helpAbout()
{
	QMessageBox::about(this, trUtf8("About QtUnit ..."), 
		trUtf8("QtUnit %1\nFramework for unit testing.\nWritten by G.Bevin (gbevin@uwyn.com).\nFor more information go to http://www.uwyn.com/projects/qtunit.").arg(QTUNIT_VERSION));
}

void GuiMainwindow::projectClose()
{
	if (0 != mpProject &&
		true == savedProjectInsurance())
	{
		delete mpProject;
		mpProject = 0;
		
		mpTestRunner->clear();
		refreshTestListview();

		resetStats();
		resetButtons();

		mpProjectNew->setEnabled(true);
		mpProjectOpen->setEnabled(true);
		mpProjectClose->setEnabled(false);
		mpProjectProperties->setEnabled(false);
		mpProjectSave->setEnabled(false);

		setCaption(QString("QtUnit ")+QTUNIT_VERSION);
	}
}

void GuiMainwindow::projectModified(bool state)
{
	if (true == state)
	{
		setCaption(QString("QtUnit ")+QTUNIT_VERSION+" : "+mpProject->name()+" *");
		mpProjectSave->setEnabled(true);
	}
	else
	{
		setCaption(QString("QtUnit ")+QTUNIT_VERSION+" : "+mpProject->name());
		mpProjectSave->setEnabled(false);
	}
}

void GuiMainwindow::projectNew()
{
	GuiProjectWizard project_wizard(this);

	if (QDialog::Accepted == project_wizard.exec())
	{
		project(*(project_wizard.project()));
	}
}

void GuiMainwindow::projectOpen()
{
	projectOpen(QFileDialog::getOpenFileName(QString::null, "QUnit project files (*.qpj)", this, QString::null, trUtf8("Select the name of the project file")));

}

void GuiMainwindow::projectOpen(const QString& rPath)
{
	if (QString::null != rPath &&
		rPath.length() > 0)
	{
		TestProjectParser handler;
		QFile xml_file(rPath);
		QXmlInputSource source(&xml_file);
		QXmlSimpleReader reader;
		reader.setContentHandler(&handler);

		if (false == reader.parse(source))
		{
			QMessageBox::warning(this, trUtf8("Xml error in project file ..."), 
				trUtf8("An error has occured while parsing the project file '%1'.\nIt could not be opened.").arg(rPath), QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
		}
		else
		{
			TestProject* p_project = handler.transferTestProject();
			p_project->path(rPath);
			project(*p_project);
		}
	}
}

void GuiMainwindow::projectProperties()
{
	if (0 != mpProject)
	{
		mProjectPropertiesDialog.project(*mpProject);

		if (QDialog::Accepted == mProjectPropertiesDialog.exec())
		{
			TestProject* p_newproject = mProjectPropertiesDialog.project();
			if (0 != mpProject)
			{
				if (*mpProject == *p_newproject)
				{
					p_newproject->modified(false);
				}
				else
				{
					p_newproject->modified(true);
				}
			}
			project(*p_newproject);
		}
	}
}

void GuiMainwindow::projectSave()
{
	if (0 != mpProject)
	{
		QFile project_file(mpProject->path());
		if (false == project_file.open(IO_WriteOnly))
		{
			QMessageBox::warning(this, trUtf8("Error while saving project file ..."), 
				trUtf8("An error has occured while saving the project file '%1'.\nYou should change its path or filename.").arg(mpProject->path()), QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
		}
		else
		{
			QTextStream project_stream(&project_file);
			project_stream << mpProject->constructXml();
			project_file.close();

			mpProject->modified(false);
		}
	}
}

void GuiMainwindow::showError(QListViewItem* pClickedItem)
{
	QString external_viewer_command(rConfig().externalViewer());
	const TestDescription& description = static_cast<GuiErrorListItem*>(pClickedItem)->testDescription();
	external_viewer_command.replace(QRegExp("%s"), description.sourcePath());
	external_viewer_command.replace(QRegExp("%f"), description.fileName());
	external_viewer_command.replace(QRegExp("%l"), QString::number(description.lineNumber()));

	QProcess external_viewer(QStringList::split(" ", external_viewer_command));
	external_viewer.start();
}

void GuiMainwindow::showPreferences()
{
	mPreferencesDialog.exec();
}

void GuiMainwindow::runAllTests()
{
	if (0 != mpProject)
	{
		if (true == rConfig().reloadModules() &&
			true == mpProject->areModulesModified())
		{
			mpTestRunner->clear();

			rebuildProjectTests();
			refreshTestListview();
		}

		mTestsToRun.clear();

		GuiTestListItem* p_testlistitem = 0;
		QListViewItemIterator it(mpTestsListview);
		while (0 != (p_testlistitem = static_cast<GuiTestListItem*>(it.current()))) 
		{
			if (true == p_testlistitem->runnable())
			{
				mTestsToRun.append(p_testlistitem);
			}
			++it;
		}
		
		runRegisteredTests();
	}
}

void GuiMainwindow::runOneTest(QListViewItem* pClickItem)
{
	mTestsToRun.clear();
	GuiTestListItem* p_testlistitem = static_cast<GuiTestListItem*>(pClickItem);
	if (true == p_testlistitem->runnable())
	{
		mTestsToRun.append(static_cast<GuiTestListItem*>(p_testlistitem));

		runRegisteredTests();
	}
}

void GuiMainwindow::runSelectedTests()
{
	if (0 != mpProject)
	{
		if (true == rConfig().reloadModules() &&
			true == mpProject->areModulesModified())
		{
			mpTestRunner->clear();
			
			rebuildProjectTests();
			refreshTestListview();
			resetStats();
			mpRunselectedButton->setEnabled(false);
			
			QMessageBox::warning(this, trUtf8("Modules in the project have been modified ..."), 
				trUtf8("Some modules in the project have been modified.\nThe tests you selected might not be available anymore,\nplease make your selection again."), QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
		}
		else
		{
			mTestsToRun.clear();
	
			GuiTestListItem* p_testlistitem = 0;
			QListViewItemIterator it(mpTestsListview);
			while (0 != (p_testlistitem = static_cast<GuiTestListItem*>(it.current()))) 
			{
				if (p_testlistitem->isSelected() &&
					true == p_testlistitem->runnable())
				{
					mTestsToRun.append(p_testlistitem);
				}
				++it;
			}
			
			runRegisteredTests();
		}
	}
}

void GuiMainwindow::stop()
{
	mStopped = true;
}

void GuiMainwindow::quit()
{
	if (0 == mpProject ||
		true == savedProjectInsurance())
	{
		if (true == rConfig().rememberProject())
		{
			if (0 == mpProject)
			{
				rConfig().rememberedProject("");
			}
			else
			{
				rConfig().rememberedProject(mpProject->path());
			}
		}

		qApp->exit();
	}
}

void GuiMainwindow::closeEvent(QCloseEvent* pCloseEvent)
{
	if (0 == mpProject)
	{
		pCloseEvent->accept();
	}
	else
	{
	}
	if (true == savedProjectInsurance())
	{
		pCloseEvent->accept();
	}
	else
	{
		pCloseEvent->ignore();
	}
}

void GuiMainwindow::showEvent(QShowEvent*)
{
	if (false == mAutoRunExecuted &&
		0 != mpProject &&
		true == rConfig().autoRunTests())
	{
		mAutoRunExecuted = true;
		runAllTests();
	}
}

void GuiMainwindow::runRegisteredTests()
{
	if (false == mRunRegisteredTests.running() &&
		0 != mpProject &&
		false == mTestsToRun.isEmpty())
	{
		mpTestRunner->resetResult();
		resetStats();
        mpProgressbar->setTotalSteps(mTestsToRun.count());
        mStopped = false;
		mpRunButton->setEnabled(false);
		mpRunselectedButton->setEnabled(false);
		mpStopButton->setEnabled(true);
		
		mRunRegisteredTests.start();
	}
}

void GuiMainwindow::testsSelected()
{
	bool items_selected = false;

	GuiTestClassListItem* p_testclass_listitem = 0;
	GuiTestMethodListItem* p_testmethod_listitem = 0;

	p_testclass_listitem = (GuiTestClassListItem*)mpTestsListview->firstChild();
	while (0 != p_testclass_listitem)
	{
		p_testmethod_listitem = 0;

		if(p_testclass_listitem->isSelected())
		{
			items_selected = true;
			break;
		}
		else
		{
			p_testmethod_listitem = (GuiTestMethodListItem*)p_testclass_listitem->firstChild();
			while (0 != p_testmethod_listitem)
			{
				if(p_testmethod_listitem->isSelected())
				{
					items_selected = true;
					break;
				}
				p_testmethod_listitem = (GuiTestMethodListItem*)p_testmethod_listitem->nextSibling();
			}
		}
		p_testclass_listitem = (GuiTestClassListItem*)p_testclass_listitem->nextSibling();
	}

	if (true == items_selected)
	{
		mpRunselectedButton->setEnabled(true);
	}
	else
	{ 
		mpRunselectedButton->setEnabled(false); 
	} 
}

void GuiMainwindow::updateStats()
{
	mpErrorsStats->setText(QString::number(mpTestRunner->testResult().countErrors()));
	mpFailuresStats->setText(QString::number(mpTestRunner->testResult().countFailures()));
	mpRunsStats->setText(QString::number(mpTestRunner->testResult().countTotal()));
}

GuiMainwindow::RunRegisteredTests::RunRegisteredTests(GuiMainwindow& rGuiMainwindow) :
	QThread(),
	mrGuiMainwindow(rGuiMainwindow)
{
}

GuiMainwindow::RunRegisteredTests::~RunRegisteredTests()
{
}

void GuiMainwindow::RunRegisteredTests::run()
{
	if (0 != mrGuiMainwindow.mpProject)
	{
		mrGuiMainwindow.mpTestRunner->lock();
		mrGuiMainwindow.mpMenubar->setEnabled(false);
		mrGuiMainwindow.mpTestsListview->setEnabled(false);
		mrGuiMainwindow.mpTestRunner->unlock();

		QPtrListIterator<GuiTestListItem> it(mrGuiMainwindow.mTestsToRun);
		
		while (0 != it.current() && false == mrGuiMainwindow.mStopped)
		{
			GuiTestListItem* p_listitem = *it;
			if (0 != p_listitem &&
				true == p_listitem->runnable())
			{
				const TestBase& r_testbase = p_listitem->test();
				
				mrGuiMainwindow.mpTestRunner->lock();
				mrGuiMainwindow.statusBar()->message(trUtf8("Running %1...").
					arg(r_testbase.testFullName()));
				if(true == mrGuiMainwindow.rConfig().showRunningTest())
				{
					mrGuiMainwindow.mpTestsListview->ensureItemVisible(p_listitem);
				}
				p_listitem->running(true);
				mrGuiMainwindow.mpTestRunner->unlock();

				mrGuiMainwindow.mpTestRunner->runTest(r_testbase);
			
				if (*it != mrGuiMainwindow.mTestsToRun.last())
				{
					msleep(mrGuiMainwindow.rConfig().delay());
				}
			
				mrGuiMainwindow.mpTestRunner->lock();
				mrGuiMainwindow.mpProgressbar->setProgress(mrGuiMainwindow.mpProgressbar->progress()+1);
				mrGuiMainwindow.mpProgressbar->update();
				mrGuiMainwindow.updateStats();
				mrGuiMainwindow.mpTestRunner->unlock();
			}
			++it;
		}
		
		mrGuiMainwindow.mpTestRunner->lock();
		if (true == mrGuiMainwindow.mStopped)
		{
			mrGuiMainwindow.statusBar()->message(trUtf8("Stopped."));
		}
		else
		{
			mrGuiMainwindow.statusBar()->message(trUtf8("Finished."));
		}

		mrGuiMainwindow.mpRunButton->setEnabled(true);
		mrGuiMainwindow.testsSelected();
		mrGuiMainwindow.mpStopButton->setEnabled(false);

		mrGuiMainwindow.mTestsToRun.getLast()->running(false);
		mrGuiMainwindow.mpTestRunner->unlock();
	
		mrGuiMainwindow.mpTestRunner->lock();
		mrGuiMainwindow.mpTestsListview->setEnabled(true);
		mrGuiMainwindow.mpMenubar->setEnabled(true);
		mrGuiMainwindow.mpTestRunner->unlock();
	}
}

