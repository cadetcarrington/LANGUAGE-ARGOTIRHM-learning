#include <iostream>

using namespace std;

class boat;
class car;

class boat {
private:
    int weight;

public:
    boat(int w) : weight(w) {}
    friend int total_weight(const boat& b, const car& c);
};

class car {
private:
    int weight;

public:
    car(int w) : weight(w) {}
    friend int total_weight(const boat& b, const car& c);
};

int total_weight(const boat& b, const car& c) {
    return b.weight + c.weight;
}

int main (){
    int n, m;
    cin >> n >> m;
    boat b(n);
    car c(m);
    
    cout << "总重量: " << total_weight(b, c) << endl;

    return 0;
}