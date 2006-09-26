#include "calculadora.h"
#include <string>
#include "Funciones.h"

using namespace std;
using namespace numth;

string salidaTemp;
map<string, lval> variables;

Calculadora::Calculadora()
{
  joins["copia"]=join_copia;
  joins["suma"]=join_suma;
  joins["resta"]=join_resta;
  joins["mul"]=join_mul;
  joins["div"]=join_div;
  joins["mod"]=join_mod;
  joins["exp"]=join_exp;
  joins["neg"]=join_neg;
  joins["par"]=join_par;
  joins["int"]=join_int;
  joins["flo"]=join_flo;
  joins["ide"]=join_ide;
  joins["asign"]=join_asign;
  joins["sent"]=join_sent;
  joins["sents"]=join_sents;
  joins["lsent"]=join_lsent;
  joins["func"] = join_func;
  joins["append"] = join_append;
  joins["empty"] = join_empty;

  toks["+"]='+';
  toks["-"]='-';
  toks["*"]='*';
  toks["/"]='/';
  toks["%"]='%';
  toks["^"]='^';
  toks["("]='(';
  toks[")"]=')';
  toks["="]='=';
  toks[";"]=';';
  toks[":"]=':';
  toks["T_INT"]=T_INT;
  toks["T_FLO"]=T_FLO;
  toks["T_IDE"]=T_IDE;
  toks[","] = ',';

  in=fopen("gram","rb");


  if(in==NULL)
    cerr << "No se encuentra el fichero con la gramatica.";
  else{

    cerr << "Generando parser ...\n";

    analizador = new parser_t<lval>(in,toks,joins,lex);
    if(analizador->error)
      cerr << "Hay errores/conflictos en la gramatica de entrada.";
    else
      cerr << "OK";

    analizador->setErrorHandler(merror);

    return;
  }
}

Calculadora::~Calculadora()
{
//  fclose(in);
  delete analizador;
}


lval  join_copia(vector<lval>::iterator v)
{
	lval res;
  
  if( v[0].tipo == 'Z' ) {
    res.tipo = 'Z';
    res.entero = v[0].entero;
  }
  else {
    res.tipo = 'R';
    res.real = v[0].real;
  }

	return res;
}

lval  join_int(vector<lval>::iterator v)
{
	lval res;
	res.entero= Z::convertir(v[0].text.c_str());
  res.tipo = 'Z';
	return res;
}

lval  join_flo(vector<lval>::iterator v)
{
	lval res;
	res.real = R::convertir(v[0].text.c_str());
  res.tipo = 'R';
	return res;
}


lval  join_ide(vector<lval>::iterator v)
{
	lval res;
	if(variables.find(v[0].text)==variables.end())
	{
		cout << "Undefined variable " << v[0].text << ". Assuming 0\n";
    res.tipo = 'Z';
		res.entero=Z::convertir((Cifra)0);
	}
	else{
    if( variables[v[0].text].tipo == 'Z' ){
      res.tipo = 'Z';   
      res.entero=variables[v[0].text].entero;
    }
    else{
      res.tipo = 'R';   
      res.real=variables[v[0].text].real;
    }
  }
	return res;
}

lval  join_suma(vector<lval>::iterator v)
{
	lval res;
  if( v[0].tipo == 'R' ){
    if( v[2].tipo == 'Z' ) {
      v[2].real = R::convertir(v[2].entero);
      v[2].tipo = 'R';
    }
    res.tipo = 'R';
    res.real = v[0].real + v[2].real;

    return res;
  }
  if( v[2].tipo == 'R' ){
    if( v[0].tipo == 'Z' ) {
      v[0].real = R::convertir(v[0].entero);
      v[0].tipo = 'R';
    }
    res.tipo = 'R';
    res.real = v[0].real + v[2].real;

    return res;
  }

  //ambos son enteros
  res.tipo = 'Z';
	res.entero = v[0].entero+v[2].entero;
  
	return res;
}

