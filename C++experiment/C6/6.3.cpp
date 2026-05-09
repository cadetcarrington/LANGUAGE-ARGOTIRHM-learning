#include <iostream>

using namespace std;

class vehicle{
    int MaxSpeed;
    double Weight;
    public:
        vehicle(int maxSpeed = 0, double weight = 0.0) : MaxSpeed(maxSpeed), Weight(weight) {}
        void Run(int s){
            MaxSpeed = s;
            cout << "vehicle Run" << endl;
        }
        void Stop(){
            cout << "vehicle Stop" << endl;
            MaxSpeed = 0;
        }
        void check(){
            cout << "vehicle check" << endl;
            cout << "vechile status: ";
            if(MaxSpeed > 0){
                cout << "running" << endl;
            }
            else{
                cout << "stopped" << endl;
            }
            cout << "MaxSpeed = " << MaxSpeed << "Km/h" << endl;
            cout << "Weight = " << Weight << "kg" << endl;
        }
        virtual ~vehicle(){}
};

class bicycle : virtual public vehicle{
    protected:
        double Height;
    public:
        bicycle(int maxSpeed = 0, double weight = 0.0, double height = 0.0) : vehicle(maxSpeed, weight), Height(height) {}
        void Run(int s){
            cout << "bicycle Run: ";
            vehicle::Run(s);
        }
        void Stop(){
            cout << "bicycle Stop: ";
            vehicle::Stop();
        }
        void check(){
            cout << "bicycle check: ";
            vehicle::check();
            cout << "Height = " << Height << endl;
        }
};

class motorcar : virtual public vehicle{
    protected:
        int SeatNum;
        int seatp;
    public:
        motorcar(int maxspeed = 0, double weight = 0.0, int seatnum = 0, int seatp = 0)
         : vehicle(maxspeed, weight), SeatNum(seatnum), seatp(seatp){}    
        void Run(int s = 0, int pp = 0){
            cout << "motorcar Run: ";
            vehicle::Run(s);
            this->seatp = pp;
        }
        void Stop(){
            cout << "motorcar Stop: ";
            vehicle::Stop();
        }
        void check(){
            cout << "motorcar check: ";
            vehicle::check();
            cout << "SeatNumber = " << SeatNum << endl;;
            cout << "People = " << seatp << endl;
        }
};

class motorcycle : public bicycle, public motorcar{
    public:
        motorcycle(int MaxSpeed = 0, double weight = 0, double height = 0, int seatnum = 0, int seat = 0)
            :vehicle(MaxSpeed, weight), bicycle(MaxSpeed, weight, height), motorcar(MaxSpeed, weight, seatnum, seat){}
        void Run(int s, int pp){
            cout << "motorcycle Run: ";
            motorcar::Run(s, pp);
        }
        void Stop(){
            cout << "motorcycle Stop: ";
            vehicle::Stop();
        }
        void check(){
            cout << "motorcycle check: ";
            vehicle::check();
            cout << "Height = " << Height << endl;
            cout << "SeatNumber = " << SeatNum << endl;
            cout << "People = " << seatp << endl;
        }
};

int main (){
    int sp, we;
    cout << "输入速度与质量: ";
    cin >> sp >> we;
    vehicle a(sp, we);

    cout << "-------初始状态-------" << endl;
    a.check();
    a.Stop();
    cout << "-------状态1-------" << endl;
    a.check();

    int ns;
    cout << "输入新的速度: ";
    cin >> ns;

    a.Run(ns);
    cout << "-------状态2-------" << endl;
    a.check();


    int hei;
    cout << "输入自行车的数据: ";
    cin >> sp >> we >> hei;
    bicycle b(sp, we, hei);

    cout << "-------初始状态-------" << endl;
    b.check();
    b.Stop();
    cout << "-------状态1-------" << endl;
    b.check();

   
    cout << "输入新的速度: ";
    cin >> ns;

    b.Run(ns);
    cout << "-------状态2-------" << endl;
    b.check();


    int Seat, p;
    cout << "输入机动车数据: ";
    cin >> sp >> we >> Seat >> p;
    motorcar c(sp, we, Seat, p);

    cout << "-------初始状态-------" << endl;
    c.check();
    c.Stop();
    cout << "-------状态1-------" << endl;
    c.check();

    int np;
    cout << "请输入新数据: " << endl;
    cin >> ns >> np;

    c.Run(ns, np);
    cout << "-------状态2-------" << endl; 
    c.check();


    cout << "请输入摩托车数据: ";
    cin >> sp >> we >> hei >> Seat >> p;
    motorcycle d(sp, we, hei, Seat, p);

    cout << "-------初始状态-------" << endl;
    d.check();
    d.Stop();
    cout << "-------状态1-------" << endl;
    d.check();

    cout << "请输入新数据: " << endl;
    cin >> ns >> np;

    d.Run(ns, np);
    cout << "-------状态2-------" << endl; 
    d.check();
    return 0;
}