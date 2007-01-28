/*
 *  $Id: s.TestProject.cpp 1.4 02/09/05 15:03:04+02:00 gbevin@willow.uwyn.office $
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

#include "TestProject.h"

#include <qdom.h>

#include "TestModule.h"

using namespace com_uwyn_qtunit;

TestProject::TestProject(const QString& rName, const QString& rAuthor, const QString& rDescription, const QString& rPath, QPtrList<TestModule>* pModules) :
	mName(rName),
	mAuthor(rAuthor),
	mDescription(rDescription),
	mPath(rPath),
	mpModules(pModules),
	mModified(true)
{
}

TestProject::~TestProject()
{
	delete mpModules;
	mpModules = 0;
}

const QString TestProject::name() const
{
	return mName;
}

void TestProject::name(const QString& rName)
{
	mName = rName;
}

const QString TestProject::author() const
{
	return mAuthor;
}

void TestProject::author(const QString& rAuthor)
{
	mAuthor = rAuthor;
}

const QString TestProject::description() const
{
	return mDescription;
}

void TestProject::description(const QString& rDescription)
{
	mDescription = rDescription;
}

const QString TestProject::path() const
{
	return mPath;
}

void TestProject::path(const QString& rPath)
{
	mPath = rPath;
}

const QPtrList<TestModule>* TestProject::modules() const
{
	return mpModules;
}

void TestProject::addModule(TestModule* pModule)
{
	if (0 == mpModules)
	{
		mpModules = new QPtrList<TestModule>;
		mpModules->setAutoDelete(true);
	}
	mpModules->append(pModule);
}

const bool TestProject::modified() const
{
	return mModified;
}

void TestProject::modified(bool state)
{
	mModified = state;
	emit modificationStateChanged(state);
}

bool TestProject::operator == (const TestProject& rProject) const
{
	if (name() != rProject.name())
	{
		return false;
	}
	else if (author() != rProject.author())
	{
		return false;
	}
	else if (description() != rProject.description())
	{
		return false;
	}
	else if (path() != rProject.path())
	{
		return false;
	}
	else
	{
		const QPtrList<TestModule>* p_modules_current = modules();
		const QPtrList<TestModule>* p_modules_other = rProject.modules();

		if (0 == p_modules_current &&
			0 == p_modules_other)
		{
			return true;
		}
		else if ((0 == p_modules_current && 0 != p_modules_other) ||
				 (0 != p_modules_current && 0 == p_modules_other))
		{
			return false;
		}
		else
		{
			QPtrListIterator<TestModule> modules_current_it(*p_modules_current);
			QPtrListIterator<TestModule> modules_other_it(*p_modules_other);

			TestModule* p_module_current = 0;
			TestModule* p_module_other = 0;
			bool correspondance = false;
			while (0 != (p_module_current = modules_current_it.current()))
			{
				++modules_current_it;

				p_module_other = 0;
				correspondance = false;
				while (0 != (p_module_other = modules_other_it.current()))
				{
					++modules_other_it;

					if (*p_module_current == *p_module_other)
					{
						correspondance = true;
						break;
					}
				}

				if (false == correspondance)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool TestProject::areModulesModified() const
{
	QPtrListIterator<TestModule> modules_it(*mpModules);
	TestModule* p_module = 0;
	while (0 != (p_module = modules_it.current()))
	{
		++modules_it;

		if (true == p_module->isModified())
		{
			return true;
		}
	}

	return false;
}

QString TestProject::constructXml() const
{
	QDomImplementation dom_impl;
	QDomDocumentType document_type = dom_impl.createDocumentType("PROJECT", QString::null, "dtd/project.dtd");
	QDomDocument document(document_type);
	QDomElement project = document.createElement("PROJECT");
	project.setAttribute("NAME", name());
	document.appendChild(project);
	
	QDomElement author = document.createElement("AUTHOR");
	QDomText author_text = document.createTextNode(mAuthor);
	author.appendChild(author_text);
	project.appendChild(author);
	
	QDomElement description = document.createElement("DESCRIPTION");
	QDomText description_text = document.createTextNode(mDescription);
	description.appendChild(description_text);
	project.appendChild(description);
	
	QPtrListIterator<TestModule> modules_it(*mpModules);
	TestModule* p_module = 0;
	while ((p_module = modules_it.current()) != 0)
	{
		++modules_it;

		QDomElement module = document.createElement("MODULE");
		project.appendChild(module);
		QDomElement filepath = document.createElement("FILEPATH");
		QDomText filepath_text = document.createTextNode(p_module->filePath());
		filepath.appendChild(filepath_text);
		module.appendChild(filepath);
		QDomElement sourcepath = document.createElement("SOURCEPATH");
		QDomText sourcepath_text = document.createTextNode(p_module->sourcePath());
		sourcepath.appendChild(sourcepath_text);
		module.appendChild(sourcepath);
	}
	
	return document.toString();
}
