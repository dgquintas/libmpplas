/* TRANSLATOR com_uwyn_qtunit::TextTestRunner */
/*
 *  $Id: s.TextTestRunner.cpp 1.3 02/06/11 16:15:41+02:00 gbevin@willow.uwyn.office $
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

#include "TextTestRunner.h"

#include <iostream>
#include <qdom.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qtextstream.h>

#include "TestDescription.h"
#include "TestModule.h"
#include "TestProject.h"
#include "TestProjectParser.h"
#include "TestSuite.h"
#include "TextTestResult.h"

using namespace com_uwyn_qtunit;
using namespace std;

TextTestRunner::TextTestRunner(int argc, char** argv) :
	TestRunner(new TextTestResult(), argc, argv, false),
	mTestDuration(),
	mpProject(0)
{
	if (this->argc() > 1)
	{
		QString project_file(this->argv()[1]);

		if (QString::null != project_file)
		{
			TestProjectParser handler;
			QFileInfo xmlfile_info(project_file);
			QFile xmlfile(xmlfile_info.absFilePath());
			QXmlInputSource source(&xmlfile);
			QXmlSimpleReader reader;
			reader.setContentHandler(&handler);

			if (FALSE == reader.parse(source))
			{
				cout << trUtf8("An error has occured while parsing the project file '%1'.\nProbably it could not be opened.").arg(project_file) << endl;
			}
			else
			{
				mpProject = handler.transferTestProject();

				QPtrListIterator<TestModule> modules_it(*mpProject->modules());
				TestModule* p_module = 0;
				TestSuite* p_testsuite = 0;
				while (0 != (p_module = modules_it.current()))
				{
					++modules_it;
					p_testsuite = p_module->testSuite();
					if (0 != p_testsuite)
					{
						add(*p_testsuite, p_module->sourcePath());
					}
				}
			}
		}
	}
}

TextTestRunner::~TextTestRunner()
{
	delete mpProject;
	mpProject = 0;
}

void TextTestRunner::run()
{
	if (0 == countTests())
	{
		cout << trUtf8("Usage: %1 [projectfile]").arg(this->argv()[0]) << endl;
	}
	else
	{
		printHeader();
		mTestDuration.start();

		for (QPtrListIterator<TestBase> it(tests()); it.current(); ++it)
		{
			runTest(*it.current());
		}

		mTestDuration = QTime().addMSecs(mTestDuration.elapsed());
		printSummary();
	}
}

void TextTestRunner::printHeader()
{
	cerr << constructBox(QObject::trUtf8("Status  Test                                                            Unit")) << endl;
}

void TextTestRunner::printErrors()
{
	if (testResult().countErrors() > 0)
	{
		QString summary;
		QTextOStream stream(&summary);
		stream << constructBox(QObject::trUtf8("Error details")) << endl;
		printDescriptions(stream, testResult().errors());
		
		cerr << summary;
	}
}

void TextTestRunner::printFailures()
{
	if(testResult().countFailures() > 0)
	{
		QString summary;
		QTextOStream stream(&summary);
		stream << constructBox(QObject::trUtf8("Failure details")) << endl;
		printDescriptions(stream, testResult().failures());
		
		cerr << summary;
	}
}

void TextTestRunner::printDescriptions(QTextOStream& rStream, QPtrList<const TestDescription> descriptions)
{
	int counter = 1;
	rStream.setf(QTextStream::left);
	QPtrListIterator<const TestDescription> it(descriptions);
	while (it.current()) 
	{
		rStream << QString::number(counter) << ") " << "void " << it.current()->testFullName() << "() " << QObject::trUtf8("at") << endl
			<< qSetW(QString::number(counter).length()+2) << "" << it.current()->sourcePath() << it.current()->fileName() << ":" << it.current()->lineNumber() << ":"
			<< it.current()->failedCondition() << endl;
		++counter;
		++it;
	}
}

void TextTestRunner::printSummary()
{
	QString status;
	
	printErrors();
	printFailures();

	if (true == testResult().wasSuccessful())
	{
		status = QObject::trUtf8("SUCCESS");
	}
	else
	{
		status = QObject::trUtf8("FAILURES");
	}
	cerr << constructBox(QObject::trUtf8("Status: %1   Time: %2   Tests: %3   Failures: %4   Errors: %5")
						 .arg(status)
						 .arg(mTestDuration.toString())
						 .arg(QString::number(testResult().countTotal()))
						 .arg(QString::number(testResult().countFailures()))
						 .arg(QString::number(testResult().countErrors())));
}

QString TextTestRunner::constructBox(const QString& rMessage)
{
	QString header;
	QTextOStream stream(&header);
	stream.setf(QTextStream::left);
	stream << endl
		<< " ______________________________________________________________________________ " << endl
		<< "|                                                                              |" << endl
		<< "| " << qSetW(76) << rMessage << " |" << endl
		<< "|______________________________________________________________________________|" << endl;

	return header;
}


