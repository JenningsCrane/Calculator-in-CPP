#ifndef CALCEXPRESSION_H
#define CALCEXPRESSION_H

#include <cmath>
#include <stdexcept>
#include <vector>

#include "symbolStruct.h"

namespace jen {
class CalcExpression {
 public:
  CalcExpression() {}
  ~CalcExpression() {}

  void PushBack(const CalcLeksem& node) { nodes_.push_back(node); }
  void PopBack() { nodes_.pop_back(); }
  bool IsEmpty() { return nodes_.empty(); }
  CalcLeksem& LastNode() { return nodes_.back(); }
  const std::vector<CalcLeksem>& GetNodes() const { return nodes_; }

  double Calculate(double x);

 private:
  std::vector<double> result_;
  std::vector<CalcLeksem> nodes_;
};
}  // namespace jen

#endif  // CALCEXPRESSION_H
