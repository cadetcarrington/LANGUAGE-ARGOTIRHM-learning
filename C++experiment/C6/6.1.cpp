#include <iostream>

using namespace std;

class Animal{
    //int age;// 这里的age是Animal中的age，编译器会报错，因为age是private的

    public:
        int age;
        void SetAge(int a){
            age = a;
        }
        Animal(int a = 0){
            age = a;
        }
        void ShowAge(){
            cout << "age = " << age << endl;
        }
};

class dog : public Animal{
    public:
        dog(int a = 0) : Animal(a){
        }
        void ShowAge(){
            cout << "dog ";
            Animal::ShowAge(); 
        }
        void SetAge(int a){
            cout << "dog SetAge" << endl;
            age = a; 
        }
};

int main (){
    dog a(6);
    a.SetAge(8);
    a.ShowAge();
    return 0;
}