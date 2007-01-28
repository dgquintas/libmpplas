/****************************************************************************
** Form implementation generated from reading ui file 'guirunner/GuiProjectModulesBase.ui'
**
** Created: Sun Jan 28 14:23:21 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "GuiProjectModulesBase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a GuiProjectModulesBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
GuiProjectModulesBase::GuiProjectModulesBase( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "GuiProjectModulesBase" );
    GuiProjectModulesBaseLayout = new QVBoxLayout( this, 0, 6, "GuiProjectModulesBaseLayout"); 

    mpModuleDefinitionFrame = new QFrame( this, "mpModuleDefinitionFrame" );
    mpModuleDefinitionFrame->setFrameShape( QFrame::Box );
    mpModuleDefinitionFrame->setFrameShadow( QFrame::Sunken );
    mpModuleDefinitionFrameLayout = new QVBoxLayout( mpModuleDefinitionFrame, 11, 6, "mpModuleDefinitionFrameLayout"); 

    mpModulePathLabel = new QLabel( mpModuleDefinitionFrame, "mpModulePathLabel" );
    mpModuleDefinitionFrameLayout->addWidget( mpModulePathLabel );

    mpModulePathHBox = new QHBoxLayout( 0, 0, 6, "mpModulePathHBox"); 

    mpModulePathLineEdit = new QLineEdit( mpModuleDefinitionFrame, "mpModulePathLineEdit" );
    mpModulePathHBox->addWidget( mpModulePathLineEdit );

    mpModulePathPushButton = new QPushButton( mpModuleDefinitionFrame, "mpModulePathPushButton" );
    mpModulePathHBox->addWidget( mpModulePathPushButton );
    mpModuleDefinitionFrameLayout->addLayout( mpModulePathHBox );

    mpSourcePathLabel = new QLabel( mpModuleDefinitionFrame, "mpSourcePathLabel" );
    mpModuleDefinitionFrameLayout->addWidget( mpSourcePathLabel );

    mpSourcePathHBox = new QHBoxLayout( 0, 0, 6, "mpSourcePathHBox"); 

    mpSourcePathLineEdit = new QLineEdit( mpModuleDefinitionFrame, "mpSourcePathLineEdit" );
    mpSourcePathHBox->addWidget( mpSourcePathLineEdit );

    mpSourcePathPushButton = new QPushButton( mpModuleDefinitionFrame, "mpSourcePathPushButton" );
    mpSourcePathHBox->addWidget( mpSourcePathPushButton );
    mpModuleDefinitionFrameLayout->addLayout( mpSourcePathHBox );
    GuiProjectModulesBaseLayout->addWidget( mpModuleDefinitionFrame );

    mpModuleButtonsHBox = new QHBoxLayout( 0, 0, 6, "mpModuleButtonsHBox"); 

    mpAddPushButton = new QPushButton( this, "mpAddPushButton" );
    mpAddPushButton->setEnabled( FALSE );
    mpModuleButtonsHBox->addWidget( mpAddPushButton );

    mpModifyPushButton = new QPushButton( this, "mpModifyPushButton" );
    mpModifyPushButton->setEnabled( FALSE );
    mpModuleButtonsHBox->addWidget( mpModifyPushButton );

    mpRemovePushButton = new QPushButton( this, "mpRemovePushButton" );
    mpRemovePushButton->setEnabled( FALSE );
    mpModuleButtonsHBox->addWidget( mpRemovePushButton );
    GuiProjectModulesBaseLayout->addLayout( mpModuleButtonsHBox );

    mpModulesListView = new QListView( this, "mpModulesListView" );
    mpModulesListView->addColumn( tr( "Module path" ) );
    mpModulesListView->header()->setClickEnabled( FALSE, mpModulesListView->header()->count() - 1 );
    mpModulesListView->addColumn( tr( "Source path" ) );
    mpModulesListView->header()->setClickEnabled( FALSE, mpModulesListView->header()->count() - 1 );
    mpModulesListView->setResizePolicy( QListView::AutoOneFit );
    mpModulesListView->setAllColumnsShowFocus( TRUE );
    mpModulesListView->setResizeMode( QListView::AllColumns );
    GuiProjectModulesBaseLayout->addWidget( mpModulesListView );
    languageChange();
    resize( QSize(384, 362).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( mpModulePathLineEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( moduleDefinitionChanged() ) );
    connect( mpSourcePathLineEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( moduleDefinitionChanged() ) );
    connect( mpModulePathPushButton, SIGNAL( clicked() ), this, SLOT( selectModulePath() ) );
    connect( mpSourcePathPushButton, SIGNAL( clicked() ), this, SLOT( selectSourcePath() ) );
    connect( mpAddPushButton, SIGNAL( clicked() ), this, SLOT( addModule() ) );
    connect( mpModifyPushButton, SIGNAL( clicked() ), this, SLOT( modifyModule() ) );
    connect( mpModulesListView, SIGNAL( selectionChanged(QListViewItem*) ), this, SLOT( moduleSelected(QListViewItem*) ) );
    connect( mpRemovePushButton, SIGNAL( clicked() ), this, SLOT( removeModule() ) );

    // buddies
    mpModulePathLabel->setBuddy( mpModulePathLineEdit );
    mpSourcePathLabel->setBuddy( mpSourcePathLineEdit );
}

/*
 *  Destroys the object and frees any allocated resources
 */
