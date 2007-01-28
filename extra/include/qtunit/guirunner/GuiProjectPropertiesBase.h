/****************************************************************************
** Form interface generated from reading ui file 'guirunner/GuiProjectPropertiesBase.ui'
**
** Created: Sun Jan 28 14:23:22 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GUIPROJECTPROPERTIESBASE_H
#define GUIPROJECTPROPERTIESBASE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>
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
class QListBox;
class QListBoxItem;
class QTabWidget;
class QWidget;
class QPushButton;

class GuiProjectPropertiesBase : public QDialog
{
    Q_OBJECT

public:
    GuiProjectPropertiesBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~GuiProjectPropertiesBase();

    QListBox* mpPropertiesList;
    QTabWidget* mpPropertiesTab;
    QWidget* mpInfoPage;
    com_uwyn_qtunit::GuiProjectInfo* mpProjectInfo;
    QWidget* mpFilePage;
    com_uwyn_qtunit::GuiProjectFile* mpProjectFile;
    QWidget* mpModulesPage;
    com_uwyn_qtunit::GuiProjectModules* mpProjectModules;
    QPushButton* mpHelpButton;
    QPushButton* mpOkButton;
    QPushButton* mpCancelButton;

public slots:
    virtual void itemSelected();
    virtual void help();
    virtual void tabSelected();

protected:
    QGridLayout* GuiProjectPropertiesBaseLayout;
    QVBoxLayout* mpInfoPageLayout;
    QVBoxLayout* mpFilePageLayout;
    QVBoxLayout* mpModulesPageLayout;
    QHBoxLayout* mpButtonsLayout;
    QSpacerItem* mpSpacer;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;

};

#endif // GUIPROJECTPROPERTIESBASE_H
