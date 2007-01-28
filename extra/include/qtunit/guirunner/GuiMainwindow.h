/*
 *  $Id: s.GuiMainwindow.h 1.5 02/09/05 15:03:05+02:00 gbevin@willow.uwyn.office $
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

#ifndef QTUNIT_GUIMAINWINDOW_H
#define QTUNIT_GUIMAINWINDOW_H

#define QTUNIT_VERSION	"0.9.8"

#include <qdict.h>
#include <qptrlist.h>
#include <qthread.h>

#include "Guards.h"
#include "GuiErrorListToolTip.h"
#include "GuiMainwindowBase.h"
#include "GuiPreferences.h"
#include "GuiProjectProperties.h"
#include "GuiSettings.h"
#include "GuiTestListItem.h"
#include "GuiTestClassListItem.h"

namespace com_uwyn_qtunit
{
	class GuiTestRunner;
	
	class GuiMainwindow : public GuiMainwindowBase
	{ 
		Q_OBJECT
		REFERENCEOBJECT (GuiMainwindow)

	private:
		class RunRegisteredTests : public QThread
		{
		public:
							RunRegisteredTests(GuiMainwindow& rGuiMainwindow);
			virtual			~RunRegisteredTests();

		protected:
			virtual void	run();

		private:

			GuiMainwindow&	mrGuiMainwindow;
		};
		friend class RunRegisteredTests;
	
	public:
											GuiMainwindow(GuiTestRunner* pTestRunner, QWidget* pParent = 0, const char* pName = 0, WFlags flags = WType_TopLevel);
		virtual								~GuiMainwindow();
		
		const TestProject* const			project() const;
		void								project(TestProject&);
	
		void								show();
		GuiSettings&						rConfig();	// TO DO : shouldn't this be refactored or renamed
		void								applyConfig();
					
	protected:                  			
		void								closeEvent(QCloseEvent* pCloseEvent);
		void 								showEvent(QShowEvent*);
//		void 								timerEvent(QTimerEvent*);
					
	public slots:            			
		void								helpAbout();
		void								projectClose();
		void								projectModified(bool state);
		void								projectNew();
		void								projectOpen();
		void								projectProperties();
		void								projectSave();
		void								quit();
		void								refreshTestListview();
		void								runAllTests();
		void								runOneTest(QListViewItem* pClickedItem);
		void								runSelectedTests();
		void								showError(QListViewItem* pClickedItem);
		void								showPreferences();
		void								stop();
		void								testsSelected();
			
	private:                            	
		void								projectOpen(const QString& rPath);
		void								rebuildProjectTests();
		void								resetButtons();
		void								resetStats();
		void								runRegisteredTests();
		void								runTest();
		bool								savedProjectInsurance();
		void								updateStats();
	
		TestProject*						mpProject;
		
		GuiTestRunner*						mpTestRunner;
		QDict<GuiTestClassListItem>			mTestClasses;
		QPtrList<GuiTestListItem>			mTestsToRun;
		RunRegisteredTests					mRunRegisteredTests;
		bool								mStopped;
	
		GuiErrorListToolTip*				mpErrorListToolTip;
		
		GuiSettings							mConfig;
		GuiPreferences						mPreferencesDialog;
		GuiProjectProperties				mProjectPropertiesDialog;
	
		bool								mAutoRunExecuted;
	};
}

#endif
