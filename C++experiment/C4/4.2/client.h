#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

typedef std::pair<int, std::string> PIS;

class Client{
    public:
        Client(int num = 1);
        void ChangeServerName(int id, std::string newName);
        int GetClientNum();
        void Show();
        void Show(int id);
        ~ Client();
    private:
        static int ClientNum;
        std::vector<PIS> ServerNames;
        //std::string ServerName;
};

#endif