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
#include <sstream>
#include <omp.h>

#include <Funciones.h>

using namespace ula;
using namespace std;
using namespace My_functions;

int Selector(int C, fstream& trap,fstream& file,double t,double xi, int n,double dx , RealVector A, ComplexVector B){
    if(C==100){

	for(int i=0; i<n; i++){
	trap<<t<<"	"<<xi+i*dx<<"	"<<A(i)<<endl;
		}
	trap<<endl;

	for(int i=0; i<n; i++){
	file<<xi+i*dx<<"	"<<real(B(i))<<"	"<<imag(B(i))<<endl;
		}
	file<<endl;
    C=0;
	}
	
   C++;
   return C;
}

// ---------------------------------------------------------------------
//-----------------------Variable_Globales------------------------------
// ---------------------------------------------------------------------
#define pi 3.14159265358979323846
#define e 1

double dx=0.05, xi=-5., xf=5. , ti=0., tf=4., dt=0.001, g=1., zero=0.0001;
int n=ceil((xf-xi)/(dx))+1;

//----------------------------------------------------------------------
// -----------------------Inicio_de_programa----------------------------
//----------------------------------------------------------------------




int main(){
  
  fstream file1,file2,file3,norma,trap1,inist;
  
  string dir  ("Datos_5PS/");
  string name ("GP_GS_"), ext(".dat");
  string dens ("dens_"), fase("fase_"), trap("trap_"), data("data_"); 

  norma.open("Datos/GP_GS_norm.dat",	ios::out);
  inist.open("Datos/Armonic_GS.dat",	ios::in);

  ComplexVector Phi(n);
  /*Phi=Gaussian(n,dx,xi,0.8,0);*/
  
  char B[64];
  char x[8],r[32];
  int j=0, C=100;
  

 
  while(inist.getline(B,64)) {
  sscanf(B,"%s	%s",x,r);
  Phi(j) = Complex(atof( r ),0);
  j=j+1;
  }

  Real norm=0.;
  
  /*Phi=Gaussian(n,dx,X,0.8,10);*/
  
    /*norm=real(inner_prod(conj(Phi),Phi))*dx; //check norm
  if(fabs(norm)!=1){ //normalize the initial state
    Phi=Phi*0.1/sqrt(norm);}*/

	file1.open(dir + name + dens + "dp_" + "10.20" + ext,	ios::out);
	file2.open(dir + name + fase + "dp_" + "10.20" + ext,	ios::out);
	file3.open(dir + name + data + "dp_" + "10.20" + ext,	ios::out);
	trap1.open(dir + name + trap + "dp_" + "10.20" + ext,	ios::out);
//----------------------------------------------------------------------
//---------------------------Rugen_Kutta--------------------------------
//----------------------------------------------------------------------
  for(double t=ti; t<=40000.*dt; t+=dt){ 
    ComplexVector k1(n), k2(n), k3(n), k4(n),Phi_(n);
   norm=0.;
   
      norm=real(inner_prod(conj(Phi),Phi));//check norm
      norma<<t<<" "<<norm<<endl;
	
  for(int i=0; i<n; i++){//loop
    if(fabs(imag(Phi(i)))<=zero && fabs(real(Phi(i)))<=zero){file2<<t<<"       "<<xi+i*dx<<"       "<<0<<endl;} //-------------------
    													     //Print Phase
    else{file2<<t<<"       "<<xi+i*dx<<"       "<<atan2(imag(Phi(i)),real(Phi(i)))<<endl;}                   //-------------------
    
    file1<<t<<"       "<<xi+i*dx<<"       "<<real(conj(Phi(i))*Phi(i))<<endl;//Print Density 
       }
    file1<<endl;
    file2<<endl;

    RealVector V(n);
    V=Trap_HE(n,dx,t,xi, 10.20);

	C=Selector(C,trap1,file3,t,xi,n,dx,V,Phi);

   GP_RK(n,dx,dt,Phi,V,g,e);
   
   }

//----------------------------------------------------------------------
//---------------------Fin_y_cierre_de_Archivos--------------
//----------------------------------------------------------------------
  
  file1.close();
  file2.close();
  file3.close();
  trap1.close();
  norma.close();
  inist.close();
  return 0;
  
      }
