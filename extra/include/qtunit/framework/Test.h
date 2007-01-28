/*
 *  $Id: s.Test.h 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#ifndef QTUNIT_TEST_H
#define QTUNIT_TEST_H

#include <typeinfo>
#include <iostream>
#include "Guards.h"
#include "TestBase.h"

namespace com_uwyn_qtunit
{
	class TestCase;
	
	template <class Fixture> class Test : public TestBase
	{
		REFERENCEOBJECT (Test)
	
		typedef void (Fixture::*TestMethod)();
	
	public:
						Test(TestCase *pTestCase, const QString& rTestClassname, const QString& rTestMethodname, TestMethod pTestMethod);
		void			run() const;
		
	private:
		TestMethod	mpTestMethod;
	};
	
	template <class Fixture> Test<Fixture>::Test(TestCase* pTestCase, const QString& rTestClassname, const QString& rTestMethodname, TestMethod pTestMethod) :
		TestBase(pTestCase, rTestClassname, rTestMethodname),
		mpTestMethod(pTestMethod)
	{
	}
	
	template <class Fixture> void Test<Fixture>::run() const
	{
		(static_cast<Fixture*>(mpTestCase)->*mpTestMethod)();
	}
}

#endif
