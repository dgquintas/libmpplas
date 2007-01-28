/****************************************************************************
** Form implementation generated from reading ui file 'guirunner/GuiProjectFileBase.ui'
**
** Created: Sun Jan 28 14:23:21 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "GuiProjectFileBase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a GuiProjectFileBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
GuiProjectFileBase::GuiProjectFileBase( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "GuiProjectFileBase" );
    GuiProjectFileBaseLayout = new QVBoxLayout( this, 0, 6, "GuiProjectFileBaseLayout"); 

    mpProjectFileLabel = new QLabel( this, "mpProjectFileLabel" );
    GuiProjectFileBaseLayout->addWidget( mpProjectFileLabel );

    mpProjectFileHBox = new QHBoxLayout( 0, 0, 6, "mpProjectFileHBox"); 

    mpProjectFileLineEdit = new QLineEdit( this, "mpProjectFileLineEdit" );
    mpProjectFileHBox->addWidget( mpProjectFileLineEdit );

    mpProjectFilePushButton = new QPushButton( this, "mpProjectFilePushButton" );
    mpProjectFilePushButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, mpProjectFilePushButton->sizePolicy().hasHeightForWidth() ) );
    mpProjectFilePushButton->setMaximumSize( QSize( 80, 32767 ) );
    mpProjectFileHBox->addWidget( mpProjectFilePushButton );
    GuiProjectFileBaseLayout->addLayout( mpProjectFileHBox );

    mpProjectDirLabel = new QLabel( this, "mpProjectDirLabel" );
    GuiProjectFileBaseLayout->addWidget( mpProjectDirLabel );

    mpProjectDirHBox = new QHBoxLayout( 0, 0, 6, "mpProjectDirHBox"); 

    mpProjectDirLineEdit = new QLineEdit( this, "mpProjectDirLineEdit" );
    mpProjectDirHBox->addWidget( mpProjectDirLineEdit );

    mpProjectDirPushButton = new QPushButton( this, "mpProjectDirPushButton" );
    mpProjectDirHBox->addWidget( mpProjectDirPushButton );
    GuiProjectFileBaseLayout->addLayout( mpProjectDirHBox );

    mpFullProjectPathLabel = new QLabel( this, "mpFullProjectPathLabel" );
    GuiProjectFileBaseLayout->addWidget( mpFullProjectPathLabel );

    mpFullProjectPathLineEdit = new QLineEdit( this, "mpFullProjectPathLineEdit" );
    mpFullProjectPathLineEdit->setFocusPolicy( QLineEdit::NoFocus );
    mpFullProjectPathLineEdit->setAcceptDrops( FALSE );
    mpFullProjectPathLineEdit->setFrameShape( QLineEdit::StyledPanel );
    mpFullProjectPathLineEdit->setFrameShadow( QLineEdit::Plain );
    mpFullProjectPathLineEdit->setLineWidth( 1 );
    mpFullProjectPathLineEdit->setReadOnly( TRUE );
    GuiProjectFileBaseLayout->addWidget( mpFullProjectPathLineEdit );
    mpSpacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    GuiProjectFileBaseLayout->addItem( mpSpacer );
    languageChange();
    resize( QSize(397, 174).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( mpProjectFilePushButton, SIGNAL( clicked() ), this, SLOT( selectProjectFile() ) );
    connect( mpProjectDirPushButton, SIGNAL( clicked() ), this, SLOT( selectProjectDir() ) );
    connect( mpProjectFileLineEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( pathChanged() ) );
    connect( mpProjectDirLineEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( pathChanged() ) );

    // buddies
    mpProjectFileLabel->setBuddy( mpProjectFileLineEdit );
    mpProjectDirLabel->setBuddy( mpProjectDirLineEdit );
}

/*
 *  Destroys the object and frees any allocated resources
 */
GuiProjectFileBase::~GuiProjectFileBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void GuiProjectFileBase::languageChange()
{
    setCaption( tr( "GuiProjectFileBase" ) );
    mpProjectFileLabel->setText( tr( "Enter the name of the project &file :" ) );
    QWhatsThis::add( mpProjectFileLineEdit, tr( "The name of the project file." ) );
    mpProjectFilePushButton->setText( tr( "Browse..." ) );
    QWhatsThis::add( mpProjectFilePushButton, tr( "Look for a file whose absolute path will be split into two parts.<br>\n"
"<br>\n"
"The file name will replace the contents of the first text entry field and the absolute path to the containing directory will replace the contents of the second text entry field." ) );
    mpProjectDirLabel->setText( tr( "Select the &directory where the project file will be stored :" ) );
    QWhatsThis::add( mpProjectDirLineEdit, tr( "The directory in which the project file will be stored." ) );
    mpProjectDirPushButton->setText( tr( "Browse..." ) );
    QWhatsThis::add( mpProjectDirPushButton, tr( "Look for a directory whose absolute path will replace the contents of the text field entry." ) );
    mpFullProjectPathLabel->setText( tr( "The complete project file path is :" ) );
    QWhatsThis::add( mpFullProjectPathLineEdit, tr( "The absolute path of the file in which the project properties will be written." ) );
}

void GuiProjectFileBase::pathChanged()
{
    qWarning( "GuiProjectFileBase::pathChanged(): Not implemented yet" );
}

void GuiProjectFileBase::selectProjectDir()
{
    qWarning( "GuiProjectFileBase::selectProjectDir(): Not implemented yet" );
}

void GuiProjectFileBase::selectProjectFile()
{
    qWarning( "GuiProjectFileBase::selectProjectFile(): Not implemented yet" );
}

