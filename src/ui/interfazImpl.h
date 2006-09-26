#ifndef INTERFAZIMPL_H
#define INTERFAZIMPL_H
#include "interfaz.h"
#include "calculadora.h"
#include <string>
#include "Perfil.h"
#include <qfile.h>
#include <qstatusbar.h>
#include <qdockwindow.h>
#include "panelFunciones.h"

class interfazImpl : public Interfaz
{
    Q_OBJECT

public:
    interfazImpl( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~interfazImpl();

private:
    Calculadora* calc;
    numth::Perfil* perf;
    bool estadisticas;
    QStatusBar* barraEstado;
    QFile* arch;

public slots:
    void fileNew();
    void fileOpen();
    void fileSave();
    void helpContents();
    void helpAbout();

    void ponerTextoFuncion(int);
    void procesarEntrada();
    void procesarArchivo();

};

#endif // INTERFAZIMPL_H
