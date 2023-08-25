#include "symbolStruct.h"

namespace jen {
int CalcOperator::GetRank() {
  int rank = 0;
  switch (symbol) {
    case PLUS:
    case MINUS:
      rank = 1;
      break;
    case MULT:
    case DIV:
    case MOD:
      rank = 2;
      break;
    case UNARY_MINUS:
    case UNARY_PLUS:
      rank = 3;
      break;
    case POW:
      rank = 4;
      break;
    case ASIN:
    case ACOS:
    case ATAN:
    case SIN:
    case COS:
    case TAN:
    case SQRT:
    case LN:
    case LOG:
      rank = 5;
      break;
  }
  return rank;
}

bool CalcOperator::IsOperand() {
  bool rez = false;
  switch (symbol) {
    case PLUS:
    case MINUS:
    case MULT:
    case DIV:
    case POW:
    case MOD:
      rez = true;
      break;
  }
  return rez;
}
}  // namespace jen
