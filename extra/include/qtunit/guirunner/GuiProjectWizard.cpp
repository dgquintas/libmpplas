/*
 *  $Id: s.GuiProjectWizard.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "GuiProjectWizard.h"

#include <qlineedit.h>
#include <qlistview.h>

#include "TestModule.h"
#include "TestProject.h"
#include "GuiProjectFile.h"
#include "GuiProjectInfo.h"
#include "GuiProjectModules.h"
#include "GuiMainwindow.h"
#include "GuiModuleListItem.h"

using namespace com_uwyn_qtunit;

GuiProjectWizard::GuiProjectWizard(GuiMainwindow* pParent, const char* pName, bool modal, WFlags flags) :
	GuiProjectWizardBase(pParent, pName, modal, flags)
{
	setNextEnabled(mpProjectInfoPage, false);
	setNextEnabled(mpProjectFilePage, false);
    connect(this, SIGNAL(helpClicked()), pParent, SLOT(whatsThis()));
}

GuiProjectWizard::~GuiProjectWizard()
{
}

TestProject* GuiProjectWizard::project() const
{
	TestProject* p_project = 0;
	
	p_project = new TestProject(mpProjectInfo->name(), mpProjectInfo->author(), mpProjectInfo->description(), mpProjectFile->path(), mpProjectModules->modules());

	return p_project;
}

void GuiProjectWizard::nameChanged(bool valid)
{
	setNextEnabled(mpProjectInfoPage, valid);
}

void GuiProjectWizard::pathChanged(bool valid)
{
	setNextEnabled(mpProjectFilePage, valid);
}

void GuiProjectWizard::modulecountChanged(int count)
{
	if (0 == count)
	{
		setFinishEnabled(mpProjectModulesPage, false);
	}
	else
	{
		setFinishEnabled(mpProjectModulesPage, true);
	}
}

void GuiProjectWizard::pageChanged(const QString& rTitle)
{
	if (title(mpProjectInfoPage) == rTitle)
	{
		mpProjectInfo->focusDefault();
	}
	else if (title(mpProjectFilePage) == rTitle)
	{
		mpProjectFile->focusDefault();
	}
	else if (title(mpProjectModulesPage) == rTitle)
	{
		mpProjectModules->focusDefault();
	}
}

