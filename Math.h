#ifndef MATH_H
#define MATH_H

#include <fstream>
#include <utility>
class Rational;

#define MATH_MODE 1

#if MATH_MODE == 1

#define Boolean bool
#define Natural unsigned int
#define Integer int
#define Rational Rational
#define Real double

#endif

namespace Math {
    inline Real abs(const Real& a) {
        if (a < 0) return -1 * a;
        return a;
    }

    inline Integer gcd(const Integer& a, const Integer& b) {
        if (a == 0) return b;
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    inline Integer lcm(const Integer& a, const Integer& b) {
        return static_cast<Integer>(abs(a * b)) / gcd(a, b);
    }
}

class Rational {
public:
    Rational() {
        this->numerator = 0;
        this->denominator = 1;
    }

    Rational(const Integer& numerator, const Natural& denominator) {
        this->numerator = numerator;
        this->denominator = denominator;
    }

    Rational(const Rational& rat) {
        this->numerator = rat.numerator;
        this->denominator = rat.denominator;
    }

    Rational& operator= (const Rational& rat) = default;

    Rational& operator= (const std::pair<Integer, Natural>& pair) {
        this->numerator = pair.first;
        this->denominator = pair.second;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& rat) {
        os << rat.numerator << "/" << rat.denominator;
        return os;
    }
private:
    Integer numerator;
    Natural denominator;
};



#endif //MATH_H
