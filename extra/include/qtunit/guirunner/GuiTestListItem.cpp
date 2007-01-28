/*
 *  $Id: s.GuiTestListItem.cpp 1.3 02/06/11 16:15:41+02:00 gbevin@willow.uwyn.office $
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

#include "GuiTestListItem.h"

#include "GuiMainwindow.h"

using namespace com_uwyn_qtunit;

GuiTestListItem::GuiTestListItem(GuiTestListItem* pParent, TestBase& rTest, GuiTestListItem* after) :
	QListViewItem(pParent, after),
	mrTest(rTest),
	mRunning(false)
{
	setMultiLinesEnabled(true);
}

GuiTestListItem::GuiTestListItem(QListView* pParent, TestBase& rTest, GuiTestListItem* after) :
	QListViewItem(pParent, after),
	mrTest(rTest),
	mRunning(false)
{
	setMultiLinesEnabled(true);
}

GuiTestListItem::~GuiTestListItem()
{
}

const TestBase& GuiTestListItem::test() const
{
	return mrTest;
}

const bool GuiTestListItem::running() const
{
	return mRunning;
}

void GuiTestListItem::running(bool running)
{
	if (true == running)
	{
		QListViewItemIterator it(listView());
		while (it.current()) 
		{
			if (this != it.current())
			{
				static_cast<GuiTestListItem*>(it.current())->running(false);
			}
			++it;
		}
	}

	mRunning = running;
	repaint();
}

int GuiTestListItem::compare(QListViewItem* pOtherItem, int column, bool ascending) const
{
	if (true == static_cast<GuiMainwindow*>(listView()->topLevelWidget())->rConfig().sortTests())
	{
		return QListViewItem::compare(pOtherItem, column, ascending);
	}
	else
	{
		return 0;
	}
}