lval  join_resta(vector<lval>::iterator v)
{
	lval res;
  if( v[0].tipo == 'R' ){
    if( v[2].tipo == 'Z' ) {
      v[2].real = R::convertir(v[2].entero);
      v[2].tipo = 'R';
    }
    res.tipo = 'R';
    res.real = v[0].real - v[2].real;

    return res;
  }
  if( v[2].tipo == 'R' ){
    if( v[0].tipo == 'Z' ) {
      v[0].real = R::convertir(v[0].entero);
      v[0].tipo = 'R';
    }
    res.tipo = 'R';
    res.real = v[0].real - v[2].real;

    return res;
  }

  //ambos son enteros
  res.tipo = 'Z';
	res.entero = v[0].entero - v[2].entero;
  
	return res;

  
}
lval  join_mul(vector<lval>::iterator v)
{
	lval res;
  if( v[0].tipo == 'R' ){
    if( v[2].tipo == 'Z' ) {
      v[2].real = R::convertir(v[2].entero);
      v[2].tipo = 'R';
    }
    res.tipo = 'R';
    res.real = v[0].real * v[2].real;

    return res;
  }
  if( v[2].tipo == 'R' ){
    if( v[0].tipo == 'Z' ) {
      v[0].real = R::convertir(v[0].entero);
      v[0].tipo = 'R';
    }
    res.tipo = 'R';
    res.real = v[0].real * v[2].real;

    return res;
  }

  //ambos son enteros
  res.tipo = 'Z';
	res.entero = v[0].entero*v[2].entero;
  
	return res;

  
}
lval  join_div(vector<lval>::iterator v)
{
	lval res;
  if( v[0].tipo == 'R' ){
    if( v[2].tipo == 'Z' ) {
      v[2].real = R::convertir(v[2].entero);
      v[2].tipo = 'R';
    }
    res.tipo = 'R';
    res.real = v[0].real / v[2].real;

    return res;
  }
  if( v[2].tipo == 'R' ){
    if( v[0].tipo == 'Z' ) {
      v[0].real = R::convertir(v[0].entero);
      v[0].tipo = 'R';
    }
    res.tipo = 'R';
    res.real = v[0].real / v[2].real;

    return res;
  }

  //ambos son enteros
  res.tipo = 'Z';
	res.entero = v[0].entero/v[2].entero;
  
	return res;
}
lval  join_mod(vector<lval>::iterator v)
{
	lval res;
  if( v[0].tipo != 'Z' )
    throw TipoParametroIncorrecto(1,'Z');
  if( v[2].tipo != 'Z' )
    throw TipoParametroIncorrecto(2,'Z');
    
  res.tipo = 'Z';
  res.entero = v[0].entero % v[2].entero;

  return res;
}

lval  join_exp(vector<lval>::iterator v)
{
	lval res;
  if( v[0].tipo == 'Z' ){
    res.tipo = 'Z';
    if( v[2].tipo == 'Z' )
      res.entero=( (v[0].entero) ^(v[2].entero));
    else
      throw TipoParametroIncorrecto(2,'Z');
  }
  else{
    res.tipo = 'R';
    if( v[2].tipo == 'Z' )
      res.real = ( (v[0].real) ^(v[2].entero));
    else
      throw TipoParametroIncorrecto(2,'Z');
      
  }
    
	return res;
}

lval  join_neg(vector<lval>::iterator v)
{
	lval res;
  if( v[1].tipo == 'Z' )
    res.entero=- v[1].entero;
  else
    res.real =- v[1].real;

  res.tipo = v[1].tipo;

	return res;
}
lval  join_par(vector<lval>::iterator v)
{

	lval res;
  if( v[1].tipo == 'Z' )
    res.entero= v[1].entero;
  else
    res.real = v[1].real;

  res.tipo = v[1].tipo;

	return res;

}

lval  join_asign(vector<lval>::iterator v)
{
	lval res;
  if( v[2].tipo == 'Z'){
    variables[v[0].text].entero = v[2].entero;
    variables[v[0].text].tipo = 'Z';
    res.entero = v[2].entero;
    res.tipo = 'Z';
  }
  else{
    variables[v[0].text].real = v[2].real;
    variables[v[0].text].tipo = 'R';
    res.real = v[2].real;
    res.tipo = 'R';
  }

	return res;
}

lval join_sent(vector<lval>::iterator v)
{
	lval res=v[0];

  ostringstream cadStream;
  string salida;
  
  if(res.tipo == 'Z'){
    if( !res.L.empty() )
      for( list<lval>::iterator it=res.L.begin(); it != res.L.end(); it++)
        cadStream << it->entero << endl;
    else{
      cadStream << res.entero;
      variables[string("ans")].tipo = 'Z';
      variables[string("ans")].entero = res.entero;
    }
  }
  else{
    if( !res.L.empty() )
      for( list<lval>::iterator it=res.L.begin(); it != res.L.end(); it++)
        cadStream << it->real << endl;
    else{
      cadStream << res.real;
      variables[string("ans")].tipo = 'R';
      variables[string("ans")].real = res.real;
    }
  }
 
  salidaTemp += cadStream.str();
  salidaTemp += '\n';

	return res;
}
lval join_sents(vector<lval>::iterator v)
{
	return v[0];
}

