/* 
 * $Id$ 
 */

#include "mp.h"
#include <algorithm>
#include <utility>
#ifdef _OPENMP
  #include <omp.h>
  #define GET_BASIC_CPU() basicCPUs_[omp_get_thread_num()]
#else
  #define GET_BASIC_CPU() basicCPUs_[0]
#endif


namespace numth{

  vCPUVectorial::vCPUVectorial(int numCPUs){
    basicCPUs_ = new vCPUBasica<Arch::ARCH>[numCPUs];
  }

  vCPUVectorial::~vCPUVectorial()
  {
    delete[] basicCPUs_;
  }

  /*** OPERACIONES BASICAS EN VECTORES UNSIGNED ***/
  /*** DESPLAZAMIENTO ***/
  void vCPUVectorial::lShift(numth::MiVec <Cifra>& a, size_t n)
  {
    if( (a.size() == 1) && (a[0] == 0) ) 
      return;
    
    unsigned long componentes = n / Constantes::BITS_EN_CIFRA;
    unsigned long fraccion = n % Constantes::BITS_EN_CIFRA;

    //  for(unsigned long i=0; i < componentes; i++){
    //    //desplazamos a la izquierda componente a componente
    //    //o lo que es lo mismo, se inserta una componente toda ceros
    //    //en el principio
    //    a.insert(a.begin(), 0);
    //  }
    a.insert(a.begin(), componentes, 0);

    vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU();

    if(fraccion){
      a.push_back(0);
      for( unsigned long i = a.size() - 2;  ; i--){
        a[i] = cpuBasica_.Shiftl(a[i],fraccion);
        //      a[i+1] = Add(a[i+1], resto);
        a[i+1] |= cpuBasica_.resto;
        if( i == 0 )
          break;
      }
    }

//    limpiarCeros(a);
//    no tiene sentido limpiar ceros, en un desplazamiento a la
//    izquierda nunca se van a generar, salvo quizas 1

    if( a.back() == 0 )
      a.pop_back();

    return;
  }

  void vCPUVectorial::rShift(numth::MiVec <Cifra> &a, size_t n)
  {
    if( (a.size() == 1) && (a[0] == 0) ) 
      return;

    unsigned long componentes = n / Constantes::BITS_EN_CIFRA;
    unsigned long fraccion = n % Constantes::BITS_EN_CIFRA;

    for(unsigned long i=0; i < componentes; i++){
      //desplazamos a la derecha componente a componente
      //o lo que es lo mismo, se inserta una componente toda ceros
      //en el principio y se borra la comp. del final
      a.erase(a.begin());
      a.push_back(0);
    }

    vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU(); 

    if(fraccion){
      a[0] = cpuBasica_.Shiftlr(a[0], fraccion);
      for(unsigned long i = 1; i < a.size() ; i++){
        a[i] = cpuBasica_.Shiftlr(a[i], n);
        //      a[i-1] = Add(a[i-1],resto);
        a[i-1] |= cpuBasica_.resto;
      }
    }

    limpiarCeros(a);
    return;
  }



  long vCPUVectorial::redondear(const numth::MiVec<Cifra>& numero, size_t exceso, const int8_t signo)
  {
    unsigned long indice = exceso - 1;
    unsigned long componente = indice/Constantes::BITS_EN_CIFRA;
    unsigned long bcomponente = indice % Constantes::BITS_EN_CIFRA;
    unsigned long mascara = (1UL << bcomponente);

    // RTE = round to even
    
    assert(componente < numero.size());
    if( numero[componente] & mascara ){ //1er bit de parte frac. es 1 -> posible RTE
      mascara = mascara >> 1; //seguimos probando bits mas a la der.
      while(true){ //saldremos via break
        Cifra compActual = numero[componente];
        while(mascara){
          if(compActual & mascara) //bit posterior al 1� es 1 => parte frac >0.5
            return signo;
          mascara = mascara >> 1;
        }
        //aqu�, mascara = 0
        //la "revivimos"
        if(componente != 0){
          mascara = (1UL << (Constantes::BITS_EN_CIFRA-1));
          componente--;
        }
        else //componente == 0
          break;
      }
      //aqu�, todos excepto el primer bit decimal, han sido 0 =>
      //=> la parte frac. es exactamente 0.5
      //veamos si el digito a la izq del primer "conflictivo" es par o impar
      componente = exceso/Constantes::BITS_EN_CIFRA;
      bcomponente = exceso % Constantes::BITS_EN_CIFRA;
      mascara = (1UL << bcomponente);
      if( numero[componente] & mascara ) // el n� de impar
        return signo;
      else //n� par
        return 0;
    }
    else //1er bit frac. es 0 => parte frac <0.5
      return 0;
  }

