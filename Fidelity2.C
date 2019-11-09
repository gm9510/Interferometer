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

  string dir  ("Datos_HC/");
  string name ("GP_GS_"), ext(".dat");
  string grst ("grst_"), trap("trap_"), data("data_"), fdty("fidelity"); 

 double Ddeep=;
#pragma omp parallel for private( fileA,fileB,fileC,Fout )
  for(int deep=0.; deep<=int(20./Ddeep); deep++){


#pragma omp critical (cout)
{
cout<<omp_get_thread_num()<<"	"<<deep*Ddeep<<endl;
}

  stringstream dp;
  dp << fixed << setprecision(1) << deep*Ddeep;

//::::::::::::::::::::::::::::::::::::::::::::::::::::
//::::::::::::::::::::::::::::::::::::::::::::::::::::
//::::::::::::::::::::::::::::::::::::::::::::::::::::



   fileA.open( dir + name + gsrt + "dp_" + dp.str() + ext , fstream::in);
   fileB.open( dir + name + data + "dp_" + dp.str() + ext , fstream::in);
   fileC.open( dir + name + trap + "dp_" + dp.str() + ext , fstream::in);
   Fout.open ( dir + name + fdty + "dp_" + dp,srt() + ext , fstream::out);

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

//::::::::::::Close_files:::::::::::

fileA.close();
fileB.close();
fileC.close();
Fout.close();
	}


//::::::::::::::::::::::::::::::::::
//:::::::::::End_main:::::::::::::::
//::::::::::::::::::::::::::::::::::

}