lval  join_lsent(vector<lval>::iterator v)
{
	lval res;
  if( v[1].tipo == 'Z'){
    res.entero=v[1].entero;
    res.tipo = 'Z';
  }
  else{
    res.real=v[1].real;
    res.tipo = 'R';
  }
	return res;
}

lval  join_func(vector<lval>::iterator v)
{
  lval res;
  list<lval> listaArgs = v[2].L;
  Funciones funcs;
  
  if( v[0].text == "listaZ" ){
    res.tipo = 'Z';

    list<lval>::iterator it;
    size_t i;
    for(it = listaArgs.begin(), i=0; 
        it != listaArgs.end(); 
        it++, i++){
      if( (*it).tipo != 'Z' )
        throw TipoParametroIncorrecto(i+1,'Z');
      res.L.push_back(*it);
    }

    res.entero.hacerCero();
    return res;
  } 
  if( v[0].text == "precisionReales" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    R::precision(listaArgs.front().entero[0]);
    
    res.entero.hacerUno();
    return res;
  }
  if( v[0].text == "precisionSalidaReales" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    R::precisionSalida(listaArgs.front().entero[0]);
    
    res.entero.hacerUno();
    return res;
  }
  if( v[0].text == "precisionSalidaEnteros" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    Z::precisionSalida(listaArgs.front().entero[0]);
    
    res.entero.hacerUno();
    return res;
  }
  if( v[0].text == "esPrimo" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    if( funcs.testPrimoProb()->esPrimo(listaArgs.front().entero) )
      res.entero.hacerUno();
    else
      res.entero.hacerCero();

    return res;
  }
  if( v[0].text == "esPrimoMersenne" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    if( funcs.testPrimoMersenne()->esPrimo(listaArgs.front().entero[0]) )
      res.entero.hacerUno();
    else
      res.entero.hacerCero();

    return res;
  }
  if( v[0].text == "randomRapido" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    res.entero = funcs.randomRapido()->leerBits(listaArgs.front().entero[0]);

    return res;
  }
  if( v[0].text == "randomSeguro" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    res.entero = funcs.randomSeguro()->leerBits(listaArgs.front().entero[0]);

    return res;
  }
  if( v[0].text == "ponerCalidad" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    funcs.randomSeguro()->ponerCalidad(listaArgs.front().entero[0]);

    res.entero.hacerUno();
    return res;
  }

  if( v[0].text == "ponerSemilla" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    funcs.randomRapido()->ponerSemilla(listaArgs.front().entero);

    res.entero.hacerUno();
    return res;
  }
  if( v[0].text == "ponerCalidadRandom" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    funcs.randomSeguro()->ponerCalidad(listaArgs.front().entero[0]);

    res.entero.hacerUno();
    return res;
  }
  if( v[0].text == "leerPrimo" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    res.entero = funcs.genPrimos()->leerPrimoProb(listaArgs.front().entero[0]);

    return res;
  }
  if( v[0].text == "siguientePrimo" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    res.entero = funcs.genPrimos()->siguientePrimoProb(listaArgs.front().entero);

    return res;
  }
  if( v[0].text == "leerPrimoFuerte" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    res.entero = funcs.genPrimos()->leerPrimoFuerte(listaArgs.front().entero[0]);

    return res;
  }
  if( v[0].text == "ponerIteraciones" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    funcs.testPrimoProb()->ponerIteraciones(listaArgs.front().entero[0]);

    return res;
  }
  if( v[0].text == "potenciaModular" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 3 )
      throw NumeroParametrosIncorrecto(3,tam);

    list<lval>::iterator it;
    size_t i =0 ;
    for(it = listaArgs.begin(), i=0; 
        it != listaArgs.end(); 
        it++, i++)
      if( (*it).tipo != 'Z' )
        throw TipoParametroIncorrecto(i+1,'Z');

    it = listaArgs.begin();
    Z base = (*it).entero; it++;
    Z exp = (*it).entero; it++;
    Z mod = (*it).entero; 
    funcs.potModular()->potModular(&base, exp, mod);

    res.entero = base;

    return res;
  }
  if( v[0].text == "gcd" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 2 )
      throw NumeroParametrosIncorrecto(2,tam);

    list<lval>::iterator it;
    size_t i =0 ;
    for(it = listaArgs.begin(), i=0; 
        it != listaArgs.end(); 
        it++, i++)
      if( (*it).tipo != 'Z' )
        throw TipoParametroIncorrecto(i+1,'Z');

    it = listaArgs.begin();
    Z a = (*it).entero; it++;
    Z b = (*it).entero; 
    res.entero = funcs.gcd()->gcd(a,b);

    return res;
  }
  if( v[0].text == "lcm" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 2 )
      throw NumeroParametrosIncorrecto(2,tam);

    list<lval>::iterator it;
    size_t i =0 ;
    for(it = listaArgs.begin(), i=0; 
        it != listaArgs.end(); 
        it++, i++)
      if( (*it).tipo != 'Z' )
        throw TipoParametroIncorrecto(i+1,'Z');

    it = listaArgs.begin();
    Z a = (*it).entero; it++;
    Z b = (*it).entero; 
    res.entero = funcs.lcm()->lcm(a,b);

    return res;
  }
  if( v[0].text == "simboloKronecker" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 2 )
      throw NumeroParametrosIncorrecto(2,tam);

    list<lval>::iterator it;
    size_t i =0 ;
    for(it = listaArgs.begin(), i=0; 
        it != listaArgs.end(); 
        it++, i++)
      if( (*it).tipo != 'Z' )
        throw TipoParametroIncorrecto(i+1,'Z');

    it = listaArgs.begin();
    Z a = (*it).entero; it++;
    Z b = (*it).entero; 
    res.entero = funcs.simboloKronecker()->simboloKronecker(a,b);

    return res;
  }
  if( v[0].text == "simboloJacobi" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 2 )
      throw NumeroParametrosIncorrecto(2,tam);

    list<lval>::iterator it;
    size_t i =0 ;
    for(it = listaArgs.begin(), i=0; 
        it != listaArgs.end(); 
        it++, i++)
      if( (*it).tipo != 'Z' )
        throw TipoParametroIncorrecto(i+1,'Z');

    it = listaArgs.begin();
    Z a = (*it).entero; it++;
    Z b = (*it).entero; 
    res.entero = funcs.simboloJacobi()->simboloJacobi(a,b);

    return res;
  }
  if( v[0].text == "simboloLegendre" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 2 )
      throw NumeroParametrosIncorrecto(2,tam);

    list<lval>::iterator it;
    size_t i =0 ;
    for(it = listaArgs.begin(), i=0; 
        it != listaArgs.end(); 
        it++, i++)
      if( (*it).tipo != 'Z' )
        throw TipoParametroIncorrecto(i+1,'Z');

    it = listaArgs.begin();
    Z a = (*it).entero; it++;
    Z b = (*it).entero; 
    res.entero = funcs.simboloLegendre()->simboloLegendre(a,b);

    return res;
  }
  if( v[0].text == "crt" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 2 )
      throw NumeroParametrosIncorrecto(2,tam);

    list<lval>::iterator it;
    size_t i =0 ;
    for(it = listaArgs.begin(), i=0; 
        it != listaArgs.end(); 
        it++, i++)
      if( (*it).tipo != 'Z' )
        throw TipoParametroIncorrecto(i+1,'Z');

    it = listaArgs.begin();
    list<lval> lista1 = it->L; it++;
    list<lval> lista2 = it->L;
    if( lista1.size() != lista2.size() )
      throw MensajeErrorCustom(string("Las listas de argumentos deben tener el mismo número de elementos"));

    MiVec<Z> m, y;
    list<lval>::iterator it2;
    for(it = lista1.begin(), it2 = lista2.begin();
        it != lista1.end(); 
        it++, it2++){
      m.push_back(it->entero);
      y.push_back(it2->entero);
    }
      
    res.entero = funcs.crt()->crt(m,y);

    return res;
  }
  if( v[0].text == "factorial" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    res.entero = listaArgs.front().entero;
    res.entero.factorial();
    return res;
  }
  if( v[0].text == "raizCuadradaEntera" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    res.entero = listaArgs.front().entero;
    res.entero.raizCuadrada();
    return res;
  }
  if( v[0].text == "potenciaModular" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 3 )
      throw NumeroParametrosIncorrecto(3,tam);

    list<lval>::iterator it;
    size_t i =0 ;
    for(it = listaArgs.begin(), i=0; 
        it != listaArgs.end(); 
        it++, i++)
      if( (*it).tipo != 'Z' )
        throw TipoParametroIncorrecto(i+1,'Z');

    it = listaArgs.begin();
    res.entero = (*it).entero; it++;
    Z b = (*it).entero; it++;
    Z c = (*it).entero;
    
    funcs.potModular()->potModular(&res.entero, b, c);
    return res;
  }
  if( v[0].text == "factoriza" ){
    res.tipo = 'Z';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'Z' )
      throw TipoParametroIncorrecto(1,'Z');
    
    MiVec<Z> factores;
    factores = funcs.factoriza()->factoriza(listaArgs.front().entero);
   
    lval elemento;
    for(size_t i=0; i < factores.size(); i++){
      elemento.tipo = 'Z';
      elemento.entero = factores[i];
      res.L.push_back(elemento);
    }

    return res;
  }
  if( v[0].text == "exponencial" ){
    res.tipo = 'R';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'R' )
      listaArgs.front().real = R::convertir(listaArgs.front().entero);
    
    res.real = funcs.exponencial()->exponencial(listaArgs.front().real);
    return res;
  }
 
  if( v[0].text == "ln" ){
    res.tipo = 'R';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'R' )
      listaArgs.front().real = R::convertir(listaArgs.front().entero);
    
    res.real = funcs.ln()->ln(listaArgs.front().real);
    return res;
  }
  if( v[0].text == "cos" ){
    res.tipo = 'R';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'R' )
      listaArgs.front().real = R::convertir(listaArgs.front().entero);
    
    res.real = funcs.coseno()->coseno(listaArgs.front().real);
    return res;
  }
  if( v[0].text == "sen" ){
    res.tipo = 'R';
    size_t tam = listaArgs.size();
    if( tam != 1 )
      throw NumeroParametrosIncorrecto(1,tam);
    if( listaArgs.front().tipo != 'R' )
      listaArgs.front().real = R::convertir(listaArgs.front().entero);
    
    res.real = funcs.seno()->seno(listaArgs.front().real);
    return res;
  }

  if( v[0].text == "pi" ){
    res.tipo = 'R';
    size_t tam = listaArgs.size();
    if( tam == 0 ){
      res.real = funcs.pi()->pi();
      return res;
    }
    else if (tam == 1){
      if( listaArgs.front().tipo != 'Z' )
        throw TipoParametroIncorrecto(1,'Z');

      res.real = funcs.pi()->pi(listaArgs.front().entero[0]);
      return res;

    }
    else
      throw NumeroParametrosIncorrecto(1,tam);

    return res;
  }



  throw FuncionIncorrecta(v[0].text);

  res.tipo = 'Z'; res.entero.hacerCero();
  return res;
}
  

