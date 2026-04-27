#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

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
    public:
        People(char * name, char * number, char * sex, char * id, Date &birthday){
            strcpy(this->name, name);
            strcpy(this->number, number);
            strcpy(this->sex, sex);
            strcpy(this->id, id);
            this->birthday = birthday;
        }

        People(const People &p){
            strcpy(this->name, p.name);
            strcpy(this->number, p.number);
            strcpy(this->sex, p.sex);
            strcpy(this->id, p.id);
            this->birthday = p.birthday;
        }
        ~People(){}

        void input(char * Name, char * Number, char * Sex, char * Id, Date &Birthday){
            strcpy(this->name, Name);
            strcpy(this->number, Number);
            strcpy(this->sex, Sex);
            strcpy(this->id, Id);
            this->birthday = Birthday;
        }

        void output(){
            std::cout << "Name: " << name << std::endl;
            std::cout << "Number: " << number << std::endl;
            std::cout << "Sex: " << sex << std::endl;
            std::cout << "Id: " << id << std::endl;
            std::cout << "Birthday: ";
            birthday.Get();
        }
    private:
        char name[11], number[7], sex[3], id[16];
        Date birthday;

};

using namespace std;

typedef pair<int, People> people;

vector<people> a;

int main (){
    int n;
    cout << "输入操作次数：(I/O)";
    cin >> n;

    while(n --){
        char op[2];
        cout << "I/O:";
        cin >> op;
        if(op[0] == 'I'){
            int num;
            cout << "输入序列号：";
            cin >> num;
            cout << endl;
            
            char name[11], number[7], sex[3], id[16];
            string get;
            cout << "顺序：姓名，电话，性别，身份证号，生日" << endl;

            cin >> name >> number >> sex >> id;
            cin >> get;

            Date birthday(get);
            People tr(name, number, sex, id, birthday);
            a.push_back({num, tr});

            sort(a.begin(), a.end());
        }
        else {
            int num; bool ch = 0;
            cout << "输入序列号：";
            cin >> num;
            cout << endl;

            int l = 0, r = a.size() - 1;
            while(l <= r){
                int mid = (l + r) >> 1;
                
                if(a[mid].first == num){
                    a[mid].second.output();
                    ch = 1;
                    break;
                }

                else if(a[mid].first < num) l = mid + 1;
                else r = mid - 1;
            }
            
            if(!ch){
                cout << "无此序号！" << endl;
            }
        }
    }
    return 0;
}