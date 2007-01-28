/*
 *  $Id: s.TestResult.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "TestResult.h"

#include "TestDescription.h"

using namespace com_uwyn_qtunit;

TestResult::TestResult() :
	mSuccesses(),
	mFailures(),
	mErrors()
{
}

TestResult::~TestResult()
{
	cleanup();
}

void TestResult::addSuccess(const TestDescription* const pTestDescription)
{
	mSuccesses.append(pTestDescription);
}

void TestResult::addFailure(const TestDescription* const pTestDescription)
{
	mFailures.append(pTestDescription);
}

void TestResult::addError(const TestDescription* const pTestDescription)
{
	mErrors.append(pTestDescription);
}

void TestResult::reset()
{
	cleanup();
	mSuccesses.clear();
	mFailures.clear();
	mErrors.clear();
}

long TestResult::countTotal() const
{
	return countSuccesses()+countFailures()+countErrors();
}

long TestResult::countSuccesses() const
{
	return mSuccesses.count();
}

long TestResult::countFailures() const
{
	return mFailures.count();
}

long TestResult::countErrors() const
{
	return mErrors.count();
}

bool TestResult::wasSuccessful() const
{
	if (countErrors() == 0 &&
	    countFailures() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const QPtrList<const TestDescription>& TestResult::successes() const
{
	return mSuccesses;
}

const QPtrList<const TestDescription>& TestResult::failures() const
{
	return mFailures;
}

const QPtrList<const TestDescription>& TestResult::errors() const
{
	return mErrors;
}

void TestResult::cleanup()
{
	for (QPtrListIterator<const TestDescription> it1(mSuccesses); it1.current(); ++it1)
	{
		delete *it1;
	}
	mSuccesses.clear();
	
	for (QPtrListIterator<const TestDescription> it2(mFailures); it2.current(); ++it2)
	{
		delete *it2;
	}
	mFailures.clear();
	
	for (QPtrListIterator<const TestDescription> it3(mErrors); it3.current(); ++it3)
	{
		delete *it3;
	}
	mErrors.clear();
}

