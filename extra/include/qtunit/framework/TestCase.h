/*
 *  $Id: s.TestCase.h 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#ifndef QTUNIT_TESTCASE_H
#define QTUNIT_TESTCASE_H

#include <qptrlist.h>

#include "Guards.h"
#include "Test.h"
#include "TestDescription.h"
#include "TestUnit.h"

class QString;

#define addTest(testclass,testmethod)\
(addTestReal(new com_uwyn_qtunit::Test<testclass>(this, #testclass, #testmethod, &testclass::testmethod), __FILE__));

#define qassertTrue(condition)\
(this->assertTrue((#condition), (condition), NULL, __FILE__, __LINE__))

#define qassertEquals(actual, expected)\
(this->assertEquals(#actual, (actual), #expected, (expected), NULL, __FILE__, __LINE__))

#define qassertEqualsDelta(actual, expected, delta)\
(this->assertEqualsDelta(#actual, (actual), #expected, (expected), (delta), NULL, __FILE__, __LINE__))

#define qassertNotEquals(actual, expected)\
(this->assertNotEquals(#actual, (actual), #expected, (expected), NULL, __FILE__, __LINE__))

#define qassertNotEqualsDelta(actual, expected, delta)\
(this->assertNotEqualsDelta(#actual, (actual), #expected, (expected), (delta), NULL, __FILE__, __LINE__))

#define qassertTrueMsg(condition, message)\
(this->assertTrue((#condition), (condition), (message), __FILE__, __LINE__))

#define qassertEqualsMsg(actual, expected, message)\
(this->assertEquals(#actual, (actual), #expected, (expected), (message), __FILE__, __LINE__))

#define qassertEqualsDeltaMsg(actual, expected, delta, message)\
(this->assertEqualsDelta(#actual, (actual), #expected, (expected), (delta), (message), __FILE__, __LINE__))

#define qassertNotEqualsMsg(actual, expected, message)\
(this->assertNotEquals(#actual, (actual), #expected, (expected), (message), __FILE__, __LINE__))

#define qassertNotEqualsDeltaMsg(actual, expected, delta, message)\
(this->assertNotEqualsDelta(#actual, (actual), #expected, (expected), (delta), (message), __FILE__, __LINE__))

namespace com_uwyn_qtunit
{
	class TestBase;
	
	class TestCase : public TestUnit
	{
		REFERENCEOBJECT (TestCase)
	
		friend class TestRunner;
	
	public:
									TestCase();
		virtual 					~TestCase();
	
		virtual void				setUp();
		virtual void				tearDown();
	
		const QPtrList<TestBase>&	tests() const;
		int							countTests() const;
		
		QString						testclassName() const;
		const QString&				lastFileName() const;
		long						lastLineNumber() const;
		
	protected:
		void						addTestReal(TestBase* pTest, const QString& rFileName = QTUNIT_UNKNOWNFILENAME);
	
		void						assertImpl(const QString& rConditionExpr, bool condition, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		
		void						assertTrue(const QString& rConditionExpr, bool condition, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		
		void						assertEquals(const QString& rActualExpr, const char* pActual, const QString& rExpectedExpr, const char* pExpected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertEquals(const QString& rActualExpr, const QString& rActual, const QString& rExpectedExpr, const char* pExpected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertEquals(const QString& rActualExpr, const char* pActual, const QString& rExpectedExpr, const QString& rExpected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertEquals(const QString& rActualExpr, const QString& rActual, const QString& rExpectedExpr, const QString& rExpected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertEquals(const QString& rActualExpr, const QObject* const pActual, const QString& rExpectedExpr, const QObject* const pExpected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertEquals(const QString& rActualExpr, unsigned long actual, const QString& rExpectedExpr, unsigned long expected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertEquals(const QString& rActualExpr, unsigned int actual, const QString& rExpectedExpr, unsigned int expected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertEquals(const QString& rActualExpr, long actual, const QString& rExpectedExpr, long expected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertEquals(const QString& rActualExpr, int actual, const QString& rExpectedExpr, int expected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertEquals(const QString& rActualExpr, bool actual, const QString& rExpectedExpr, bool expected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertEqualsDelta(const QString& rActualExpr, double actual, const QString& rExpectedExpr, double expected, double delta, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertEqualsDelta(const QString& rActualExpr, float actual, const QString& rExpectedExpr, float expected, float delta, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
					
		void						assertNotEquals(const QString& rActualExpr, const char* rActual, const QString& rExpectedExpr, const char* rExpected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertNotEquals(const QString& rActualExpr, const QString& rActual, const QString& rExpectedExpr, const QString& rExpected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertNotEquals(const QString& rActualExpr, const QObject* const pActual, const QString& rExpectedExpr, const QObject* const pExpected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertNotEquals(const QString& rActualExpr, unsigned long actual, const QString& rExpectedExpr, unsigned long expected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertNotEquals(const QString& rActualExpr, unsigned int actual, const QString& rExpectedExpr, unsigned int expected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertNotEquals(const QString& rActualExpr, long actual, const QString& rExpectedExpr, long expected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertNotEquals(const QString& rActualExpr, int actual, const QString& rExpectedExpr, int expected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertNotEquals(const QString& rActualExpr, bool actual, const QString& rExpectedExpr, bool expected, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertNotEqualsDelta(const QString& rActualExpr, double actual, const QString& rExpectedExpr, double expected, double delta, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
		void						assertNotEqualsDelta(const QString& rActualExpr, float actual, const QString& rExpectedExpr, float expected, float delta, const char* pMessage = NULL, const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER);
					
		QString						notTrueMessage(const QString& rConditionExpr);

		QString						notEqualsMessage(const QString& rActualExpr, const QString& actual, const QString& rExpectedExpr, const QString& expected);
		QString						notEqualsMessage(const QString& rActualExpr, const QObject* const actual, const QString& rExpectedExpr, const QObject* const expected);
		QString						notEqualsMessage(const QString& rActualExpr, unsigned long actual, const QString& rExpectedExpr, unsigned long expected);
		QString						notEqualsMessage(const QString& rActualExpr, unsigned int actual, const QString& rExpectedExpr, unsigned int expected);
		QString						notEqualsMessage(const QString& rActualExpr, long actual, const QString& rExpectedExpr, long expected);
		QString						notEqualsMessage(const QString& rActualExpr, int actual, const QString& rExpectedExpr, int expected);
		QString						notEqualsMessage(const QString& rActualExpr, bool actual, const QString& rExpectedExpr, bool expected);
		QString						notEqualsMessageDelta(const QString& rActualExpr, double actual, const QString& rExpectedExpr, double expected, double delta);
		QString						notEqualsMessageDelta(const QString& rActualExpr, float actual, const QString& rExpectedExpr, float expected, float delta);

		QString						equalsMessage(const QString& rActualExpr, const QString& actual, const QString& rExpectedExpr, const QString& expected);
		QString						equalsMessage(const QString& rActualExpr, const QObject* const actual, const QString& rExpectedExpr, const QObject* const expected);
		QString						equalsMessage(const QString& rActualExpr, unsigned long actual, const QString& rExpectedExpr, unsigned long expected);
		QString						equalsMessage(const QString& rActualExpr, unsigned int actual, const QString& rExpectedExpr, unsigned int expected);
		QString						equalsMessage(const QString& rActualExpr, long actual, const QString& rExpectedExpr, long expected);
		QString						equalsMessage(const QString& rActualExpr, int actual, const QString& rExpectedExpr, int expected);
		QString						equalsMessage(const QString& rActualExpr, bool actual, const QString& rExpectedExpr, bool expected);
		QString						equalsMessageDelta(const QString& rActualExpr, double actual, const QString& rExpectedExpr, double expected, double delta);
		QString						equalsMessageDelta(const QString& rActualExpr, float actual, const QString& rExpectedExpr, float expected, float delta);
		
	private:
		void						lastFileName(const QString& lastFilename);
		
		QPtrList<TestBase>			mTests;
		QString						mLastFileName;
		long						mLastLineNumber;
	};
}

#endif