GuiProjectModulesBase::~GuiProjectModulesBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void GuiProjectModulesBase::languageChange()
{
    setCaption( tr( "GuiProjectModulesBase" ) );
    mpModulePathLabel->setText( tr( "Select the module &path" ) );
    QWhatsThis::add( mpModulePathLineEdit, tr( "The absolute path of a module file." ) );
    mpModulePathPushButton->setText( tr( "Browse..." ) );
    QWhatsThis::add( mpModulePathPushButton, tr( "Look for the module file whose absolute path will replace the content of text entry field." ) );
    mpSourcePathLabel->setText( tr( "Select the &source path" ) );
    QWhatsThis::add( mpSourcePathLineEdit, tr( "The absolute path of the base directory where the sources of the module reside." ) );
    mpSourcePathPushButton->setText( tr( "Browse..." ) );
    QWhatsThis::add( mpSourcePathPushButton, tr( "Look for the base directory where the sources of this module are stored. The absolute path will replace the content of text entry field." ) );
    mpAddPushButton->setText( tr( "&Add" ) );
    QWhatsThis::add( mpAddPushButton, tr( "Add the above module definition to the list of modules that are part of this project." ) );
    mpModifyPushButton->setText( tr( "&Modify" ) );
    QWhatsThis::add( mpModifyPushButton, tr( "Modify the definition of the module by the new content of the text entries above." ) );
    mpRemovePushButton->setText( tr( "&Remove" ) );
    QWhatsThis::add( mpRemovePushButton, tr( "Remove the selected module definition from the project." ) );
    mpModulesListView->header()->setLabel( 0, tr( "Module path" ) );
    mpModulesListView->header()->setLabel( 1, tr( "Source path" ) );
    QWhatsThis::add( mpModulesListView, tr( "The modules that are part of the project." ) );
}

void GuiProjectModulesBase::addModule()
{
    qWarning( "GuiProjectModulesBase::addModule(): Not implemented yet" );
}

void GuiProjectModulesBase::modifyModule()
{
    qWarning( "GuiProjectModulesBase::modifyModule(): Not implemented yet" );
}

void GuiProjectModulesBase::moduleDefinitionChanged()
{
    qWarning( "GuiProjectModulesBase::moduleDefinitionChanged(): Not implemented yet" );
}

void GuiProjectModulesBase::moduleSelected(QListViewItem*)
{
    qWarning( "GuiProjectModulesBase::moduleSelected(QListViewItem*): Not implemented yet" );
}

void GuiProjectModulesBase::removeModule()
{
    qWarning( "GuiProjectModulesBase::removeModule(): Not implemented yet" );
}

void GuiProjectModulesBase::selectModulePath()
{
    qWarning( "GuiProjectModulesBase::selectModulePath(): Not implemented yet" );
}

void GuiProjectModulesBase::selectSourcePath()
{
    qWarning( "GuiProjectModulesBase::selectSourcePath(): Not implemented yet" );
}

