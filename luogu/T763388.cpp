#include <iostream>
using namespace std;

int main() {
    int a, b, c, m;
    cin >> a >> b >> c >> m;

    int p, q, t;
    cin >> p >> q >> t;

    bool busOK = (a + b + m < t);
    bool taxiOK = (a + c + m < t);

    if (!busOK && !taxiOK) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;

    int cost;
    string communleater;

    if (busOK && taxiOK) {
        if (p <= q) {
            cost = p;
            communleater = "bus";
        } else {
            cost = q;
            communleater = "taxi";
        }
    }
    else if (busOK) {
        cost = p;
        communleater = "bus";
    }
    else {
        cost = q;
        communleater = "taxi";
    }

    cout << cost << endl;
    cout << communleater << endl;

    return 0;
}