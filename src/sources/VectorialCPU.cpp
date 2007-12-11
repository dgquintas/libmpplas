/* 
 * $Id$ 
 */

#include <algorithm>
#include <utility>
#include <iostream>

#include "VectorialCPU.h"
#include "kernel.h"


namespace mpplas{

  /*** OPERACIONES BASICAS EN VECTORES UNSIGNED ***/
  /*** DESPLAZAMIENTO ***/
  void VectorialCPU::lShift(mpplas::MiVec <Digit>& a, const int n) {
    if( ((a.size() == 1) && (a[0] == 0)) || n == 0 ) {
      return;
    }
    
    const int componentes = n >> Constants::LOG_2_BITS_EN_CIFRA ; 
    const int fraccion = n & Constants::DIGIT_MOD_MASK;

    a.insert(a.begin(), componentes, 0);

    Digit resto = 0;
    if(fraccion){
      a.push_back(0);
      for( int i = a.size() - 2; i >= 0 ; i--){
        a[i] = BasicCPU::Shiftl(a[i],fraccion, resto);
        //      a[i+1] = Add(a[i+1], resto);
        a[i+1] |= resto;
      }
    }

//    limpiarCeros(a);
//    no tiene sentido limpiar ceros, en un desplazamiento a la
//    izquierda nunca se van a generar, salvo quizas 1

    if( a.back() == 0 ){
      a.pop_back();
    }

    return;
  }

  void VectorialCPU::rShift(mpplas::MiVec <Digit> &a, const int n) {
    if( ((a.size() == 1) && (a[0] == 0)) || n == 0 ) {
      return;
    }

    const int componentes = n >> Constants::LOG_2_BITS_EN_CIFRA ; 
    const int fraccion = n & Constants::DIGIT_MOD_MASK;

     //desplazamos a la derecha componente a componente
     //o lo que es lo mismo, se inserta una componente toda ceros
     //en el principio y se borra la comp. del final
     //a.erase(a.begin());
    if( componentes > 0 ){
      if( a.size() <= componentes ){
        a.clear();
        a.push_back(0);
      }
      else{
        a.erase(a.begin(), a.begin() + componentes );
      }
    }


    Digit resto = 0;
    if(fraccion){
      a[0] = BasicCPU::Shiftlr(a[0], fraccion, resto);
      for(int i = 1; i < a.size() ; i++){
        a[i] = BasicCPU::Shiftlr(a[i], n, resto);
        //      a[i-1] = Add(a[i-1],resto);
        a[i-1] |= resto;
      }
    }

    limpiarCeros(a);
    return;
  }

    int VectorialCPU::getBitLength(const Digit num) {
      return BasicCPU::Mnob(num);
    }


  SignedDigit VectorialCPU::round(const mpplas::MiVec<Digit>& numero, int exceso, const int8_t signo)
  {
    const int indice = exceso - 1;

    int componente = indice >> Constants::LOG_2_BITS_EN_CIFRA ; 
    int bcomponente = indice & Constants::DIGIT_MOD_MASK;

    Digit mascara = ((Digit)1) << bcomponente;

    // RTE = round to even
    
    assert(componente < numero.size());
    if( numero[componente] & mascara ){ //1er bit de parte frac. es 1 -> posible RTE
      mascara >>= 1; //seguimos probando bits mas a la der.
      while(true){ //saldremos via break
        Digit compActual = numero[componente];
        while(mascara){
          if(compActual & mascara){ //bit posterior al 1� es 1 => parte frac >0.5
            return signo;
          }
          mascara >>= 1;
        }
        //aqu�, mascara = 0
        //la "revivimos"
        if(componente != 0){
          mascara = ( ((Digit)1) << (Constants::BITS_EN_CIFRA-1));
          componente--;
        }
        else{ //componente == 0
          break;
        }
      }
      //aqu�, todos excepto el primer bit decimal, han sido 0 =>
      //=> la parte frac. es exactamente 0.5
      //veamos si el digito a la izq del primer "conflictivo" es par o impar
      componente = exceso/Constants::BITS_EN_CIFRA;
      bcomponente = exceso % Constants::BITS_EN_CIFRA;
      mascara = ( ((Digit)1) << bcomponente);
      if( numero[componente] & mascara ) { // el n� de impar
        return signo;
      }
      else {//n� par
        return 0;
      }
    }
    else { //1er bit frac. es 0 => parte frac <0.5
      return 0;
    }
  }


