#ifndef VECTORGLPK_H
#define VECTORGLPK_H

#include <string>
#include <stdexcept>
#include <vector>

#include <glpk.h>

typedef std::vector<std::vector<double>> Matrix;
typedef std::vector<double> Vector;

/**
 * This class represents an instance of a primal linear program of the form:
 * max c^Tx subject to Mx <= b and x >= 0.
 *
 * Since GLPK uses one-based numbering the vectors passed to an object of this
 * class might change.
 */
class VectorGLPK {
private:
  glp_prob* linear_program;
  size_t rows;
  size_t columns;
  // Array that stores indices
  std::vector<int> indices;
public:
  /**
   * Create an instance of a linear programming problem.
   */
  VectorGLPK();

  /**
   * Delete a linear programming instance.
   */
  ~VectorGLPK();

  /**
   * Add an objective vector to the instance.
   *
   * Let c' be the previous objective vector. After calling this function the
   * new vector looks like [c', c], where c is the argument. I. e. the
   * argument gets appended to the problem. Intuitively, this adds more
   * coefficients to the objective function.
   *
   * c: the vector objective coefficients
   */
  void addObjective(Vector& c);

  /**
   * Add a constraint to the instance.
   *
   * Add a constraint of the form m_1 * x_1, ..., m_n * x_n <= b to the linear
   * program.
   *
   * m: vector consisting of the left-hand side coefficients
   * b: right-hand side constraint
   * throws: invalid_argument exception if the size of m does not match the
   *   number of columns added so far.
   */
  void addConstraint(Vector& m, double b);

  /**
   * Specify if it is a maximization or a minimization problem.
   *
   * By default it a maximization problem.
   *
   * object: true: maximization; false minimization
   */
  void setObjectiveMaximize(const bool objective);

  /**
   * Solve the linear problem and return the solution (usually denoted as x).
   */
  void solve(Vector& x);

  /**
   * Return true if the problem has an optimal solution.
   *
   * return:
   */
  bool hasSolution(void);
};
#endif /* VECTORGLPK_H */
