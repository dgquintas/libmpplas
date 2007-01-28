/****************************************************************************
** Form interface generated from reading ui file 'guirunner/GuiPreferencesBase.ui'
**
** Created: Sun Jan 28 14:23:06 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GUIPREFERENCESBASE_H
#define GUIPREFERENCESBASE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QListBox;
class QListBoxItem;
class QTabWidget;
class QWidget;
class QCheckBox;
class QLabel;
class QSpinBox;
class QLineEdit;
class QPushButton;
class QGroupBox;

class GuiPreferencesBase : public QDialog
{
    Q_OBJECT

public:
    GuiPreferencesBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~GuiPreferencesBase();

    QListBox* mpPreferencesList;
    QTabWidget* mpPreferencesTab;
    QWidget* mpTestsPage;
    QCheckBox* mpSortTestsCheckbox;
    QCheckBox* mpHighlightRunningTestCheckbox;
    QCheckBox* mpShowRunningTestCheckbox;
    QLabel* mpDelayLabel;
    QSpinBox* mpDelaySpinBox;
    QWidget* mpFailuresPage;
    QLabel* mpExternalViewerLabel;
    QLineEdit* mpExternalViewerLineEdit;
    QPushButton* mpExternalViewerFilePushButton;
    QPushButton* mpExternalViewerArgumentsPushButton;
    QCheckBox* mpFailureTypeIndicationCheckbox;
    QGroupBox* mpFailureTypeIndicationGroupBox;
    QPushButton* mpFailureForegroundColorButton;
    QLabel* mpFailureForegroundColorLabel;
    QPushButton* mpFailureBackgroundColorButton;
    QLabel* mpFailureBackgroundColorLabel;
    QPushButton* mpErrorForegroundColorButton;
    QLabel* mpErrorForegroundColorLabel;
    QPushButton* mpErrorBackgroundColorButton;
    QLabel* mpErrorBackgroundColorLabel;
    QWidget* mpProjectPage;
    QCheckBox* mpReloadModulesCheckbox;
    QCheckBox* mpRememberProjectCheckbox;
    QCheckBox* mpAutoRunTestsCheckbox;
    QPushButton* mpHelpButton;
    QPushButton* mpOkButton;
    QPushButton* mpCancelButton;

public slots:
    virtual void init();
    virtual void help();
    virtual void editErrorBackgroundColor();
    virtual void editErrorForegroundColor();
    virtual void editFailureBackgroundColor();
    virtual void editFailureForegroundColor();
    virtual void hideExternalViewerArguments();
    virtual void itemSelected();
    virtual void tabSelected();
    virtual void selectExternalViewer();
    virtual void showExternalViewerArguments();

protected:
    QVBoxLayout* GuiPreferencesBaseLayout;
    QHBoxLayout* mpPreferenceHBox;
    QVBoxLayout* mpTestsPageLayout;
    QSpacerItem* mpTestPageSpacer;
    QHBoxLayout* mpDelayHBox;
    QSpacerItem* mpDelaySpacer;
    QVBoxLayout* mpFailuresPageLayout;
    QSpacerItem* mpFailuresPageSpacer;
    QHBoxLayout* mpExternalViewerHBox;
    QVBoxLayout* mpFailureTypeIndicationGroupBoxLayout;
    QHBoxLayout* mpFailureForegroundColorLayout;
    QHBoxLayout* mpFailureBackgroundColorLayout;
    QHBoxLayout* mpErrorForegroundColorLayout;
    QHBoxLayout* mpErrorBackgroundColorLayout;
    QVBoxLayout* mpProjectPageLayout;
    QSpacerItem* mpProjectPageSpacer;
    QHBoxLayout* mpButtonLayout;
    QSpacerItem* mpSpacer;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // GUIPREFERENCESBASE_H
