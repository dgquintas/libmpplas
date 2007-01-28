/*
 *  $Id: s.TestDescription.h 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#ifndef QTUNIT_TESTDESCRIPTION_H
#define QTUNIT_TESTDESCRIPTION_H

#include <qstring.h>

#include "Guards.h"

#define QTUNIT_UNKNOWNTESTNAME		"<unknown>"
#define QTUNIT_UNKNOWNLINENUMBER	(-1)
#define QTUNIT_UNKNOWNFILENAME		"<unknown>"

namespace com_uwyn_qtunit
{
  class TestDescription
  {
    REFERENCEOBJECT (TestDescription)

    public:
      TestDescription(const QString& rFileName = QTUNIT_UNKNOWNFILENAME, long lineNumber = QTUNIT_UNKNOWNLINENUMBER, const QString& rTestName = QTUNIT_UNKNOWNTESTNAME, const float rTime = 0.0f, const QString& rFailedCondition = "", const QString& rSourcePath = "");
      virtual				~TestDescription();

      const QString&		fileName() const;
      void	fileName(const QString& rFileName);
      long	lineNumber() const;
      void	lineNumber(long lineNumber);
      const QString&		testFullName() const;
      void	testFullName(const QString& rTestName);
      const QString&		failedCondition() const;
      void	failedCondition(const QString& rFailedCondition);
      const QString&		sourcePath() const;
      void	sourcePath(const QString& rSourcePath);
      const float       time() const;
      void  time(const float time);
        

    private:
      QString				mFileName;
      long				mLineNumber;
      QString				mTestName;
      QString				mFailedCondition;
      QString				mSourcePath;
      float         mTime;
  };
}

#endif

