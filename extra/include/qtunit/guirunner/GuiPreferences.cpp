/* TRANSLATOR com_uwyn_qtunit::GuiPreferences */
/*
 *  $Id: s.GuiPreferences.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "GuiPreferences.h"

#include <qcheckbox.h>
#include <qcolordialog.h>
#include <qfiledialog.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qtabwidget.h>
#include <qtoolbutton.h>
#include <qvariant.h>

#include "GuiMainwindow.h"

using namespace com_uwyn_qtunit;

GuiPreferences::GuiPreferences(GuiMainwindow* pParent, const char* pName, bool modal, WFlags flags) :
	GuiPreferencesBase(pParent, pName, modal, flags),
	mExternalViewerArgumentsMenu(),
	mFailureForegroundColor(),
	mFailureBackgroundColor(), 
	mErrorForegroundColor(),
	mErrorBackgroundColor()
{
    mpDelaySpinBox->setLineStep(pParent->rConfig().smDelayUnit);
	
	initPreferences();

	connect(&mExternalViewerArgumentsMenu, SIGNAL(aboutToHide()), this, SLOT(hideExternalViewerArguments()));
	connect(&mExternalViewerArgumentsMenu, SIGNAL(activated(int)), this, SLOT(externalViewerArgumentActivated(int)));
	mExternalViewerArgumentsMenu.insertItem(QString("%s - ")+trUtf8("Sourcepath"), 0);
	mExternalViewerArgumentsMenu.insertItem(QString("%f - ")+trUtf8("Filename"), 1);
	mExternalViewerArgumentsMenu.insertItem(QString("%l - ")+trUtf8("Line number"), 2);
	
}

GuiPreferences::~GuiPreferences()
{
}

void GuiPreferences::initPreferences()
{
	GuiMainwindow* pmainwindow = static_cast<GuiMainwindow*>(parentWidget());

	mpSortTestsCheckbox->setChecked(pmainwindow->rConfig().sortTests());
	mpHighlightRunningTestCheckbox->setChecked(pmainwindow->rConfig().highlightRunningTest());
	mpShowRunningTestCheckbox->setChecked(pmainwindow->rConfig().showRunningTest());
    mpDelaySpinBox->setValue(pmainwindow->rConfig().delay());
	mpExternalViewerLineEdit->setText(pmainwindow->rConfig().externalViewer());
	mpFailureTypeIndicationCheckbox->setChecked(pmainwindow->rConfig().failureTypeIndication());
	
	mFailureForegroundColor = pmainwindow->rConfig().failureForegroundColor();
	mFailureBackgroundColor = pmainwindow->rConfig().failureBackgroundColor();
	mErrorForegroundColor = pmainwindow->rConfig().errorForegroundColor();
	mErrorBackgroundColor = pmainwindow->rConfig().errorBackgroundColor();
	updateFailureForegroundColorButton();
	updateFailureBackgroundColorButton();
	updateErrorForegroundColorButton();
	updateErrorBackgroundColorButton();

	mpReloadModulesCheckbox->setChecked(pmainwindow->rConfig().reloadModules());
	mpRememberProjectCheckbox->setChecked(pmainwindow->rConfig().rememberProject());
	mpAutoRunTestsCheckbox->setChecked(pmainwindow->rConfig().autoRunTests());
}

void GuiPreferences::updateErrorBackgroundColorButton()
{
	QPixmap error_background_color_pixmap(16, 16);
	error_background_color_pixmap.fill(mErrorBackgroundColor);
    mpErrorBackgroundColorButton->setPixmap(error_background_color_pixmap);
}

void GuiPreferences::updateErrorForegroundColorButton()
{
	QPixmap error_foreground_color_pixmap(16, 16);
	error_foreground_color_pixmap.fill(mErrorForegroundColor);
    mpErrorForegroundColorButton->setPixmap(error_foreground_color_pixmap);
}

void GuiPreferences::updateFailureBackgroundColorButton()
{
	QPixmap failure_backround_color_pixmap(16, 16);
	failure_backround_color_pixmap.fill(mFailureBackgroundColor);
    mpFailureBackgroundColorButton->setPixmap(failure_backround_color_pixmap);
}

void GuiPreferences::updateFailureForegroundColorButton()
{
	QPixmap failure_foreground_color_pixmap(16, 16);
	failure_foreground_color_pixmap.fill(mFailureForegroundColor);
    mpFailureForegroundColorButton->setPixmap(failure_foreground_color_pixmap);
}

void GuiPreferences::accept()
{
	GuiMainwindow* pmainwindow = static_cast<GuiMainwindow*>(parentWidget());

	pmainwindow->rConfig().sortTests(mpSortTestsCheckbox->isChecked());
	pmainwindow->rConfig().highlightRunningTest(mpHighlightRunningTestCheckbox->isChecked());
	pmainwindow->rConfig().showRunningTest(mpShowRunningTestCheckbox->isChecked());
    pmainwindow->rConfig().delay(mpDelaySpinBox->value());
	
	pmainwindow->rConfig().externalViewer(mpExternalViewerLineEdit->text());
	pmainwindow->rConfig().failureTypeIndication(mpFailureTypeIndicationCheckbox->isChecked());
	pmainwindow->rConfig().failureForegroundColor(mFailureForegroundColor);
	pmainwindow->rConfig().failureBackgroundColor(mFailureBackgroundColor);
	pmainwindow->rConfig().errorForegroundColor(mErrorForegroundColor);
	pmainwindow->rConfig().errorBackgroundColor(mErrorBackgroundColor);
	
	pmainwindow->rConfig().reloadModules(mpReloadModulesCheckbox->isChecked());
	pmainwindow->rConfig().rememberProject(mpRememberProjectCheckbox->isChecked());
	pmainwindow->rConfig().autoRunTests(mpAutoRunTestsCheckbox->isChecked());
	
	static_cast<GuiMainwindow*>(parentWidget())->applyConfig();
	
	GuiPreferencesBase::accept();
}

void GuiPreferences::editErrorBackgroundColor()
{
    QColor color = QColorDialog::getColor(mErrorBackgroundColor, this);
	if (color.isValid())
	{
		mErrorBackgroundColor = color;
		updateErrorBackgroundColorButton();
	}
}

void GuiPreferences::editErrorForegroundColor()
{
    QColor color = QColorDialog::getColor(mErrorForegroundColor, this);
	if (color.isValid())
	{
		mErrorForegroundColor = color;
		updateErrorForegroundColorButton();
	}
}

void GuiPreferences::editFailureBackgroundColor()
{
    QColor color = QColorDialog::getColor(mFailureBackgroundColor, this);
	if (color.isValid())
	{
		mFailureBackgroundColor = color;
		updateFailureBackgroundColorButton();
	}
}

void GuiPreferences::editFailureForegroundColor()
{
    QColor color = QColorDialog::getColor(mFailureForegroundColor, this);
	if (color.isValid())
	{
		mFailureForegroundColor = color;
		updateFailureForegroundColorButton();
	}
}

void GuiPreferences::externalViewerArgumentActivated(int id)
{
	QString externalviewerargument(mpExternalViewerLineEdit->text());
	int cursorposition = mpExternalViewerLineEdit->cursorPosition();
	switch (id)
	{
		case 0:
			externalviewerargument.insert(cursorposition, "%s");
			mpExternalViewerLineEdit->setText(externalviewerargument);
			mpExternalViewerLineEdit->setCursorPosition(cursorposition+2);
			break;
		case 1:
			externalviewerargument.insert(cursorposition, "%f");
			mpExternalViewerLineEdit->setText(externalviewerargument);
			mpExternalViewerLineEdit->setCursorPosition(cursorposition+2);
			break;
		case 2:
			externalviewerargument.insert(cursorposition, "%l");
			mpExternalViewerLineEdit->setText(externalviewerargument);
			mpExternalViewerLineEdit->setCursorPosition(cursorposition+2);
			break;
	}
}

void GuiPreferences::help()
{
	((GuiMainwindow*)this->parentWidget())->whatsThis();
}

void GuiPreferences::hideExternalViewerArguments()
{
	mpExternalViewerArgumentsPushButton->setDown(false);
}

void GuiPreferences::itemSelected()
{
	mpPreferencesTab->setCurrentPage(mpPreferencesList->currentItem());
}

void GuiPreferences::tabSelected()
{
	mpPreferencesList->setSelected(mpPreferencesTab->currentPageIndex(), true);
	switch (mpPreferencesTab->currentPageIndex())
	{
		case 0:
			mpSortTestsCheckbox->setFocus();
			break;
		case 1:
			mpExternalViewerLineEdit->setFocus();
			break;
	}
}

void GuiPreferences::reject()
{
	initPreferences();
	GuiPreferencesBase::reject();
}

void GuiPreferences::selectExternalViewer()
{
	mpExternalViewerLineEdit->setText(mpExternalViewerLineEdit->text()+QFileDialog::getOpenFileName(QString::null, QString::null, this, QString::null, trUtf8("Select external viewer")));
}

void GuiPreferences::showExternalViewerArguments()
{
	QSize center = mpExternalViewerArgumentsPushButton->size()/2;
	mExternalViewerArgumentsMenu.move(mpExternalViewerArgumentsPushButton->mapToGlobal(QPoint(center.width(), center.height())));
	mExternalViewerArgumentsMenu.show();
}

