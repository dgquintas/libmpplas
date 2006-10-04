#ifndef __PRUEBA_H
#define __PRUEBA_H

#include<cstdio>
#include"mlex.h"
#include"parser.h"
#include<cmath>
#include "Z.h"
#include "R.h"
#include <list>
#include <sstream>

using namespace std;
using namespace numth;

struct lval
{
	string text;
	Z entero;
  R real;
  char tipo;
  list<lval> L;
};


 lval  join_copia(vector<lval>::iterator v);
 lval  join_int(vector<lval>::iterator v);
 lval  join_flo(vector<lval>::iterator v);
 lval  join_ide(vector<lval>::iterator v);
 lval  join_suma(vector<lval>::iterator v);
 lval  join_resta(vector<lval>::iterator v);
 lval  join_mul(vector<lval>::iterator v);
 lval  join_div(vector<lval>::iterator v);
 lval  join_mod(vector<lval>::iterator v);
 lval  join_exp(vector<lval>::iterator v);
 lval  join_neg(vector<lval>::iterator v);
 lval  join_par(vector<lval>::iterator v);
 lval  join_asign(vector<lval>::iterator v);
 lval  join_sent(vector<lval>::iterator v);
 lval  join_sents(vector<lval>::iterator v);
 lval  join_lsent(vector<lval>::iterator v);
 lval  join_func(vector<lval>::iterator v);
 lval  join_append(vector<lval>::iterator v);
 lval  join_empty(vector<lval>::iterator v);

 
 bool merror(vector<lval>::iterator b,
      vector<lval>::iterator e,
      list<int> &ex,
      int &tok,
      lex_t &lex);




class Calculadora 
{

  public:
    Calculadora();
    ~Calculadora();
    
    string procesar(string);
    
  private:
    parser_t<lval>::mapToks_t toks;
    parser_t<lval>::mapJoins_t joins;
    FILE* in;
    mlex_t lex;
    parser_t<lval>* analizador;
};

class ExcepcionCalculadora : public numth::Errores::Excepcion {};

class NumeroParametrosIncorrecto : public ExcepcionCalculadora
{
  public:
    NumeroParametrosIncorrecto(size_t ok, size_t bad)
      : n_ok(ok), n_bad(bad)
    {}
    virtual const char* info(void) const 
    {
      ostringstream cadStream;

      cadStream << "Número de parámetros (" << n_bad << ") incorrecto." 
        << " Se esperaban " << n_ok << ".";
      
      return cadStream.str().c_str();
    }
  private:
    size_t n_ok;
    size_t n_bad;
};

class TipoParametroIncorrecto : public ExcepcionCalculadora
{
  public:
    TipoParametroIncorrecto(size_t i, char tipo)
      : n_param(i), esperado(tipo)
    {}
    virtual const char* info(void) const 
    {
      ostringstream cadStream;

      cadStream << "Tipo del " << n_param << "º parámetro incorrecto." <<
        " Se esperaba un " << esperado << ".";
      
      return cadStream.str().c_str();
    }
  private:
    size_t n_param;
    char esperado;
};

class FuncionIncorrecta : public ExcepcionCalculadora
{
  public:
    FuncionIncorrecta(string nom)
      : nombre(nom)
    {}
    virtual ~FuncionIncorrecta(){}
    virtual const char* info(void) const 
    {
      ostringstream cadStream;

      cadStream << "Funcion " << nombre << " desconocida.";
      return cadStream.str().c_str();
    }
  private:
    string nombre;
};

class MensajeErrorCustom : public ExcepcionCalculadora
{
  public:
    MensajeErrorCustom(string msg)
      : mensaje(msg)
    {}
    virtual ~MensajeErrorCustom(){}
    virtual const char* info(void) const 
    {
      ostringstream cadStream;

      cadStream << mensaje;
      return cadStream.str().c_str();
    }
  private:
    string mensaje;
};


#endif
