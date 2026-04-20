#include <iostream>
#include "client.h"
#include <algorithm>

using namespace std;

int Client::ClientNum = 0;

Client::Client(int num) {
    ClientNum = num;
}

void Client::ChangeServerName(int id, std::string newName) {

    cout << "Change Server Name " << id << ": " << newName << endl;
    if (id < 0 /*|| id >= ClientNum*/) {
        cout << "Invalid Server ID." << endl;
        return;
    }
    ServerNames.push_back({id, newName});
    if(id >= ClientNum) ClientNum ++;
    sort(ServerNames.begin(), ServerNames.end());
}

int Client::GetClientNum() {
    return ClientNum;
}

void Client::Show() {
    cout << "All Server Names: " << endl;
    for (auto server : ServerNames) {
        cout << "ID: " << server.first << " Name: " << server.second << endl;
    }
}

void Client::Show(int id) {
    int l = 0, r = ServerNames.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (ServerNames[mid].first == id) {
            cout << "Server ID: " << ServerNames[mid].first << " Name: " << ServerNames[mid].second << endl;
            return;
        }
        else if (ServerNames[mid].first < id) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    cout << "Server ID " << id << " not found." << endl;
}

Client::~Client() {
    //cout << "Client destroyed." << endl;
}