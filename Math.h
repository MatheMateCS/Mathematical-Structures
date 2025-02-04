#ifndef MATH_H
#define MATH_H

#include <fstream>
#include <iostream>
#include <utility>

class Rational;
class Matrix;

#define MATH_MODE 1

#if MATH_MODE == 1

typedef bool Boolean;
typedef unsigned int Natural;
typedef int Integer;
typedef Rational Rational;
typedef double Real;

#define INF INT_MAX

namespace Math {
    Real abs(const Real& a);
    Integer sign(const Real& a);
    Integer gcd(const Integer& a, const Integer& b);
    Integer lcm(const Integer& a, const Integer& b);
}

#endif

class Rational {
public:
    Rational();
    Rational(const Integer& numerator, const Natural& denominator);
    Rational(const std::pair<Integer, Natural>& frac);
    Rational(const Rational& rat);

    void reduce();
    void inverse();
    [[nodiscard]]
    Real cast() const;

    Rational& operator= (const Rational&) = default;
    Rational& operator= (const std::pair<Integer, Natural>& frac);

    Rational& operator+= (const Rational& rhs);
    Rational& operator-= (const Rational& rhs);
    Rational& operator*= (const Rational& rhs);
    Rational& operator/= (Rational rhs);

    friend Rational operator+ (const Rational& lhs, const Rational& rhs);
    friend Rational operator- (const Rational& lhs, const Rational& rhs);
    friend Rational operator* (const Rational& lhs, const Rational& rhs);
    friend Rational operator/ (const Rational& lhs, Rational rhs);
    friend std::ostream& operator<<(std::ostream& os, const Rational& rat);
private:
    Integer numerator;
    Natural denominator;
};

class Matrix {
public:
    struct Dimension {
        Natural m;
        Natural n;

        Dimension(const Natural& m, const Natural& n) : m(m), n(n) {}
        Dimension(const std::pair<Natural, Natural>& d) : m(d.first), n(d.second) {}

        friend std::ostream& operator<<(std::ostream& os, const Dimension& d) {
            os << "[" << d.m << "x" << d.n << "]";
            return os;
        }
    };

    Matrix();
    Matrix(const Natural& m, const Natural& n);
    Matrix(const Dimension& dim);
    Matrix(const Matrix& matrix);

    void transpose();
    [[nodiscard]]
    Matrix T() const;

    Dimension dim();

    Real& operator[] (const std::pair<Natural, Natural>& pos);
    Real operator() (const Natural& i, const Natural& j) const;
private:
    Dimension dimension;
    Real** data;
};



#endif //MATH_H
