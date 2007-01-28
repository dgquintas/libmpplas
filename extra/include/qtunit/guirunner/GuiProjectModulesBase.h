/****************************************************************************
** Form interface generated from reading ui file 'guirunner/GuiProjectModulesBase.ui'
**
** Created: Sun Jan 28 14:23:06 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GUIPROJECTMODULESBASE_H
#define GUIPROJECTMODULESBASE_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QListView;
class QListViewItem;

class GuiProjectModulesBase : public QWidget
{
    Q_OBJECT

public:
    GuiProjectModulesBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~GuiProjectModulesBase();

    QFrame* mpModuleDefinitionFrame;
    QLabel* mpModulePathLabel;
    QLineEdit* mpModulePathLineEdit;
    QPushButton* mpModulePathPushButton;
    QLabel* mpSourcePathLabel;
    QLineEdit* mpSourcePathLineEdit;
    QPushButton* mpSourcePathPushButton;
    QPushButton* mpAddPushButton;
    QPushButton* mpModifyPushButton;
    QPushButton* mpRemovePushButton;
    QListView* mpModulesListView;

protected:
    QVBoxLayout* GuiProjectModulesBaseLayout;
    QVBoxLayout* mpModuleDefinitionFrameLayout;
    QHBoxLayout* mpModulePathHBox;
    QHBoxLayout* mpSourcePathHBox;
    QHBoxLayout* mpModuleButtonsHBox;

protected slots:
    virtual void languageChange();

    virtual void addModule();
    virtual void modifyModule();
    virtual void moduleDefinitionChanged();
    virtual void moduleSelected(QListViewItem*);
    virtual void removeModule();
    virtual void selectModulePath();
    virtual void selectSourcePath();


};

#endif // GUIPROJECTMODULESBASE_H