lval  join_append(vector<lval>::iterator v)
{
  lval res = v[0];
  res.L.push_back( v[2] );
  return res;
}


lval  join_empty(vector<lval>::iterator v)
{
  lval res;
  if( v[0].tipo == 'Z' )
    res.tipo = 'Z';
  else
    res.tipo = 'R';
  
  res.L.push_back(v[0]);
  
  return res;
}

bool merror(vector<lval>::iterator b,vector<lval>::iterator e,list<int> &ex,
								int &tok,lex_t &lex)
{
	if(tok==T_EOF)
	{
		cout<<"Unexpected end of file, giving up...\n";
		return true;
	}
	cout<<"Ignoring unexpected token "<<lex.text()<<" at line "<<
					lex.line()<<endl;
	tok=lex.nextToken();
	return false;
}


string Calculadora::procesar(string entrada)
{
  inputString_t input(entrada.c_str());
  lex.setInput(&input); 
  string salida;
  salidaTemp.clear();
  
    try{
      if(!analizador->parse()){
        salida = "Error en el programa\n";
      }
      else
        input.refresh(entrada);
      
    }
    catch(Errores::Excepcion &ex)
    {
      salida = ex.info();
    }

    if( !salida.empty() ){
      salidaTemp.clear();
      return salida;
    }
    
    return salidaTemp;
    
}

