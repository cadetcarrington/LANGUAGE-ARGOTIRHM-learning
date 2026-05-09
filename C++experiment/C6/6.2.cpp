#include <iostream>

using namespace std;

class BaseClass{
    int Number;
    public:
        void SetNumber(int n){
            Number = n;
        }
        BaseClass(int n = 0){
            Number = n;
            cout << "BaseClass constructor" << endl;
        }
        ~BaseClass(){
            cout << "BaseClass destructor" << endl;
        }
};

class DerivedClass : public BaseClass{
    public:
        DerivedClass(int n = 0) : BaseClass(n){
            cout << "DerivedClass constructor" << endl;
        }
        ~DerivedClass(){
            cout << "DerivedClass destructor" << endl;
        }
};

int main (){
    DerivedClass a(5);

    return 0;
}