#include <iostream>
using namespace std;
 
class Animal {
  public:
    virtual void sound() {
      cout << "Animal sound\n";
    }
    void print() {
      cout << "Animal\n";
    }
};
 
class Dog : public Animal {
  public:
    void sound() override {
      cout << "Dog barks\n";
    }
    void print() {
      cout << "Dog\n";
    }
};
 
int main() {
  Animal* a;  // Declare a pointer to the base class (Animal)
  Dog d;  // Create an object of the derived class (Dog)
  a = &d;  // Point the base class pointer to the Dog object
  a->sound(); // Call the sound() function using the pointer. Since sound() is not virtual, this calls Animal's version
  a->print();
  return 0;
}
