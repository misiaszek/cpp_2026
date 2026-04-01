#include <iostream>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;

public:
    // Konstruktor z parametrami
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {}
	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
};

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
	os << f.numerator << "/" << f.denominator;
	return os;
}

int main() {
	Fraction f1;
	Fraction f2(1, 2);
	
	std::cout << f1 << " " << f2 << std::endl;

    operator<<(operator<<(operator<<(std::cout, f1), " "), f2);

	return 0;
}
