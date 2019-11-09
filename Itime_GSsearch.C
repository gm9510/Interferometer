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
using namespace My_functions;

// ---------------------------------------------------------------------
//-----------------------Variable_Globales------------------------------
// ---------------------------------------------------------------------
#define pi 3.14159265358979323846
#define e 1

double x, dx=0.05, xi=-5., xf=5., ti=0., tf=4., dt=0.001, g=1., zero=1.e-3;
int n=ceil((xf-xi)/(dx))+1;

RealVector IniState(int n,double dx, double xi,Real Sx=0.75/*Spread of the Gaussian*/,Real xm=4./*Maximun of the gaussian*/){
  RealVector F(n);
  Real A=1/(Sx*sqrt(2*pi));
  for(int i=0; i<n; i++){
    F(i)=A*exp(-pow((xi+i*dx)-xm,2)/(2*Sx*Sx));}
  return F;
}

//----------------------------------------------------------------------
// -----------------------Inicio_de_programa----------------------------
//---------------------------------------------------------------------

int main(){
  
  ofstream file1,norma,trap1;
  file1.open("Datos/Itime_Data.dat");
  norma.open("Datos/Itime_norma.dat");
 
  RealVector Phi(n);
  Real norm=0.;
      RealVector V(n);
    V=Trap_HE(n,dx,0,xi);

  
  Phi=IniState(n,dx,xi,0.8,0);
  
    norm=real(inner_prod(conj(Phi),Phi)); //check norm
  if(fabs(norm)!=1){ //normalize the initial state
    Phi/=sqrt(norm);}

//----------------------------------------------------------------------
//---------------------------Rugen_Kutta--------------------------------
//----------------------------------------------------------------------
  for(double t=ti; t<=10000.*dt; t+=dt){ 

   norm=0.;

      norm=inner_prod(Phi,Phi);//check norm
      if(fabs(norm)!=1){ //normalize the initial state
      Phi/=sqrt(norm);
      norm=inner_prod(Phi,Phi);
      }
      norma<<t<<" "<<norm<<endl;
    
   
   GP_IT(n,dx,dt,Phi,V,g,e);
   

     for(int i=0; i<n; i++){
     file1<<t<<"	"<<xi+i*dx<<"	"<<Phi(i)<<endl;
       }
    file1<<endl;
   }
   



//----------Estado_Final------------------------------------------------
        fstream gstate;
  gstate.open("Datos/Armonic_GS.dat",ofstream::out);
  for(int i=0; i<n; i++){gstate<<xi+i*dx<<"	"<<Phi(i)<<endl;}
  gstate.close();

//----------------------------------------------------------------------
// -----------------------Fin_y_cierre_de_Archivos----------------------
//----------------------------------------------------------------------
  file1.close();
  norma.close();
  return 0;
  
      }
