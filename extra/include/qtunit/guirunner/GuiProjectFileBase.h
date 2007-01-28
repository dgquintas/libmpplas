/****************************************************************************
** Form interface generated from reading ui file 'guirunner/GuiProjectFileBase.ui'
**
** Created: Sun Jan 28 14:23:06 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GUIPROJECTFILEBASE_H
#define GUIPROJECTFILEBASE_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;

class GuiProjectFileBase : public QWidget
{
    Q_OBJECT

public:
    GuiProjectFileBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~GuiProjectFileBase();

    QLabel* mpProjectFileLabel;
    QLineEdit* mpProjectFileLineEdit;
    QPushButton* mpProjectFilePushButton;
    QLabel* mpProjectDirLabel;
    QLineEdit* mpProjectDirLineEdit;
    QPushButton* mpProjectDirPushButton;
    QLabel* mpFullProjectPathLabel;
    QLineEdit* mpFullProjectPathLineEdit;

public slots:
    virtual void pathChanged();
    virtual void selectProjectDir();
    virtual void selectProjectFile();

protected:
    QVBoxLayout* GuiProjectFileBaseLayout;
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpProjectFileHBox;
    QHBoxLayout* mpProjectDirHBox;

protected slots:
    virtual void languageChange();

};

#endif // GUIPROJECTFILEBASE_H
