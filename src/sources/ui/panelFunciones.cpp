/****************************************************************************
** Form implementation generated from reading ui file 'panelFunciones.ui'
**
** Created: Sun Apr 25 14:34:02 2004
**      by: The User Interface Compiler ($Id: panelFunciones.cpp,v 1.1.1.1 2005/12/16 17:44:18 dgquintas Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "panelFunciones.h"

#include <qvariant.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a panelFunciones as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
panelFunciones::panelFunciones( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "panelFunciones" );
    panelFuncionesLayout = new QVBoxLayout( this, 11, 6, "panelFuncionesLayout"); 

    groupBox1 = new QGroupBox( this, "groupBox1" );
    groupBox1->setColumnLayout(0, Qt::Vertical );
    groupBox1->layout()->setSpacing( 6 );
    groupBox1->layout()->setMargin( 11 );
    groupBox1Layout = new QGridLayout( groupBox1->layout() );
    groupBox1Layout->setAlignment( Qt::AlignTop );

    pushButton2 = new QPushButton( groupBox1, "pushButton2" );

    groupBox1Layout->addWidget( pushButton2, 0, 1 );

    pushButton1 = new QPushButton( groupBox1, "pushButton1" );

    groupBox1Layout->addWidget( pushButton1, 0, 0 );

    pushButton4 = new QPushButton( groupBox1, "pushButton4" );

    groupBox1Layout->addWidget( pushButton4, 1, 1 );

    pushButton3 = new QPushButton( groupBox1, "pushButton3" );

    groupBox1Layout->addWidget( pushButton3, 1, 0 );

    pushButton5 = new QPushButton( groupBox1, "pushButton5" );

    groupBox1Layout->addWidget( pushButton5, 2, 1 );

    pushButton6 = new QPushButton( groupBox1, "pushButton6" );

    groupBox1Layout->addWidget( pushButton6, 2, 0 );
    panelFuncionesLayout->addWidget( groupBox1 );
    languageChange();
    resize( QSize(276, 146).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
panelFunciones::~panelFunciones()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void panelFunciones::languageChange()
{
    setCaption( tr( "Funciones" ) );
    groupBox1->setTitle( tr( "groupBox1" ) );
    pushButton2->setText( tr( "pushButton2" ) );
    pushButton1->setText( tr( "pushButton1" ) );
    pushButton4->setText( tr( "pushButton4" ) );
    pushButton3->setText( tr( "pushButton3" ) );
    pushButton5->setText( tr( "pushButton5" ) );
    pushButton6->setText( tr( "pushButton6" ) );
}

