/* TRANSLATOR com_uwyn_qtunit::GuiProjectFile */
/*
 *  $Id: s.GuiProjectFile.cpp 1.3 02/06/11 16:15:40+02:00 gbevin@willow.uwyn.office $
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

#include "GuiProjectFile.h"

#include <qfileinfo.h>
#include <qfiledialog.h>
#include <qlineedit.h>

using namespace com_uwyn_qtunit;

GuiProjectFile::GuiProjectFile(QWidget* pParent, const char* pName, WFlags flags) :
	GuiProjectFileBase(pParent, pName, flags)
{
}

GuiProjectFile::~GuiProjectFile()
{
}

const QString GuiProjectFile::path() const
{
	return mpFullProjectPathLineEdit->text();
}

void GuiProjectFile::path(const QString& rPath)
{
	if (rPath.length() > 0)
	{
		QFileInfo path_info(rPath);
		mpProjectDirLineEdit->setText(path_info.dirPath());
		QString filename = path_info.fileName();
		if (false == filename.endsWith(".qpj"))
		{
			filename.append(".qpj");
		}
		mpProjectFileLineEdit->setText(filename);
	}
}

void GuiProjectFile::focusDefault() const
{
    mpProjectFileLineEdit->setFocus();
}

void GuiProjectFile::pathChanged()
{
	QString full_project_path;
	if (0 < mpProjectDirLineEdit->text().length())
	{
		QChar seperator_char(QDir::separator());
		full_project_path.append(mpProjectDirLineEdit->text());
		if (false == full_project_path.endsWith(seperator_char))
		{
			full_project_path.append(seperator_char);
		}
	}
	full_project_path.append(mpProjectFileLineEdit->text());
	mpFullProjectPathLineEdit->setText(full_project_path);

	if (0 == full_project_path.length())
	{
		emit pathChanged(false);
	}
	else
	{
		QFileInfo full_projectpath_info(full_project_path);
		if (mpProjectFileLineEdit->text().length() > 0)
		{
			QFileInfo full_projectdir_info(full_projectpath_info.dirPath());
			if (full_projectdir_info.exists() &&
				full_projectdir_info.isDir() &&
				full_projectdir_info.isWritable())
			{
				emit pathChanged(true);
			}
			else
			{
				emit pathChanged(false);
			}
		}
		else
		{
			emit pathChanged(false);
		}
	}
}

void GuiProjectFile::selectProjectDir()
{
	QString dir = QFileDialog::getExistingDirectory(QString::null, this, QString::null, trUtf8("Select the directory where the project file will be stored"));
	if (dir.length() > 0)
	{
		mpProjectDirLineEdit->setText(dir);
	}
}

void GuiProjectFile::selectProjectFile()
{
	QString save_filename = QFileDialog::getSaveFileName(QString::null, "QUnit project files (*.qpj)", this, QString::null, trUtf8("Select the name of the project file"));
	path(save_filename);
}

