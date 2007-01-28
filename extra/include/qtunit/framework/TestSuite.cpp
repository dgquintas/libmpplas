/*
 *  $Id: s.TestSuite.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "TestSuite.h"

#include <stddef.h>

#include "TestBase.h"
#include "TestUnit.h"

using namespace com_uwyn_qtunit;

TestSuite::TestSuite() :
	mpTests(new QPtrList<TestBase>),
	mTestUnits()
{
}

TestSuite::~TestSuite()
{
	delete mpTests;
	mpTests = 0;
}

const QPtrList<TestBase>& TestSuite::tests() const
{
	mpTests->clear();
	
	QPtrListIterator<const TestUnit> it(mTestUnits);
	while (it.current())
	{
		QPtrList<TestBase> tests = it.current()->tests();
		
		QPtrListIterator<TestBase> it2(tests);
		while (it2.current())
		{
			mpTests->append(it2.current());
			
			++it2;
		}
		
		++it;
	}
	
	return *mpTests;
}

int TestSuite::countTests() const
{
	int count = 0;
	
	QPtrListIterator<const TestUnit> it(mTestUnits);
	while (it.current())
	{
		count += it.current()->countTests();
		
		++it;
	}
	
	return count;
}

void TestSuite::addTestUnit(const TestUnit& rTestUnit)
{
	mTestUnits.append(&rTestUnit);
}

const QPtrList<const TestUnit>& TestSuite::testUnits() const
{
	return mTestUnits;
}

