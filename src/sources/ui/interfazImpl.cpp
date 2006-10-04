#include "interfazImpl.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qtextbrowser.h>
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qlabel.h>
#include <qstatusbar.h>
#include <qfiledialog.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include <sstream>
#include <qtoolbox.h>
#include <qbuttongroup.h>
#include <qtooltip.h>



/* 
 *  Constructs a interfazImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
interfazImpl::interfazImpl( QWidget* parent,  const char* name, WFlags fl )
    : Interfaz( parent, name, fl )
{
  calc = new Calculadora();
  perf = new numth::Perfil();
 
  barraEstado = this->statusBar();
  barraEstado->message( "Listo" );

  arch = new QFile();
    QDockWindow *dw = new QDockWindow( QDockWindow::InDock, this );
    dw->setResizeEnabled( TRUE );
    dw->setVerticalStretchable( TRUE );
    addDockWindow( dw, DockLeft );
    setDockEnabled( dw, DockTop, FALSE );
    setDockEnabled( dw, DockBottom, FALSE );
    dw->setCloseMode( QDockWindow::Never );
    
    QToolBox* toolBox = new QToolBox( dw );
    dw->setWidget( toolBox );

    dw->setCaption( tr( "Funciones" ) );
 
    QButtonGroup* grupo;
    QPushButton* bot1, *bot2, *bot3, *bot4, *bot5, *bot6, *bot7;
    
    grupo = new QButtonGroup(1, Horizontal, toolBox);
    bot1 = new QPushButton("randomRapido",grupo);
    bot2 = new QPushButton("ponerSemilla",grupo);
    bot3 = new QPushButton("randomSeguro",grupo);
    bot4 = new QPushButton("ponerCalidad",grupo);
    grupo->insert(bot1, 11);
    grupo->insert(bot2, 12);
    grupo->insert(bot3, 13);
    grupo->insert(bot4, 14);
    QToolTip::add( bot1, "Generar número pseudo-aleatorio");
    QToolTip::add( bot2, "Establecer manualmente la semilla del generador pseudo-aleatorio");
    QToolTip::add( bot3, "Generar número pseudo-aleatorio criptográficamente seguro");
    QToolTip::add( bot4, "Establecer la calidad del generador criptograficamente seguro\n"
                         "Se mide en bits, e inicialmente es 256" );
    connect( grupo, SIGNAL( clicked(int) ),
             this, SLOT( ponerTextoFuncion( int ) ) );
    toolBox->addItem((QWidget*)grupo, "Random");

    grupo = new QButtonGroup(1, Horizontal, toolBox);
    bot1 = new QPushButton("esPrimo",grupo);
    bot2 = new QPushButton("ponerIteraciones",grupo);
    bot3 = new QPushButton("esPrimoMersenne",grupo);
    bot4 = new QPushButton("leerPrimo",grupo);
    bot6 = new QPushButton("siguientePrimo",grupo);
    bot5 = new QPushButton("leerPrimoFuerte",grupo);
    grupo->insert(bot1, 21);
    grupo->insert(bot2, 22);
    grupo->insert(bot3, 23);
    grupo->insert(bot4, 24);
    grupo->insert(bot6, 26);
    grupo->insert(bot5, 25);
    QToolTip::add( bot1, "Prueba probabilistica de primalidad.");
    QToolTip::add( bot2, "Establecer manualmente las iteraciones del test de composición.");
    QToolTip::add( bot3, "Prueba determinística de primalidad de números\n"
                         "de la forma 2^p - 1");
    QToolTip::add( bot4, "Obtener un primo con un altísimo grado de probabilidad.");
    QToolTip::add( bot6, "Obtener el primer primo mayor que el número dado" );
    QToolTip::add( bot5, "Obtener un primo fuerte con un altísimo grado de probabilidad.");
    connect( grupo, SIGNAL( clicked(int) ),
             this, SLOT( ponerTextoFuncion( int ) ) );
    toolBox->addItem((QWidget*)grupo, "Primos");

    grupo = new QButtonGroup(1, Horizontal, toolBox);
    bot1 = new QPushButton("precisionReales",grupo);
    bot2 = new QPushButton("precisionSalidaReales",grupo);
    bot3 = new QPushButton("precisionSalidaEnteros",grupo);
    grupo->insert(bot1, 31);
    grupo->insert(bot2, 32);
    grupo->insert(bot3, 33);
    QToolTip::add( bot1, "Establece el número de bits que se utilizarán\n"
                         "en la representación interna del real.\n"
                         "Inicialmente se utilizan 300 bits.");
    QToolTip::add( bot2, "Establece el número de cifras en base 10 que se mostrarán\n"
                         "para los reales.");
    QToolTip::add( bot3, "Establece el número de cifras en base 10 que se mostrarán\n"
                         "para los enteros.");
    connect( grupo, SIGNAL( clicked(int) ),
             this, SLOT( ponerTextoFuncion( int ) ) );
    toolBox->addItem((QWidget*)grupo, "Precisión");

    grupo = new QButtonGroup(1, Horizontal, toolBox);
    bot1 = new QPushButton("simboloKronecker",grupo);
    bot2 = new QPushButton("simboloJacobi",grupo);
    bot3 = new QPushButton("simboloLegendre",grupo);
    bot4 = new QPushButton("gcd",grupo);
    bot5 = new QPushButton("lcm",grupo);
    bot6 = new QPushButton("crt",grupo);
    bot7 = new QPushButton("factoriza",grupo);
    grupo->insert(bot1, 41);
    grupo->insert(bot2, 42);
    grupo->insert(bot3, 43);
    grupo->insert(bot4, 44);
    grupo->insert(bot5, 45);
    grupo->insert(bot6, 46);
    grupo->insert(bot7, 47);
    QToolTip::add( bot1, "Cálculo del simbolo de Kronecker");
    QToolTip::add( bot2, "Cálculo del simbolo de Jacobi");
    QToolTip::add( bot3, "Cálculo del simbolo de Legendre");
    QToolTip::add( bot4, "Cálculo del Máximo Común Divisor ");
    QToolTip::add( bot5, "Cálculo del Mínimo Común Múltiplo");
    QToolTip::add( bot6, "Cálculo del Teorema del Resto Chino");
    QToolTip::add( bot7, "Factorización de enteros");
    connect( grupo, SIGNAL( clicked(int) ),
             this, SLOT( ponerTextoFuncion( int ) ) );
    toolBox->addItem((QWidget*)grupo, "Teoría de números");
   
    grupo = new QButtonGroup(1, Horizontal, toolBox);
    bot1 = new QPushButton("factorial",grupo);
    bot2 = new QPushButton("potenciaModular",grupo);
    bot3 = new QPushButton("raizCuadradaEntera",grupo);
    grupo->insert(bot1, 51);
    grupo->insert(bot2, 52);
    grupo->insert(bot3, 53);
    QToolTip::add( bot1, "Factorial de un entero simple\n"
                         "(menor o igual que la base de trabajo, normalmente 2^32)");
    QToolTip::add( bot2, "Potencia modular de un entero");
    QToolTip::add( bot3, "Parte entera de la raiz cuadrada de un entero");
    connect( grupo, SIGNAL( clicked(int) ),
             this, SLOT( ponerTextoFuncion( int ) ) );
    toolBox->addItem((QWidget*)grupo, "Miscelanea");
  
    
    estadisticas = true;
  try{
    perf->finalizar();
  }
  catch(Errores::Excepcion &ex)
  {
    estadisticas = false;
    groupBox3->setDisabled(true);
  }


  QObject::connect( lineEdit1, SIGNAL(returnPressed()), 
                    this, SLOT(procesarEntrada() ));

  QObject::connect( comboBox1, SIGNAL(activated(const QString&)),
                    lineEdit1, SLOT(setText(const QString&) ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
interfazImpl::~interfazImpl()
{
  delete calc;
  delete perf;
}

/*
 * public slot
 */
