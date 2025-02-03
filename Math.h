#ifndef MATH_H
#define MATH_H

class Number;
class R;
class Q;
class Z;
class N;

class Number {
protected:
    explicit Number(const double& value) : value(value) {}
private:
    double value;
};

class R : public Number {}; // Real


class Z : public Number { // Integer
public:
    Z() : Z(0) {}

    Z(int integer) : Number(integer) {
        this->value = integer;
    }

    Z(const Z& integer) : Number(integer.value) {
        this->value = integer.value;
    }

    Z& operator= (const int& value) {
        this->value = value;
        return *this;
    }

    Z& operator= (const Z& integer) {
        this->value = integer.value;
        return *this;
    }

private:
    int value;
};

class N : public Number { // Natural
public:
    N() : N(0) {}

    N(unsigned int natural) : Number(natural) {
        this->value = natural;
    }

    N(const N& natural) : Number(natural.value) {
        this->value = natural.value;
    }

    N& operator= (const unsigned int& value) {
        this->value = value;
        return *this;
    }

    N& operator= (const N& natural) {
        this->value = natural.value;
        return *this;
    }
private:
    unsigned int value;
};

class Q : public Number { // Rational
public:
    Q() : Q(0, 1) {}

    Q(int numerator, unsigned int denominator) : Number(static_cast<double>(numerator) / denominator) {
        this->numerator = numerator;
        this->denominator = denominator;
    }

    Q(const Q& rational) {
        this->numerator = rational.numerator;
        this->denominator = rational.denominator;
    }
private:
    Z numerator;
    N denominator;
};


#endif //MATH_H
