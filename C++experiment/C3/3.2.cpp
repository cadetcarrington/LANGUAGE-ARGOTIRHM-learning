#include <iostream>

enum CPU_Rank {P1 = 1, P2, P3, P4, P5, P6, P7};

class CPU{
    private:   
        CPU_Rank rank;
        int frequency;
        double voltage;
    public:
        void run(enum CPU_Rank p, int f, double v);
        void stop(){
            printf("process stop\n");
            std::cout << "Current Status: CPU_Rank: " << rank 
                      << "\nfrequency: " << frequency 
                      << "\nvoltage: " << voltage << std::endl;
            rank = P1;
            frequency = 0;
            voltage = 0;
        }
        CPU(enum CPU_Rank p = P1, int f = 0, double v = 0){
            rank = p; 
            frequency = f;
            voltage = v;
            std::cout << "gouzao(CPU)" << std::endl;
        }
        ~CPU(){
            std::cout << "xigou(CPU)" << std::endl;
        }

        void Get(){
            std::cout << "Current Status: CPU_Rank: " << rank 
                      << "\nfrequency: " << frequency 
                      << "\nvoltage: " << voltage << std::endl;
        }
        void Get(CPU_Rank p){
            std::cout << "Current Status: CPU_Rank: " << rank << std::endl;
        }
        void Get(int f){
            std::cout << "Current Status: " << "frequency: " << frequency << std::endl;
        }
        void Get(double v){
            std::cout << "Current Status: " << "voltage: " << voltage << std::endl;
        }

        void change(CPU_Rank p, int f, double v){
            rank = p; 
            frequency = f;
            voltage = v;
        }    
};

void CPU::run (CPU_Rank p, int f, double v){
    rank = p;
    frequency = f;
    voltage = v;
}

class ram{
    private:
        int size;
        int frequency;
    public:
        void run(int s, int f);
        void stop(){
            printf("process stop\n");
            std::cout << "Current Status: size: " << size 
                      << "\nfrequency: " << frequency << std::endl;
            size = 0;
            frequency = 0;
        }
        ram(int s = 0, int f = 0){
            size = s; 
            frequency = f;
            std::cout << "gouzao(ram)" << std::endl;
        }
        ~ram(){
            std::cout << "xigou(ram)" << std::endl;
        }

        void Get(){
            std::cout << "Current Status: size: " << size 
                      << "\nfrequency: " << frequency << std::endl;
        }

        void change(int s, int f){
            size = s; 
            frequency = f;
        }    
};

void ram::run (int s, int f){
    size = s;
    frequency = f;
}

class cdrom{
    private:
        int size;
    public:
        void run(int s);
        void stop(){
            printf("process stop\n");
            std::cout << "Current Status: size: " << size << std::endl;
            size = 0;
        }

        cdrom(int s = 0){
            size = s; 
            std::cout << "gouzao(cdrom)" << std::endl;
        }
        ~cdrom(){
            std::cout << "xigou(cdrom)" << std::endl;
        }

        void Get(){
            std::cout << "Current Status: size: " << size << std::endl;
        }
        void Get(int s){
            std::cout << "Current Status: size: " << size << std::endl;
        }

        void change(int s){
            size = s; 
        }
};

void cdrom::run (int s){
    size = s;
}

class Computer{
    private:
        CPU cpu;
        ram r;
        cdrom c;
    public:
        void run(CPU_Rank p, int f, double v, int s, int rf, int cs);
        void stop(){
            printf("process stop\n");
            cpu.stop();
            r.stop();
            c.stop();
        }
        Computer(CPU_Rank p = P1, int f = 0, double v = 0, int s = 0, int rf = 0, int cs = 0)
            :cpu(p, f, v), r(s, rf), c(cs){
            std::cout << "gouzao(computer)" << std::endl;
        }
        ~Computer(){
            std::cout << "xigou(computer)" << std::endl;
        }

        void Get(){
            cpu.Get();
            r.Get();
            c.Get();
        }

        void change(CPU_Rank p, int f, double v, int s, int rf, int cs){
            cpu.change(p, f, v);
            r.change(s, rf);
            c.change(cs);
        }
};

void Computer::run (CPU_Rank p, int f, double v, int s, int rf, int cs){
    cpu.run(p, f, v);
    r.run(s, rf);
    c.run(cs);
}

using namespace std;

int main (){
    Computer a(P3, 3000, 1.2, 16, 3200, 512);
    a.run(P5, 3500, 1.3, 32, 3600, 1024);
    a.Get();
    a.change(P7, 4000, 1.4, 64, 4000, 2048);
    a.Get();
    a.stop();
    return 0;
}