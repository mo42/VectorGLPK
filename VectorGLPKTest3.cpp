#include <iostream>
#include <vector>

#include <VectorGLPK.h>

int main(int argc, char* argv[]) {
  VectorGLPK e;
  Vector v = {0.0, 1.0};
  e.addObjective(v);
  v = {-1.0, 1.0};
  e.addConstraint(v, 1.0);
  v = {3.0, 2.0};
  e.addConstraint(v, 12.0);
  v = {2.0, 3.0};
  e.addConstraint(v, 12.0);
  e.setIntegerLinearProgram();
  e.solve(v);
  std::cout << v[0] << " " << v[1] << std::endl;
  std::cout << e.getStatus() << std::endl;
  return 0;
}
