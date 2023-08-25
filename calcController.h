#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include "calcModel.h"

namespace jen {

class CalcController {
 public:
  CalcController(CalcModel* m) : model(m) {}

  double ComputeExpression(const char* src, double x);
  void CalculationGraph(const char* str, double* x, double* y, size_t len);

 private:
  CalcModel* model;
};

}  // namespace jen

#endif  // CALCCONTROLLER_H
