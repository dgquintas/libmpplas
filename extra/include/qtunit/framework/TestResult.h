/*
 *  $Id: s.TestResult.h 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#ifndef QTUNIT_TESTRESULT_H
#define QTUNIT_TESTRESULT_H

#include <qptrlist.h>

#include "Guards.h"
#include "TestDescription.h"

namespace com_uwyn_qtunit
{
	class QtUnitException;
	
	class TestResult
	{
		REFERENCEOBJECT (TestResult)
	
	public:
												TestResult();
		virtual									~TestResult();
					
		virtual void							addSuccess(const TestDescription* const pTestDescription);
		virtual void							addFailure(const TestDescription* const pTestDescription);
		virtual void							addError(const TestDescription* const pTestDescription);
				
		virtual void							reset();
		
		long									countTotal() const;
		long									countSuccesses() const;
		long									countFailures() const;
		long									countErrors() const;
		
		bool									wasSuccessful() const;
	
		const QPtrList<const TestDescription>&	successes() const;
		const QPtrList<const TestDescription>&	failures() const;
		const QPtrList<const TestDescription>&	errors() const;
	
	protected:
		QPtrList<const TestDescription>			mSuccesses;
		QPtrList<const TestDescription>			mFailures;
		QPtrList<const TestDescription>			mErrors;
	
	private:
		void									cleanup();
	};
}

#endif