  /*** COMPARACION ***/
  bool VectorialCPU::mayorque(mpplas::MiVec<Digit> a, mpplas::MiVec<Digit> b, const bool limpiar) 
  {
    if(limpiar){
      limpiarCeros(a);
      limpiarCeros(b);
    }

    if( a.size() > b.size() ){
      return true;
    }

    if( b.size() > a.size() ){
      return false;
    }

    //equal size
    typedef mpplas::MiVec<Digit>::reverse_iterator It ;
    std::pair<It, It> p = mismatch(a.rbegin(), a.rend(), b.rbegin());
    if (p.first == a.rend() ){
      return false; //a and b are equal
    }
    if(*(p.first) > *(p.second)){
      return true; 
    }
    return false;

  }

  bool VectorialCPU::menorque(mpplas::MiVec<Digit> a, mpplas::MiVec<Digit> b, const bool limpiar ) 
  {
    if(limpiar){
      limpiarCeros(a);
      limpiarCeros(b);
    }

    if( a.size() < b.size() ){
      return true;
    }

    if( b.size() < a.size() ){
      return false;
    }

    //equal size
    typedef mpplas::MiVec<Digit>::reverse_iterator It ;
    std::pair<It, It> p = mismatch(a.rbegin(), a.rend(), b.rbegin());
    if (p.first == a.rend() ){
      return false; //a and b are equal
    }
    if(*(p.first) < *(p.second)){
      return true; 
    }
    return false;

  }

  bool VectorialCPU::igual(mpplas::MiVec<Digit> a, mpplas::MiVec<Digit> b,const  bool limpiar ) 
  {
    if(limpiar){
      limpiarCeros(a);
      limpiarCeros(b);
    }
  
    if( a.size() != b.size()){
      return false;
    }
    else{ //equal size
      return equal(a.begin(), a.end(), b.begin());
    }

  }

  bool VectorialCPU::mayorque(mpplas::MiVec<Digit> vec, Digit num, const bool limpiar ) 
  {
    if(limpiar){
      limpiarCeros(vec);
    }

    assert(vec.size() > 0);
    if( vec.size() > 1 ){
      return true;
    }
    else{ // => vec.size() == 1
      return (vec[0] > num);
    }
  }

  bool VectorialCPU::menorque(mpplas::MiVec<Digit> vec, Digit num, const bool limpiar ) 
  {
    if(limpiar){
      limpiarCeros(vec);
    }

    assert(vec.size() > 0);
    if( vec.size() > 1 )
      return false;
    else // => vec.size() == 1
      return (vec[0] < num);
  }

  bool VectorialCPU::igual(mpplas::MiVec<Digit> vec, Digit num, const bool limpiar )  
  {
    if(limpiar){
      limpiarCeros(vec);
    }

    assert(vec.size() > 0);
    if( vec.size() > 1 )
      return false;
    else // => vec.size() == 1
      return (vec[0] == num);
  }


