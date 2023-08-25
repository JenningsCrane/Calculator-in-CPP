#include "calcController.h"

namespace jen {
double CalcController::ComputeExpression(const char* src, double x) {
  return model->ComputeLine(src, x);
}
void CalcController::CalculationGraph(const char* str, double* x, double* y,
                                      size_t len) {
  model->ComputeGraph(str, x, y, len);
}
}  // namespace jen
