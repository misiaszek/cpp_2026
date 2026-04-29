#include <iostream>
#include <vector>

class Base
{
protected:
    int m_value {};
 
public:
    Base(int value)
        : m_value{ value }
    {
    }
 
    virtual std::string_view getName() const { return "Base"; }
    int getValue() const { return m_value; }
};
 
class Derived: public Base
{
public:
    Derived(int value)
        : Base{ value }
    {
    }
 
    std::string_view getName() const { return "Derived"; }
    int getValueDoubled() const { return m_value * 2; }
};
 
int main() {
   std::vector<Base*> vm;
   Base* p1 = new Base(1);
   Base* p2 = new Base(2);
   Derived* p3 = new Derived(3);
   vm.push_back(p1);
   vm.push_back(p2);
   vm.push_back(p3);
   for(auto v : vm) std::cout << v->getName() << "\n";
}
