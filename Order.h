//
// Created by Yana on 09/12/2017.
//

#ifndef MIDTERMPRO_ORDER_H
#define MIDTERMPRO_ORDER_H

#include "string"

using namespace std;

class Order {
public:
    string service_name;
    string agency_name;
    string customer_name;
    int priority;
    __int64 time;
    int identifier;
};


#endif //MIDTERMPRO_ORDER_H
