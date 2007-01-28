/*
 *  $Id: s.GuiProjectProperties.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "GuiProjectProperties.h"

#include <qlistbox.h>
#include <qptrlist.h>
#include <qtabwidget.h>

#include "TestModule.h"
#include "TestProject.h"
#include "GuiMainwindow.h"
#include "GuiProjectFile.h"
#include "GuiProjectInfo.h"
#include "GuiProjectModules.h"

using namespace com_uwyn_qtunit;

GuiProjectProperties::GuiProjectProperties(GuiMainwindow* pParent, const char* pName, bool modal, WFlags flags) :
	GuiProjectPropertiesBase(pParent, pName, modal, flags)
{
}

GuiProjectProperties::~GuiProjectProperties()
{
}

void GuiProjectProperties::name(const QString& rName)
{
	mpProjectInfo->name(rName);
}

void GuiProjectProperties::author(const QString& rAuthor)
{
	mpProjectInfo->author(rAuthor);
}

void GuiProjectProperties::description(const QString& rDescription)
{
	mpProjectInfo->description(rDescription);
}

void GuiProjectProperties::path(const QString& rPath)
{
	mpProjectFile->path(rPath);
}

TestProject* GuiProjectProperties::project() const
{
	TestProject* p_project = 0;
	
	p_project = new TestProject(mpProjectInfo->name(), mpProjectInfo->author(), mpProjectInfo->description(), mpProjectFile->path(), mpProjectModules->modules());

	return p_project;
}

void GuiProjectProperties::project(const TestProject& project)
{
	mpPropertiesTab->setCurrentPage(0);
	
	name(project.name());
	author(project.author());
	description(project.description());
	path(project.path());
	mpProjectModules->removeAllModules();
	QPtrListIterator<TestModule> modules_it(*(project.modules()));
	TestModule* p_module = 0;
	while ((p_module = modules_it.current()) != 0)
	{
		++modules_it;

		mpProjectModules->addModule(p_module->filePath(), p_module->sourcePath());
	}
}

void GuiProjectProperties::help()
{
	((GuiMainwindow*)this->parentWidget())->whatsThis();
}

void GuiProjectProperties::itemSelected()
{
	mpPropertiesTab->setCurrentPage(mpPropertiesList->currentItem());
}

void GuiProjectProperties::tabSelected()
{
	mpPropertiesList->setSelected(mpPropertiesTab->currentPageIndex(), true);
	switch (mpPropertiesTab->currentPageIndex())
	{
		case 0:
			mpProjectInfo->focusDefault();
			break;
		case 1:
			mpProjectFile->focusDefault();
			break;
		case 2:
			mpProjectModules->focusDefault();
			break;
	}
}
