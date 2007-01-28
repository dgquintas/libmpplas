/*
 *  $Id: s.TestModule.h 1.4 02/07/01 11:28:22+02:00 gbevin@oak.uwyn.office $
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

#ifndef QTUNIT_TESTMODULE_H
#define QTUNIT_TESTMODULE_H

#include <qdatetime.h>
#include <qstring.h>

#include "Guards.h"

class QLibrary;

#ifndef Q_EXTERN_C
#ifdef __cplusplus
#ifdef Q_WS_WIN
#define Q_EXTERN_C    extern "C" _declspec(dllexport)
#else
#define Q_EXTERN_C    extern "C"
#endif
#else
#define Q_EXTERN_C    extern
#endif
#endif

#define createTestModule(testSuite)\
Q_EXTERN_C com_uwyn_qtunit::TestSuite* getTestSuite()\
{\
	return new testSuite;\
}
#endif

namespace com_uwyn_qtunit
{
	class TestSuite;
	
	class TestModule
	{ 
		REFERENCEOBJECT (TestModule)
	
	public:
						TestModule(const QString& rFilePath, const QString& rSourcePath);
		virtual			~TestModule();
	
		const QString&	filePath() const;
		const QString&	sourcePath() const;
		bool			isModified() const;
		TestSuite*		testSuite();
	
		bool			operator == (const TestModule& rModule) const;
	
	private:
		void			cleanupLibrary();
		void			cleanupTestSuite();
	
		QString			mFilePath;
		QString			mSourcePath;
		QLibrary*		mpLibrary;
		QDateTime		mLastModified;
		TestSuite*		mpTestSuite;
	};

	typedef TestSuite* (*EXP_getTestSuite)();
}

