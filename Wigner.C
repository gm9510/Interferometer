#include <lapack.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <matrixtypes.h>

#include <stdio.h>
#include <Funciones.h>

using namespace ula;
using namespace std;
using namespace My_functions;

#define pi 3.14159265358979323846
#define e 1

double dx=0.05, xi=-5., xf=5. , ti=0., tf=4., dt=0.001, g=1., zero=0.0001;
int n=ceil((xf-xi)/(dx))+1;

int main(){

ComplexVector Phi(n), X(2*n), FX(2*n);
ComplexMatrix Ro(n,n), RoT(2*n,2*n), RoFT(2*n,2*n), RoW(n,n),DFTM(2*n,2*n);

 fstream inist, fileR;
  inist.open("Datos/Armonic_GS.dat",	ios::in);
  fileR.open("Datos/Ro_Matrix.dat",	ios::out);
//---------------------------
//---------------------------Extrayendo datos del estado
//---------------------------

  char B[64];
  char x[8],r[32];
  int j=0;

  while(inist.getline(B,64)) {
  sscanf(B,"%s	%s",x,r);
  Phi(j) = Complex(atof( r ),0);
  j=j+1;
  }

//---------------------------
//---------------------------
//---------------------------

	for(int i=0; i<n; i++){
	 for(int k=0; k<n; k++){

	Ro(i,k) = Phi(i) * conj(Phi(k));	
	
	 }
	}


	RoT.clear();//iniciar en ceros
	for(int i=0; i<n; i++){
	 for(int k=0; k<n; k++){

	RoT(i+k,n-1+i-k) = Ro(i,k);	
	
	 }
	}

	for(int i=0;i<2*n;i++){
	 for(int k=0;k<2*n;k++){
	DFTM(i,k)=(cos(-2.*pi*i*k/(2*n))+I*sin(-2.*pi*i*k/(2*n)))/sqrt(2*n);
	 }
	}

	for(int i=0; i<2*n; i++){
	 for(int k=0; k<2*n; k++){
	X(k) = RoT(i,k);
	 }
	FX = prod(DFTM,X);
	 for(int k=0; k<2*n; k++){
	RoFT(i,k) = FX(k);
	 }
	}

	for(int i=0; i<n; i++){
	 for(int k=0; k<n; k++){
	RoW(i,k) = RoFT(i+k,n-1+i-k);
	 }
	}

	for(int i=0; i<n; i++){
	 for(int k=0; k<n; k++){
	fileR<< real( RoT(i,k) )<<"	";
	 }
	fileR<<endl;
	}



//---------------------------
//---------------------------Cierre de Archivos
//---------------------------
  inist.close();
  fileR.close();
  return 0;

}
