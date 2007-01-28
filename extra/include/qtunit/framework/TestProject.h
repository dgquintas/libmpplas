/*
 *  $Id: s.TestProject.h 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#ifndef QTUNIT_TESTPROJECT_H
#define QTUNIT_TESTPROJECT_H

#include <qobject.h>
#include <qptrlist.h>
#include <qstring.h>

#include "Guards.h"

namespace com_uwyn_qtunit
{
	class TestModule;
	class TestProjectParser;
	
	class TestProject : public QObject
	{ 
		Q_OBJECT
		REFERENCEOBJECT (TestProject)
	
	public:
									TestProject(const QString& rName = "", const QString& rAuthor = "", const QString& rDescription = "", const QString& rPath = "", QPtrList<TestModule>* pModules = 0);
		virtual						~TestProject();
	
		const QString				name() const;
		void						name(const QString& rName);
		const QString				author() const;
		void						author(const QString& rAuthor);
		const QString				description() const;
		void						description(const QString& rDescription);
		const QString				path() const;
		void						path(const QString& rPath);
		const QPtrList<TestModule>*	modules() const;
		void						addModule(TestModule* pModule);
		const bool					modified() const;
		void						modified(bool state);
		bool						areModulesModified() const;
		QString 					constructXml() const;
	
		bool						operator == (const TestProject& rProject) const;
	
	signals:
		void						modificationStateChanged(bool);
	
	private:
	
		QString						mName;
		QString						mAuthor;
		QString						mDescription;
		QString						mPath;
		QPtrList<TestModule>*		mpModules;
		bool						mModified;
		char			SPACE_HOLDER[102400];
	};
}

#endif
