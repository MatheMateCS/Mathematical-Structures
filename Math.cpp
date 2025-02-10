#include "Math.h"

Real Math::abs(const Real &a)  {
    if (a < 0) return -1 * a;
    return a;
}

Integer Math::sign(const Real &a) {
    if (a < 0) return -1;
    if (a == 0) return 0;
    return 1;
}

Integer Math::gcd(const Integer &a, const Integer &b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return gcd(b, a % b);
}

Integer Math::lcm(const Integer &a, const Integer &b) {
    return static_cast<Integer>(abs(a * b)) / gcd(a, b);
}

Rational::Rational() {
    this->numerator = 0;
    this->denominator = 1;
}

Rational::Rational(const Integer &numerator, const Natural &denominator) {
    this->numerator = numerator;
    this->denominator = denominator;
}

Rational::Rational(const std::pair<Integer, Natural> &frac) {
    this->numerator = frac.first;
    this->denominator = frac.second;
}

Rational::Rational(const Rational &rat) {
    this->numerator = rat.numerator;
    this->denominator = rat.denominator;
}

void Rational::reduce() {
    const Integer gcd = Math::gcd(this->numerator, static_cast<Integer>(this->denominator));
    this->numerator /= gcd;
    this->denominator /= gcd;
}

void Rational::inverse() {
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
            new_numerator = INF;
            new_denominator = 1;
            break;
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

double Rational::cast() const {
    return static_cast<Real>(this->numerator) / this->denominator;
}

Rational & Rational::operator=(const std::pair<Integer, Natural> &frac) {
    this->numerator = frac.first;
    this->denominator = frac.second;
    return *this;
}

Rational & Rational::operator+= (const Rational &rhs) {
    const Natural common_denominator = Math::lcm(static_cast<Integer>(this->denominator), static_cast<Integer>(rhs.denominator));
    this->numerator = static_cast<Integer>(common_denominator / this->denominator) * this->numerator;
    const Integer rhs_numerator = static_cast<Integer>(common_denominator / rhs.denominator) * rhs.numerator;
    this->numerator += rhs_numerator;
    this->denominator = common_denominator;
    this->reduce();
    return *this;
}

Rational & Rational::operator-= (const Rational &rhs) {
    const Natural common_denominator = Math::lcm(static_cast<Integer>(this->denominator), static_cast<Integer>(rhs.denominator));
    this->numerator = static_cast<Integer>(common_denominator / this->denominator) * this->numerator;
    const Integer rhs_numerator = static_cast<Integer>(common_denominator / rhs.denominator) * rhs.numerator;
    this->numerator -= rhs_numerator;
    this->denominator = common_denominator;
    this->reduce();
    return *this;
}

Rational & Rational::operator*= (const Rational &rhs) {
    this->numerator *= rhs.numerator;
    this->denominator *= rhs.denominator;
    this->reduce();
    return *this;
}

Rational & Rational::operator/= (Rational rhs) {
    rhs.inverse();
    this->operator*=(rhs);
    return *this;
}

Rational operator* (const Rational &lhs, const Rational &rhs)  {
    Rational res(lhs.numerator * rhs.numerator, lhs.denominator * rhs.denominator);
    res.reduce();
    return res;
}

Rational operator/ (const Rational &lhs, Rational rhs) {
    rhs.inverse();
    Rational res = lhs * rhs;
    res.reduce();
    return res;
}

std::ostream & operator<< (std::ostream &os, const Rational &rat) {
    os << rat.numerator << "/" << rat.denominator;
    return os;
}

Rational operator+ (const Rational &lhs, const Rational &rhs) {
    const Natural common_denominator = Math::lcm(static_cast<Integer>(lhs.denominator), static_cast<Integer>(rhs.denominator));
    const Integer lhs_numerator = static_cast<Integer>(common_denominator / lhs.denominator) * lhs.numerator;
    const Integer rhs_numerator = static_cast<Integer>(common_denominator / rhs.denominator) * rhs.numerator;
    Rational res(lhs_numerator + rhs_numerator, common_denominator);
    res.reduce();
    return res;
}

Rational operator- (const Rational &lhs, const Rational &rhs) {
    const Natural common_denominator = Math::lcm(static_cast<Integer>(lhs.denominator), static_cast<Integer>(rhs.denominator));
    const Integer lhs_numerator = static_cast<Integer>(common_denominator / lhs.denominator) * lhs.numerator;
    const Integer rhs_numerator = static_cast<Integer>(common_denominator / rhs.denominator) * rhs.numerator;
    Rational res(lhs_numerator - rhs_numerator, common_denominator);
    res.reduce();
    return res;
}

Matrix::Matrix(): Matrix(1, 1) {}

Matrix::Matrix(const Natural &m, const Natural &n) : dimension(m, n) {
    this->data = new Real* [this->dimension.m];
    for (Natural i = 0; i < this->dimension.m; ++i) {
        this->data[i] = new Real [this->dimension.n];
    }
}

Matrix::Matrix(const Dimension &dim) : Matrix(dim.m, dim.n) {}

Matrix::Matrix(const Matrix &matrix) : Matrix(matrix.dimension.m, matrix.dimension.n) {
    for (Natural i = 0; i < this->dimension.m; ++i) {
        for (Natural j = 0; j < this->dimension.n; ++j) {
            this->data[i][j] = matrix.data[i][j];
        }
    }
}

void Matrix::transpose() {
    Matrix T(this->dimension.n, this->dimension.m);
    for (Natural i = 0; i < T.dimension.m; ++i) {
        for (Natural j = 0; j < T.dimension.n; ++j) {
            T[{i, j}] = this->data[j][i];
        }
    }
    *this = T;
}

Matrix Matrix::T() const {
    Matrix T(this->dimension.n, this->dimension.m);
    for (Natural i = 0; i < T.dimension.m; ++i) {
        for (Natural j = 0; j < T.dimension.n; ++j) {
            T[{i, j}] = this->data[j][i];
        }
    }
    return T;
}

Matrix::Dimension Matrix::dim() {
    return this->dimension;
}

Real & Matrix::operator[](const std::pair<Natural, Natural> &pos) {
    return this->data[pos.first][pos.second];
}

Real Matrix::operator()(const Natural &i, const Natural &j) const {
    return this->data[i][j];
}

Function linear(Real k, Real b) {
    return [k, b] (const Real& x) -> Real { return k * x + b; };
}

Function quadratic(Real a, Real b, Real c) {
    return [a, b, c] (const Real& x) -> Real { return a * x * x + b * x + c; };
}

