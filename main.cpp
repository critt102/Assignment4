/** main.cpp
 *Main file for registrar's office simulation
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 4
 */
#include "registrar.h"
using namespace std;

/**
 * main method, implemetns and runs registrar.h
 * @param  argc numer of arguments
 * @param  argv command lines arguments
 * @return 0 to end main call
 */
int main(int argc, char**argv){
  //if there is no command line argument
  if(argv[1]==NULL){
    cout<<"Please Enter a valid file name"<<endl;
  }
  //take in file name from command line
  else{
    Registrar registrar1(argv[1]);
    registrar1.runSim();
    registrar1.calc();
  }
  return 0;
}
