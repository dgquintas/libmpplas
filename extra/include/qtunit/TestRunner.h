/*
 *  $Id: s.TestRunner.h 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#ifndef QTUNIT_TESTRUNNER_H
#define QTUNIT_TESTRUNNER_H

#include <qapplication.h>
#include <qptrlist.h>
#include <qtranslator.h>

#include "Guards.h"
#include "TestBase.h"
#include "TestResult.h"

namespace com_uwyn_qtunit
{
	class TestCase;
	class TestUnit;
	class TestDescription;
	
	class TestRunner : public QApplication
	{
		Q_OBJECT
		REFERENCEOBJECT (TestRunner)
	
		friend class TestCase;    		
	
	public:
									TestRunner(TestResult* pResult, int argc, char** argv, bool guiEnabled);
		virtual						~TestRunner();
			
		virtual void				run() = 0;
		void						runTest(const TestBase& rTest);
				
		void						add(const TestBase& rTest, const QString& rSourcePath = "");
		void 						add(const TestUnit& rTest, const QString& rSourcePath = "");
		void						clear();
		
		const QPtrList<TestBase>&	tests() const;
		int					countTests() const;
		
		const TestResult&			testResult() const;
	
	signals:
		void						testcountChanged(int);
	
	protected:
		void						resetResult();
			
	private:                		
		QTranslator					mTranslator;
		TestResult*					mpResult;
		QPtrList<TestBase>			mTests;
	};
}

#endif

