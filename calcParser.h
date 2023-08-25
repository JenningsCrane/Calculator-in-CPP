#ifndef CALCPARSER_H
#define CALCPARSER_H

#include <string>

#include "calcExpression.h"

namespace jen {
class CalcParser {
 public:
  CalcParser() {}
  ~CalcParser() {}

  CalcExpression Parse(const char* str);
  void CheckFunction(CalcExpression& tmpList, const char** str);
  bool CmpFunc(const char* func, const char* orig);
  void AddOperand(CalcExpression& outList, CalcExpression& tmpList,
                  CalcLeksem symbol, bool nextUnary);
};
}  // namespace jen
#endif  // CALCPARSER_H
