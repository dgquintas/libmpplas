/*
 *  $Id: s.TestCase.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "TestCase.h"

#include <cmath>
#include <qstring.h>
#include <stdexcept>
#include <typeinfo>

#include "QtUnitException.h"
#include "TestBase.h"
#include "TestDescription.h"
#include "TestRunner.h"

using namespace com_uwyn_qtunit;

TestCase::TestCase() :
	mTests()
{
}

TestCase::~TestCase()
{
	QPtrListIterator<TestBase> it(mTests);
	while (it.current()) 
	{
		delete it.current();
		 ++it;
	}
}

void TestCase::setUp()
{
}

void TestCase::tearDown()
{
}

QString TestCase::testclassName() const
{
	const std::type_info& rthis_class = typeid(*this);
	
	return QString(rthis_class.name());
}

const QString& TestCase::lastFileName() const
{
	return mLastFileName;
}

long TestCase::lastLineNumber() const
{
	return mLastLineNumber;
}

void TestCase::addTestReal(TestBase* pTest, const QString& rFileName)
{
	lastFileName(rFileName);
	mTests.append(pTest);
}

const QPtrList<TestBase>& TestCase::tests() const
{
	return mTests;
}

int TestCase::countTests() const
{
	return mTests.count();
}

void TestCase::assertImpl(const QString& rConditionExpr, bool condition, const QString& rFileName, long lineNumber)
{ 
	lastFileName(rFileName);
	mLastLineNumber = lineNumber;

	if (false == condition)
	{
		throw QtUnitException(rConditionExpr);
	}
}

void TestCase::assertTrue(const QString& rConditionExpr, bool condition, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notTrueMessage(rConditionExpr), condition, rFileName, lineNumber);
}

void TestCase::assertEquals(const QString& rActualExpr, const char* pActual, const QString& rExpectedExpr, const char* pExpected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notEqualsMessage(rActualExpr, QString(pActual), rExpectedExpr, QString(pExpected)), QString(pActual) == QString(pExpected), rFileName, lineNumber);
}

void TestCase::assertEquals(const QString& rActualExpr, const QString& rActual, const QString& rExpectedExpr, const char* pExpected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notEqualsMessage(rActualExpr, rActual, rExpectedExpr, QString(pExpected)), rActual == QString(pExpected), rFileName, lineNumber);
}

void TestCase::assertEquals(const QString& rActualExpr, const char* pActual, const QString& rExpectedExpr, const QString& rExpected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notEqualsMessage(rActualExpr, QString(pActual), rExpectedExpr, rExpected), QString(pActual) == rExpected, rFileName, lineNumber);
}

void TestCase::assertEquals(const QString& rActualExpr, const QString& rActual, const QString& rExpectedExpr, const QString& rExpected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notEqualsMessage(rActualExpr, rActual, rExpectedExpr, rExpected), rActual == rExpected, rFileName, lineNumber);
}

void TestCase::assertEquals(const QString& rActualExpr, const QObject* const pActual, const QString& rExpectedExpr, const QObject* const pExpected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notEqualsMessage(rActualExpr, pActual, rExpectedExpr, pExpected), pActual == pExpected, rFileName, lineNumber);
}

void TestCase::assertEquals(const QString& rActualExpr, unsigned long actual, const QString& rExpectedExpr, unsigned long expected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notEqualsMessage(rActualExpr, actual, rExpectedExpr, expected), actual == expected, rFileName, lineNumber);
}

void TestCase::assertEquals(const QString& rActualExpr, unsigned int actual, const QString& rExpectedExpr, unsigned int expected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notEqualsMessage(rActualExpr, actual, rExpectedExpr, expected), actual == expected, rFileName, lineNumber);
}

void TestCase::assertEquals(const QString& rActualExpr, long actual, const QString& rExpectedExpr, long expected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notEqualsMessage(rActualExpr, actual, rExpectedExpr, expected), actual == expected, rFileName, lineNumber);
}

void TestCase::assertEquals(const QString& rActualExpr, int actual, const QString& rExpectedExpr, int expected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notEqualsMessage(rActualExpr, actual, rExpectedExpr, expected), actual == expected, rFileName, lineNumber);
}

void TestCase::assertEquals(const QString& rActualExpr, bool actual, const QString& rExpectedExpr, bool expected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notEqualsMessage(rActualExpr, actual, rExpectedExpr, expected), actual == expected, rFileName, lineNumber);
}

void TestCase::assertEqualsDelta(const QString& rActualExpr, double actual, const QString& rExpectedExpr, double expected, double delta, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notEqualsMessageDelta(rActualExpr, actual, rExpectedExpr, expected, delta), fabs(actual - expected) <= delta, rFileName, lineNumber);
}

void TestCase::assertEqualsDelta(const QString& rActualExpr, float actual, const QString& rExpectedExpr, float expected, float delta, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+notEqualsMessageDelta(rActualExpr, actual, rExpectedExpr, expected, delta), fabs(actual - expected) <= delta, rFileName, lineNumber);
}

void TestCase::assertNotEquals(const QString& rActualExpr, const char* rActual, const QString& rExpectedExpr, const char* rExpected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+equalsMessage(rActualExpr, rActual, rExpectedExpr, rExpected), QString(rActual) != QString(rExpected), rFileName, lineNumber);
}

void TestCase::assertNotEquals(const QString& rActualExpr, const QString& rActual, const QString& rExpectedExpr, const QString& rExpected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+equalsMessage(rActualExpr, rActual, rExpectedExpr, rExpected), rActual != rExpected, rFileName, lineNumber);
}

void TestCase::assertNotEquals(const QString& rActualExpr, const QObject* const pActual, const QString& rExpectedExpr, const QObject* const pExpected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+equalsMessage(rActualExpr, pActual, rExpectedExpr, pExpected), pActual != pExpected, rFileName, lineNumber);
}

void TestCase::assertNotEquals(const QString& rActualExpr, unsigned long actual, const QString& rExpectedExpr, unsigned long expected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+equalsMessage(rActualExpr, actual, rExpectedExpr, expected), actual != expected, rFileName, lineNumber);
}

void TestCase::assertNotEquals(const QString& rActualExpr, unsigned int actual, const QString& rExpectedExpr, unsigned int expected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+equalsMessage(rActualExpr, actual, rExpectedExpr, expected), actual != expected, rFileName, lineNumber);
}

void TestCase::assertNotEquals(const QString& rActualExpr, long actual, const QString& rExpectedExpr, long expected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+equalsMessage(rActualExpr, actual, rExpectedExpr, expected), actual != expected, rFileName, lineNumber);
}

void TestCase::assertNotEquals(const QString& rActualExpr, int actual, const QString& rExpectedExpr, int expected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+equalsMessage(rActualExpr, actual, rExpectedExpr, expected), actual != expected, rFileName, lineNumber);
}

void TestCase::assertNotEquals(const QString& rActualExpr, bool actual, const QString& rExpectedExpr, bool expected, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+equalsMessage(rActualExpr, actual, rExpectedExpr, expected), actual != expected, rFileName, lineNumber);
}

void TestCase::assertNotEqualsDelta(const QString& rActualExpr, double actual, const QString& rExpectedExpr, double expected, double delta, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+equalsMessageDelta(rActualExpr, actual, rExpectedExpr, expected, delta), fabs(actual - expected) > delta, rFileName, lineNumber);
}

void TestCase::assertNotEqualsDelta(const QString& rActualExpr, float actual, const QString& rExpectedExpr, float expected, float delta, const char* pMessage, const QString& rFileName, long lineNumber)
{ 
	QString message;

	if (NULL != pMessage)
	{
		message = QString(pMessage)+" : ";
	}
	assertImpl(message+equalsMessageDelta(rActualExpr, actual, rExpectedExpr, expected, delta), fabs(actual - expected) > delta, rFileName, lineNumber);
}

QString TestCase::notTrueMessage(const QString& rConditionExpr)
{
	return QObject::trUtf8("%1 was not true").arg(rConditionExpr);
}

QString TestCase::notEqualsMessage(const QString& rActualExpr, const QString& rActual, const QString& rExpectedExpr, const QString& rExpected)
{ 
	Q_UNUSED(rExpectedExpr);
	return QObject::trUtf8("%1 was %2, expected %3").arg(rActualExpr).arg(rActual).arg(rExpected);
}

QString TestCase::notEqualsMessage(const QString& rActualExpr, const QObject* const pActual, const QString& rExpectedExpr, const QObject* const pExpected)
{ 
	Q_UNUSED(pActual);
	Q_UNUSED(pExpected);
	return QObject::trUtf8("%1 and %2 aren't the same QObject").arg(rActualExpr).arg(rExpectedExpr);
}

QString TestCase::notEqualsMessage(const QString& rActualExpr, unsigned long actual, const QString& rExpectedExpr, unsigned long expected)
{ 
	Q_UNUSED(rExpectedExpr);
	return QObject::trUtf8("%1 was %2, expected %3").arg(rActualExpr).arg(QString::number(actual)).arg(QString::number(expected));
}

QString TestCase::notEqualsMessage(const QString& rActualExpr, unsigned int actual, const QString& rExpectedExpr, unsigned int expected)
{ 
	Q_UNUSED(rExpectedExpr);
	return QObject::trUtf8("%1 was %2, expected %3").arg(rActualExpr).arg(QString::number(actual)).arg(QString::number(expected));
}

QString TestCase::notEqualsMessage(const QString& rActualExpr, long actual, const QString& rExpectedExpr, long expected)
{ 
	Q_UNUSED(rExpectedExpr);
	return QObject::trUtf8("%1 was %2, expected %3").arg(rActualExpr).arg(QString::number(actual)).arg(QString::number(expected));
}

QString TestCase::notEqualsMessage(const QString& rActualExpr, int actual, const QString& rExpectedExpr, int expected)
{ 
	Q_UNUSED(rExpectedExpr);
	return QObject::trUtf8("%1 was %2, expected %3").arg(rActualExpr).arg(QString::number(actual)).arg(QString::number(expected));
}

QString TestCase::notEqualsMessage(const QString& rActualExpr, bool actual, const QString& rExpectedExpr, bool expected)
{ 
	Q_UNUSED(rExpectedExpr);
	QString actual_string;
	QString expected_string;

	if (true == actual)
	{
		actual_string = "true";
	}
	else
	{
		actual_string = "false";
	}
	if (true == expected)
	{
		expected_string = "true";
	}
	else
	{
		expected_string = "false";
	}
	return QObject::trUtf8("%1 was %2, expected %3").arg(rActualExpr).arg(actual_string).arg(expected_string);
}

QString TestCase::notEqualsMessageDelta(const QString& rActualExpr, double actual, const QString& rExpectedExpr, double expected, double delta)
{ 
	Q_UNUSED(rExpectedExpr);
	return QObject::trUtf8("%1 was %2, expected between %3 and %4").arg(rActualExpr).arg(QString::number(actual)).arg(QString::number(expected-delta)).arg(QString::number(expected+delta));
}

QString TestCase::notEqualsMessageDelta(const QString& rActualExpr, float actual, const QString& rExpectedExpr, float expected, float delta)
{ 
	Q_UNUSED(rExpectedExpr);
	return QObject::trUtf8("%1 was %2, expected between %3 and %4").arg(rActualExpr).arg(QString::number(actual)).arg(QString::number(expected-delta)).arg(QString::number(expected+delta));
}

QString TestCase::equalsMessage(const QString& rActualExpr, const QString& rActual, const QString& rExpectedExpr, const QString& rExpected)
{ 
	Q_UNUSED(rExpectedExpr);
	Q_UNUSED(rExpected);
	return QObject::trUtf8("%1 was %2, expected it to be different").arg(rActualExpr).arg(rActual);
}

QString TestCase::equalsMessage(const QString& rActualExpr, const QObject* const pActual, const QString& rExpectedExpr, const QObject* const pExpected)
{ 
	Q_UNUSED(pActual);
	Q_UNUSED(pExpected);
	return QObject::trUtf8("%1 and %2 are the same QObject").arg(rActualExpr).arg(rExpectedExpr);
}

QString TestCase::equalsMessage(const QString& rActualExpr, unsigned long actual, const QString& rExpectedExpr, unsigned long expected)
{ 
	Q_UNUSED(rExpectedExpr);
	Q_UNUSED(expected);
	return QObject::trUtf8("%1 was %2, expected it to be different").arg(rActualExpr).arg(QString::number(actual));
}

QString TestCase::equalsMessage(const QString& rActualExpr, unsigned int actual, const QString& rExpectedExpr, unsigned int expected)
{ 
	Q_UNUSED(rExpectedExpr);
	Q_UNUSED(expected);
	return QObject::trUtf8("%1 was %2, expected it to be different").arg(rActualExpr).arg(QString::number(actual));
}

QString TestCase::equalsMessage(const QString& rActualExpr, long actual, const QString& rExpectedExpr, long expected)
{ 
	Q_UNUSED(rExpectedExpr);
	Q_UNUSED(expected);
	return QObject::trUtf8("%1 was %2, expected it to be different").arg(rActualExpr).arg(QString::number(actual));
}

QString TestCase::equalsMessage(const QString& rActualExpr, int actual, const QString& rExpectedExpr, int expected)
{ 
	Q_UNUSED(rExpectedExpr);
	Q_UNUSED(expected);
	return QObject::trUtf8("%1 was %2, expected it to be different").arg(rActualExpr).arg(QString::number(actual));
}

QString TestCase::equalsMessage(const QString& rActualExpr, bool actual, const QString& rExpectedExpr, bool expected)
{ 
	Q_UNUSED(rExpectedExpr);
	Q_UNUSED(expected);
	QString actual_string;
	QString expected_string;

	if (true == actual)
	{
		actual_string = "true";
	}
	else
	{
		actual_string = "false";
	}
	if (true == expected)
	{
		expected_string = "true";
	}
	else
	{
		expected_string = "false";
	}
	return QObject::trUtf8("%1 was %2, expected it to be different").arg(rActualExpr).arg(actual_string);
}

QString TestCase::equalsMessageDelta(const QString& rActualExpr, double actual, const QString& rExpectedExpr, double expected, double delta)
{ 
	Q_UNUSED(rExpectedExpr);
	return QObject::trUtf8("%1 was %2 which is between %3 and %4, it was expected to be outside").arg(rActualExpr).arg(QString::number(actual)).arg(QString::number(expected-delta)).arg(QString::number(expected+delta));
}

QString TestCase::equalsMessageDelta(const QString& rActualExpr, float actual, const QString& rExpectedExpr, float expected, float delta)
{ 
	Q_UNUSED(rExpectedExpr);
	return QObject::trUtf8("%1 was %2 which is between %3 and %4, it was expected to be outside").arg(rActualExpr).arg(QString::number(actual)).arg(QString::number(expected-delta)).arg(QString::number(expected+delta));
}

void TestCase::lastFileName(const QString& lastFilename)
{
	mLastFileName = lastFilename;
}

