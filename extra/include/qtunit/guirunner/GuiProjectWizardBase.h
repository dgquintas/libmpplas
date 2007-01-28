/****************************************************************************
** Form interface generated from reading ui file 'guirunner/GuiProjectWizardBase.ui'
**
** Created: Sun Jan 28 14:23:22 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GUIPROJECTWIZARDBASE_H
#define GUIPROJECTWIZARDBASE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwizard.h>
#include "Namespace.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
namespace com_uwyn_qtunit {
class GuiProjectModules;
}
namespace com_uwyn_qtunit {
class GuiProjectFile;
}
namespace com_uwyn_qtunit {
class GuiProjectInfo;
}
class QWidget;

class GuiProjectWizardBase : public QWizard
{
    Q_OBJECT

public:
    GuiProjectWizardBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~GuiProjectWizardBase();

    QWidget* mpProjectInfoPage;
    com_uwyn_qtunit::GuiProjectInfo* mpProjectInfo;
    QWidget* mpProjectFilePage;
    com_uwyn_qtunit::GuiProjectFile* mpProjectFile;
    QWidget* mpProjectModulesPage;
    com_uwyn_qtunit::GuiProjectModules* mpProjectModules;

public slots:
    virtual void modulecountChanged(int);
    virtual void pathChanged(bool);
    virtual void nameChanged(bool);
    virtual void pageChanged(const QString &);

protected:
    QVBoxLayout* mpProjectInfoPageLayout;
    QVBoxLayout* mpProjectFilePageLayout;
    QVBoxLayout* mpProjectModulesPageLayout;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;

};

#endif // GUIPROJECTWIZARDBASE_H
