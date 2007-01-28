/****************************************************************************
** Form implementation generated from reading ui file 'guirunner/GuiProjectInfoBase.ui'
**
** Created: Sun Jan 28 14:23:21 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "GuiProjectInfoBase.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtextbrowser.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a GuiProjectInfoBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
GuiProjectInfoBase::GuiProjectInfoBase( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "GuiProjectInfoBase" );
    GuiProjectInfoBaseLayout = new QVBoxLayout( this, 0, 6, "GuiProjectInfoBaseLayout"); 

    mpProjectNameLabel = new QLabel( this, "mpProjectNameLabel" );
    GuiProjectInfoBaseLayout->addWidget( mpProjectNameLabel );

    mpProjectNameLineEdit = new QLineEdit( this, "mpProjectNameLineEdit" );
    GuiProjectInfoBaseLayout->addWidget( mpProjectNameLineEdit );

    mpProjectAuthorLabel = new QLabel( this, "mpProjectAuthorLabel" );
    GuiProjectInfoBaseLayout->addWidget( mpProjectAuthorLabel );

    mpProjectAuthorLineEdit = new QLineEdit( this, "mpProjectAuthorLineEdit" );
    GuiProjectInfoBaseLayout->addWidget( mpProjectAuthorLineEdit );

    mpProjectDescriptionLabel = new QLabel( this, "mpProjectDescriptionLabel" );
    GuiProjectInfoBaseLayout->addWidget( mpProjectDescriptionLabel );

    mpProjectDescriptionTextEdit = new QTextBrowser( this, "mpProjectDescriptionTextEdit" );
    mpProjectDescriptionTextEdit->setTextFormat( QTextBrowser::PlainText );
    mpProjectDescriptionTextEdit->setReadOnly( FALSE );
    GuiProjectInfoBaseLayout->addWidget( mpProjectDescriptionTextEdit );
    languageChange();
    resize( QSize(253, 250).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( mpProjectNameLineEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( nameChanged(const QString&) ) );

    // buddies
    mpProjectNameLabel->setBuddy( mpProjectNameLineEdit );
    mpProjectAuthorLabel->setBuddy( mpProjectAuthorLineEdit );
    mpProjectDescriptionLabel->setBuddy( mpProjectDescriptionTextEdit );
}

/*
 *  Destroys the object and frees any allocated resources
 */
GuiProjectInfoBase::~GuiProjectInfoBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void GuiProjectInfoBase::languageChange()
{
    setCaption( tr( "GuiProjectInfoBase" ) );
    mpProjectNameLabel->setText( tr( "Enter the &name of the project :" ) );
    QWhatsThis::add( mpProjectNameLineEdit, tr( "The name that will be used to identify this project." ) );
    mpProjectAuthorLabel->setText( tr( "Enter the &author of the project :" ) );
    QWhatsThis::add( mpProjectAuthorLineEdit, tr( "The developer that is resposible for this project." ) );
    mpProjectDescriptionLabel->setText( tr( "Enter a &description about the project :" ) );
    QWhatsThis::add( mpProjectDescriptionTextEdit, tr( "A description of the project." ) );
}

void GuiProjectInfoBase::nameChanged(const QString&)
{
    qWarning( "GuiProjectInfoBase::nameChanged(const QString&): Not implemented yet" );
}

