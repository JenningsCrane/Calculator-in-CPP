#include "calcParser.h"

#include <cstring>
#include <stdexcept>

namespace jen {
CalcExpression CalcParser::Parse(const char* str) {
  CalcExpression outList;
  CalcExpression tmpList;

  bool nextNumber = true;
  bool nextUnary = true;
  bool nextOperand = true;
  bool nextSkoba = true;

  for (const char* str_p = str; *str_p != '\0'; ++str_p) {
    char symbol = *str_p;

    if (symbol == ' ') continue;

    if (symbol >= '0' && symbol <= '9' && nextNumber) {
      int len = 0;
      double num = 0.0;
      sscanf(str_p, "%lf%n", &num, &len);
      str_p += len - 1;
      nextNumber = false;
      nextUnary = false;
      nextOperand = true;
      nextSkoba = true;

      outList.PushBack(CalcLeksem(num));
    }

    else if (symbol == 'x' && nextNumber) {
      outList.PushBack(CalcLeksem(true));
      nextNumber = false;
      nextUnary = false;
      nextOperand = true;
      nextSkoba = true;
    }

    else if (CalcOperator(symbol).IsOperand() && nextOperand) {
      AddOperand(outList, tmpList, CalcOperator(symbol), nextUnary);
      nextUnary = true;
      nextNumber = true;
      nextSkoba = false;
      if (symbol == CalcOperator::PLUS || symbol == CalcOperator::MINUS)
        nextOperand = false;
    }

    else if (symbol >= 'a' && symbol <= 'z') {
      CheckFunction(tmpList, &str_p);
      str_p -= 1;
      nextNumber = false;
      nextUnary = false;
      nextOperand = true;
      nextSkoba = true;
    }

    else if (symbol == '(') {
      CalcOperator op = '(';
      tmpList.PushBack(CalcLeksem(op));
      nextNumber = true;
      nextUnary = true;
      nextOperand = true;
      nextSkoba = true;
    }

    else if (symbol == ')' && nextSkoba) {
      while (!tmpList.IsEmpty()) {
        CalcLeksem lek = tmpList.LastNode();
        tmpList.PopBack();
        outList.PushBack(lek);
        if (lek.symbol == '(') break;
      }

      nextNumber = false;
      nextUnary = false;
      nextOperand = true;
      nextSkoba = true;
    }

    else
      throw std::logic_error("SEGAMAN!");
  }

  while (!tmpList.IsEmpty()) {
    CalcLeksem lek = tmpList.LastNode();
    tmpList.PopBack();
    outList.PushBack(lek);
    if (lek.symbol == '(') break;
  }

  return outList;
}

void CalcParser::CheckFunction(CalcExpression& tmpList, const char** str) {
  CalcOperator op = CalcOperator::SYMBOL_NONE;
  const char* tmp = *str;
  if (CmpFunc(tmp, "sin(")) {
    op = CalcOperator::SIN;
    tmpList.PushBack(CalcLeksem(op));
    tmp += 3;
  }

  else if (CmpFunc(tmp, "cos(")) {
    op = CalcOperator::COS;
    tmpList.PushBack(CalcLeksem(op));
    tmp += 3;
  }

  else if (CmpFunc(tmp, "tan(")) {
    op = CalcOperator::TAN;
    tmpList.PushBack(CalcLeksem(op));
    tmp += 3;
  }

  else if (CmpFunc(tmp, "sqrt(")) {
    op = CalcOperator::SQRT;
    tmpList.PushBack(CalcLeksem(op));
    tmp += 4;
  }

  else if (CmpFunc(tmp, "ln(")) {
    op = CalcOperator::LN;
    tmpList.PushBack(CalcLeksem(op));
    tmp += 2;
  }

  else if (CmpFunc(tmp, "log(")) {
    op = CalcOperator::LOG;
    tmpList.PushBack(CalcLeksem(op));
    tmp += 3;
  }

  else if (CmpFunc(tmp, "asin(")) {
    op = CalcOperator::ASIN;
    tmpList.PushBack(CalcLeksem(op));
    tmp += 4;
  }

  else if (CmpFunc(tmp, "acos(")) {
    op = CalcOperator::ACOS;
    tmpList.PushBack(CalcLeksem(op));
    tmp += 4;
  }

  else if (CmpFunc(tmp, "atan(")) {
    op = CalcOperator::ATAN;
    tmpList.PushBack(CalcLeksem(op));
    tmp += 4;
  }

  else
    throw std::logic_error("SEGAMAN!");

  *str = tmp;
}

bool CalcParser::CmpFunc(const char* func, const char* orig) {
  int len = strlen(orig);
  int res = true;

  for (int i = 0; i < len && res; ++i) {
    if (func[i] != orig[i]) res = false;
  }
  return res;
}

void CalcParser::AddOperand(CalcExpression& outList, CalcExpression& tmpList,
                            CalcLeksem symbol, bool nextUnary) {
  if (nextUnary && symbol.symbol == CalcOperator::PLUS)
    symbol.symbol = CalcOperator(CalcOperator::UNARY_PLUS);
  else if (nextUnary && symbol.symbol == CalcOperator::MINUS)
    symbol.symbol = CalcOperator(CalcOperator::UNARY_MINUS);

  while (!tmpList.IsEmpty()) {
    CalcLeksem lek = tmpList.LastNode();
    if (lek.symbol != '(' &&
        (lek.symbol.GetRank() > symbol.symbol.GetRank() ||
         (lek.symbol != CalcOperator::POW &&
          lek.symbol.GetRank() == symbol.symbol.GetRank()))) {
      tmpList.PopBack();
      outList.PushBack(lek);
    } else
      break;
  }

  tmpList.PushBack(CalcLeksem(symbol));
}
}  // namespace jen
