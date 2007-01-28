/* TRANSLATOR com_uwyn_qtunit::GuiProjectModules */
/*
 *  $Id: s.GuiProjectModules.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "GuiProjectModules.h"

#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qlibrary.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qptrlist.h>
#include <qpushbutton.h>

#include "TestModule.h"
#include "GuiModuleListItem.h"

using namespace com_uwyn_qtunit;

GuiProjectModules::GuiProjectModules(QWidget* pParent, const char* pName, WFlags flags) :
	GuiProjectModulesBase(pParent, pName, flags)
{
}

GuiProjectModules::~GuiProjectModules()
{
}

QPtrList<TestModule>* GuiProjectModules::modules()
{
	QPtrList<TestModule>* module_definitions = new QPtrList<TestModule>;
	module_definitions->setAutoDelete(true);

	QListViewItemIterator listview_it(mpModulesListView);

	for (; listview_it.current(); ++listview_it)
	{
		module_definitions->append(new TestModule(listview_it.current()->text(0), listview_it.current()->text(1)));
	}

	return module_definitions;
}

void GuiProjectModules::focusDefault() const
{
    mpModulePathLineEdit->setFocus();
}

void GuiProjectModules::moduleDefinitionChanged()
{
	bool enabled = false;

	if (0 < mpModulePathLineEdit->text().length() &&
		0 < mpSourcePathLineEdit->text().length())
	{
		QFileInfo modulepath_info(mpModulePathLineEdit->text());
		QFileInfo sourcepath_info(mpSourcePathLineEdit->text());
		if (modulepath_info.exists() &&
			modulepath_info.isFile() &&
			modulepath_info.isReadable() &&
			sourcepath_info.exists() &&
			sourcepath_info.isDir() &&
			sourcepath_info.isReadable())
		{
			QLibrary library(mpModulePathLineEdit->text());

			EXP_getTestSuite p_exported_function = (EXP_getTestSuite) library.resolve("getTestSuite");
			if (0 != p_exported_function)
			{
				enabled = true;
			}

			library.unload();
		}
	}

	mpAddPushButton->setEnabled(enabled);

	if (0 != mpModulesListView->selectedItem())
	{
		mpModifyPushButton->setEnabled(enabled);
	}
}

void GuiProjectModules::moduleSelected(QListViewItem* pListViewItem)
{
	if (0 == pListViewItem)
	{
		mpModifyPushButton->setEnabled(false);
		mpRemovePushButton->setEnabled(false);
	}
	else
	{
		mpModifyPushButton->setEnabled(true);
		mpRemovePushButton->setEnabled(true);

		mpModulePathLineEdit->setText(pListViewItem->text(0));
		mpSourcePathLineEdit->setText(pListViewItem->text(1));
	}
}

void GuiProjectModules::addModule()
{
	addModule(mpModulePathLineEdit->text(), mpSourcePathLineEdit->text());
}

void GuiProjectModules::addModule(const QString& rModulePath, const QString& rSourcePath)
{
	new GuiModuleListItem(mpModulesListView, rModulePath, rSourcePath);
	mpModulesListView->clearSelection();

	emit modulecountChanged(mpModulesListView->childCount());
}

void GuiProjectModules::removeAllModules()
{
	mpModulesListView->clear();

	emit modulecountChanged(mpModulesListView->childCount());
}

void GuiProjectModules::modifyModule()
{
	QListViewItem *p_listview_item = mpModulesListView->selectedItem();
	if (0 != p_listview_item)
	{
		p_listview_item->setText(0, mpModulePathLineEdit->text());
		p_listview_item->setText(1, mpSourcePathLineEdit->text());
	}
}

void GuiProjectModules::removeModule()
{
	if (0 != mpModulesListView->selectedItem())
	{
		mpModulesListView->removeItem(mpModulesListView->selectedItem());
		mpModulesListView->clearSelection();
		
		mpModifyPushButton->setEnabled(false);
		mpRemovePushButton->setEnabled(false);
		
		emit modulecountChanged(mpModulesListView->childCount());
	}
}

void GuiProjectModules::selectModulePath()
{
	QString lib_extension;
#if defined(Q_WS_WIN)
	lib_extension = "dll";
#elif defined(Q_OS_MACX)
	lib_extension = "dylib";
#else
	lib_extension = "so";
#endif
	mpModulePathLineEdit->setText(QFileDialog::getOpenFileName(QString::null, QObject::trUtf8("Modules (*.%1)").arg(lib_extension), this, QString::null, trUtf8("Select the module")));
}

void GuiProjectModules::selectSourcePath()
{
	mpSourcePathLineEdit->setText(QFileDialog::getExistingDirectory(QString::null, this, QString::null, trUtf8("Select the root directory of the sources of this module")));
}

