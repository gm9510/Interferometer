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
#include <cstring>

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

void Block_Reader(fstream& file,RealVector& Rphi){
        int j=0;
	char B[64],P[32],T[8],X[8];
	const char a[2]="";

	  if(!file.is_open())  //Check if file is not open
	    perror("Error opening file");
  
	  else
	    /*cout<<"Start Read"<<endl;*/
	
	  while(!file.eof()){

	    file.getline(B,64); 
	    if(file.fail()){   //If failbit flag is up then break the while loop.
	      perror("Error while reading file");    
	      break;
	           }
	  else{
	   if(strcmp(B,a)==0){ // If we get an empty line then break the while loop.
	    /*cout<<"Block Ended: Size "<<j<<endl;*/
	    break;
	       }
	
	   else{
	    sscanf(B,"%s	%s	%s",T,X,P);   //scan the extracted line
	    Rphi(j) = atof( P );
	    /*cout<<T<<"	"<<X<<"	"<<Rphi(j)<<endl;*/
	    j++;
	       }
	        }
	         }
     }

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
  
  fstream Trap,Gstt;
  Trap.open("Datos_5PS/GP_GS_trap_dp_10.20.dat",	ios::in  );
  Gstt.open("Datos/GP_GS_dp_10.20.dat",	ios::out );

  
  RealVector Phi(n);
  RealVector V(n);
  Real norm=0.;

      
    Phi=IniState(n,dx,xi,0.8,0);
    norm=inner_prod(conj(Phi),Phi); //check norm
  if(fabs(norm)!=1){ //normalize the initial state
    Phi/=sqrt(norm);}

//----------------------------------------------------------------------
//---------------------------Rugen_Kutta--------------------------------
//----------------------------------------------------------------------

 while(!Trap.eof()){

  
  Block_Reader( Trap,V );

  for(double t=ti; t<=5000.*dt; t+=dt){
   norm=0.;

      norm=inner_prod(Phi,Phi);//check norm
      if(fabs(norm)!=1){ //normalize the initial state
      Phi/=sqrt(norm);
      norm=inner_prod(Phi,Phi);
      }
    
   GP_IT(n,dx,dt,Phi,V,g,e);

   cout<<"Runnig Itime_Msearch t ="<<t<<"\r";
   }
   cout<<endl;

  for(int j=0; j<n; j++){Gstt<<xi+j*dx<<"	"<<Phi(j)<<"	"<<"0"<<endl;}
     Gstt<<endl;

	}

//----------------------------------------------------------------------
// -----------------------Fin_y_cierre_de_Archivos----------------------
//----------------------------------------------------------------------
  Trap.close();
  Gstt.close();
  return 0;
  
      }
