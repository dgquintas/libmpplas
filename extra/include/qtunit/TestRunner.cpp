/* TRANSLATOR com_uwyn_qtunit::TestRunner */
/*
 *  $Id: s.TestRunner.cpp 1.5 02/09/17 18:51:08+02:00 gbevin@inspiron.uwyn.office $
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

#include "TestRunner.h"

#include <qdatetime.h>
#include <qobject.h>
#include <qptrlist.h>
#include <qstring.h>
#include <qtextcodec.h>
#include <qvaluevector.h>
#include <utility>

#include <ctime>

#include "QtUnitException.h"
#include "TestBase.h"
#include "TestCase.h"
#include "TestDescription.h"
#include "TestUnit.h"
#include "TestResult.h"

using namespace com_uwyn_qtunit;

TestRunner::TestRunner(TestResult* pResult, int argc, char** argv, bool guiEnabled) :
	QApplication(argc, argv, guiEnabled),
	mTranslator(0),
	mpResult(pResult),
	mTests()
{
	mTranslator.load(QString("qtunit_")+QTextCodec::locale(), "./src/translations");
	installTranslator(&mTranslator);
}

TestRunner::~TestRunner()
{
	delete mpResult;
	mpResult = 0;	
}

void TestRunner::runTest(const TestBase& rTest)
{
  float time = 0.0f;
	try
	{
		rTest.setUp();
		try
		{
      clock_t t1 = clock();
			rTest.run();
      time = ((float)(clock() - t1))/CLOCKS_PER_SEC;
			mpResult->addSuccess(new TestDescription(rTest.testCase().lastFileName(), rTest.testCase().lastLineNumber(), rTest.testFullName(),time));
		}
		catch (QtUnitException& rException)
		{
			mpResult->addFailure(new TestDescription(rTest.testCase().lastFileName(), rTest.testCase().lastLineNumber(), rTest.testFullName(), time, rException.what(), rTest.sourcePath()));
		}
		catch (std::exception& rException)
		{
			mpResult->addError(new TestDescription(rTest.testCase().lastFileName(), 0, rTest.testFullName(), time, rException.what(), rTest.sourcePath()));
		}
		catch (...)
		{
			mpResult->addError(new TestDescription(rTest.testCase().lastFileName(), 0, rTest.testFullName(), time, trUtf8("<unknown>"), rTest.sourcePath()));
		}
	}
	catch (QtUnitException& rException)
	{
		mpResult->addFailure(new TestDescription(rTest.testCase().lastFileName(), rTest.testCase().lastLineNumber(), rTest.testFullName(), time, rException.what(), rTest.sourcePath()));
	}
	catch (std::exception& rException)
	{
		mpResult->addError(new TestDescription(rTest.testCase().lastFileName(), 0, rTest.testFullName(), time, rException.what(), rTest.sourcePath()));
	}
    catch (...)
	{
		mpResult->addError(new TestDescription(rTest.testCase().lastFileName(), 0, rTest.testFullName(),time, trUtf8("setUp() failed"), rTest.sourcePath()));
    }
	
	try
	{
		rTest.tearDown();
	}
	catch (QtUnitException& rException)
	{
		mpResult->addFailure(new TestDescription(rTest.testCase().lastFileName(), rTest.testCase().lastLineNumber(), rTest.testFullName(), time,rException.what(), rTest.sourcePath()));
	}
	catch (std::exception& rException)
	{
		mpResult->addError(new TestDescription(rTest.testCase().lastFileName(), 0, rTest.testFullName(),time, rException.what(), rTest.sourcePath()));
	}
    catch (...)
	{
		mpResult->addError(new TestDescription(rTest.testCase().lastFileName(), 0, rTest.testFullName(), time, trUtf8("tearDown() failed"), rTest.sourcePath()));
    }
}

void TestRunner::add(const TestBase& rTest, const QString& rSourcePath)
{
	rTest.sourcePath(rSourcePath);
	mTests.append(&rTest);

	emit testcountChanged(mTests.count());
}

void TestRunner::add(const TestUnit& rTestUnit, const QString& rSourcePath)
{
	const QPtrList<TestBase>& tests = rTestUnit.tests();
	
	for (QPtrListIterator<TestBase> it(tests); it.current(); ++it)
	{
		(*it)->sourcePath(rSourcePath);
		mTests.append(*it);
	}

	emit testcountChanged(mTests.count());
}

void TestRunner::clear()
{
	mTests.clear();

	emit testcountChanged(0);
}

const QPtrList<TestBase>& TestRunner::tests() const
{
	return mTests;
}

const int TestRunner::countTests() const
{
	return mTests.count();
}

const TestResult& TestRunner::testResult() const
{
	return *mpResult;
}

void TestRunner::resetResult()
{
	mpResult->reset();
}

