/*
 *  $Id: s.TestModule.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "TestModule.h"

#include <qfileinfo.h>
#include <qlibrary.h>

#include "TestSuite.h"

using namespace com_uwyn_qtunit;

TestModule::TestModule(const QString& rFilePath, const QString& rSourcePath) :
	mFilePath(rFilePath),
	mSourcePath(rSourcePath),
	mpLibrary(0),
	mLastModified(),
	mpTestSuite(0)
{
}

TestModule::~TestModule()
{
	cleanupTestSuite();
	cleanupLibrary();
}

const QString& TestModule::filePath() const
{
	return mFilePath;
}

const QString& TestModule::sourcePath() const
{
	return mSourcePath;
}

bool TestModule::operator == (const TestModule& rModule) const
{
	if (filePath() != rModule.filePath())
	{
		return false;
	}
	else if (sourcePath() != rModule.sourcePath())
	{
		return false;
	}

	return true;
}

bool TestModule::isModified() const
{
	if (mLastModified.isNull())
	{
		return true;
	}
	else
	{
		QFileInfo filepath_info(mFilePath);
		filepath_info.setCaching(false);
		if (filepath_info.lastModified() > mLastModified)
		{
			return true;
		}
	}

	return false;
}

TestSuite* TestModule::testSuite()
{
	QFileInfo filepath_info(mFilePath);
	if (filepath_info.exists())
	{
		filepath_info.setCaching(false);
		mLastModified = filepath_info.lastModified();

		cleanupTestSuite();
		cleanupLibrary();
		
		mpLibrary = new QLibrary(mFilePath);
		mpLibrary->setAutoUnload(FALSE);

		EXP_getTestSuite p_exported_function = (EXP_getTestSuite)mpLibrary->resolve("getTestSuite");
		if (0 != p_exported_function)
		{
			mpTestSuite = p_exported_function();
		}


		return mpTestSuite;
	}
	else
	{
		return 0;
	}
}

void TestModule::cleanupLibrary()
{
	if (0 != mpLibrary)
	{
		mpLibrary->unload();
		delete mpLibrary;
		mpLibrary = 0;
	}
}

void TestModule::cleanupTestSuite()
{
	if (0 != mpTestSuite)
	{
		delete mpTestSuite;
		mpTestSuite = 0;
	}
}

