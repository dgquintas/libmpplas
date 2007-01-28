/****************************************************************************
** Form interface generated from reading ui file 'guirunner/GuiProjectInfoBase.ui'
**
** Created: Sun Jan 28 14:23:06 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GUIPROJECTINFOBASE_H
#define GUIPROJECTINFOBASE_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QTextBrowser;

class GuiProjectInfoBase : public QWidget
{
    Q_OBJECT

public:
    GuiProjectInfoBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~GuiProjectInfoBase();

    QLabel* mpProjectNameLabel;
    QLineEdit* mpProjectNameLineEdit;
    QLabel* mpProjectAuthorLabel;
    QLineEdit* mpProjectAuthorLineEdit;
    QLabel* mpProjectDescriptionLabel;
    QTextBrowser* mpProjectDescriptionTextEdit;

public slots:
    virtual void nameChanged(const QString &);

protected:
    QVBoxLayout* GuiProjectInfoBaseLayout;

protected slots:
    virtual void languageChange();

};

#endif // GUIPROJECTINFOBASE_H
