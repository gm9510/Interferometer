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
#include <omp.h>

using namespace ula;
using namespace std;

#define pi 3.14159265358979323846

namespace My_functions{

Complex I(0,1);

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
ComplexVector Gaussian(int n,double dx, double xi,Real Sx=0.75/*Spread of the Gaussian*/,Real xm=4./*Maximun of the gaussian*/){
  ComplexVector F(n);
  Real A=1/(Sx*sqrt(2*pi));
  for(int i=0; i<n; i++){
    F(i)=A*exp(-pow((xi+i*dx)-xm,2)/(2*Sx*Sx));}
  return F;
}

ComplexVector Gaussian(int n,double dx,RealVector X,Real Sx=0.75/*Spread of the Gaussian*/,Real xm=4./*Maximun of the gaussian*/){
  ComplexVector F(n);
  Real A=1/(Sx*sqrt(2*pi));
  for(int i=0; i<n; i++){
    F(i)=A*exp(-pow(X(i)-xm,2)/(2*Sx*Sx));}
  return F;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------


RealVector Trap_HD(int n, double dx, double t, double xi, double H=4){
 RealVector V(n);
 double al=0.85, b=15,om=1.;
 
 for(int i=0; i<n; i++){
   V(i)=al*(xi+i*dx)*(xi+i*dx)+b*sqrt(1-pow((t-20)/15,2))*cos(om*(xi+i*dx))*cos(om*(xi+i*dx))-H*exp(-pow(xi+i*dx-2.530,2)-pow((t-20)/5,2));
 }
 return V;
}

RealVector Trap_HE(int n, double dx, double t, double xi, double H=4, double sigma=25){
 RealVector V(n);
 double al=0.85, b=15,om=1.;
 
 
 for(int i=0; i<n; i++){
   V(i)=al*(xi+i*dx)*(xi+i*dx)+b*exp(-pow(t-20,2)/sigma)*cos(om*(xi+i*dx))*cos(om*(xi+i*dx))-H*exp(-pow(xi+i*dx-2.530,2)-pow((t-20)/5,2));
 }
 return V;
}


//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

RealVector Trap_HC(int n, double dx, double t, double xi){
 RealVector V(n);
 double al=0.85, b=1.5,om=1.;
 
 for(int i=0; i<n; i++){
   V(i)=al*(xi+i*dx)*(xi+i*dx)+b*t*cos(om*(xi+i*dx))*cos(om*(xi+i*dx));
 }
 return V;
}

RealVector Trap_HC_PS( int n, double dx, double t, double xi, double H=4 ){
 RealVector V(n);
 double al=0.85, b=1.5,om=1.;
 
 for(int i=0; i<n; i++){
   V(i)=al*(xi+i*dx)*(xi+i*dx)+b*10*cos(om*(xi+i*dx))*cos(om*(xi+i*dx))-H*exp(-pow(xi+i*dx-2.530,2)-pow((t-20)/5,2));
 }
 return V;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
RealVector TrapH(int n, double dx, double t, double xi,double A=1.,double a=4.){
 RealVector V(n);
 
 	for(int i=0; i<n; i++){
 	V(i)=(A*t+a*(1.-t))*pow(pow(fabs(xi+i*dx),1+t)-t*(a/A),2);
  }
 return V;
 }

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

RealVector BeamSpliter(int n, double dx, double t, double xi,double A=15/8){
  RealVector V(n);
  
  	for(int i=0; i<n; i++){
  	V(i)=A*pow((xi+i*dx)-sqrt(4-4*pow(t-15,2)/100),2)*pow((xi+i*dx)+sqrt(4-4*pow(t-15,2)/100),2);
  	}
  return V;
 }
 //------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
RealVector Asymetric(int n, double dx, double t, double xi,double A=15/8){//Diferencias de Caminos
  RealVector V(n);
  
  for(int i=0; i<n; i++){
  if(xi+i*dx<=0)
  V(i)=A*pow((xi+i*dx)-2,2)*pow((xi+i*dx)+2,2);
  else if(xi+i*dx>0 && xi+i*dx<2*exp(-pow(t-20,2)/(4.)))
  V(i)=30;
  else
  V(i)=A*pow((xi+i*dx)-2*exp(-pow(t-20,2)/(4.))-2,2)*pow((xi+i*dx)-2*exp(-pow(t-20,2)/(4.))+2,2);
  }
  return V;
}
 //------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
RealVector Symetric(int n, double dx, double t, double xi,double A=15/8){//simetrica
  RealVector V(n);

  for(int i=0; i<n; i++){
  if(xi+i*dx<=0)
  V(i)=A*pow((xi+i*dx)-2,2)*pow((xi+i*dx)+2,2);
  else
  V(i)=A*pow((xi+i*dx)-2,2)*pow((xi+i*dx)+2,2);
  }
  return V;
}
 //------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
RealVector Delayer(int n, double dx, double t, double xi,double A=15/8){
  RealVector V(n);

  for(int i=0; i<n; i++){
  if(xi+i*dx<=0)
  V(i)=A*pow((xi+i*dx)-2,2)*pow((xi+i*dx)+2,2);
  else
  V(i)=A*pow((xi+i*dx)+2,2)*((xi+i*dx)-0.5*exp(-pow(t-20,2)/(4.))-2)*((xi+i*dx)+0.5*exp(-pow(t-20,2)/(4.))-2);
  }
  return V;
}
 //------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
RealVector Recombiner(int n, double dx, double t, double xi,double A=15/8){
  RealVector V(n);

  for(int i=0; i<n; i++){
  V(i)=A*pow((xi+i*dx)-sqrt(4-4*pow(t-25,2)/100),2)*pow((xi+i*dx)+sqrt(4-4*pow(t-25,2)/100),2);
  }
  return V;
}
 //------------------------------------------------------------------------------------------------
//----------------Finete-Diference-Method-----------------------------------------------------
/*
void F(int n, double dx,ComplexVector &Phi,ComplexVector &dPhi,RealVector V,double g,double e){

  Complex cfL=0., cfR=0.; //Boundary conditions

  dPhi(0)=-I*( -(e*0.5/(dx*dx))*(cfL-2.*Phi(0)+Phi(1)) + 0.5*V(0)*Phi(0) + g*conj(Phi(0))*Phi(0)*Phi(0) );

  for(int i=1; i<n-1; i++){//Metodo de Diferencias Finitas
    dPhi(i)=-I*( -(e*0.5/(dx*dx))*(Phi(i-1)-2.*Phi(i)+Phi(i+1)) + 0.5*V(i)*Phi(i) + g*conj(Phi(i))*Phi(i)*Phi(i) );
                           }
  dPhi(n-1)=-I*( -(e*0.5/(dx*dx))*(Phi(n-2)-2.*Phi(n-1)+cfR) + 0.5*V(n-1)*Phi(n-1) + g*conj(Phi(n-1))*Phi(n-1)*Phi(n-1) );
 
}

void F_IT(int n, double dx,RealVector Phi,RealVector &dPhi,RealVector V,double g,double e){

  Real cfL=0., cfR=0.; //Boundary conditions

  dPhi(0)= (e*0.5/(dx*dx))*(cfL-2.*Phi(0)+Phi(1)) - 0.5*V(0)*Phi(0) - g*pow(Phi(0),3) ;

  for(int i=1; i<n-1; i++){//Metodo de Diferencias Finitas
    dPhi(i)= (e*0.5/(dx*dx))*(Phi(i-1)-2.*Phi(i)+Phi(i+1)) - 0.5*V(i)*Phi(i) - g*pow(Phi(i),3) ;
                           }
  dPhi(n-1)= (e*0.5/(dx*dx))*(Phi(n-2)-2.*Phi(n-1)+cfR) - 0.5*V(n-1)*Phi(n-1) - g*pow(Phi(n-1),3);
 
}
*/
 
 //----Five-Point-Stencil-Method---------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void F(int n, double dx,ComplexVector &Phi,ComplexVector &dPhi,RealVector V,double g,double e){

  Complex cfL1=0.,cfL2=0., cfR1=0., cfR2=0.; //Boundary conditions

  dPhi(0) = -I*( -(e*0.5/(12*dx*dx))*(16.*cfL1-30.*Phi(0)+16.*Phi(1)-Phi(2)-cfL2) + 0.5*V(0)*Phi(0) + g*conj(Phi(0))*Phi(0)*Phi(0) );

  dPhi(1) = -I*( -(e*0.5/(12*dx*dx))*(16.*Phi(0)-30.*Phi(1)+16.*Phi(2)-Phi(3)-cfL1) + 0.5*V(1)*Phi(1) +g*conj(Phi(1))*Phi(1)*Phi(1) );

  for(int i=2; i<n-2; i++){//Metodo de Diferencias Finitas
    dPhi(i) = -I*( -(e*0.5/(12*dx*dx))*(16.*Phi(i-1)-30.*Phi(i)+16.*Phi(i+1)-Phi(i+2)-Phi(i-2)) + 0.5*V(i)*Phi(i) + g*conj(Phi(i))*Phi(i)*Phi(i) );
                           }
  dPhi(n-2) = -I*( -(e*0.5/(12*dx*dx))*(16.*Phi(n-3)-30.*Phi(n-2)+16.*Phi(n-1)-cfR1-Phi(n-4)) + 0.5*V(n-2)*Phi(n-2) + g*conj(Phi(n-2))*Phi(n-2)*Phi(n-2) );

  dPhi(n-1) = -I*( -(e*0.5/(12*dx*dx))*(16.*Phi(n-2)-30.*Phi(n-1)+16.*cfR1-cfR2-Phi(n-3)) + 0.5*V(n-1)*Phi(n-1) + g*conj(Phi(n-1))*Phi(n-1)*Phi(n-1) );

}

void F_IT(int n, double dx,RealVector Phi,RealVector &dPhi,RealVector V,double g,double e){

  double cfL1=0.,cfL2=0., cfR1=0., cfR2=0.; //Boundary conditions

  dPhi(0) = ( (e*0.5/(12*dx*dx))*(16.*cfL1-30.*Phi(0)+16.*Phi(1)-Phi(2)-cfL2) - 0.5*V(0)*Phi(0) - g*conj(Phi(0))*Phi(0)*Phi(0) );

  dPhi(1) = ( (e*0.5/(12*dx*dx))*(16.*Phi(0)-30.*Phi(1)+16.*Phi(2)-Phi(3)-cfL1) - 0.5*V(1)*Phi(1) - g*conj(Phi(1))*Phi(1)*Phi(1) );

  for(int i=2; i<n-2; i++){
    dPhi(i) = ( (e*0.5/(12*dx*dx))*(16.*Phi(i-1)-30.*Phi(i)+16.*Phi(i+1)-Phi(i+2)-Phi(i-2)) - 0.5*V(i)*Phi(i) - g*conj(Phi(i))*Phi(i)*Phi(i) );
                           }
  dPhi(n-2) = ( (e*0.5/(12*dx*dx))*(16.*Phi(n-3)-30.*Phi(n-2)+16.*Phi(n-1)-cfR1-Phi(n-4)) - 0.5*V(n-2)*Phi(n-2) - g*conj(Phi(n-2))*Phi(n-2)*Phi(n-2) );

  dPhi(n-1) = ( (e*0.5/(12*dx*dx))*(16.*Phi(n-2)-30.*Phi(n-1)+16.*cfR1-cfR2-Phi(n-3)) - 0.5*V(n-1)*Phi(n-1) - g*conj(Phi(n-1))*Phi(n-1)*Phi(n-1) );
 
}
 //------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void GP_RK(int n,double dx,double dt,ComplexVector &Phi,RealVector V,double g,double e){
  ComplexVector k1(n), k2(n), k3(n), k4(n),Phi_(n);

  Phi_=Phi;
    F(n,dx,Phi_,k1,V,g,e);
    
    Phi_=Phi+0.5*dt*k1;
    F(n,dx,Phi_,k2,V,g,e);

    Phi_=Phi+0.5*dt*k2;
    F(n,dx,Phi_,k3,V,g,e);

    Phi_=Phi+dt*k3;
    F(n,dx,Phi_,k4,V,g,e);
 
 Phi+=dt*(k1+2.*k2+2.*k3+k4)/6.;//promedio de pendientes
}

 //------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void GP_IT(int n,double dx,double dt,RealVector &Phi,RealVector V,double g,double e){
  RealVector k1(n), k2(n), k3(n), k4(n),Phi_(n);
  Phi_=Phi;
    F_IT(n,dx,Phi_,k1,V,g,e);
    
    Phi_=Phi+0.5*dt*k1;
    F_IT(n,dx,Phi_,k2,V,g,e);

    Phi_=Phi+0.5*dt*k2;
    F_IT(n,dx,Phi_,k3,V,g,e);

    Phi_=Phi+dt*k3;
    F_IT(n,dx,Phi_,k4,V,g,e);
 
 Phi+=dt*(k1+2.*k2+2.*k3+k4)/6.;//promedio de pendientes
 }


}//--------------end-myspace-----------------------------------------------
