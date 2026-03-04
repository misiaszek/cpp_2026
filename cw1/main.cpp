#include <iostream>

int main() {
    std::cout << "hello world" << std::endl;
    std::cout.precision(2);
    std::cout << "pi: " << 3.14159 << std::endl;
    // std::cout - jest obiektem, operator<< jest funkcją, która przyjmuje dwa argumenty: 
    // strumień wyjściowy (std::cout) i tekst do wypisania ("Hello world"). Funkcja ta zwraca 
    // referencję do strumienia wyjściowego, co pozwala na łańcuchowe wywoływanie operatora<<. 
    // W tym przypadku, po wypisaniu "Hello world", zostanie również wypisany znak nowej linii (std::endl).
    (std::operator<<(std::cout, "Hello world")).operator<<(std::endl); 
    return 0;
}