  void VectorialCPU::limpiarCeros(mpplas::MiVec<Digit> &vec) throw()
  {
    mpplas::MiVec<Digit>::iterator it;
    for( it = vec.end()-1; 
        (it != vec.begin()) && ( !(*it) )  ; 
        it--) ;
    vec.erase(it+1, vec.end());
      
    return;
  }
  /*** OPERADORES ARITMETICOS ***/
  mpplas::MiVec<Digit> 
    VectorialCPU::sumaMP(const mpplas::MiVec<Digit>& a, const mpplas::MiVec<Digit>& b) 
    {
      const mpplas::MiVec<Digit> *mayor;
      const mpplas::MiVec<Digit> *menor;

      int tamA = a.size();
      int tamB = b.size();

      if(tamA < tamB){
        mayor = &b;
        menor = &a;

        tamA = mayor->size();
        tamB = menor->size();
      }
      else{
        mayor = &a;
        menor = &b;
      }

      // el vector "a" siempre sera el grande => tamA el tam. mayor

      mpplas::MiVec<Digit> c(tamA + 1, 0); // +1 por el carry posible

      int i;
      Digit overflow = 0;
      for(i = 0; i < tamB; i++){
        c[i]= BasicCPU::Addx((*mayor)[i],(*menor)[i], overflow);
        // el propio "loop" del n� del desbordarse es 
        // equivalente al modulo. FIXME: no te fies de
        // esto
      }

      for(; i < tamA; i++){
        c[i] = BasicCPU::Addx((*mayor)[i],0, overflow);
      }

      if( i < c.size() ){
        c[i] = overflow;
      }

      limpiarCeros(c);

      return c;
    }
  mpplas::MiVec<Digit> 
    VectorialCPU::sumaMP(const mpplas::MiVec<Digit>& a, const Digit b) 
    {
      const int tamA = a.size();

      mpplas::MiVec<Digit> c(tamA + 1, 0); // +1 por el carry posible

      int i;

      Digit overflow = 0;
      c[0]= BasicCPU::Addx(a[0],b, overflow);

      for(i=1; i < tamA; i++){
        c[i] = BasicCPU::Addx(a[i],0, overflow);
      }

      if( i < c.size() ){
        c[i] = overflow;
      }

      limpiarCeros(c);

      return c;
    }

  mpplas::MiVec<Digit> 
    VectorialCPU::restaMP(const mpplas::MiVec<Digit>&a, const mpplas::MiVec<Digit>& b) 
    {
      /* PRECONDICION:
       * el n� que representa "a" deber ser >= que el n� q rep. "b"
       */

      const int tamA = a.size();
      const int tamB = b.size();

      if( menorque(a,b) ){ // a < b
        throw Errors::NegativeSubstraction();
      }

      mpplas::MiVec<Digit> c(tamA,0);

      Digit overflow = 0;
      int i;
      for(i = 0; i < tamB; i++)
        c[i] = BasicCPU::Subx(a[i],b[i], overflow);

      for(; i < tamA; i++)
        c[i] = BasicCPU::Subx(a[i],0, overflow);


      limpiarCeros(c);

      return c;
    }
 mpplas::MiVec<Digit> 
    VectorialCPU::restaMP(const mpplas::MiVec<Digit>&a, const Digit b) 
    {
      const int tamA = a.size();

      mpplas::MiVec<Digit> c(tamA,0);

      Digit overflow = 0;
      c[0] = BasicCPU::Subx(a[0],b, overflow);

      for(int i=1; i < tamA; i++)
        c[i] = BasicCPU::Subx(a[i],0, overflow);

      limpiarCeros(c);

      return c;
    }
  mpplas::MiVec<Digit> 
    VectorialCPU::restaMP(const Digit a, const mpplas::MiVec<Digit>& b) 
    {
      assert( b[0] <= a ); 

      mpplas::MiVec<Digit> c(1);
      Digit overflow = 0;
      c[0] = BasicCPU::Sub(a,b[0], overflow);

      limpiarCeros(c);

      return c;
    }

