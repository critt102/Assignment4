#include "registrar.h"
using namespace std;

int main(int argc, char**argv){
  Registrar registrar1(argv[1]);
  registrar1.runSim();
  registrar1.calc();
  return 0;
}
