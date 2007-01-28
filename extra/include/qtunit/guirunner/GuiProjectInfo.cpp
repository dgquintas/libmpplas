/*
 *  $Id: s.GuiProjectInfo.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "GuiProjectInfo.h"

#include <qlineedit.h>
#include <qtextbrowser.h>

using namespace com_uwyn_qtunit;

GuiProjectInfo::GuiProjectInfo(QWidget* pParent, const char* pName, WFlags flags) :
	GuiProjectInfoBase(pParent, pName, flags)
{
}

GuiProjectInfo::~GuiProjectInfo()
{
}

const QString GuiProjectInfo::name() const
{
	return mpProjectNameLineEdit->text();
}

void GuiProjectInfo::name(const QString& rName)
{
	mpProjectNameLineEdit->setText(rName);
}

const QString GuiProjectInfo::author() const
{
	return mpProjectAuthorLineEdit->text();
}

void GuiProjectInfo::author(const QString& rAuthor)
{
	mpProjectAuthorLineEdit->setText(rAuthor);
}

const QString GuiProjectInfo::description() const
{
	return mpProjectDescriptionTextEdit->text();
}

void GuiProjectInfo::description(const QString& rDescription)
{
	mpProjectDescriptionTextEdit->setText(rDescription);
}

void GuiProjectInfo::focusDefault() const
{
    mpProjectNameLineEdit->setFocus();
}

void GuiProjectInfo::nameChanged(const QString& rName)
{
	if (0 == rName.length())
	{
		emit nameChanged(false);
	}
	else
	{
		emit nameChanged(true);
	}
}
