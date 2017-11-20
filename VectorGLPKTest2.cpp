#include <iostream>
#include <vector>

#include <VectorGLPK.h>

int main(int argc, char* argv[]) {
  VectorGLPK e;
  Vector v = {1.0, 2.0, 3.0};
  e.addObjective(v);
  v = {1.0, 1.0, -1.0};
  e.addConstraint(v, 1.0);
  v = {-1.0, -1.0, 1.0};
  e.addConstraint(v, -1.0);
  v = {2.0, -1.0, -2.0};
  e.addConstraint(v, 5.0);
  v = {1.0, -1.0, 0.0};
  e.addConstraint(v, 4.0);
  v = {0.0, 1.0, 1.0};
  e.addConstraint(v, 5.0);
  e.solve(v);
  std::cout << v[0] << " " << v[1] << " " << v[2] << std::endl;
  std::cout << e.hasSolution() << std::endl;
  return 0;
}