void interfazImpl::fileNew()
{
    qWarning( "interfazImpl::fileNew() not yet implemented!" );
}

/*
 * public slot
 */
void interfazImpl::fileOpen()
{
  QString archivo = QFileDialog::getOpenFileName(".", "*.nth");

  if(!archivo.isEmpty()){
    arch->setName(archivo);
    this->procesarArchivo();

    arch->close();
  }

  return;
}

/*
 * public slot
 */
void interfazImpl::fileSave()
{
  QString archivo = QFileDialog::getSaveFileName(".", "*.txt");
 
  if(!archivo.isEmpty()){
    arch->setName(archivo);

    if( !arch->open( IO_WriteOnly ) ){
      QMessageBox::critical(0, "Guardar registro", 
          "No ha podido guardarse el archivo",
          "Ok");
      return;
    }
    QTextStream stream( arch );
    QString datos = textBrowser1->text();
    stream << datos;

    arch->close();
  }
  return;
  
}


/*
 * public slot
 */
void interfazImpl::helpContents()
{
    qWarning( "interfazImpl::helpContents() not yet implemented!" );
}

/*
 * public slot
 */
void interfazImpl::helpAbout()
{
  QMessageBox::about(this, "Acerca de Calculadora LibNumTh...", 
                           "Programa demostración de la librería NumTh\n\n"
                           "Proyecto Fin de Carrera E.U.I.T.I.G.\n\n\n"
                           "David García Quintas. DNI: 53542483\n\n"
                           "Compilada el " __DATE__);

}

