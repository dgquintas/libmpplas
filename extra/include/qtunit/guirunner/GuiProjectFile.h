/*
 *  $Id: s.GuiProjectFile.h 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#ifndef QTUNIT_GUIPROJECTFILE_H
#define QTUNIT_GUIPROJECTFILE_H

#include "Guards.h"
#include "GuiProjectFileBase.h"

namespace com_uwyn_qtunit
{
	class GuiProjectFile : public GuiProjectFileBase
	{ 
		Q_OBJECT
		REFERENCEOBJECT (GuiProjectFile)
	
	public:
						GuiProjectFile(QWidget* pParent, const char* pName = 0, WFlags flags = 0);
		virtual			~GuiProjectFile();
				
		const QString	path() const;
		void			path(const QString& rPath);
	
		void			focusDefault() const;
	
	protected slots:
		void	pathChanged();
		void	selectProjectDir();
		void	selectProjectFile();
	
	signals:
		void	pathChanged(bool valid);
	};
}

#endif
