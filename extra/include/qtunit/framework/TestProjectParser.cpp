/*
 *  $Id: s.TestProjectParser.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "TestProjectParser.h"

#include <qstring.h>
 
#include "TestModule.h"
#include "TestProject.h"

using namespace com_uwyn_qtunit;

TestProjectParser::TestProjectParser() :
	mpTestProject(0),
	mModuleFilepath(""),
	mModuleSourcepath("")
{
}

TestProjectParser::~TestProjectParser()
{
	cleanupTestProject();
}

void TestProjectParser::cleanupTestProject()
{
	delete mpTestProject;
	mpTestProject = 0;
}

bool TestProjectParser::startDocument()
{
	cleanupTestProject();
	
	mpTestProject = new TestProject;
	mpTestProject->modified(false);

	return TRUE;
}

bool TestProjectParser::startElement(const QString& rNamespaceURI, const QString& rLocalName, const QString& rQualifiedName, const QXmlAttributes& rAttributes)
{
	Q_UNUSED(rNamespaceURI);
	Q_UNUSED(rLocalName);

	mCharacterData = "";

	if ("PROJECT" == rQualifiedName)
	{
		mpTestProject->name(rAttributes.value("NAME"));
	}

	return TRUE;
}

bool TestProjectParser::characters(const QString& rCharacters)
{
	mCharacterData.append(rCharacters);

	return TRUE;
}

bool TestProjectParser::endElement(const QString& rNamespaceURI, const QString& rLocalName, const QString& rQualifiedName)
{
	Q_UNUSED(rNamespaceURI);
	Q_UNUSED(rLocalName);
	
	if ("AUTHOR" == rQualifiedName)
	{
		mpTestProject->author(mCharacterData);
	}
	else if ("DESCRIPTION" == rQualifiedName)
	{
		mpTestProject->description(mCharacterData);
	}
	else if ("FILEPATH" == rQualifiedName)
	{
		mModuleFilepath = mCharacterData;
	}
	else if ("SOURCEPATH" == rQualifiedName)
	{
		mModuleSourcepath = mCharacterData;
	}
	else if ("MODULE" == rQualifiedName)
	{
		mpTestProject->addModule(new TestModule(mModuleFilepath, mModuleSourcepath));
	}

	return TRUE;
}

TestProject* TestProjectParser::transferTestProject()
{
	TestProject* p_testproject = mpTestProject;

	mpTestProject = 0;

	return p_testproject;
}
