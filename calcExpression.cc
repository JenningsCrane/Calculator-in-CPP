#include "calcExpression.h"

namespace jen {
double CalcExpression::Calculate(double x) {
  result_.clear();

  size_t len = nodes_.size();

  for (const CalcLeksem& lek : nodes_) {
    if (lek.IsNumber() || lek.isX) ++len;
  }

  result_.reserve(len);

  int i = 0;

  for (const CalcLeksem& lek : nodes_) {
    if (lek.IsNumber()) {
      result_[i] = lek.number;
      ++i;
    } else if (lek.isX) {
      result_[i] = x;
      ++i;
    } else {
      if (lek.symbol == CalcOperator::PLUS && len >= 2) {
        result_[i - 2] = result_[i - 2] + result_[i - 1];
        --i;
      }

      else if (lek.symbol == CalcOperator::MINUS && len >= 2) {
        result_[i - 2] = result_[i - 2] - result_[i - 1];
        --i;
      }

      else if (lek.symbol == CalcOperator::UNARY_MINUS && len >= 1) {
        result_[i - 1] *= -1;
      }

      else if (lek.symbol == CalcOperator::UNARY_PLUS && len >= 1) {
        continue;
      }

      else if (lek.symbol == CalcOperator::MULT && len >= 2) {
        result_[i - 2] = result_[i - 2] * result_[i - 1];
        --i;
      }

      else if (lek.symbol == CalcOperator::DIV && len >= 2) {
        result_[i - 2] = result_[i - 2] / result_[i - 1];
        --i;
      }

      else if (lek.symbol == CalcOperator::POW && len >= 2) {
        result_[i - 2] = pow(result_[i - 2], result_[i - 1]);
        --i;
      }

      else if (lek.symbol == CalcOperator::MOD && len >= 2) {
        result_[i - 2] = fmod(result_[i - 2], result_[i - 1]);
        --i;
      }

      else if (lek.symbol == CalcOperator::SIN && len >= 1) {
        result_[i - 1] = sin(result_[i - 1]);
      }

      else if (lek.symbol == CalcOperator::COS && len >= 1) {
        result_[i - 1] = cos(result_[i - 1]);
      }

      else if (lek.symbol == CalcOperator::TAN && len >= 1) {
        result_[i - 1] = tan(result_[i - 1]);
      }

      else if (lek.symbol == CalcOperator::SQRT && len >= 1) {
        result_[i - 1] = sqrt(result_[i - 1]);
      }

      else if (lek.symbol == CalcOperator::LN && len >= 1) {
        result_[i - 1] = log(result_[i - 1]);
      }

      else if (lek.symbol == CalcOperator::LOG && len >= 1) {
        result_[i - 1] = log10(result_[i - 1]);
      }

      else if (lek.symbol == CalcOperator::ASIN && len >= 1) {
        result_[i - 1] = asin(result_[i - 1]);
      }

      else if (lek.symbol == CalcOperator::ACOS && len >= 1) {
        result_[i - 1] = acos(result_[i - 1]);
      }

      else if (lek.symbol == CalcOperator::ATAN && len >= 1) {
        result_[i - 1] = atan(result_[i - 1]);
      }
    }
  }

  if (i != 1) throw std::logic_error("SegMANtation fault in calc!");
  return result_[0];
}

}  // namespace jen
