
#include <iostream>
#include <cmath>
using namespace std;

class Point {
public:
    void set(int getx, int gety);
    int getX() const { return x; }
    int getY() const { return y; }
private:
    int x;
    int y;
};

class Circle {
public:
    void set(int rr, int xx, int yy);
    bool contains(const Point& p) const;
private:
    int r;
    int x;
    int y;
};

void Circle::set(int rr, int xx, int yy) {
    r = rr;
    x = xx;
    y = yy;
}

bool Circle::contains(const Point & p) const {
    int dx = p.getX() - x;
    int dy = p.getY() - y;
    return dx * dx + dy * dy <= r * r;
}

void Point::set(int getx, int gety) {
    x = getx;
    y = gety;
}

int main() {
    Circle a;
    Point b;
    int rr, x1, y1, x0, y0;
    cin >> rr >> x1 >> y1 >> x0 >> y0;
    a.set(rr, x1, y1);
    b.set(x0, y0);
    if (a.contains(b)) {
        cout << "Point is inside or on the circle." << endl;
    } else {
        cout << "Point is outside the circle." << endl;
    }
    return 0;
}