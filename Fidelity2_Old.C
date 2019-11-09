#include <lapack.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <matrixtypes.h>
#include <cstring>

#include <Funciones.h>

using namespace ula;
using namespace std;
using namespace My_functions;

void Block_Reader_c(fstream& file,RealVector& Rphi){
        int j=0;
	char B[64],R[32],Im[32],X[8];
	const char a[2]="";

	  if(!file.is_open())  //Check if file is not open
	    perror("Error opening file");
  
	  else
	    cout<<"Start Read"<<endl;
	
	  while(!file.eof()){

	    file.getline(B,64); 
	    if(file.fail()){   //If failbit flag is up then break the while loop.
	      perror("Error while reading file");    
	      break;
	           }
	  else{
	   if(strcmp(B,a)==0){ // If we get an empty line then break the while loop.
	    cout<<"Block Ended: Size "<<j<<endl;
	    break;
	       }
	
	   else{
	    sscanf(B,"%s	%s	%s",X,R,Im);   //scan the extracted line
	    Rphi(j) = atof(X);
	    /*cout<<X<<"	"<<real(Rphi(j))<<"	"<<imag(Rphi(j))<<endl;*/
	    j++;
	       }
	        }
	         }
     }

void Block_Reader(fstream& file,ComplexVector& Rphi){
        int j=0;
	char B[64],R[32],Im[32],X[8];
	const char a[2]="";

	  if(!file.is_open())  //Check if file is not open
	    perror("Error opening file");
  
	  else
	    cout<<"Start Read"<<endl;
	
	  while(!file.eof()){

	    file.getline(B,64); 
	    if(file.fail()){   //If failbit flag is up then break the while loop.
	      perror("Error while reading file");    
	      break;
	           }
	  else{
	   if(strcmp(B,a)==0){ // If we get an empty line then break the while loop.
	    cout<<"Block Ended: Size "<<j<<endl;
	    break;
	       }
	
	   else{
	    sscanf(B,"%s	%s	%s",X,R,Im);   //scan the extracted line
	    Rphi(j) = Complex( atof( R ),atof( Im ) );
	    /*cout<<X<<"	"<<real(Rphi(j))<<"	"<<imag(Rphi(j))<<endl;*/
	    j++;
	       }
	        }
	         }
     }



int main(){

  fstream fileA,fileB,fileC,Fout;
   fileA.open("Datos/GP_GS_dp_10.20.dat",	ios::in); //Ground states
   fileB.open("Datos_5PS/GP_GS_data_dp_10.20.dat",	ios::in); //Time evolulion
   fileC.open("Datos_5PS/GP_GS_trap_dp_10.20.dat",	ios::in); //trapp in time
   Fout.open("Datos/GP_GS_fid_10.20.dat",	ios::out); //fidelity

 double PaPb;
 ComplexVector Pa(201),Pb(201);
 RealVector Pc(201);

 while(!fileA.eof()){
   
   Block_Reader_c( fileC,Pc );
   Block_Reader( fileA,Pa );
   Block_Reader( fileB,Pb );

      PaPb = real(conj(inner_prod( Pa,Pb ))*inner_prod( Pa,Pb ));

      Fout<<Pc(1)<<"	"<<PaPb<<endl;

	}

//::::::::::::::::::::::::::::::::::
//:::::::::::End_main:::::::::::::::
//::::::::::::::::::::::::::::::::::

fileA.close();
fileB.close();
Fout.close();
	}
