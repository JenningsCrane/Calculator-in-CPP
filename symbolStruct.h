#ifndef SYMBOLSTRUCT_H
#define SYMBOLSTRUCT_H

namespace jen {
struct CalcOperator {
  enum Operators {

    PLUS = '+',
    MINUS = '-',
    MULT = '*',
    DIV = '/',
    MOD = '%',
    POW = '^',

    UNARY_MINUS = '~',
    UNARY_PLUS = '#',

    SIN = 's',
    COS = 'c',
    TAN = 't',
    SQRT = 'q',
    LN = 'l',
    LOG = 'g',
    ASIN = '1',
    ACOS = '2',
    ATAN = '3',

    SYMBOL_NONE = '\0',

  };

  CalcOperator() {}
  CalcOperator(char symbol) : symbol(symbol) {}
  bool operator==(char symbol) const { return this->symbol == symbol; }
  bool operator!=(char symbol) const { return this->symbol != symbol; }

  int GetRank();
  bool IsOperand();

  char symbol = Operators::SYMBOL_NONE;
};

struct CalcLeksem {
  CalcLeksem() {}
  CalcLeksem(double number) : number(number) {}
  CalcLeksem(CalcOperator symbol) : symbol(symbol) {}
  CalcLeksem(bool isX) : isX(isX) {}

  bool IsNumber() const { return !IsSymbol() && !isX; }
  bool IsSymbol() const { return symbol != CalcOperator::SYMBOL_NONE; }

  double number = 0.0;
  CalcOperator symbol = CalcOperator::SYMBOL_NONE;
  bool isX = false;
};
}  // namespace jen

#endif  // SYMBOLSTRUCT_H
