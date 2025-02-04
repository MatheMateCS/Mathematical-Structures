#ifndef MATH_H
#define MATH_H

#include <fstream>
#include <iostream>
#include <utility>

class Rational;

#define MATH_MODE 1

#if MATH_MODE == 1

namespace Math {
    #define Boolean bool
    #define Natural unsigned int
    #define Integer int
    #define Real double

    #define INF INT_MAX

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
    void reverse();
    [[nodiscard]]
    Real cast() const;

    Rational& operator= (const Rational&) = default;
    Rational& operator= (const std::pair<Integer, Natural>& frac);

    Rational& operator+= (const Rational& rhs);
    Rational& operator-= (const Rational& rhs);
    Rational& operator*= (const Rational& rhs);
    Rational& operator/= (Rational rhs);

    Rational& operator+= (const std::pair<Integer, Natural>& frac);
    Rational& operator-= (const std::pair<Integer, Natural>& frac);
    Rational& operator*= (const std::pair<Integer, Natural>& frac);
    Rational& operator/= (const std::pair<Integer, Natural>& frac);

    friend Rational operator+ (const Rational& lhs, const Rational& rhs);
    friend Rational operator- (const Rational& lhs, const Rational& rhs);
    friend Rational operator* (const Rational& lhs, const Rational& rhs);
    friend Rational operator/ (const Rational& lhs, Rational rhs);
    friend std::ostream& operator<<(std::ostream& os, const Rational& rat);
private:
    Integer numerator;
    Natural denominator;
};



#endif //MATH_H
