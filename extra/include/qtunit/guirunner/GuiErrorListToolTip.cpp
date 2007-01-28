/*
 *  $Id: s.GuiErrorListToolTip.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "GuiErrorListToolTip.h"

#include <iostream>
#include <qheader.h>

#include "GuiErrorListItem.h"
#include "TestDescription.h"

using namespace com_uwyn_qtunit;

GuiErrorListToolTip::GuiErrorListToolTip(QListView* pParent) :
	QToolTip(pParent)
{
}

void GuiErrorListToolTip::maybeTip(const QPoint& rPoint)
{
	QListView* p_parentlistview	= (QListView*)parentWidget();
	int header_height = p_parentlistview->header()->height();
	QPoint correct_point(rPoint.x(), rPoint.y()-header_height);
	GuiErrorListItem* p_itematpoint = (GuiErrorListItem*)p_parentlistview->itemAt(correct_point);
	if (0 != p_itematpoint)
	{
		QRect item_rect(p_parentlistview->itemRect(p_itematpoint));
		item_rect.moveBy(0, header_height);

		const TestDescription* p_testdescription = &(p_itematpoint->testDescription());

		QString tooltip_contents;
		tooltip_contents.sprintf("<b>%s</b><br><i>%s:%ld</i><br><br>%s",
			p_testdescription->testFullName().ascii(),
			p_testdescription->fileName().ascii(),
			p_testdescription->lineNumber(),
			p_testdescription->failedCondition().ascii());
		tip(item_rect, tooltip_contents);
	}
}
