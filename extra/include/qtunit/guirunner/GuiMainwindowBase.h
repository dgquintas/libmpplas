/****************************************************************************
** Form interface generated from reading ui file 'guirunner/GuiMainwindowBase.ui'
**
** Created: Sun Jan 28 14:23:06 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GUIMAINWINDOWBASE_H
#define GUIMAINWINDOWBASE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qmainwindow.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QSplitter;
class QListView;
class QListViewItem;
class QGroupBox;
class QProgressBar;
class QLabel;
class QFrame;
class QPushButton;

class GuiMainwindowBase : public QMainWindow
{
    Q_OBJECT

public:
    GuiMainwindowBase( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~GuiMainwindowBase();

    QSplitter* mpSplitter;
    QListView* mpTestsListview;
    QGroupBox* mpProgressGroupBox;
    QProgressBar* mpProgressbar;
    QLabel* mpRunsLabel;
    QLabel* mpRunsStats;
    QLabel* mpErrorsLabel;
    QLabel* mpErrorsStats;
    QLabel* mpFailuresLabel;
    QLabel* mpFailuresStats;
    QGroupBox* mpErrorsGroupbox;
    QListView* mpErrorsListview;
    QFrame* mpHorizLine;
    QPushButton* mpRunButton;
    QPushButton* mpRunselectedButton;
    QPushButton* mpStopButton;
    QPushButton* mpQuitButton;
    QMenuBar *mpMenubar;
    QPopupMenu *mpFileMenu;
    QPopupMenu *mpPopupMenu;
    QPopupMenu *mpHelpMenu;
    QAction* mpHelpContentsAction;
    QAction* mpHelpIndexAction;
    QAction* mpHelpAboutAction;
    QAction* mpFileQuitAction;
    QAction* mpFilePreferencesAction;
    QAction* mpProjectNew;
    QAction* mpProjectOpen;
    QAction* mpProjectClose;
    QAction* mpProjectProperties;
    QAction* mpProjectSave;
    QAction* mpHelpWhatsThis;

public slots:
    virtual void quit();
    virtual void runAllTests();
    virtual void runSelectedTests();
    virtual void stop();
    virtual void showPreferences();
    virtual void testsSelected();
    virtual void helpAbout();
    virtual void showError(QListViewItem *);
    virtual void projectNew();
    virtual void projectClose();
    virtual void projectSave();
    virtual void projectOpen();
    virtual void projectProperties();
    virtual void runOneTest(QListViewItem *);

protected:
    QVBoxLayout* GuiMainwindowBaseLayout;
    QVBoxLayout* mpRunLayout;
    QVBoxLayout* mpProgressGroupBoxLayout;
    QHBoxLayout* mpStatsLayout;
    QHBoxLayout* mpErrorsGroupboxLayout;
    QHBoxLayout* mpMainButtonsLayout;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;

};

#endif // GUIMAINWINDOWBASE_H
