#include "calcModel.h"

namespace jen {

double CalcModel::ComputeLine(const char* src, double x) {
  return parser.Parse(src).Calculate(x);
}
void CalcModel::ComputeGraph(const char* str, double* x, double* y,
                             size_t len) {
  CalcExpression pars = parser.Parse(str);
  for (int i = 0; (i < (int)len); ++i) {
    y[i] = pars.Calculate(x[i]);
  }
}

}  // namespace s21
