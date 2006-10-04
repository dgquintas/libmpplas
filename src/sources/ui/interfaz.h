/****************************************************************************
** Form interface generated from reading ui file 'interfaz.ui'
**
** Created: Tue May 25 23:02:24 2004
**      by: The User Interface Compiler ($Id: interfaz.h,v 1.1.1.1 2005/12/16 17:44:18 dgquintas Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef INTERFAZ_H
#define INTERFAZ_H

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
class QGroupBox;
class QTextBrowser;
class QLabel;
class QLineEdit;
class QComboBox;

class Interfaz : public QMainWindow
{
    Q_OBJECT

public:
    Interfaz( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~Interfaz();

    QSplitter* splitter4;
    QGroupBox* grupoSalida;
    QTextBrowser* textBrowser1;
    QGroupBox* groupBox3;
    QLabel* txtSumas;
    QLabel* numSumas;
    QLabel* txtSumasA;
    QLabel* numSumasA;
    QLabel* txtRestas;
    QLabel* numRestas;
    QLabel* txtRestasA;
    QLabel* numRestasA;
    QLabel* txtProductos;
    QLabel* numProductos;
    QLabel* txtProdSuma;
    QLabel* numProdSuma;
    QLabel* txtDivisiones;
    QLabel* numDivisiones;
    QLabel* txtPorDos;
    QLabel* numPorDos;
    QLabel* txtEntreDos;
    QLabel* numEntreDos;
    QLabel* txtCCeros;
    QLabel* numCCeros;
    QLabel* txtTiempo;
    QLabel* numTiempo;
    QGroupBox* groupoEntrada;
    QLineEdit* lineEdit1;
    QComboBox* comboBox1;
    QMenuBar *MenuBar;
    QPopupMenu *Archivo;
    QPopupMenu *Ayuda;
    QAction* fileNewAction;
    QAction* fileOpenAction;
    QAction* fileSaveAction;
    QAction* fileExitAction;
    QAction* editUndoAction;
    QAction* editRedoAction;
    QAction* editCutAction;
    QAction* editCopyAction;
    QAction* editPasteAction;
    QAction* editFindAction;
    QAction* helpContentsAction;
    QAction* helpIndexAction;
    QAction* helpAboutAction;
    QAction* Action;
    QAction* menunew_itemAction;

public slots:
    virtual void fileNew();
    virtual void fileOpen();
    virtual void fileSave();
    virtual void fileSaveAs();
    virtual void filePrint();
    virtual void fileExit();
    virtual void editUndo();
    virtual void editRedo();
    virtual void editCut();
    virtual void editCopy();
    virtual void editPaste();
    virtual void editFind();
    virtual void helpIndex();
    virtual void helpContents();
    virtual void helpAbout();

protected:
    QVBoxLayout* InterfazLayout;
    QVBoxLayout* layout33;
    QVBoxLayout* grupoSalidaLayout;
    QVBoxLayout* groupBox3Layout;
    QHBoxLayout* layout2;
    QHBoxLayout* layout3;
    QHBoxLayout* layout4;
    QHBoxLayout* layout5;
    QHBoxLayout* layout6;
    QHBoxLayout* layout7;
    QHBoxLayout* layout8;
    QHBoxLayout* layout9;
    QHBoxLayout* layout10;
    QHBoxLayout* layout27;
    QHBoxLayout* layout11;
    QVBoxLayout* groupoEntradaLayout;
    QVBoxLayout* layout17;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;
    QPixmap image6;
    QPixmap image7;
    QPixmap image8;
    QPixmap image9;

};

#endif // INTERFAZ_H