  size_t vCPUVectorial::numBits(const Cifra num)
  {
    size_t bits = sizeof(Cifra) << 3;

    vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU(); 
    bits -= cpuBasica_.Bfffo(num);

    return bits;
  }

  /*** COMPARACION ***/
  bool vCPUVectorial::mayorque(numth::MiVec<Cifra> a, numth::MiVec<Cifra> b, bool limpiar) 
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
    typedef numth::MiVec<Cifra>::reverse_iterator It ;
    std::pair<It, It> p = mismatch(a.rbegin(), a.rend(), b.rbegin());
    if (p.first == a.rend() ){
      return false; //a and b are equal
    }
    if(*(p.first) > *(p.second)){
      return true; 
    }
    return false;

  }

  bool vCPUVectorial::menorque(numth::MiVec<Cifra> a, numth::MiVec<Cifra> b, bool limpiar ) 
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
    typedef numth::MiVec<Cifra>::reverse_iterator It ;
    std::pair<It, It> p = mismatch(a.rbegin(), a.rend(), b.rbegin());
    if (p.first == a.rend() ){
      return false; //a and b are equal
    }
    if(*(p.first) < *(p.second)){
      return true; 
    }
    return false;

  }

  bool vCPUVectorial::igual(numth::MiVec<Cifra> a, numth::MiVec<Cifra> b, bool limpiar ) 
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

  bool vCPUVectorial::mayorque(numth::MiVec<Cifra> vec, Cifra num, bool limpiar ) 
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

  bool vCPUVectorial::menorque(numth::MiVec<Cifra> vec, Cifra num, bool limpiar ) 
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

  bool vCPUVectorial::igual(numth::MiVec<Cifra> vec, Cifra num, bool limpiar )  
  {
    if(limpiar)
      limpiarCeros(vec);

    assert(vec.size() > 0);
    if( vec.size() > 1 )
      return false;
    else // => vec.size() == 1
      return (vec[0] == num);
  }


  void vCPUVectorial::limpiarCeros(numth::MiVec<Cifra> &vec) throw()
  {
    numth::MiVec<Cifra>::iterator it;
    for( it = vec.end()-1; 
        (it != vec.begin()) && ( !(*it) )  ; 
        it--) ;
    vec.erase(it+1, vec.end());
      
    return;
  }
  /*** OPERADORES ARITMETICOS ***/
  numth::MiVec<Cifra> 
    vCPUVectorial::sumaMP(const numth::MiVec<Cifra>& a, const numth::MiVec<Cifra>& b) 
    {
      const numth::MiVec<Cifra> *mayor;
      const numth::MiVec<Cifra> *menor;

      size_t tamA = a.size();
      size_t tamB = b.size();

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

      numth::MiVec<Cifra> c(tamA + 1, 0); // +1 por el carry posible

      vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU(); 
      size_t i;
      cpuBasica_.overflow = 0;
      for(i = 0; i < tamB; i++){
        c[i]= cpuBasica_.Addx((*mayor)[i],(*menor)[i]);
        // el propio "loop" del n� del desbordarse es 
        // equivalente al modulo. FIXME: no te fies de
        // esto
      }

      for(; i < tamA; i++)
        c[i] = cpuBasica_.Addx((*mayor)[i],0);

      if( i < c.size() )
        c[i] = cpuBasica_.overflow;

      limpiarCeros(c);

      return c;
    }
  numth::MiVec<Cifra> 
    vCPUVectorial::sumaMP(const numth::MiVec<Cifra>& a, const Cifra b) 
    {
      size_t tamA = a.size();

      numth::MiVec<Cifra> c(tamA + 1, 0); // +1 por el carry posible

      size_t i;

      vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU(); 
      cpuBasica_.overflow = 0;
      c[0]= cpuBasica_.Addx(a[0],b);

      for(i=1; i < tamA; i++)
        c[i] = cpuBasica_.Addx(a[i],0);

      if( i < c.size() )
        c[i] = cpuBasica_.overflow;

      limpiarCeros(c);

      return c;
    }

  numth::MiVec<Cifra> 
    vCPUVectorial::restaMP(const numth::MiVec<Cifra>&a, const numth::MiVec<Cifra>& b) 
    {
      /* PRECONDICION:
       * el n� que representa "a" deber ser >= que el n� q rep. "b"
       */

      size_t tamA = a.size();
      size_t tamB = b.size();

      if( menorque(a,b) ){ // a < b
        throw Errores::RestaNegativa();
      }

      numth::MiVec<Cifra> c(tamA,0);

      vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU(); 
      cpuBasica_.overflow = 0;
      size_t i;
      for(i = 0; i < tamB; i++)
        c[i] = cpuBasica_.Subx(a[i],b[i]);

      for(; i < tamA; i++)
        c[i] = cpuBasica_.Subx(a[i],0);


      limpiarCeros(c);

      return c;
    }
  numth::MiVec<Cifra> 
    vCPUVectorial::restaMP(const numth::MiVec<Cifra>&a, const Cifra b) 
    {
      size_t tamA = a.size();

      numth::MiVec<Cifra> c(tamA,0);

      vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU(); 
      cpuBasica_.overflow = 0;
      size_t i;
      c[0] = cpuBasica_.Subx(a[0],b);

      for(i=1; i < tamA; i++)
        c[i] = cpuBasica_.Subx(a[i],0);

      limpiarCeros(c);

      return c;
    }
  numth::MiVec<Cifra> 
    vCPUVectorial::restaMP(const Cifra a, const numth::MiVec<Cifra>& b) 
    {
      assert( b[0] <= a ); 

      vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU(); 
      numth::MiVec<Cifra> c(1);
      c[0] = cpuBasica_.Sub(a,b[0]);

      limpiarCeros(c);

      return c;
    }

  numth::MiVec<Cifra> 
    vCPUVectorial::multMP(const numth::MiVec<Cifra>& a, const numth::MiVec<Cifra>& b) 
    {
      Cifra v, u, c;

     const size_t tamA = a.size();
     const size_t tamB = b.size();
      
      numth::MiVec<Cifra> w(tamA + tamB, 0);
      const size_t maxSize = tamA > tamB? tamA : tamB;
      if( maxSize >= Constantes::UMBRAL_KARATSUBA ){ 
        if ( maxSize  < 2 * std::min(tamA, tamB)) { //if the bigger factor is less than twice the size of the other
          if( tamA < tamB ){
            MiVec<Cifra> aBis(a);
            aBis.resize(tamB, 0);
            karatsuba(w, aBis,b);
            return w;
          }
          else if ( tamA > tamB ){ 
            MiVec<Cifra> bBis(b);
            bBis.resize(tamA, 0);
            karatsuba(w, a,bBis);
            return w;
          }
          else{ //igual tama�o
            karatsuba(w, a,b);
            return w;
          }
        }
      }

      vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU(); 
      for(size_t i=0; i < tamB; i++){
        c = 0;
        // esta "iteracion particular de j=0" se pone aqui
        // para que al compilar con optimizaciones no se de
        // el caso de que se utilize "u" sin haberse inicializado
        // en el punto (1) posterior 
          v = cpuBasica_.Add(c, w[i]);
          u = cpuBasica_.overflow;

          cpuBasica_.resto = v; //para su uso por Addmul

          v = cpuBasica_.Addmul(a[0],b[i]);
          u += cpuBasica_.resto;

          w[i] = v;
          c = u;
          
        for(size_t j=1; j < tamA; j++){
          v = cpuBasica_.Add(c, w[i+j]);
          u = cpuBasica_.overflow;

          cpuBasica_.resto = v; //para su uso por Addmul

          v = cpuBasica_.Addmul(a[j],b[i]);
          u += cpuBasica_.resto;

          w[i+j] = v;
          c = u;
        }
        w[i+tamA] = u; //(1) (ver parrafo anterior)
      }

      limpiarCeros(w);

      return w;
    }

  numth::MiVec<Cifra> 
    vCPUVectorial::multMP(const numth::MiVec<Cifra>& a, const Cifra b ) 
    {
      unsigned int tamA = a.size();

      numth::MiVec<Cifra> c(tamA + 1, 0);

      vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU(); 
      cpuBasica_.resto = 0;
      unsigned int i;
      for(i=0; i < tamA; i++)
        c[i] = cpuBasica_.Addmul(a[i],b);    

      // i == tamA
      c[i] = cpuBasica_.Add(c[i], cpuBasica_.resto);

      limpiarCeros(c);

      return c;
    }

  void vCPUVectorial::cuadKaratsuba(MiVec<Cifra>& resultado, const MiVec<Cifra>& x)
  {
    /* x^2 = (b^2+b)*x1^2 - b*(x1-x0)^2 + (b+1)*x0^2 
     *               ^^^^     ^^^^^^^^^         ^^^^
     *                P1          P2             P3
     */
     
    
    const size_t m = x.size() >> 1; 
    
    MiVec<Cifra> x0; x0.insert(x0.begin(), x.begin(), x.begin()+m);
    MiVec<Cifra> x1; x1.insert(x1.begin(), x.begin()+m, x.end());
    limpiarCeros(x0); limpiarCeros(x1);
    
    const size_t shifting = Constantes::BITS_EN_CIFRA*m;
    MiVec<Cifra> P1, P2, P3;
    MiVec<Cifra> S11/*, S12, S2*/, S31; //, S32;

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
  
  numth::MiVec<Cifra>
    vCPUVectorial::cuadMP(const numth::MiVec<Cifra>& x)
    {
      size_t t = x.size(); //n� de cifras en la base de trabajo de "x"

      numth::MiVec<Cifra> w(2*t,0); //vector de resultado

      if( t > Constantes::UMBRAL_CUAD_KARATSUBA ){ 
          cuadKaratsuba(w,x);
          return w;
      }

      vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU(); 
      
      //los resultados temporales se expresan como un numero (uA uB v) en la
      //base de trabajo.

      for(size_t i = 0; i < t; i++){
        Cifra uA, uB; // partes Alta y Baja de "u"
        Cifra v; // cifra menos significativa del numero de trabajo
        Cifra cA, cB; // versiones para "carry" de "u"

        // (uA uB v) = x[i]*x[i] + w[2*i]
        v = cpuBasica_.Mul(x[i],x[i]);
        uB = cpuBasica_.resto;
        v = cpuBasica_.Add(v, w[2*i]);
        uB += cpuBasica_.overflow; //ya que aqui no va a darse nunca un 2� overflow
        uA = 0;

        w[2*i] = v;

        //tomamos nota para sgtes iteraciones.
        cA = uA; cB = uB;

        for(size_t j=(i+1); j < t; j++){
          // (uA uB v) = 2*x[i]*x[j] + w[i+j] + c
          //             ^^^^^^^^^^^   ^^^^^^  ^^^ 
          //                 (A)         (B)   (C)


          //      (A)
          v = cpuBasica_.Mul(x[j],x[i]);
          uB = cpuBasica_.resto;
          v = cpuBasica_.Shiftl(v, 1); // *2 
          Cifra restoTemp = cpuBasica_.resto;
          uB = cpuBasica_.Shiftl(uB, 1); // *2
          uA = cpuBasica_.resto;
          uB = cpuBasica_.Add(uB, restoTemp);
          uA += cpuBasica_.overflow; 

          //     (B)
          v = cpuBasica_.Add(v,w[i+j]);
          uB = cpuBasica_.Addx(uB,0);
          uA += cpuBasica_.overflow;

          //     (C)
          v = cpuBasica_.Add(v,cB);
          uB = cpuBasica_.Addx(uB,cA);
          uA += cpuBasica_.overflow;

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
  std::pair< numth::MiVec<Cifra>, numth::MiVec<Cifra> > 
    vCPUVectorial::divMP(numth::MiVec<Cifra> a, numth::MiVec<Cifra> b)
    {
      numth::MiVec<Cifra>b2;
      numth::MiVec<Cifra>a2;


      if( b.size() == 1 )
        return divMP(a,b[0]);
      assert( b.size() > 0 ); 
      //  numth::MiVec<Cifra> a = u;
      //  numth::MiVec<Cifra> b = v;

      Cifra d;
      size_t tamA, tamB;
      Cifra _q;

      tamA = a.size()-1;
      tamB = b.size()-1;

      //D1. NORMALIZAR

      //obtenemos el digito mas significativo del divisor
      //=> siempre sera el se�alado por size() - 1 (o deberia serlo)

      vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU(); 
      d = cpuBasica_.Bfffo(b[tamB]); // n� de ceros a la izq
      // del 1er bit del long 
      // en cuestion 

      // multiplicar dividendo y divisor por 2^d
      if( menorque(a,b) ) // si el dividendo es menor que el divisor...
        // q = 0, r = a
        return std::pair< numth::MiVec<Cifra>, numth::MiVec<Cifra> >
          (numth::MiVec<Cifra>(1,0),a);

      numth::MiVec<Cifra> q((tamA - tamB)+1,0);
      numth::MiVec<Cifra> r;

      lShift(a, d);
      lShift(b, d);

      if(tamA == a.size()-1)
        a.push_back(0); // se ha de introducir un nuevo digito en "a" 
      // siempre 
      tamA++;
      // D2
      size_t variacionDividendo; //para actualizar convenientemente la guarda del bucle
      for( size_t j = tamA; j > tamB; j-=variacionDividendo){
        //D3
        //assert( ((j+tamB) < a.size() ) ); //FIXME: revisar este aserto
        assert( (tamB < b.size()) );
        assert(((j+tamB-1) > 0) );

        if( a[j] == b[tamB] )
          _q = Constantes::CIFRA_MAX; // base-1
        else{
          cpuBasica_.resto = a[j];
          _q = cpuBasica_.Div(a[j-1],b[tamB]);
        }

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

          if( mayorque(b2,a2) )
            _q--;
          else
            break;
        }


        
        /* � v2�q > ((u0�b + u1)-q�v1)�b + u2 ?
         * parteDrchaAlta = resto -> RestoDe[ (u0�b + u1) / v1 ]
         * parteDrchaBaja = u2
         * parteIzdaAlta:parteIzdaBaja  = v2�q */
//        bool centinela = false;
//        bool segundaVez = false;
//        bool terceraVez = false;
//        Cifra restoGuardado = cpuBasica_.resto;
//        do{
//          if(terceraVez)
//            break; //se demuestra que como maximo se comete un error de 2 en _q
//          centinela = false;
//          numth::MiVec<Cifra> izda(1,b[tamB-1]);
//          numth::MiVec<Cifra> drcha(1,restoGuardado);
//
//          if(segundaVez){
//            //        drcha = sumaMP(drcha, numth::MiVec<Cifra>(1,b[tamB]));
//            drcha = sumaMP(drcha, (Cifra)b[tamB]);
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
        MiVec<Cifra>::iterator it = a.begin()+j;
        a2.insert(a2.begin(), it-tamB-1, it+1);
        b2 = multMP(b,_q);
//        if( j > 1)
//          b2.insert(b2.begin(), j-1, (Cifra)0);
                  

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
//            b2.insert(b2.begin(), j-1, (Cifra)0);
        }

        variacionDividendo = a.size();
        a2 = restaMP(a2,b2);
        a.erase(it-tamB-1, it+1);
        a.insert(it-tamB-1, a2.begin(), a2.end());
//        a.resize(tamA+1,(Cifra)0);
        variacionDividendo -= a.size();

        q[j-tamB-1] = _q;
      }

      rShift(a,d);

      r = a;

      limpiarCeros(r);
      limpiarCeros(q);

      return std::pair< numth::MiVec<Cifra>, numth::MiVec<Cifra> >(q,r);

    }


  /*         cociente            modulo              */
  std::pair< numth::MiVec<Cifra>, numth::MiVec<Cifra> > 
    vCPUVectorial::divMP(const numth::MiVec<Cifra>& a, const Cifra b ) 
    {

      vCPUBasica<Arch::ARCH> cpuBasica_ = GET_BASIC_CPU(); 
      cpuBasica_.resto = 0;
      numth::MiVec<Cifra> q(a.size());

      for(CifraSigno j=a.size()-1; j>=0; j--)
        q[j] = cpuBasica_.Div(a[j], b);

      //No es necesario llevar cuenta del resto aparte ya que la CPU
      //b�sica se encarga de forma transparente de ello: en cada
      //division, "cpuBasica.resto" almacena el resto, y a la hora de
      //dividir en el paso ulterior, considera el contenido de
      //"cpuBasica.resto" como la parte alta del divisor (y a lo que
      //se pase como primer par�metro a Div como la baja)

      limpiarCeros(q);

      return std::pair< numth::MiVec<Cifra>, numth::MiVec<Cifra> >(q,
          numth::MiVec<Cifra> (1, cpuBasica_.resto));
    }

  void vCPUVectorial::karatsuba(MiVec<Cifra>& resultado, 
      const MiVec<Cifra>& x, const MiVec<Cifra>& y)
  {
    /* precond: "x" e "y" tienen el mismo tama�o (mismo n� de pos el
     * vector) */
    size_t m = x.size() >> 1; // indistintamente podria haberse usado y.size()

    MiVec<Cifra> x0; x0.insert(x0.begin(), x.begin(), x.begin()+m);
    MiVec<Cifra> x1; x1.insert(x1.begin(), x.begin()+m, x.end());
    MiVec<Cifra> y0; y0.insert(y0.begin(), y.begin(), y.begin()+m);
    MiVec<Cifra> y1; y1.insert(y1.begin(), y.begin()+m, y.end());
    limpiarCeros(x0); limpiarCeros(x1);
    limpiarCeros(y0); limpiarCeros(y1);
    MiVec<Cifra> P1, P2, P3;
    MiVec<Cifra> S11/*, S12, S2*/, S31; //, S32;
    const size_t shifting = Constantes::BITS_EN_CIFRA*m;

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


    
    resultado = sumaMP(S11, P1);
    resultado = sumaMP(resultado, S31);
    resultado = sumaMP(resultado, P3);
   
    if(negativo){
      assert( !mayorque(P2, resultado) );
      resultado = restaMP(resultado, P2);
    }
    else
      resultado = sumaMP(resultado, P2);

    return ;
  }
  
}

