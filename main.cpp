#include <iostream>
#include <ctime>
#include <chrono>
#include <sstream>
#include <vector>
#include "Service.h"
#include "Agency.h"

class milliseconds;

using namespace std;

int main() {

    Service *ser = new Service();
    Agency *agency = new Agency(ser);
    string command;
    char split_char = ' ';
    vector<string> tokens;
    while (1) {
        getline(cin, command);
        istringstream split(command);
        for (string each; getline(split, each, split_char); tokens.push_back(each));
        try {
            if (tokens.at(0) == "add") {
                if (tokens.at(1) == "service")
                    ser->addService(tokens.at(2));
                if (tokens.at(1) == "subservice") {
                    stringstream geek(tokens.at(6));
                    int index = 0;
                    geek >> index;
                    ser->addSubService(tokens.at(2), tokens.at(4), index);
                }
                if (tokens.at(1) == "offer")
                    agency->addOffer(tokens.at(2), tokens.at(4));
                if (tokens.at(1) == "agency")
                    agency->addAgency(tokens.at(2));
            }
            if (tokens.at(0) == "list") {
                if (tokens.at(1) == "services")
                    agency->listServices();
                if (tokens.at(1) == "agencies")
                    agency->listAgencies();
                if (tokens.at(1) == "services" && tokens.at(2) == "from")
                    ser->listServicesFrom(tokens.at(3));
                if (tokens.at(1) == "orders")
                    agency->listOrder(tokens.at(2));
            }
            if (tokens.at(0) == "delete")
                agency->deleteService(tokens.at(1), tokens.at(3));
            if (tokens.at(0) == "order") {
                __int64 time = chrono::duration_cast<chrono::milliseconds>(
                        chrono::system_clock::now().time_since_epoch()).count();
                stringstream geek(tokens.at(7));
                int immediacy_level = 0;
                geek >> immediacy_level;
                stringstream geek2(tokens.at(8));
                int index = 0;
                geek2 >> index;
                agency->order(tokens.at(1), tokens.at(3), tokens.at(5), immediacy_level, time, index);
            }
            if (tokens.at(0) == "all")
                ser->listServices();
            if (tokens.at(0) == "exit")
                break;
        } catch (out_of_range &ex) {
            cout << "\nOut of range exception caught.\n" << ex.what() << endl;
        }
        tokens.clear();
    }

    delete (ser);
    delete (agency);
    return 0;
}

