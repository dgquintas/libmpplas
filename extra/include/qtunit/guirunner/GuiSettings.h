/*
 *  $Id: s.GuiSettings.h 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#ifndef QTUNIT_GUISETTINGS_H
#define QTUNIT_GUISETTINGS_H

#include <qsettings.h>

#include "Guards.h"

class QColor;
	
namespace com_uwyn_qtunit
{
	class GuiSettings
	{ 
		REFERENCEOBJECT (GuiSettings)
	
	public:
					GuiSettings();
		virtual		~GuiSettings();
	
		bool   		autoRunTests();
		int	   		delay();
		QColor 		errorBackgroundColor();
		QColor 		errorForegroundColor();
		QString		externalViewer();
		QColor 		failureBackgroundColor();
		QColor 		failureForegroundColor();
		bool   		failureTypeIndication();
		bool   		highlightRunningTest();
		bool   		reloadModules();
		bool   		rememberProject();
		QString		rememberedProject();
		bool   		showRunningTest();
		bool   		sortTests();
	
		void   		autoRunTests(bool enabled);
		void   		delay(int delay);
		void   		errorBackgroundColor(const QColor& rColor);
		void   		errorForegroundColor(const QColor& rColor);
		void   		externalViewer(const QString& rViewer);
		void   		failureBackgroundColor(const QColor& rColor);
		void   		failureForegroundColor(const QColor& rColor);
		void   		failureTypeIndication(bool enabled);
		void   		highlightRunningTest(bool enabled);
		void   		reloadModules(bool enabled);
		void   		rememberedProject(const QString& rPath);
		void   		rememberProject(bool enabled);
		void   		showRunningTest(bool enabled);
		void   		sortTests(bool enabled);
	
		static const int	smDelayUnit;
	
	private:                            	
		QSettings				mSettings;
		static const QString	smKeybase;
	};
}

#endif