  mpplas::MiVec<Digit> 
    VectorialCPU::multMP(const mpplas::MiVec<Digit>& a, const mpplas::MiVec<Digit>& b) 
    {
      Digit v, u, c;

     const int tamA = a.size();
     const int tamB = b.size();

      
      mpplas::MiVec<Digit> w(tamA + tamB, 0);
      const int maxSize = tamA > tamB? tamA : tamB;
      if( maxSize >= Constants::UMBRAL_KARATSUBA ){ 
        if ( maxSize  < 2 * std::min(tamA, tamB)) { //if the bigger factor is less than twice the size of the other
          if( tamA < tamB ){
            MiVec<Digit> aBis(a); 
            aBis.resize(tamB, 0);
            karatsuba(w, aBis,b);
            return w;
          }
          else if ( tamA > tamB ){ 
            MiVec<Digit> bBis(b);
            bBis.resize(tamA, 0);
            karatsuba(w, a,bBis);
            return w;
          }
          else{ //igual tama�o
            karatsuba(w, a,b );
            return w;
          }
        }
      }

      Digit overflow = 0, resto = 0;
      for(int i=0; i < tamB; i++){
        c = 0;
        // esta "iteracion particular de j=0" se pone aqui
        // para que al compilar con optimizaciones no se de
        // el caso de que se utilize "u" sin haberse inicializado
        // en el punto (1) posterior 
          v = BasicCPU::Add(c, w[i], overflow);
          u = overflow;

          resto = v; //para su uso por Addmul

          v = BasicCPU::Addmul(a[0],b[i], resto);
          u += resto;

          w[i] = v;
          c = u;
          
        for(int j=1; j < tamA; j++){
          v = BasicCPU::Add(c, w[i+j], overflow);
          u = overflow;

          resto = v; //para su uso por Addmul

          v = BasicCPU::Addmul(a[j],b[i], resto);
          u += resto;

          w[i+j] = v;
          c = u;
        }
        w[i+tamA] = u; //(1) (ver parrafo anterior)
      }

      limpiarCeros(w);

      return w;
    }

 mpplas::MiVec<Digit> 
    VectorialCPU::multMP(const mpplas::MiVec<Digit>& a, const Digit b ) 
    {
      const int tamA = a.size();

      mpplas::MiVec<Digit> c(tamA + 1, 0);

      Digit resto = 0, overflow = 0;
      int i;
      for(i=0; i < tamA; i++){
        c[i] = BasicCPU::Addmul(a[i],b, resto);    
      }

      // i == tamA
      c[i] = BasicCPU::Add(c[i], resto, overflow);

      limpiarCeros(c);

      return c;
    }

  void VectorialCPU::cuadKaratsuba(MiVec<Digit>& resultado, const MiVec<Digit>& x)
  {
    /* x^2 = (b^2+b)*x1^2 - b*(x1-x0)^2 + (b+1)*x0^2 
     *               ^^^^     ^^^^^^^^^         ^^^^
     *                P1          P2             P3
     */
     
    
    const int m = x.size() >> 1; 
    
    MiVec<Digit> x0; x0.insert(x0.begin(), x.begin(), x.begin()+m);
    MiVec<Digit> x1; x1.insert(x1.begin(), x.begin()+m, x.end());
    limpiarCeros(x0); limpiarCeros(x1);
    
    const int shifting = Constants::BITS_EN_CIFRA*m;
    MiVec<Digit> P1, P2, P3;
    MiVec<Digit> S11/*, S12, S2*/, S31; //, S32;

#pragma omp parallel sections
    {
#pragma omp section
      { 
        P1 = cuadMP(x1);
        S11 = P1;
        lShift(S11, 2*shifting);
        //    S12 = P1;
        lShift(P1, shifting);
      }
#pragma omp section
      {
        // esta parafernalia es debida a que en restaMP el
        // minuendo debe ser >= que el sustraendo
        if( mayorque(x0,x1) ){
          P2 = restaMP( x0, x1 );
        }
        else{
          P2 = restaMP( x1, x0 );
        }
        P2 = cuadMP(P2);

        //    S2 = P2;
        lShift(P2, shifting);

      }
#pragma omp section
      {
        P3 = cuadMP(x0);
        S31 = P3;
        lShift(S31, shifting);
        //S32 = P3
      }
    }

  
    resultado = sumaMP(S11, P1);
    resultado = sumaMP(resultado, S31);
    resultado = sumaMP(resultado, P3);

    resultado = restaMP(resultado, P2);
    
    return ;
  }
  
