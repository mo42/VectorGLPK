#include <VectorGLPK.h>

VectorGLPK::VectorGLPK() {
  linear_program = glp_create_prob();
  glp_set_obj_dir(linear_program, GLP_MAX);
  // Set the constant term
  glp_set_obj_coef(linear_program, 0, 0.0);
  // Disable terminal output
  glp_term_out(GLP_OFF);
  rows = 0;
  columns = 0;
  indices.push_back(0);
  isIntegerLinearProgram = false;
}

VectorGLPK::~VectorGLPK() {
  glp_delete_prob(linear_program);
  glp_free_env();
}

void VectorGLPK::addObjective(Vector& c) {
  glp_add_cols(linear_program, c.size());
  for(size_t i = 0; i < c.size(); ++i) {
    glp_set_col_bnds(linear_program, i + 1, GLP_LO, 0.0, 0.0);
    glp_set_obj_coef(linear_program, i + 1, c[i]);
    // Add increasing number to the indices
    indices.push_back(indices[indices.size() - 1] + 1);
    ++columns;
  }
}
 
void VectorGLPK::addConstraint(Vector& m, double b) {
  if(m.size() != columns)
    throw std::invalid_argument("Dimensions do not match!");
  glp_add_rows(linear_program, 1);
  ++rows;
  m.insert(m.begin(), 0.0);
  // Add right-hand side
  glp_set_row_bnds(linear_program, rows, GLP_UP, 0.0, b);
  // Add left-hand side
  glp_set_mat_row(linear_program, rows, m.size() - 1, indices.data(), m.data());
}

void VectorGLPK::setObjectiveMaximize(const bool objective) {
  if(objective) {
    glp_set_obj_dir(linear_program, GLP_MAX);
  } else {
    glp_set_obj_dir(linear_program, GLP_MIN);
  }
}

void VectorGLPK::solve(Vector& x) {
  if(!isIntegerLinearProgram) {
    glp_simplex(linear_program, NULL);
    x.clear();
    for(size_t i = 1; i <= columns; ++i) {
      x.push_back(glp_get_col_prim(linear_program, i));
    }
  } else {
    glp_iocp parameter;
    glp_init_iocp(&parameter);
    parameter.presolve = GLP_ON;
    glp_intopt(linear_program, &parameter);
    x.clear();
    for(size_t i = 1; i <= columns; ++i) {
      x.push_back(glp_mip_col_val(linear_program, i));
    }
  }
}

bool VectorGLPK::hasSolution(void) {
  int status = glp_get_status(linear_program);
  if(status == GLP_OPT) {
    return true;
  } else {
    return false;
  }
}

void VectorGLPK::setIntegerLinearProgram(void) {
  for(size_t i = 1; i <= columns; ++i) {
    glp_set_col_kind(linear_program, i, GLP_IV);
  }
  isIntegerLinearProgram = true;
}
