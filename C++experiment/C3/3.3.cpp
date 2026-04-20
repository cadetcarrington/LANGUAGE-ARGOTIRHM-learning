#include <iostream>

class Date{
    private:
        int year;
        int month;
        int day;
    public:
        Date(std::string s = "2005-01-26"){
            //sscanf(s.c_str(), "%d-%d-%d", &year, &month, &day);
            year = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0');
            month = (s[5] - '0') * 10 + (s[6] - '0');
            day = (s[8] - '0') * 10 + (s[9] - '0');
            //std::cout << "gouzao(Date)::string" << std::endl;
        }
        Date(int y, int m, int d):year(y), month(m), day(d){
            //std::cout << "gouzao(Date)::int" << std::endl;
        }
        ~Date(){
            //std::cout << "xigou(Date)" << std::endl;
        }
        void Get(){
            std::cout << "Current Status: year: " << year 
                      << "\nmonth: " << month 
                      << "\nday: " << day << std::endl;
        }
        
        void input(int y, int m, int d){
            year = y;
            month = m;
            day = d;
        }

        void input(std::string s){
            //sscanf(s.c_str(), "%d-%d-%d", &year, &month, &day);
            year = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0');
            month = (s[5] - '0') * 10 + (s[6] - '0');
            day = (s[8] - '0') * 10 + (s[9] - '0');
        }
        std::string show(){
            return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
        }
};

class People{
    private:
        int number;
        std::string sex;
        std::string name;
        Date birthday;
        int id;
    public:
        void input(int n, std::string nm, std::string s, Date b, int i){
            number = n;
            name = nm;
            sex = s;
            birthday = b;
            id = i;
        }

        void output(){
            std::cout << "number: " << number << "\nname: " << name << "\nsex: " << sex << "\nbirthday: " << birthday.show();
            //birthday.get();
            std::cout << "\nid: " << id << std::endl;
        }

        People(int n = -1, std::string nm = "Unknown", std::string s = "-1-1", Date b = Date(), int i = -1)
            :number(n), name(nm), sex(s), birthday(b), id(i){
            //std::cout << "gouzao" << std::endl;
        }
        ~People(){
            //std::cout << "xigou" << std::endl;
        }
};

using namespace std;

const int N = 100010;

int n, m;
People a[N];

int main (){ 
    printf("输入人数和操作次数：");
    cin >> n >> m;

    while(m --){
        char o[2];
        int getid, getnumber;
        string getsex, getbirthday, name;
        printf("输入操作：(I输入、O输出):");
        cin >> o;
        if(o[0] == 'I'){
            cout << "输入id、number、name、sex(male/female)、birthday(格式：2005-01-26 ):" << endl;
            cin >> getid >> getnumber >> name >> getsex >> getbirthday;
            Date birthday(getbirthday);
            a[getid].input(getnumber, name, getsex, birthday, getid);
        }
        else if(o[0] == 'O'){
            cout << "输入id:";
            cin >> getid;
            a[getid].output();
        }
    }
    return 0;
}