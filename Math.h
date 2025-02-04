#ifndef MATH_H
#define MATH_H

#include <fstream>
#include <iostream>
#include <utility>
class Rational;

#define MATH_MODE 1

#if MATH_MODE == 1

#define Boolean bool
#define Natural unsigned int
#define Integer int
#define Rational Rational
#define Real double

#define INF INT_MAX

#endif

namespace Math {
    inline Real abs(const Real& a) {
        if (a < 0) return -1 * a;
        return a;
    }

    inline Real sign(const Real& a) {
        if (a < 0) return -1;
        if (a == 0) return 0;
        return 1;
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

    void reduce() {
        const Integer gcd = Math::gcd(this->numerator, static_cast<Integer>(this->denominator));
        this->numerator /= gcd;
        this->denominator /= gcd;
    }

    void reverse() {
        Integer new_numerator;
        Natural new_denominator;
        switch (Math::sign(this->numerator)) {
            case -1: {
                new_numerator = -1 * static_cast<Integer>(this->denominator);
                new_denominator = static_cast<Natural>(Math::abs(this->numerator));
                break;
            }
            case 0: {
                std::cerr << "Division by zero!";
                return;
            }
            case 1: {
                new_numerator = static_cast<Integer>(this->denominator);
                new_denominator = static_cast<Natural>(Math::abs(this->numerator));
                break;
            }
            default: {
                return;
            }
        }
        this->numerator = new_numerator;
        this->denominator = new_denominator;
    }

    [[nodiscard]]
    Real cast() const {
        return static_cast<Real>(this->numerator) / this->denominator;
    }

    Rational& operator= (const Rational& rat) = default;

    Rational& operator= (const std::pair<Integer, Natural>& pair) {
        this->numerator = pair.first;
        this->denominator = pair.second;
        return *this;
    }

    friend Rational operator* (const Rational& lhs, const Rational& rhs) {
        Rational res(lhs.numerator * rhs.numerator, lhs.denominator * rhs.denominator);
        res.reduce();
        return res;
    }

    friend Rational operator/ (const Rational& lhs, Rational rhs) {
        try {
            rhs.reverse();
        } catch (...) {
            return Rational(INF, 1);
        }
        Rational res = lhs * rhs;
        res.reduce();
        return res;
    }

    friend Rational operator+ (const Rational& lhs, const Rational& rhs) {
        const Natural common_denominator = Math::lcm(static_cast<Integer>(lhs.denominator), static_cast<Integer>(rhs.denominator));
        const Integer lhs_numerator = static_cast<Integer>(common_denominator / lhs.denominator) * lhs.numerator;
        const Integer rhs_numerator = static_cast<Integer>(common_denominator / rhs.denominator) * rhs.numerator;
        Rational res(lhs_numerator + rhs_numerator, common_denominator);
        res.reduce();
        return res;
    }

    friend Rational operator- (const Rational& lhs, const Rational& rhs) {
        const Natural common_denominator = Math::lcm(static_cast<Integer>(lhs.denominator), static_cast<Integer>(rhs.denominator));
        const Integer lhs_numerator = static_cast<Integer>(common_denominator / lhs.denominator) * lhs.numerator;
        const Integer rhs_numerator = static_cast<Integer>(common_denominator / rhs.denominator) * rhs.numerator;
        Rational res(lhs_numerator - rhs_numerator, common_denominator);
        res.reduce();
        return res;
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
