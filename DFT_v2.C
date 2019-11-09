#include <lapack.h>
#include <matrixtypes.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>

#define L 10000                               // System Dimension
#define PI 3.14159265358979323846

using namespace ula;

Complex I(0.,1.);                             // Imaginay Unit




int main(){
  ComplexMatrix DFTM(L,L);
  ComplexMatrix IDFTM(L,L);
  //  Complex *DFTM;                              // Vandermonde Matrix Definition
  //  DFTM=(Complex*)calloc(L*L,sizeof(Complex)); // Vandermonde Matrix space allocation
  ComplexVector X(L);                         // Entry vector
  ComplexVector FX(L);                         // Entry vector
  ComplexVector IFX(L);                         // Entry vector

  FILE *dskw1;                                // Output File
  FILE *dskw2;                                // Output File
  FILE *dskw3;                                // Output File
  dskw1=fopen("vctr_in.dat","w+");
  dskw2=fopen("vctr_out.dat","w+");
  dskw3=fopen("vctr_res.dat","w+");

  for(int i=0;i<L;i++){
	if(i<l/2){
    X(i+L/2)=X(i)=exp(-(i-L/4.)*(i-L/4.)/(0.0001*L*L));// X Initialize
		}
    for(int j=0;j<L;j++){
      DFTM(i,j)=(cos(-2.*PI*i*j/L)+I*sin(-2.*PI*i*j/L))/sqrt(L);
      IDFTM(i,j)=(cos(-2.*PI*i*j/L)-I*sin(-2.*PI*i*j/L))/sqrt(L);
	 }
	}


 for(int i=0;i<L;i++)
    fprintf(dskw1,"%g %g %g\n",i/(float)L,real(X(i)),imag(X(i)));
  fflush(dskw1);
  fclose(dskw1);

  FX=prod(DFTM,X);

  for(int i=0;i<L;i++)
    fprintf(dskw2,"%g %g %g\n",i/(float)L,real(FX(i)),imag(FX(i)));  
  fflush(dskw2);
  fclose(dskw2);
      
  IFX=prod(IDFTM,FX);

  for(int i=0;i<L;i++)
    fprintf(dskw3,"%g %g %g\n",i/(float)L,real(IFX(i)),imag(IFX(i)));  
  fflush(dskw3);
  fclose(dskw3);
  
  
  return 0;
}




/* 

 * Compiling *

Make DFT_v1.70921

* Running *

time ./DFT_v1.70921

*/
