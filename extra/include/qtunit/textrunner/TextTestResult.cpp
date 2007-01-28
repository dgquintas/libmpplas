/*
 *  $Id: s.TextTestResult.cpp 1.3 02/06/11 16:15:41+02:00 gbevin@willow.uwyn.office $
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

#include "TextTestResult.h"

#include <qobject.h>
#include <qstring.h>
#include <qtextstream.h>
#include <iostream>

#include "TestDescription.h"

using namespace com_uwyn_qtunit;
using namespace std;

TextTestResult::TextTestResult()
{
}

TextTestResult::~TextTestResult()
{
}

void TextTestResult::addSuccess(const TestDescription* const pTestDescription)
{
	TestResult::addSuccess(pTestDescription);
	
	QString output;
	formatTest(QObject::trUtf8("ok"), output, pTestDescription);
	cerr << output;
}

void TextTestResult::addFailure(const TestDescription* const pTestDescription)
{
	TestResult::addFailure(pTestDescription);
	
	QString output;
	formatTest(QObject::trUtf8("failed"), output, pTestDescription);
	cerr << output;
}

void TextTestResult::addError(const TestDescription* const pTestDescription)
{
	TestResult::addError(pTestDescription);
	
	QString output;
	formatTest(QObject::trUtf8("error"), output, pTestDescription);
	cerr << output;
}

void TextTestResult::formatTest(const QString& rStatus, QString& rOutput, const TestDescription* const pTestDescription)
{
	QTextOStream stream(&rOutput);
	stream.setf(QTextStream::left);
	stream << "  " << qSetW(8) << rStatus << qSetW(25) << pTestDescription->testFullName();
	if (pTestDescription->testFullName().length() >= 25 || pTestDescription->fileName().length() >= 43)
	{
		stream << endl << qSetW(78);
	}
	else
	{
		stream << qSetW(43);
	}
	stream.unsetf(QTextStream::left);
	stream << pTestDescription->fileName() << endl;
}

