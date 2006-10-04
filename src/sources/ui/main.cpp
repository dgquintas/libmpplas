#include <qapplication.h>
#include "interfazImpl.h"

int main(int argc, char** argv)
{
  QApplication app( argc, argv );

  interfazImpl* ifaz = new interfazImpl();

  app.setMainWidget( ifaz );
  ifaz->show();
  
  return app.exec();

}
