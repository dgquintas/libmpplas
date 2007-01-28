/****************************************************************************
** Form implementation generated from reading ui file 'guirunner/GuiProjectWizardBase.ui'
**
** Created: Sun Jan 28 14:23:39 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "GuiProjectWizardBase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "guirunner/GuiProjectModules.h"
#include "guirunner/GuiProjectFile.h"
#include "guirunner/GuiProjectInfo.h"
#include "GuiProjectWizardBase.ui.h"

/*
 *  Constructs a GuiProjectWizardBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The wizard will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal wizard.
 */
GuiProjectWizardBase::GuiProjectWizardBase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QWizard( parent, name, modal, fl )
{
    if ( !name )
	setName( "GuiProjectWizardBase" );

    mpProjectInfoPage = new QWidget( this, "mpProjectInfoPage" );
    mpProjectInfoPageLayout = new QVBoxLayout( mpProjectInfoPage, 11, 6, "mpProjectInfoPageLayout"); 

    mpProjectInfo = new com_uwyn_qtunit::GuiProjectInfo( mpProjectInfoPage, "mpProjectInfo" );
    mpProjectInfoPageLayout->addWidget( mpProjectInfo );
    addPage( mpProjectInfoPage, QString("") );

    mpProjectFilePage = new QWidget( this, "mpProjectFilePage" );
    mpProjectFilePageLayout = new QVBoxLayout( mpProjectFilePage, 11, 6, "mpProjectFilePageLayout"); 

    mpProjectFile = new com_uwyn_qtunit::GuiProjectFile( mpProjectFilePage, "mpProjectFile" );
    mpProjectFilePageLayout->addWidget( mpProjectFile );
    addPage( mpProjectFilePage, QString("") );

    mpProjectModulesPage = new QWidget( this, "mpProjectModulesPage" );
    mpProjectModulesPageLayout = new QVBoxLayout( mpProjectModulesPage, 11, 6, "mpProjectModulesPageLayout"); 

    mpProjectModules = new com_uwyn_qtunit::GuiProjectModules( mpProjectModulesPage, "mpProjectModules" );
    mpProjectModulesPageLayout->addWidget( mpProjectModules );
    addPage( mpProjectModulesPage, QString("") );
    languageChange();
    resize( QSize(393, 292).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( mpProjectModules, SIGNAL( modulecountChanged(int) ), this, SLOT( modulecountChanged(int) ) );
    connect( mpProjectInfo, SIGNAL( nameChanged(bool) ), this, SLOT( nameChanged(bool) ) );
    connect( mpProjectFile, SIGNAL( pathChanged(bool) ), this, SLOT( pathChanged(bool) ) );
    connect( this, SIGNAL( selected(const QString&) ), this, SLOT( pageChanged(const QString&) ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
GuiProjectWizardBase::~GuiProjectWizardBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void GuiProjectWizardBase::languageChange()
{
    setCaption( tr( "Project wizard" ) );
    setTitle( mpProjectInfoPage, tr( "Create new project - Specify project information" ) );
    setTitle( mpProjectFilePage, tr( "Create new project - Specify project file" ) );
    setTitle( mpProjectModulesPage, tr( "Create new project - Add test modules" ) );
}

