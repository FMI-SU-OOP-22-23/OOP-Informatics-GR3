#include <iostream>
#include <numeric>

/*
 * Задача 1
 */

// can we optimize this one?
int findLcm(int a, int b) {
  int max = (a > b) ? a : b;
  while (true) {
    if (max % a == 0 && max % b == 0) {
      return max;
    }
    ++max;
  }
  return max;
}

class Fraction {
 public:
  Fraction(int numerator = 0, int denominator = 1)
      : _numerator(numerator), _denominator(denominator) {
    if (denominator == 0) {
      // the right thing to do is to throw an exception
      // throw std::invalid_argument("Denominator cannot be zero.");

      std::cerr << "The denominator should not be 0!\n";
      _denominator = 1;
    }
  }

  void setNumerator(int numerator) { _numerator = numerator; }
  void setDenominator(int denum) { _denominator = denum; }

  int getNumerator() const { return _numerator; }
  int getDenominator() const { return _denominator; }

  void add(const Fraction& other) {
    int lcm = findLcm(_denominator, _numerator);
    int newNumerator = _numerator * (lcm / _denominator) +
                       other._numerator * (lcm / other._denominator);
    _numerator = newNumerator;
    _denominator = lcm;
  }

  void subtract(const Fraction& other) {
    int lcd = findLcm(_denominator, other._denominator);
    _numerator = _numerator * (lcd / _denominator) -
                 other._numerator * (lcd / other._denominator);
    _denominator = lcd;
    reduce();
  }

  void multiply(const Fraction& other) {
    _numerator *= other._numerator;
    _denominator *= other._denominator;
  }

  void print() const {
    std::cout << _numerator << "/" << _denominator << std::endl;
  }

 private:
  void reduce() {
    int gcd = std::gcd(_numerator, _denominator);
    _numerator /= gcd;
    _denominator /= gcd;
  }

  int _numerator;
  int _denominator;
};

/*
 * Задача 2
 */

class Rectangle {
 public:
  // Those are called default values for function arguments.
  // In this way we have both default constructor and one with args.
  Rectangle(unsigned a = 1, unsigned b = 1) : _a(a), _b(b) {}

  unsigned getA() const { return _a; }
  unsigned getB() const { return _b; }

  unsigned getArea() const { return _a * _b; }
  unsigned getPerimeter() const { return 2 * (_a + _b); }

  /// sqrt is a quite heavy operation it's good to be avoided if possible 
  float calcDiagonalLen() const { return sqrtf(_a * _a + _b * _b); } /// a^2 + b^2 = c^2 

 private:
  unsigned _a, _b;  // sides
};

int main() {
  Fraction a(2, 3);
  Fraction b(3, 4);

  a.add(Fraction(2, 3));
  a.subtract(b);
  a.print();

  std::cout << Rectangle(12, 13).getArea() << " " << Rectangle(4, 3).calcDiagonalLen();
}