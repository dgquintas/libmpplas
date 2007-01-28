/*
 *  $Id: s.GuiErrorListItem.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "GuiErrorListItem.h"

#include "GuiMainwindow.h"
#include "TestDescription.h"

using namespace com_uwyn_qtunit;

GuiErrorListItem::GuiErrorListItem(QListView* pParent, const TestDescription& rTestDescription, Type type, QListViewItem* after) :
	QListViewItem(pParent, after),
	mrTestDescription(rTestDescription),
	mType(type)
{
}

GuiErrorListItem::~GuiErrorListItem()
{
}

QString GuiErrorListItem::text(int column) const
{
	switch (column)
	{
		case 0:
			switch (mType)
			{
				case TEST_FAILURE:
					return QObject::trUtf8("failure");
				case TEST_ERROR:
					return QObject::trUtf8("error");
			}
			break;
		case 1:
			return mrTestDescription.testFullName();
			break;
		case 2:
			return mrTestDescription.failedCondition();
			break;
		case 3:
			return mrTestDescription.fileName();
			break;
		case 4:
			return QString::number(mrTestDescription.lineNumber());
			break;
	}
	
	return QObject::trUtf8("<unknown>");
}

const TestDescription& GuiErrorListItem::testDescription() const
{
	return mrTestDescription;
}

void GuiErrorListItem::paintCell(QPainter* pPainter, const QColorGroup& rColorGroup, int column, int width, int align)
{
	QColorGroup color_group(rColorGroup);
	
	if(static_cast<GuiMainwindow*>(listView()->topLevelWidget())->rConfig().failureTypeIndication())
	{
		switch (mType)
		{
			case TEST_FAILURE:
				color_group.setColor(QColorGroup::Text, static_cast<GuiMainwindow*>(listView()->topLevelWidget())->rConfig().failureForegroundColor());
				color_group.setColor(QColorGroup::Base, static_cast<GuiMainwindow*>(listView()->topLevelWidget())->rConfig().failureBackgroundColor());
				break;
			case TEST_ERROR:
				color_group.setColor(QColorGroup::Text, static_cast<GuiMainwindow*>(listView()->topLevelWidget())->rConfig().errorForegroundColor());
				color_group.setColor(QColorGroup::Base, static_cast<GuiMainwindow*>(listView()->topLevelWidget())->rConfig().errorBackgroundColor());
				break;
		}
	}
	QListViewItem::paintCell(pPainter, color_group, column, width, align);
}