void interfazImpl::ponerTextoFuncion(int id)
{
  switch( id ){
    //Random
    case 11:
      lineEdit1->setText("randomRapido(numBits);");
      break;
    case 12:
      lineEdit1->setText("ponerSemilla(semilla);");
      break;
    case 13:
      lineEdit1->setText("randomSeguro(numBits);");
      break;
    case 14:
      lineEdit1->setText("ponerCalidad(numBits);");
      break;
    //Primos
    case 21:
      lineEdit1->setText("esPrimo(entero);");
      break;
    case 22:
      lineEdit1->setText("ponerIteraciones(num);");
      break;
    case 23:
      lineEdit1->setText("esPrimoMersenne(expoP);");
      break;
    case 24:
      lineEdit1->setText("leerPrimo(numBits);");
      break;
    case 25:
      lineEdit1->setText("leerPrimoFuerte(numBits);");
      break;
    case 26:
      lineEdit1->setText("siguientePrimo(Z_inicio);");
      break;

    //Precision
     case 31:
      lineEdit1->setText("precisionReales(numBits);");
      break;
     case 32:
      lineEdit1->setText("precisionSalidaReales(numCifras);");
      break;
     case 33:
      lineEdit1->setText("precisionSalidaEnteros(numCifras);");
      break;

    //Teoría de números
     case 41:
      lineEdit1->setText("simboloKronecker(a,b);");
      break;
     case 42:
      lineEdit1->setText("simboloJacobi(a,b);");
      break;
     case 43:
      lineEdit1->setText("simboloLegendre(a,p);");
      break;
     case 44:
      lineEdit1->setText("gcd(a,b);");
      break;
     case 45:
      lineEdit1->setText("lcm(a,b);");
      break;
     case 46:
      lineEdit1->setText("crt(listaZ(y1,y2,...),listaZ(m1,m2,...));");
      break;
     case 47:
      lineEdit1->setText("factoriza(entero);");
      break;

    //Miscelanea
     case 51:
      lineEdit1->setText("factorial(num);");
      break;
     case 52:
      lineEdit1->setText("potenciaModular(base,exp,mod);");
      break;
     case 53:
      lineEdit1->setText("raizCuadradaEntera(entero);");
      break;

    
  }
  return;
}

void interfazImpl::procesarArchivo()
{ 
  if( !arch->open( IO_ReadOnly ) ){
      QMessageBox::critical(0, "Abrir script", 
          "No ha podido abrirse el archivo",
          "Ok"
          );

    return;
  }
  QTextStream stream( arch );
  QString str;
  QString strRes;
  
  barraEstado->message("Procesando...");
  if(estadisticas){
    perf->iniciar();
    while( !stream.eof() ){
      str = stream.readLine();

      strRes = calc->procesar( string(str.ascii()) );

      str.prepend("<B>");
      str.append( "</B>");
      textBrowser1->append( str );
      textBrowser1->append( strRes );
 //     perf->acumular();
    }
    perf->finalizar();
    
    ostringstream cadStream;

    cadStream << perf->leerVectorOperaciones()[0];
    numSumas->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[1];
    numSumasA->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[2];
    numRestas->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[3];
    numRestasA->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[4];
    numProdSuma->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[5];
    numProductos->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[6];
    numDivisiones->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[7];
    numPorDos->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[8];
    numEntreDos->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[9];
    numCCeros->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerSegundos();
    numTiempo->setText( cadStream.str() );
  }
  else{
    while( !stream.eof() ){
      str = stream.readLine();

      strRes = calc->procesar( string(str.ascii()) );

      str.prepend("<B>");
      str.append( "</B>");
      textBrowser1->append( str );
      textBrowser1->append( strRes );
    }
  }
  barraEstado->message("Listo");
  
  return;
}

void interfazImpl::procesarEntrada()
{ 
  QString str = lineEdit1->text();
  QString strRes;
  lineEdit1->clear();
  
  comboBox1->insertItem( str );
 
  if(estadisticas){
    perf->iniciar();
    barraEstado->message("Procesando...");
    strRes = calc->procesar( string(str.ascii()) );
    perf->finalizar();
    barraEstado->message("Listo");
 
    ostringstream cadStream;

    cadStream << perf->leerVectorOperaciones()[0];
    numSumas->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[1];
    numSumasA->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[2];
    numRestas->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[3];
    numRestasA->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[4];
    numProdSuma->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[5];
    numProductos->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[6];
    numDivisiones->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[7];
    numPorDos->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[8];
    numEntreDos->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerVectorOperaciones()[9];
    numCCeros->setText( cadStream.str() );

    cadStream.str(string(""));
    cadStream << perf->leerSegundos();
    numTiempo->setText( cadStream.str() );


  }
  else{
    barraEstado->message("Procesando...");
    strRes = calc->procesar( string(str.ascii()) );
    barraEstado->message("Listo");
  }


  str.prepend("<B>");
  str.append( "</B>");
  textBrowser1->append( str );
  textBrowser1->append( strRes );

  
  
  return;
}
  

