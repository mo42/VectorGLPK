# VectorGLPK
Use [GLPK](https://www.gnu.org/software/glpk/) with
[std::vector](http://en.cppreference.com/w/cpp/container/vector).
## Feature
Simply pass a vector object to the wrapper class without looking at indexing.
## Example
```c++
VectorGLPK e;
Vector v = {0.6, 0.5};
e.addObjective(v);
v = {1.0, 2.0};
e.addConstraint(v, 1.0);
v = {3.0, 1.0};
e.addConstraint(v, 2.0);
e.solve(v);
```
