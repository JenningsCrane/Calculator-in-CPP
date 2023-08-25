#ifndef CALCMODEL_H
#define CALCMODEL_H

#include "calcExpression.h"
#include "calcParser.h"

namespace jen {

class CalcModel {
 public:
  double ComputeLine(const char* src, double x);
  void ComputeGraph(const char* str, double* x, double* y, size_t len);

 private:
  CalcParser parser;
};
}  // namespace jen

#endif  // CALCMODEL_H
