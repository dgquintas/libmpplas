/****************************************************************************
** Form implementation generated from reading ui file 'guirunner/GuiProjectPropertiesBase.ui'
**
** Created: Sun Jan 28 14:23:39 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "GuiProjectPropertiesBase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlistbox.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "GuiProjectModules.h"
#include "GuiProjectFile.h"
#include "GuiProjectInfo.h"
#include "GuiProjectPropertiesBase.ui.h"

/*
 *  Constructs a GuiProjectPropertiesBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
GuiProjectPropertiesBase::GuiProjectPropertiesBase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "GuiProjectPropertiesBase" );
    setSizeGripEnabled( TRUE );
    GuiProjectPropertiesBaseLayout = new QGridLayout( this, 1, 1, 11, 6, "GuiProjectPropertiesBaseLayout"); 

    mpPropertiesList = new QListBox( this, "mpPropertiesList" );
    mpPropertiesList->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)7, 0, 0, mpPropertiesList->sizePolicy().hasHeightForWidth() ) );

    GuiProjectPropertiesBaseLayout->addWidget( mpPropertiesList, 0, 0 );

    mpPropertiesTab = new QTabWidget( this, "mpPropertiesTab" );

    mpInfoPage = new QWidget( mpPropertiesTab, "mpInfoPage" );
    mpInfoPageLayout = new QVBoxLayout( mpInfoPage, 11, 6, "mpInfoPageLayout"); 

    mpProjectInfo = new com_uwyn_qtunit::GuiProjectInfo( mpInfoPage, "mpProjectInfo" );
    mpInfoPageLayout->addWidget( mpProjectInfo );
    mpPropertiesTab->insertTab( mpInfoPage, QString("") );

    mpFilePage = new QWidget( mpPropertiesTab, "mpFilePage" );
    mpFilePageLayout = new QVBoxLayout( mpFilePage, 11, 6, "mpFilePageLayout"); 

    mpProjectFile = new com_uwyn_qtunit::GuiProjectFile( mpFilePage, "mpProjectFile" );
    mpFilePageLayout->addWidget( mpProjectFile );
    mpPropertiesTab->insertTab( mpFilePage, QString("") );

    mpModulesPage = new QWidget( mpPropertiesTab, "mpModulesPage" );
    mpModulesPageLayout = new QVBoxLayout( mpModulesPage, 11, 6, "mpModulesPageLayout"); 

    mpProjectModules = new com_uwyn_qtunit::GuiProjectModules( mpModulesPage, "mpProjectModules" );
    mpModulesPageLayout->addWidget( mpProjectModules );
    mpPropertiesTab->insertTab( mpModulesPage, QString("") );

    GuiProjectPropertiesBaseLayout->addWidget( mpPropertiesTab, 0, 1 );

    mpButtonsLayout = new QHBoxLayout( 0, 0, 6, "mpButtonsLayout"); 

    mpHelpButton = new QPushButton( this, "mpHelpButton" );
    mpHelpButton->setAccel( QKeySequence( 276824136 ) );
    mpHelpButton->setAutoDefault( TRUE );
    mpButtonsLayout->addWidget( mpHelpButton );
    mpSpacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    mpButtonsLayout->addItem( mpSpacer );

    mpOkButton = new QPushButton( this, "mpOkButton" );
    mpOkButton->setAccel( QKeySequence( 276824143 ) );
    mpOkButton->setAutoDefault( TRUE );
    mpOkButton->setDefault( TRUE );
    mpButtonsLayout->addWidget( mpOkButton );

    mpCancelButton = new QPushButton( this, "mpCancelButton" );
    mpCancelButton->setAccel( QKeySequence( 276824131 ) );
    mpCancelButton->setAutoDefault( TRUE );
    mpButtonsLayout->addWidget( mpCancelButton );

    GuiProjectPropertiesBaseLayout->addMultiCellLayout( mpButtonsLayout, 1, 1, 0, 1 );
    languageChange();
    resize( QSize(502, 364).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( mpOkButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( mpCancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( mpPropertiesTab, SIGNAL( currentChanged(QWidget*) ), this, SLOT( tabSelected() ) );
    connect( mpPropertiesList, SIGNAL( selectionChanged() ), this, SLOT( itemSelected() ) );
    connect( mpHelpButton, SIGNAL( clicked() ), this, SLOT( help() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
GuiProjectPropertiesBase::~GuiProjectPropertiesBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void GuiProjectPropertiesBase::languageChange()
{
    setCaption( tr( "Project Properties" ) );
    mpPropertiesList->clear();
    mpPropertiesList->insertItem( tr( "Info" ) );
    mpPropertiesList->insertItem( tr( "File" ) );
    mpPropertiesList->insertItem( tr( "Modules" ) );
    mpPropertiesTab->changeTab( mpInfoPage, tr( "&Info" ) );
    mpPropertiesTab->changeTab( mpFilePage, tr( "&File" ) );
    mpPropertiesTab->changeTab( mpModulesPage, tr( "&Modules" ) );
    mpHelpButton->setText( tr( "&Help" ) );
    QWhatsThis::add( mpHelpButton, tr( "Activates the context sensitive help." ) );
    mpOkButton->setText( tr( "&OK" ) );
    QWhatsThis::add( mpOkButton, tr( "Confirms the project properties in this dialog and activates them." ) );
    mpCancelButton->setText( tr( "&Cancel" ) );
    QWhatsThis::add( mpCancelButton, tr( "Discards the eventual changes that have been made in this project dialog and maintain the prior settings." ) );
}

