#include <iostream>
#include <ctime>
#include <chrono>
#include "Service.h"
#include "Agency.h"

class milliseconds;

using namespace std;

int run() {
    Service *service = new Service();
    Agency *agency = new Agency(service);

    service->addService("A");
    service->addService("B");
    service->addService("C");
    service->addService("D");
    service->addSubService("E", "A", 0);
    service->addSubService("F", "A", 1);
    service->addSubService("F", "A", 0);
    service->addSubService("Z", "A", 1);
    service->addSubService("A", "E", 0);
    service->addSubService("B", "F", 0);
    service->addSubService("K", "F", 0);
    service->addSubService("B", "F", 0);
    service->addSubService("G", "K", 0);
    service->addSubService("G", "K", 1);
    service->addSubService("A", "G", 0);
    service->addSubService("G", "C", 0);
    service->addSubService("H", "C", 0);
    service->addSubService("T", "B", 0);

    service->listServices();

    service->listServicesFrom("E");

    service->deleteMainService("D");
    service->listServices();

    agency->addAgency("1");
    agency->addAgency("2");
    agency->addAgency("3");
    agency->addAgency("4");
    agency->addAgency("5");
    agency->addAgency("6");

    agency->listAgencies();

    agency->addOffer("A", "1");
    agency->addOffer("C", "1");
    agency->addOffer("A", "2");
    agency->addOffer("C", "3");
    agency->addOffer("C", "4");
    agency->addOffer("D", "4");
    agency->addOffer("F", "7");

    agency->listServices();

    agency->deleteService("C", "4");
    agency->deleteService("C", "3");
    agency->deleteService("C", "1");

    service->listServices();

    __int64 time = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();
    agency->order("E", "1", "phl", 1, time, 0);
    time = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();

    agency->order("A", "1", "phl", 1, time, 0);
    time = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();

    agency->order("F", "1", "phl", 1, time, 0);
    time = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();

    agency->order("B", "1", "phl", 2, time, 0);
    time = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();

    agency->order("G", "1", "phl", 3, time, 0);
    time = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();

    agency->order("G", "1", "phl", 1, time, 0);
    time = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();

    agency->order("G", "1", "phl", 2, time, 0);
    time = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();

    //Error
    agency->order("B", "1", "phl", 2, time, 1);
    time = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();
    //Error
    agency->order("B", "2", "phl", 2, time, 1);
    time = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();
    //Error
    agency->order("B", "10", "phl", 2, time, 0);
    time = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();
    //Error
    agency->order("U", "2", "phl", 2, time, 0);
    time = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();

    agency->order("K", "1", "phl", 3, time, 0);

    agency->listOrder("1");
    agency->listOrder("2");
    return 0;
}