 mpplas::MiVec<Digit>
    VectorialCPU::cuadMP(const mpplas::MiVec<Digit>& x)
    {
      const int t = x.size(); //n� de cifras en la base de trabajo de "x"

      mpplas::MiVec<Digit> w(2*t,0); //vector de resultado

      if( t > Constants::UMBRAL_CUAD_KARATSUBA ){ 
          cuadKaratsuba(w,x);
          return w;
      }

      
      //los resultados temporales se expresan como un numero (uA uB v) en la
      //base de trabajo.
      Digit resto, overflow = 0;
      for(int i = 0; i < t; i++){
        Digit uA, uB; // partes Alta y Baja de "u"
        Digit v; // cifra menos significativa del numero de trabajo
        Digit cA, cB; // versiones para "carry" de "u"

        // (uA uB v) = x[i]*x[i] + w[2*i]
        v = BasicCPU::Mul(x[i],x[i], resto);
        uB = resto;
        v = BasicCPU::Add(v, w[2*i], overflow);
        uB += overflow; //ya que aqui no va a darse nunca un 2� overflow
        uA = 0;

        w[2*i] = v;

        //tomamos nota para sgtes iteraciones.
        cA = uA; cB = uB;

        for(int j=(i+1); j < t; j++){
          // (uA uB v) = 2*x[i]*x[j] + w[i+j] + c
          //             ^^^^^^^^^^^   ^^^^^^  ^^^ 
          //                 (A)         (B)   (C)


          //      (A)
          v = BasicCPU::Mul(x[j],x[i], resto);
          uB = resto;
          v = BasicCPU::Shiftl(v, 1, resto); // *2 
          Digit restoTemp = resto;
          uB = BasicCPU::Shiftl(uB, 1, resto); // *2
          uA = resto;
          uB = BasicCPU::Add(uB, restoTemp, overflow);
          uA += overflow; 

          //     (B)
          v = BasicCPU::Add(v,w[i+j], overflow);
          uB = BasicCPU::Addx(uB,0, overflow);
          uA += overflow;

          //     (C)
          v = BasicCPU::Add(v,cB, overflow);
          uB = BasicCPU::Addx(uB,cA, overflow);
          uA += overflow;

          w[i+j] = v;

          //tomamos nota para siguientes iteraciones.
          cA = uA; cB = uB;
        }
        if( uA ) //esto NO deberia ser cierto en la ultima iteraci�n, ya que el cuad. 
          //tiene s�lo el doble de cifras que el n� original
          w[i+1+t] += uA;

        w[i+t] += uB;
      }

      limpiarCeros(w);

      return w;
    }


