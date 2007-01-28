/****************************************************************************
** Form implementation generated from reading ui file 'guirunner/GuiPreferencesBase.ui'
**
** Created: Sun Jan 28 14:23:21 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "GuiPreferencesBase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlistbox.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qlineedit.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "GuiPreferencesBase.ui.h"
static const char* const image0_data[] = { 
"12 8 2 1",
". c None",
"# c #000000",
"....#.......",
"....##......",
"....###.....",
"....####....",
"....####....",
"....###.....",
"....##......",
"....#......."};


/*
 *  Constructs a GuiPreferencesBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
GuiPreferencesBase::GuiPreferencesBase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl ),
      image0( (const char **) image0_data )
{
    if ( !name )
	setName( "GuiPreferencesBase" );
    setSizeGripEnabled( TRUE );
    GuiPreferencesBaseLayout = new QVBoxLayout( this, 11, 6, "GuiPreferencesBaseLayout"); 

    mpPreferenceHBox = new QHBoxLayout( 0, 0, 6, "mpPreferenceHBox"); 

    mpPreferencesList = new QListBox( this, "mpPreferencesList" );
    mpPreferencesList->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)7, 0, 0, mpPreferencesList->sizePolicy().hasHeightForWidth() ) );
    mpPreferencesList->setFrameShape( QListBox::StyledPanel );
    mpPreferencesList->setFrameShadow( QListBox::Sunken );
    mpPreferenceHBox->addWidget( mpPreferencesList );

    mpPreferencesTab = new QTabWidget( this, "mpPreferencesTab" );

    mpTestsPage = new QWidget( mpPreferencesTab, "mpTestsPage" );
    mpTestsPageLayout = new QVBoxLayout( mpTestsPage, 11, 6, "mpTestsPageLayout"); 

    mpSortTestsCheckbox = new QCheckBox( mpTestsPage, "mpSortTestsCheckbox" );
    mpTestsPageLayout->addWidget( mpSortTestsCheckbox );

    mpHighlightRunningTestCheckbox = new QCheckBox( mpTestsPage, "mpHighlightRunningTestCheckbox" );
    mpTestsPageLayout->addWidget( mpHighlightRunningTestCheckbox );

    mpShowRunningTestCheckbox = new QCheckBox( mpTestsPage, "mpShowRunningTestCheckbox" );
    mpTestsPageLayout->addWidget( mpShowRunningTestCheckbox );

    mpDelayHBox = new QHBoxLayout( 0, 0, 6, "mpDelayHBox"); 

    mpDelayLabel = new QLabel( mpTestsPage, "mpDelayLabel" );
    mpDelayHBox->addWidget( mpDelayLabel );

    mpDelaySpinBox = new QSpinBox( mpTestsPage, "mpDelaySpinBox" );
    mpDelaySpinBox->setMaxValue( 3000 );
    mpDelayHBox->addWidget( mpDelaySpinBox );
    mpDelaySpacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    mpDelayHBox->addItem( mpDelaySpacer );
    mpTestsPageLayout->addLayout( mpDelayHBox );
    mpTestPageSpacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    mpTestsPageLayout->addItem( mpTestPageSpacer );
    mpPreferencesTab->insertTab( mpTestsPage, QString("") );

    mpFailuresPage = new QWidget( mpPreferencesTab, "mpFailuresPage" );
    mpFailuresPageLayout = new QVBoxLayout( mpFailuresPage, 11, 6, "mpFailuresPageLayout"); 

    mpExternalViewerLabel = new QLabel( mpFailuresPage, "mpExternalViewerLabel" );
    mpFailuresPageLayout->addWidget( mpExternalViewerLabel );

    mpExternalViewerHBox = new QHBoxLayout( 0, 0, 6, "mpExternalViewerHBox"); 

    mpExternalViewerLineEdit = new QLineEdit( mpFailuresPage, "mpExternalViewerLineEdit" );
    mpExternalViewerLineEdit->setMargin( 0 );
    mpExternalViewerHBox->addWidget( mpExternalViewerLineEdit );

    mpExternalViewerFilePushButton = new QPushButton( mpFailuresPage, "mpExternalViewerFilePushButton" );
    mpExternalViewerHBox->addWidget( mpExternalViewerFilePushButton );

    mpExternalViewerArgumentsPushButton = new QPushButton( mpFailuresPage, "mpExternalViewerArgumentsPushButton" );
    mpExternalViewerArgumentsPushButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)5, 0, 0, mpExternalViewerArgumentsPushButton->sizePolicy().hasHeightForWidth() ) );
    mpExternalViewerArgumentsPushButton->setFocusPolicy( QPushButton::NoFocus );
    mpExternalViewerArgumentsPushButton->setPixmap( image0 );
    mpExternalViewerHBox->addWidget( mpExternalViewerArgumentsPushButton );
    mpFailuresPageLayout->addLayout( mpExternalViewerHBox );

    mpFailureTypeIndicationCheckbox = new QCheckBox( mpFailuresPage, "mpFailureTypeIndicationCheckbox" );
    mpFailuresPageLayout->addWidget( mpFailureTypeIndicationCheckbox );

    mpFailureTypeIndicationGroupBox = new QGroupBox( mpFailuresPage, "mpFailureTypeIndicationGroupBox" );
    mpFailureTypeIndicationGroupBox->setEnabled( FALSE );
    mpFailureTypeIndicationGroupBox->setColumnLayout(0, Qt::Vertical );
    mpFailureTypeIndicationGroupBox->layout()->setSpacing( 6 );
    mpFailureTypeIndicationGroupBox->layout()->setMargin( 11 );
    mpFailureTypeIndicationGroupBoxLayout = new QVBoxLayout( mpFailureTypeIndicationGroupBox->layout() );
    mpFailureTypeIndicationGroupBoxLayout->setAlignment( Qt::AlignTop );

    mpFailureForegroundColorLayout = new QHBoxLayout( 0, 0, 6, "mpFailureForegroundColorLayout"); 

    mpFailureForegroundColorButton = new QPushButton( mpFailureTypeIndicationGroupBox, "mpFailureForegroundColorButton" );
    mpFailureForegroundColorButton->setEnabled( FALSE );
    mpFailureForegroundColorButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, mpFailureForegroundColorButton->sizePolicy().hasHeightForWidth() ) );
    mpFailureForegroundColorLayout->addWidget( mpFailureForegroundColorButton );

    mpFailureForegroundColorLabel = new QLabel( mpFailureTypeIndicationGroupBox, "mpFailureForegroundColorLabel" );
    mpFailureForegroundColorLabel->setEnabled( FALSE );
    mpFailureForegroundColorLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)1, 0, 0, mpFailureForegroundColorLabel->sizePolicy().hasHeightForWidth() ) );
    mpFailureForegroundColorLayout->addWidget( mpFailureForegroundColorLabel );
    mpFailureTypeIndicationGroupBoxLayout->addLayout( mpFailureForegroundColorLayout );

    mpFailureBackgroundColorLayout = new QHBoxLayout( 0, 0, 6, "mpFailureBackgroundColorLayout"); 

    mpFailureBackgroundColorButton = new QPushButton( mpFailureTypeIndicationGroupBox, "mpFailureBackgroundColorButton" );
    mpFailureBackgroundColorButton->setEnabled( FALSE );
    mpFailureBackgroundColorButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, mpFailureBackgroundColorButton->sizePolicy().hasHeightForWidth() ) );
    mpFailureBackgroundColorLayout->addWidget( mpFailureBackgroundColorButton );

    mpFailureBackgroundColorLabel = new QLabel( mpFailureTypeIndicationGroupBox, "mpFailureBackgroundColorLabel" );
    mpFailureBackgroundColorLabel->setEnabled( FALSE );
    mpFailureBackgroundColorLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)1, 0, 0, mpFailureBackgroundColorLabel->sizePolicy().hasHeightForWidth() ) );
    mpFailureBackgroundColorLayout->addWidget( mpFailureBackgroundColorLabel );
    mpFailureTypeIndicationGroupBoxLayout->addLayout( mpFailureBackgroundColorLayout );

    mpErrorForegroundColorLayout = new QHBoxLayout( 0, 0, 6, "mpErrorForegroundColorLayout"); 

    mpErrorForegroundColorButton = new QPushButton( mpFailureTypeIndicationGroupBox, "mpErrorForegroundColorButton" );
    mpErrorForegroundColorButton->setEnabled( FALSE );
    mpErrorForegroundColorButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, mpErrorForegroundColorButton->sizePolicy().hasHeightForWidth() ) );
    mpErrorForegroundColorLayout->addWidget( mpErrorForegroundColorButton );

    mpErrorForegroundColorLabel = new QLabel( mpFailureTypeIndicationGroupBox, "mpErrorForegroundColorLabel" );
    mpErrorForegroundColorLabel->setEnabled( FALSE );
    mpErrorForegroundColorLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)1, 0, 0, mpErrorForegroundColorLabel->sizePolicy().hasHeightForWidth() ) );
    mpErrorForegroundColorLayout->addWidget( mpErrorForegroundColorLabel );
    mpFailureTypeIndicationGroupBoxLayout->addLayout( mpErrorForegroundColorLayout );

    mpErrorBackgroundColorLayout = new QHBoxLayout( 0, 0, 6, "mpErrorBackgroundColorLayout"); 

    mpErrorBackgroundColorButton = new QPushButton( mpFailureTypeIndicationGroupBox, "mpErrorBackgroundColorButton" );
    mpErrorBackgroundColorButton->setEnabled( FALSE );
    mpErrorBackgroundColorButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, mpErrorBackgroundColorButton->sizePolicy().hasHeightForWidth() ) );
    mpErrorBackgroundColorLayout->addWidget( mpErrorBackgroundColorButton );

    mpErrorBackgroundColorLabel = new QLabel( mpFailureTypeIndicationGroupBox, "mpErrorBackgroundColorLabel" );
    mpErrorBackgroundColorLabel->setEnabled( FALSE );
    mpErrorBackgroundColorLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)1, 0, 0, mpErrorBackgroundColorLabel->sizePolicy().hasHeightForWidth() ) );
    mpErrorBackgroundColorLayout->addWidget( mpErrorBackgroundColorLabel );
    mpFailureTypeIndicationGroupBoxLayout->addLayout( mpErrorBackgroundColorLayout );
    mpFailuresPageLayout->addWidget( mpFailureTypeIndicationGroupBox );
    mpFailuresPageSpacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    mpFailuresPageLayout->addItem( mpFailuresPageSpacer );
    mpPreferencesTab->insertTab( mpFailuresPage, QString("") );

    mpProjectPage = new QWidget( mpPreferencesTab, "mpProjectPage" );
    mpProjectPageLayout = new QVBoxLayout( mpProjectPage, 11, 6, "mpProjectPageLayout"); 

    mpReloadModulesCheckbox = new QCheckBox( mpProjectPage, "mpReloadModulesCheckbox" );
    mpProjectPageLayout->addWidget( mpReloadModulesCheckbox );

    mpRememberProjectCheckbox = new QCheckBox( mpProjectPage, "mpRememberProjectCheckbox" );
    mpProjectPageLayout->addWidget( mpRememberProjectCheckbox );

    mpAutoRunTestsCheckbox = new QCheckBox( mpProjectPage, "mpAutoRunTestsCheckbox" );
    mpProjectPageLayout->addWidget( mpAutoRunTestsCheckbox );
    mpProjectPageSpacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    mpProjectPageLayout->addItem( mpProjectPageSpacer );
    mpPreferencesTab->insertTab( mpProjectPage, QString("") );
    mpPreferenceHBox->addWidget( mpPreferencesTab );
    GuiPreferencesBaseLayout->addLayout( mpPreferenceHBox );

    mpButtonLayout = new QHBoxLayout( 0, 0, 6, "mpButtonLayout"); 

    mpHelpButton = new QPushButton( this, "mpHelpButton" );
    mpHelpButton->setAccel( QKeySequence( 276824136 ) );
    mpHelpButton->setAutoDefault( TRUE );
    mpButtonLayout->addWidget( mpHelpButton );
    mpSpacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    mpButtonLayout->addItem( mpSpacer );

    mpOkButton = new QPushButton( this, "mpOkButton" );
    mpOkButton->setAutoDefault( TRUE );
    mpOkButton->setDefault( TRUE );
    mpButtonLayout->addWidget( mpOkButton );

    mpCancelButton = new QPushButton( this, "mpCancelButton" );
    mpCancelButton->setAutoDefault( TRUE );
    mpButtonLayout->addWidget( mpCancelButton );
    GuiPreferencesBaseLayout->addLayout( mpButtonLayout );
    languageChange();
    resize( QSize(555, 456).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( mpOkButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( mpCancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( mpPreferencesList, SIGNAL( selectionChanged() ), this, SLOT( itemSelected() ) );
    connect( mpPreferencesTab, SIGNAL( currentChanged(QWidget*) ), this, SLOT( tabSelected() ) );
    connect( mpFailureTypeIndicationCheckbox, SIGNAL( toggled(bool) ), mpFailureTypeIndicationGroupBox, SLOT( setEnabled(bool) ) );
    connect( mpFailureTypeIndicationCheckbox, SIGNAL( toggled(bool) ), mpFailureForegroundColorButton, SLOT( setEnabled(bool) ) );
    connect( mpFailureTypeIndicationCheckbox, SIGNAL( toggled(bool) ), mpFailureForegroundColorLabel, SLOT( setEnabled(bool) ) );
    connect( mpFailureTypeIndicationCheckbox, SIGNAL( toggled(bool) ), mpFailureBackgroundColorButton, SLOT( setEnabled(bool) ) );
    connect( mpFailureTypeIndicationCheckbox, SIGNAL( toggled(bool) ), mpFailureBackgroundColorLabel, SLOT( setEnabled(bool) ) );
    connect( mpFailureTypeIndicationCheckbox, SIGNAL( toggled(bool) ), mpErrorForegroundColorButton, SLOT( setEnabled(bool) ) );
    connect( mpFailureTypeIndicationCheckbox, SIGNAL( toggled(bool) ), mpErrorForegroundColorLabel, SLOT( setEnabled(bool) ) );
    connect( mpFailureTypeIndicationCheckbox, SIGNAL( toggled(bool) ), mpErrorBackgroundColorButton, SLOT( setEnabled(bool) ) );
    connect( mpFailureTypeIndicationCheckbox, SIGNAL( toggled(bool) ), mpErrorBackgroundColorLabel, SLOT( setEnabled(bool) ) );
    connect( mpFailureForegroundColorButton, SIGNAL( clicked() ), this, SLOT( editFailureForegroundColor() ) );
    connect( mpFailureBackgroundColorButton, SIGNAL( clicked() ), this, SLOT( editFailureBackgroundColor() ) );
    connect( mpErrorForegroundColorButton, SIGNAL( clicked() ), this, SLOT( editErrorForegroundColor() ) );
    connect( mpErrorBackgroundColorButton, SIGNAL( clicked() ), this, SLOT( editErrorBackgroundColor() ) );
    connect( mpExternalViewerFilePushButton, SIGNAL( clicked() ), this, SLOT( selectExternalViewer() ) );
    connect( mpExternalViewerArgumentsPushButton, SIGNAL( pressed() ), this, SLOT( showExternalViewerArguments() ) );
    connect( mpHelpButton, SIGNAL( clicked() ), this, SLOT( help() ) );

    // tab order
    setTabOrder( mpPreferencesList, mpHelpButton );
    setTabOrder( mpHelpButton, mpOkButton );
    setTabOrder( mpOkButton, mpCancelButton );
    setTabOrder( mpCancelButton, mpPreferencesTab );
    setTabOrder( mpPreferencesTab, mpSortTestsCheckbox );
    setTabOrder( mpSortTestsCheckbox, mpHighlightRunningTestCheckbox );
    setTabOrder( mpHighlightRunningTestCheckbox, mpShowRunningTestCheckbox );
    setTabOrder( mpShowRunningTestCheckbox, mpDelaySpinBox );
    setTabOrder( mpDelaySpinBox, mpExternalViewerLineEdit );
    setTabOrder( mpExternalViewerLineEdit, mpExternalViewerFilePushButton );
    setTabOrder( mpExternalViewerFilePushButton, mpFailureTypeIndicationCheckbox );
    setTabOrder( mpFailureTypeIndicationCheckbox, mpFailureForegroundColorButton );
    setTabOrder( mpFailureForegroundColorButton, mpFailureBackgroundColorButton );
    setTabOrder( mpFailureBackgroundColorButton, mpErrorForegroundColorButton );
    setTabOrder( mpErrorForegroundColorButton, mpErrorBackgroundColorButton );

    // buddies
    mpDelayLabel->setBuddy( mpDelaySpinBox );
    mpExternalViewerLabel->setBuddy( mpExternalViewerLineEdit );
    mpFailureForegroundColorLabel->setBuddy( mpFailureForegroundColorButton );
    mpFailureBackgroundColorLabel->setBuddy( mpFailureBackgroundColorButton );
    mpErrorForegroundColorLabel->setBuddy( mpErrorForegroundColorButton );
    mpErrorBackgroundColorLabel->setBuddy( mpErrorBackgroundColorButton );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
GuiPreferencesBase::~GuiPreferencesBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void GuiPreferencesBase::languageChange()
{
    setCaption( tr( "QtUnit Preferences" ) );
    mpPreferencesList->clear();
    mpPreferencesList->insertItem( tr( "Tests" ) );
    mpPreferencesList->insertItem( tr( "Failures" ) );
    mpPreferencesList->insertItem( tr( "Project" ) );
    mpSortTestsCheckbox->setText( tr( "&Sort registered tests" ) );
    QWhatsThis::add( mpSortTestsCheckbox, tr( "When checked : the project's displayed tests are automatically sorted ascendingly according to their class name and method name.<br>\n"
"<br>\n"
"When unchecked : the tests are displayed in the order of their definition and module inclusion." ) );
    mpHighlightRunningTestCheckbox->setText( tr( "&Highlight currently running test" ) );
    QWhatsThis::add( mpHighlightRunningTestCheckbox, tr( "When checked : the test that's currently being executed is highlighted with a distinctive background color in the tests listview.<br>\n"
"<br>\n"
"When unchecked : no visual indication is shown about the execution advancement in the tests listview." ) );
    mpShowRunningTestCheckbox->setText( tr( "Always make currently running test &visible" ) );
    QWhatsThis::add( mpShowRunningTestCheckbox, tr( "When checked : the tests listview automatically scrolls to ensure that the entry corresponding to the currently running test is always visible.<br>\n"
"<br>\n"
"When unchecked : the tests listview doesn't track this." ) );
    mpDelayLabel->setText( tr( "&Delay between tests:" ) );
    QWhatsThis::add( mpDelayLabel, tr( "The number of milliseconds that the gui runner should pause between test executions." ) );
    mpDelaySpinBox->setSuffix( tr( "ms" ) );
    QWhatsThis::add( mpDelaySpinBox, tr( "The number of milliseconds that the gui runner should pause between test executions." ) );
    mpPreferencesTab->changeTab( mpTestsPage, tr( "&Tests" ) );
    mpExternalViewerLabel->setText( tr( "Command line to execute external &viewer :" ) );
    QWhatsThis::add( mpExternalViewerLabel, tr( "Shell command that should be executed when a failure or error has been double-clicked.<br>\n"
"<br>\n"
"The browse button allows the retrieval of a file whose absolute path will be inserted.<br>\n"
"<br>\n"
"The arrow displays a popup menu of parameters that will be substituted when the command is actually executed. The selection of such a parameter inserts the corresponding string.<br>\n"
"<br>\n"
"All insertions are made after the current cursor position.<br>\n"
"<br>\n"
"<b>eg.:</b> an external viewer command like :<br>\n"
"<code>/opt/vslick/bin/vs %s%f -#%l</code><br>\n"
"could expand to :<br>\n"
"<code>/opt/vslick/bin/vs /opt/Workspace/qtunit/samples/testmodule/ExampleTextCase.cpp -#24</code>" ) );
    QWhatsThis::add( mpExternalViewerLineEdit, tr( "Shell command that should be executed when a failure or error has been double-clicked.<br>\n"
"<br>\n"
"The browse button allows the retrieval of a file whose absolute path will be inserted.<br>\n"
"<br>\n"
"The arrow displays a popup menu of parameters that will be substituted when the command is actually executed. The selection of such a parameter inserts the corresponding string.<br>\n"
"<br>\n"
"All insertions are made after the current cursor position.<br>\n"
"<br>\n"
"<b>eg.:</b> an external viewer command like :<br>\n"
"<code>/opt/vslick/bin/vs %s%f -#%l</code><br>\n"
"could expand to :<br>\n"
"<code>/opt/vslick/bin/vs /opt/Workspace/qtunit/samples/testmodule/ExampleTextCase.cpp -#24</code>" ) );
    mpExternalViewerFilePushButton->setText( tr( "Browse..." ) );
    QWhatsThis::add( mpExternalViewerFilePushButton, tr( "Look for a file whose absolute path will be inserted after the current cursor position." ) );
    mpExternalViewerArgumentsPushButton->setText( QString::null );
    QWhatsThis::add( mpExternalViewerArgumentsPushButton, tr( "Displays a popup menu of parameters that will be substituted when the command is actually executed. The selection of such a parameter inserts the corresponding string after the current cursor position." ) );
    mpFailureTypeIndicationCheckbox->setText( tr( "Enable failure type color &indications" ) );
    QWhatsThis::add( mpFailureTypeIndicationCheckbox, tr( "When checked : colors are used to indicate the difference between error entries and failure entries in the errors and failures listview.<br>\n"
"<br>\n"
"When unchecked : all entries in the errors and failures listview have an identical appearance." ) );
    mpFailureTypeIndicationGroupBox->setTitle( tr( "Failure type colors" ) );
    QWhatsThis::add( mpFailureTypeIndicationGroupBox, tr( "Specify the colors that should be used for the background and foreground text display of the error and failure entries in the listview." ) );
    mpFailureForegroundColorButton->setText( QString::null );
    mpFailureForegroundColorLabel->setText( tr( "F&ailure foreground color" ) );
    mpFailureBackgroundColorButton->setText( QString::null );
    mpFailureBackgroundColorLabel->setText( tr( "Failure &background color" ) );
    mpErrorForegroundColorButton->setText( QString::null );
    mpErrorForegroundColorLabel->setText( tr( "E&rror foreground color" ) );
    mpErrorBackgroundColorButton->setText( QString::null );
    mpErrorBackgroundColorLabel->setText( tr( "&Error background color" ) );
    mpPreferencesTab->changeTab( mpFailuresPage, tr( "&Failures" ) );
    mpReloadModulesCheckbox->setText( tr( "Reload modules after &modification" ) );
    QWhatsThis::add( mpReloadModulesCheckbox, tr( "When checked : the modification times of all the modules in the current project are checked before running a series of tests. If modules were found to be outdated, the tests in the project are reloaded before the run is started.<br>\n"
"<br>\n"
"When unchecked : the validity of the current tests is never verified." ) );
    mpRememberProjectCheckbox->setText( tr( "&Remember project at exit and open it after start" ) );
    QWhatsThis::add( mpRememberProjectCheckbox, tr( "When checked : the filename of the project that is open when the application is exiting will be stored. When QtUnit is started again, this project will be automatically opened.<br>\n"
"<br>\n"
"When unchecked : the project name will not be saved and no project will be opened automatically." ) );
    mpAutoRunTestsCheckbox->setText( tr( "Automatically run &all tests of remembered project after start" ) );
    QWhatsThis::add( mpAutoRunTestsCheckbox, tr( "When checked : all the tests of a project that has been remembered will be run automatically after QtUnit's launch.<br>\n"
"<br>\n"
"When unchecked : no tests will be automatically run." ) );
    mpPreferencesTab->changeTab( mpProjectPage, tr( "&Project" ) );
    mpHelpButton->setText( tr( "&Help" ) );
    QWhatsThis::add( mpHelpButton, tr( "Activates the context sensitive help." ) );
    mpOkButton->setText( tr( "&OK" ) );
    QWhatsThis::add( mpOkButton, tr( "Confirms the settings in this dialog and activates them." ) );
    mpCancelButton->setText( tr( "&Cancel" ) );
    QWhatsThis::add( mpCancelButton, tr( "Discards the eventual changes that have been made in this dialog and maintain the prior settings." ) );
}

