/*
 *  $Id: s.TestDescription.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "TestDescription.h"

using namespace com_uwyn_qtunit;

TestDescription::TestDescription(const QString& rFileName, 
    long lineNumber, 
    const QString& rTestName, 
    const float rTime,
    const QString& rFailedCondition, 
    const QString& rSourcePath ) :
	mFileName(rFileName),
	mLineNumber(lineNumber),
	mTestName(rTestName),
	mFailedCondition(rFailedCondition),
	mSourcePath(rSourcePath),
  mTime(rTime)
{
}

TestDescription::~TestDescription()
{
}

const QString& TestDescription::fileName() const
{
	return mFileName;
}

void TestDescription::fileName(const QString& rFileName)
{
	mFileName = rFileName;
}

long TestDescription::lineNumber() const
{
	return mLineNumber;
}

void TestDescription::lineNumber(long lineNumber)
{
	mLineNumber = lineNumber;
}

const QString& TestDescription::testFullName() const
{
	return mTestName;
}

void TestDescription::testFullName(const QString& rTestName)
{
	mTestName = rTestName;
}

const QString& TestDescription::failedCondition() const
{
	return mFailedCondition;
}

void TestDescription::failedCondition(const QString& rFailedCondition)
{
	mFailedCondition = rFailedCondition;
}

const QString& TestDescription::sourcePath() const
{
	return mSourcePath; 
}

void TestDescription::sourcePath(const QString& rSourcePath)
{
	mSourcePath = rSourcePath;
}

const float TestDescription::time() const
{
  return mTime;
}

void TestDescription::time(const float rTime){
  mTime = rTime;
}


