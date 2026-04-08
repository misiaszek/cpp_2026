#include <iostream>
#include <string>

class Silnik {
public:
   Silnik(const std::string& typ) : typ(typ) {}
   void uruchom() const {
       std::cout << "Silnik " << typ << " uruchomiony." << std::endl;
   }
private:
   std::string typ;
};

class Samochod {
public:
   Samochod(const std::string& marka, const std::string& typSilnika)
       : marka(marka), silnik(typSilnika) {}
   void uruchom() const {
       std::cout << "Samochod " << marka << " uruchamia silnik." << std::endl;
       silnik.uruchom();
   }
private:
   std::string marka;
   Silnik silnik;
};

int main() {
   Samochod samochod("Toyota", "benzynowy");
   samochod.uruchom();
   return 0;
}
