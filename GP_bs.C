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
//-----------------------Variables_Globales------------------------------
// ---------------------------------------------------------------------
#define pi 3.14159265358979323846
#define e 1

double dx=0.05, xi=-5., xf=5. , ti=0., tf=4., dt=0.001, g=1., zero=0.0001;
int n=ceil((xf-xi)/(dx))+1;

//----------------------------------------------------------------------
// -----------------------Inicio_de_programa----------------------------
//----------------------------------------------------------------------


int main(){
  
  fstream file1,file2,norma,trap1,inist;

  file1.open("Datos/GP_GS_dens.dat",	ios::out);
  file2.open("Datos/GP_GS_data.dat",	ios::out);
  trap1.open("Datos/GP_GS_trap.dat",	ios::out);
  norma.open("Datos/GP_GS_norm.dat",	ios::out);
  inist.open("Datos/Armonic_GS.dat",	ios::in);

  ComplexVector Phi(n);
  RealVector V(n);
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


//----------------------------------------------------------------------
//---------------------------Rugen_Kutta--------------------------------
//----------------------------------------------------------------------
  for(double t=ti; t<=10000.*dt; t+=dt){ 
    ComplexVector k1(n), k2(n), k3(n), k4(n),Phi_(n);
   norm=0.;
   
      norm=real(inner_prod(conj(Phi),Phi));//check norm
      norma<<t<<" "<<norm<<endl;
	
  for(int i=0; i<n; i++){//loop    
    file1<<t<<"	"<<xi+i*dx<<"	"<<real(conj(Phi(i))*Phi(i))<<endl;//Print Density 
       }
    file1<<endl;

	C=Selector(C,trap1,file2,t,xi,n,dx,V,Phi);

    V=Trap_HC(n,dx,t,xi);

   GP_RK(n,dx,dt,Phi,V,g,e);
   
   }

  file1.close();
  trap1.close();
  norma.close();
  inist.close();

  return 0;


}
