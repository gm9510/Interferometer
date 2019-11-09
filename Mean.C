#include <cstring>
#include <sstream>
#include <Funciones.h>

using namespace ula;
using namespace std;
using namespace My_functions;

double x, dx=0.05, xi=-5., xf=5., ti=0., tf=4., dt=0.001, g=1., zero=1.e-7;
int n=ceil((xf-xi)/(dx))+1;
int k=(n-1)/2;

void List_Reader(fstream& file, RealVector& Rx,RealVector& Ry){
//Reads a two colums list of data 
        int j=0;
	char B[64],X[16],Y[16];
	const char a[2]="";

	  if(!file.is_open())  //Check if file is not open
	    perror("Error opening file");
  
	  else{
	
	  while(!file.eof()){

	    file.getline(B,64); 
	    if(file.bad()){   //If failbit flag is up then break the while loop.
	      perror("Error while reading fileA");    
	      break;
	           }
	  else{
	   if(strcmp(B,a)==0){ // If we get an empty line then break the while loop
	    break;
	       }
	
	   else{
	    sscanf(B,"%s	%s",X,Y);   //scan the extracted line
	    Rx(j) = atof( X );
	    Ry(j) = atof( Y );
	    j++;
	       }
		}
	         }
	          }
     }

void Block_Reader(fstream& file, RealVector& Rp,RealVector& Rx, RealVector& Rt){
        int j=0;
	char B[64],P[32],T[8],X[8];
	const char a[2]="";

	  if(!file.is_open())  //Check if file is not open
	    perror("Error opening file");
  
	  else{
	
	  while(!file.eof()){

	    file.getline(B,64); 
	    if(file.bad()){   //If failbit flag is up then break the while loop.
	      perror("Error while reading file");    
	      break;
	           }
	  else{
	   if(strcmp(B,a)==0){ // If we get an empty line then break the while loop.
	    break;
	       }
	
	   else{
	    sscanf(B,"%s	%s	%s",T,X,P);   //scan the extracted line
	    Rp(j) = atof( P );
	    Rx(j) = atof( X );
	    Rt(j) = atof( T );
	    j++;

	       }
	        }
	         }
		  }
     }

int main(){
  fstream fileA,foutA,foutB,foutC;
  string dir  ("Datos_5PS/");
  string dir2 ("Datos/");
  string name ("GP_GS_"), ext(".dat");
  string fase("fase_"), mtime("mt"), mspace("mx");

  foutC.open(dir2 + name + "mfull" + ext, ios::out);

  RealVector p(n), x(n), t(n);
  RealVector promt(k), tm; 
  int cx=0,ct=0;
  Real promx=0., s=0.;
  RealVector X(k), Y(k);
  double promedio=0.;
  int ck=0;

double Ddeep=0.05;
  for(int deep=0.; deep<=int(20./Ddeep); deep++){

  stringstream dp;
  dp << fixed << setprecision(2) << deep*Ddeep;

  fileA.open(dir + name + fase +"dp_" + dp.str() + ext, ios::in);
  foutA.open(dir2 + name + mspace + "_dp_" + dp.str() + ext, ios::out);
  foutB.open(dir2 + name + mtime + "_dp_" + dp.str() + ext, ios::out);

  for(int i=0; i<k; i++){
	promt(i)=0;
	}
   
    promedio=0; //reset counters
    ck=0;
    ct=0;

//-------------------------
//-------------------------
//-------------------------
  while(!fileA.eof()){
    cx=0;
    s=0.;
    Block_Reader( fileA, p, x, t );

	if(t(1) > 10 && 30 > t(1)){
	for(int i=0; i<k; i++){
	 if( x(i)+x(n-i-1)<zero ){
		promt(i)+=fabs(p(i)-p(n-i-1));
		s+=fabs(p(i)-p(n-i-1));
		cx += 1;
		 }
		}
  ct += 1;
  promx=s/cx;
  foutA<<t(1)<<"	"<<promx<<"	"<<cx<<endl;
	 }
	}

  promt=promt/ct;

  for(int i=0; i<k; i++){
	foutB<<x(n-i-1)<<"	"<<promt(i)<<endl;
	}
	

  foutA.close();
  foutB.close();
    
    foutB.open(dir2 + name + mtime + "_dp_" + dp.str() + ext, ios::in);
    

    List_Reader(foutB,X,Y);

    for(int i=0; i<k; i++){

	if(X(i)> 1 && 4 > X(i)){
        promedio+= Y(i);
	ck++;
     }
    }

    cout<<"files "<<"dp_"<<dp.str()<<" finished"<<endl;
    promedio=promedio/ck; // Diferencia de fases final
    foutC<<deep*Ddeep<<"	"<<promedio<<endl;
    foutB.close();

  fileA.close();

//-------------------------
//-------------------------
//-------------------------
 }
foutC.close();
}
