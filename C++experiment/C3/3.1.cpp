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
            std::cout << "gouzao" << std::endl;
        }
        ~CPU(){
            std::cout << "xigou" << std::endl;
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

using namespace std;

int main (){
    CPU aa, bb(P3, 2, 0.3);
    aa.change(P1, 4, 0.9);
    aa.Get();
    bb.Get();
    aa.stop();
    aa.Get();
    return 0;
}