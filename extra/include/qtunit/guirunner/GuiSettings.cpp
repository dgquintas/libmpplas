/*
 *  $Id: s.GuiSettings.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "GuiSettings.h"

#include <qcolor.h>

#include "GuiMainwindow.h"

using namespace com_uwyn_qtunit;

const QString GuiSettings::smKeybase(QString("/QtUnit/1.0/"));
const int GuiSettings::smDelayUnit(100);

GuiSettings::GuiSettings() :
	mSettings()
{
	mSettings.insertSearchPath(QSettings::Windows, "/TheLeaf");
}

GuiSettings::~GuiSettings()
{
}

bool GuiSettings::autoRunTests()
{
	return mSettings.readBoolEntry(smKeybase+"AutoRunTests", false);
}

int GuiSettings::delay()
{
	return mSettings.readNumEntry(smKeybase+"Delay", 0);
}

QColor GuiSettings::errorBackgroundColor()
{
	QColor color(mSettings.readNumEntry(smKeybase+"ErrorBackground/Red", 255),
				 mSettings.readNumEntry(smKeybase+"ErrorBackground/Green", 153),
				 mSettings.readNumEntry(smKeybase+"ErrorBackground/Blue", 153));

	return color;
}

QColor GuiSettings::errorForegroundColor()
{
	QColor color(mSettings.readNumEntry(smKeybase+"ErrorForeground/Red", 0),
				 mSettings.readNumEntry(smKeybase+"ErrorForeground/Green", 0),
				 mSettings.readNumEntry(smKeybase+"ErrorForeground/Blue", 0));

	return color;
}

QString GuiSettings::externalViewer()
{
	return mSettings.readEntry(smKeybase+"ExternalViewer", "");
}

QColor GuiSettings::failureBackgroundColor()
{
	QColor color(mSettings.readNumEntry(smKeybase+"FailureBackground/Red", 255),
				 mSettings.readNumEntry(smKeybase+"FailureBackground/Green", 215),
				 mSettings.readNumEntry(smKeybase+"FailureBackground/Blue", 0));

	return color;
}

QColor GuiSettings::failureForegroundColor()
{
	QColor color(mSettings.readNumEntry(smKeybase+"FailureForeground/Red", 0),
				 mSettings.readNumEntry(smKeybase+"FailureForeground/Green", 0),
				 mSettings.readNumEntry(smKeybase+"FailureForeground/Blue", 0));

	return color;
}

bool GuiSettings::failureTypeIndication()
{
	return mSettings.readBoolEntry(smKeybase+"FailureTypeIndication", true);
}

bool GuiSettings::highlightRunningTest()
{
	return mSettings.readBoolEntry(smKeybase+"HighlightRunningTest", true);
}

bool GuiSettings::reloadModules()
{
	return mSettings.readBoolEntry(smKeybase+"ReloadModules", true);
}

bool GuiSettings::rememberProject()
{
	return mSettings.readBoolEntry(smKeybase+"RememberProject", true);
}

QString GuiSettings::rememberedProject()
{
	return mSettings.readEntry(smKeybase+"RememberedProject", "");
}

bool GuiSettings::showRunningTest()
{
	return mSettings.readBoolEntry(smKeybase+"ShowRunningTest", true);
}

bool GuiSettings::sortTests()
{
	return mSettings.readBoolEntry(smKeybase+"SortTests", false);
}

void GuiSettings::autoRunTests(bool enabled)
{
	mSettings.writeEntry(smKeybase+"AutoRunTests", enabled);
}

void GuiSettings::delay(int delay)
{
	mSettings.writeEntry(smKeybase+"Delay", delay);
}

void GuiSettings::errorBackgroundColor(const QColor& rColor)
{
	mSettings.writeEntry(smKeybase+"ErrorBackground/Red", rColor.red());
	mSettings.writeEntry(smKeybase+"ErrorBackground/Blue", rColor.blue());
	mSettings.writeEntry(smKeybase+"ErrorBackground/Green", rColor.green());
}

void GuiSettings::errorForegroundColor(const QColor& rColor)
{
	mSettings.writeEntry(smKeybase+"ErrorForeground/Red", rColor.red());
	mSettings.writeEntry(smKeybase+"ErrorForeground/Blue", rColor.blue());
	mSettings.writeEntry(smKeybase+"ErrorForeground/Green", rColor.green());
}

void GuiSettings::externalViewer(const QString& rViewer)
{
	mSettings.writeEntry(smKeybase+"ExternalViewer", rViewer);
}

void GuiSettings::failureBackgroundColor(const QColor& rColor)
{
	mSettings.writeEntry(smKeybase+"FailureBackground/Red", rColor.red());
	mSettings.writeEntry(smKeybase+"FailureBackground/Blue", rColor.blue());
	mSettings.writeEntry(smKeybase+"FailureBackground/Green", rColor.green());
}

void GuiSettings::failureForegroundColor(const QColor& rColor)
{
	mSettings.writeEntry(smKeybase+"FailureForeground/Red", rColor.red());
	mSettings.writeEntry(smKeybase+"FailureForeground/Blue", rColor.blue());
	mSettings.writeEntry(smKeybase+"FailureForeground/Green", rColor.green());
}

void GuiSettings::failureTypeIndication(bool enabled)
{
	mSettings.writeEntry(smKeybase+"FailureTypeIndication", enabled);
}

void GuiSettings::highlightRunningTest(bool enabled)
{
	mSettings.writeEntry(smKeybase+"HighlightRunningTest", enabled);
}

void GuiSettings::reloadModules(bool enabled)
{
	mSettings.writeEntry(smKeybase+"ReloadModules", enabled);
}

void GuiSettings::rememberProject(bool enabled)
{
	mSettings.writeEntry(smKeybase+"RememberProject", enabled);
}

void GuiSettings::rememberedProject(const QString& rPath)
{
	mSettings.writeEntry(smKeybase+"RememberedProject", rPath);
}

void GuiSettings::showRunningTest(bool enabled)
{
	mSettings.writeEntry(smKeybase+"ShowRunningTest", enabled);
}

void GuiSettings::sortTests(bool enabled)
{
	mSettings.writeEntry(smKeybase+"SortTests", enabled);
}

