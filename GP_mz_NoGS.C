#include <lapack.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <matrixtypes.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>//libreria estandar modo c
#include <time.h> //numeros aleatorios
#include <complex>
#include <functional>
#include <numeric>
#include <math.h>
#include <string>

#include <Funciones.h>

using namespace ula;
using namespace std;
using namespace Functions;

// ---------------------------------------------------------------------
//-----------------------Variable_Globales------------------------------
// ---------------------------------------------------------------------
#define pi 3.14159265358979323846
#define e 1

double dx=0.05, xi=-5, xf=5 , ti=0., tf=4., dt=0.001, g=0., zero=1.e-3;
int n=ceil((xf-xi)/(dx))+1;

//----------------------------------------------------------------------
// -----------------------Inicio_de_programa----------------------------
//----------------------------------------------------------------------


int main(){
  
  fstream file1,file2,norma,trap1,initial;
  file1.open("Datos/Datos.dat",ofstream::out);
  file2.open("Datos/Fase.dat",ofstream::out);
  norma.open("Datos/norma.dat",ofstream::out);
  trap1.open("Datos/Trap.dat",ofstream::out);

  ComplexVector Phi(n);
  Phi=Gaussian(n,dx,xi,0.8,0);
    
  Real norm=0.;
  norm=real(inner_prod(conj(Phi),Phi)); //check norm

  Phi/=sqrt(norm);//normalize the initial state
    
    
    
//----------------------------------------------------------------------
//---------------------------Rugen_Kutta--------------------------------
//----------------------------------------------------------------------
  for(double t=ti; t<=40000.*dt; t+=dt){
    ComplexVector k1(n), k2(n), k3(n), k4(n),Phi_(n);
   norm=0.;

      norm=real(inner_prod(conj(Phi),Phi))*dx;//check norm
      /*if(fabs(norm)!=1){ //normalize
    Phi=Phi/sqrt(norm);}*/
      norma<<t<<" "<<norm<<endl;

  for(int i=0; i<n; i++){
    if(fabs(imag(Phi(i)))<=zero && fabs(real(Phi(i)))<=zero){file2<<t<<"       "<<xi+i*dx<<"       "<<endl;}
    
    else{file2<<t<<"       "<<xi+i*dx<<"       "<<atan2(imag(Phi(i)),real(Phi(i)))<<endl;}
    
         file1<<t<<"       "<<xi+i*dx<<"       "<<real(conj(Phi(i))*Phi(i))<<endl;
         }
    file1<<endl;
    file2<<endl;
    
   
  if(t<=5){
    RealVector V(n);
    V=TrapH(n,dx,0,xi);

    for(int i=0; i<n; i++){trap1<<t<<" "<<xi+i*dx<<" "<<V(i)<<endl;}
     trap1<<endl;
   
   GP_RK(n,dx,dt,Phi,V,g,e);
   }
  
  else if(t>5 && t<15){
    RealVector V(n);
    V=TrapH(n,dx,(t-5)/10.,xi);

    for(int i=0; i<n; i++){trap1<<t<<" "<<xi+i*dx<<" "<<V(i)<<endl;}
     trap1<<endl;
   
   GP_RK(n,dx,dt,Phi,V,g,e);
   }

  else if(t>=15 && t<25){
    RealVector V(n);
    V=TrapH(n,dx,1.,xi);

    for(int i=0; i<n; i++){trap1<<t<<" "<<xi+i*dx<<" "<<V(i)<<endl;}
     trap1<<endl;
   
   GP_RK(n,dx,dt,Phi,V,g,e);
   }

  else if(t>=25 && t<=35){
    RealVector V(n);
    V=TrapH(n,dx,1.-(t-25.)/10.,xi);

    for(int i=0; i<n; i++){trap1<<t<<" "<<xi+i*dx<<" "<<V(i)<<endl;}
     trap1<<endl;
   
   GP_RK(n,dx,dt,Phi,V,g,e);
   }
      
  else{
    RealVector V(n);
    V=TrapH(n,dx,0,xi);

    for(int i=0; i<n; i++){trap1<<t<<" "<<xi+i*dx<<" "<<V(i)<<endl;}
     trap1<<endl;

   GP_RK(n,dx,dt,Phi,V,g,e);
   }

   }

//----------------------------------------------------------------------
// -----------------------Fin_y_cierre_de_Archivos----------------------
//----------------------------------------------------------------------
  file1.close();
  file2.close();
  trap1.close();
  norma.close();
  initial.close();
  return 0;
  
      }
