/****************************************************************************
** Form interface generated from reading ui file 'panelFunciones.ui'
**
** Created: Sun Apr 25 14:33:39 2004
**      by: The User Interface Compiler ($Id: panelFunciones.h,v 1.1.1.1 2005/12/16 17:44:18 dgquintas Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef PANELFUNCIONES_H
#define PANELFUNCIONES_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QGroupBox;
class QPushButton;

class panelFunciones : public QWidget
{
    Q_OBJECT

public:
    panelFunciones( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~panelFunciones();

    QGroupBox* groupBox1;
    QPushButton* pushButton2;
    QPushButton* pushButton1;
    QPushButton* pushButton4;
    QPushButton* pushButton3;
    QPushButton* pushButton5;
    QPushButton* pushButton6;

protected:
    QVBoxLayout* panelFuncionesLayout;
    QGridLayout* groupBox1Layout;

protected slots:
    virtual void languageChange();

};

#endif // PANELFUNCIONES_H