  /*         cociente            modulo              */
  std::pair< mpplas::MiVec<Digit>, mpplas::MiVec<Digit> > 
    VectorialCPU::divMP(mpplas::MiVec<Digit> a, mpplas::MiVec<Digit> b)
    {



      if( b.size() == 1 ){
        return divMP(a,b[0]);
      }
      assert( b.size() > 0 ); 
      //  mpplas::MiVec<Digit> a = u;
      //  mpplas::MiVec<Digit> b = v;

      Digit d;
      int tamA = a.size()-1;
      const int tamB = b.size()-1;
      Digit _q;

      //D1. NORMALIZAR

      //obtenemos el digito mas significativo del divisor
      //=> siempre sera el se�alado por size() - 1 (o deberia serlo)

      d = Constants::BITS_EN_CIFRA - BasicCPU::Mnob(b[tamB]); 

      // multiplicar dividendo y divisor por 2^d
      if( menorque(a,b) ) // si el dividendo es menor que el divisor...
        // q = 0, r = a
        return std::pair< mpplas::MiVec<Digit>, mpplas::MiVec<Digit> >
          (mpplas::MiVec<Digit>(1,0),a);

      mpplas::MiVec<Digit> q((tamA - tamB)+1,0);
      //mpplas::MiVec<Digit> r;

      lShift(a, d);
      lShift(b, d);

      if(tamA == a.size()-1){
        a.push_back(0); // se ha de introducir un nuevo digito en "a" 
      }
      // siempre 
      tamA++;
      // D2
      int variacionDividendo; //para actualizar convenientemente la guarda del bucle
      for( int j = tamA; j > tamB; j-=variacionDividendo){
        //D3
        //assert( ((j+tamB) < a.size() ) ); //FIXME: revisar este aserto
        assert( (tamB < b.size()) );
        assert(((j+tamB-1) > 0) );

        if( a[j] == b[tamB] )
          _q = Constants::CIFRA_MAX; // base-1
        else{
          Digit resto = a[j];
          _q = BasicCPU::Div(a[j-1],b[tamB], resto);
        }

        mpplas::MiVec<Digit>b2;
        mpplas::MiVec<Digit>a2;
        while(true){
          a2.clear();
          a2.push_back(a[j-1]);
          a2.push_back(a[j]);

          b2.clear();
          b2.push_back(b[tamB]);
          b2 = multMP(b2, _q);

          a2 = restaMP(a2, b2);
          a2.insert(a2.begin(), a[j-2]);
          limpiarCeros(a2);          

          b2.clear();
          b2.push_back(b[tamB-1]);
          b2 = multMP(b2, _q);

          if( mayorque(b2,a2) ){
            _q--;
          }
          else{
            break;
          }
        }


        
        /* � v2�q > ((u0�b + u1)-q�v1)�b + u2 ?
         * parteDrchaAlta = resto -> RestoDe[ (u0�b + u1) / v1 ]
         * parteDrchaBaja = u2
         * parteIzdaAlta:parteIzdaBaja  = v2�q */
//        bool centinela = false;
//        bool segundaVez = false;
//        bool terceraVez = false;
//        Digit restoGuardado = BasicCPU::resto;
//        do{
//          if(terceraVez)
//            break; //se demuestra que como maximo se comete un error de 2 en _q
//          centinela = false;
//          mpplas::MiVec<Digit> izda(1,b[tamB-1]);
//          mpplas::MiVec<Digit> drcha(1,restoGuardado);
//
//          if(segundaVez){
//            //        drcha = sumaMP(drcha, mpplas::MiVec<Digit>(1,b[tamB]));
//            drcha = sumaMP(drcha, (Digit)b[tamB]);
//            terceraVez = true;
//          }
//
//          izda = multMP(izda, _q);
//          drcha.insert(drcha.begin(), a[j-2]);
//
//
//          /* COMPARACION */
//          if( mayorque(izda,drcha)){
//            _q--;
//            centinela = true;
//            segundaVez = true;
//          }
//        } while(centinela);

        // D4

        a2.clear();
        MiVec<Digit>::iterator it = a.begin()+j;
        a2.insert(a2.begin(), it-tamB-1, it+1);
        b2 = multMP(b,_q);
//        if( j > 1)
//          b2.insert(b2.begin(), j-1, (Digit)0);
                  

        if( mayorque(b2, a2, true) ){ // si el nuevo dividendo va a ser negativo...
          //sabemos que nos hemos pasado en uno en el cociente propuesto
          _q--;

          //se corrige la multiplicacion cociente-dividendo
          //Esto podria hacerse de forma mas eficiente (aunque como viene
          //siendo habitual, menos comoda) restando 'b*BASE^{j-1}' a 'b2'
          //Teniendo en cuenta que este trozo de codigo rara vez va a
          //ejecutarse, se puede permitir uno esta licencia...
          b2 = multMP(b,_q);
//          if( j > 1)
//            b2.insert(b2.begin(), j-1, (Digit)0);
        }

        variacionDividendo = a.size();
        a2 = restaMP(a2,b2);
        a.erase(it-tamB-1, it+1);
        a.insert(it-tamB-1, a2.begin(), a2.end());
//        a.resize(tamA+1,(Digit)0);
        variacionDividendo -= a.size();

        q[j-tamB-1] = _q;
      }

      rShift(a,d);

      //r = a;

      limpiarCeros(a);
      limpiarCeros(q);

      return std::pair< mpplas::MiVec<Digit>, mpplas::MiVec<Digit> >(q,a);

    }


