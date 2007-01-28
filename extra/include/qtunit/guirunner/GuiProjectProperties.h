/*
 *  $Id: s.GuiProjectProperties.h 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#ifndef QTUNIT_GUIPROJECTPROPERTIES_H
#define QTUNIT_GUIPROJECTPROPERTIES_H

#include "Guards.h"
#include "GuiProjectPropertiesBase.h"

namespace com_uwyn_qtunit
{
	class GuiMainwindow;
	class TestProject;
	
	class GuiProjectProperties : public GuiProjectPropertiesBase
	{ 
		Q_OBJECT
		REFERENCEOBJECT (GuiProjectProperties)
	
	public:
								GuiProjectProperties(GuiMainwindow* pParent, const char* pName = 0, bool modal = FALSE, WFlags flags = 0);
		virtual					~GuiProjectProperties();
	
		void					name(const QString& rName);
		void					author(const QString& rAuthor);
		void					description(const QString& rDescription);
		void					path(const QString& rPath);
		
		TestProject*			project() const;
		void					project(const TestProject& project);
	
	public slots:
		void		help();
		void		itemSelected();
		void		tabSelected();
	};
}

#endif
