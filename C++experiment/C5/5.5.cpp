#include <iostream>
#include <vector>

typedef std::string S;

class Employee {
        S Name, Address, City;
        int CodeNumber;
    public:
        Employee(S name = "sullyoon", S address = "jypp",
             S city = "seoul", int codeNumber = 123456) 
             : Name(name), Address(address), City(city), 
             CodeNumber(codeNumber) {};
        
        void changeName(S name) { Name = name; }
        void in(S name, S address, S city, int codeNumber) { 
            Name = name; 
            Address = address; 
            City = city; 
            CodeNumber = codeNumber; 
        }
        void display() { 
            std::cout << "Name: " << Name << std::endl;
            std::cout << "Address: " << Address << std::endl;
            std::cout << "City: " << City << std::endl;
            std::cout << "CodeNumber: " << CodeNumber << std::endl;
        }
};

using namespace std;

vector<Employee> employees;

int main (){
    int n;
    cout << "输入操作数：(I/O)";
    cin >> n;

    while(n --){
        cout << "输入(I/O): " << endl;
        
        char op[2];
        cin >> op;

        if(op[0] == 'I'){
            cout << "输入员工信息：姓名 地址 城市 编号" << endl;

            S name, address, city;
            int codeNumber;
            cin >> name >> address >> city >> codeNumber;

            Employee employee(name, address, city, codeNumber);
            employees.push_back(employee);
        }
        else if(op[0] == 'O'){
            int numb;
            cin >> numb;
            if(numb >= employees.size()){
                cout << "无此序号！" << endl;
            }
            else{
                employees[numb - 1].display();
            }
        }
    }
}