  /*         cociente            modulo              */
  std::pair< mpplas::MiVec<Digit>, mpplas::MiVec<Digit> > 
    VectorialCPU::divMP(const mpplas::MiVec<Digit>& a, const Digit b ) 
    {

      Digit resto = 0;
      mpplas::MiVec<Digit> q(a.size());

      for(SignedDigit j=a.size()-1; j>=0; j--){
        q[j] = BasicCPU::Div(a[j], b, resto);
      }

      //No es necesario llevar cuenta del resto aparte ya que la CPU
      //b�sica se encarga de forma transparente de ello: en cada
      //division, "cpuBasica.resto" almacena el resto, y a la hora de
      //dividir en el paso ulterior, considera el contenido de
      //"cpuBasica.resto" como la parte alta del divisor (y a lo que
      //se pase como primer par�metro a Div como la baja)

      limpiarCeros(q);

      return std::pair< mpplas::MiVec<Digit>, mpplas::MiVec<Digit> >(q,
          mpplas::MiVec<Digit> (1, resto));
    }

  void VectorialCPU::karatsuba(MiVec<Digit>& resultado, 
      const MiVec<Digit>& x, const MiVec<Digit>& y)
  {
    /* precond: "x" e "y" tienen el mismo tama�o (mismo n� de pos el
     * vector) */
    const int m = x.size() /2;// indistintamente podria haberse usado y.size()

    MiVec<Digit> x0; x0.insert(x0.begin(), x.begin(), x.begin()+m);
    MiVec<Digit> x1; x1.insert(x1.begin(), x.begin()+m, x.end());
    MiVec<Digit> y0; y0.insert(y0.begin(), y.begin(), y.begin()+m);
    MiVec<Digit> y1; y1.insert(y1.begin(), y.begin()+m, y.end());
    limpiarCeros(x0); limpiarCeros(x1);
    limpiarCeros(y0); limpiarCeros(y1);
    MiVec<Digit> P1, P2, P3;
    MiVec<Digit> S11/*, S12, S2*/, S31; //, S32;
    const int shifting = Constants::BITS_EN_CIFRA*m;

    bool negativo = false;
#pragma omp parallel sections
    {
#pragma omp section
      {
        P1 = multMP(x1,y1); 
        S11 = P1;

        lShift(S11, shifting*2);

        //    S12 = P1;
        lShift(P1,shifting);
      }
#pragma omp section
      {
        if( mayorque(x0,x1) ){
          P2 = restaMP( x0, x1 );
          negativo = true;
        }
        else{
          P2 = restaMP( x1, x0 );
        }
        if( mayorque(y1,y0) ){
          P2 = multMP( P2, restaMP( y1, y0 ) );
          negativo = !negativo;
        }
        else{
          P2 = multMP( P2, restaMP( y0, y1 ) );
        }

        //    S2 = P2;
        lShift(P2, shifting);

      }
#pragma omp section
      {
        P3 = multMP(x0, y0);
        S31 = P3;
        lShift(S31,shifting);
        //S32 = P3
      }
  }


    
    resultado = sumaMP(sumaMP( sumaMP(S11, P1) , S31), P3);
   
    if(negativo){
      assert( !mayorque(P2, resultado) );
      resultado = restaMP(resultado, P2);
    }
    else
      resultado = sumaMP(resultado, P2);

    return ;
  }
  
}

