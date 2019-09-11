//
// Created by Yana on 09/12/2017.
//

#ifndef MIDTERMPRO_AGENCY_H
#define MIDTERMPRO_AGENCY_H


#include <iostream>
#include <string>
#include <stdlib.h>
#include "Service.h"
#include "Order.h"
#include <ctime>
#include <vector>

using namespace std;

/**
 * class ANode is built for storing data of a agency.
 * we create a ANode for each Agency.
 */
class ANode {

private:
    /**
     * cast the max_heap vector to a vector which contains elements in MAX_HEAP format
     * by using algorithm which its time complexity is O(log n)
     * @param loc   location of last order in max_heap vector ( index )
     */
    void castToMaxHeap(int loc) {
        if (loc - 1 == 0)
            return;
        int parent = (loc / 2) - 1;
        if (max_heap.at(parent)->priority < max_heap.at(loc - 1)->priority)
            return;

        if (max_heap.at(parent)->priority == max_heap.at(loc - 1)->priority) {
            if (max_heap.at(parent)->time <= max_heap.at(loc - 1)->time)
                return;
            else {
                Order *temp = max_heap.at(parent);
                max_heap.at(parent) = max_heap.at(loc - 1);
                max_heap.at(loc - 1) = temp;
                castToMaxHeap(parent + 1);
                return;
            }
        }

        if (max_heap.at(parent)->priority > max_heap.at(loc - 1)->priority) {
            Order *temp = max_heap.at(parent);
            max_heap.at(parent) = max_heap.at(loc - 1);
            max_heap.at(loc - 1) = temp;
            castToMaxHeap(parent + 1);
            return;
        }
    }

    /**
     * Heapify Max_Heap by starting at root recursively.
     * Time Complexity : O(log n)
     * @param loc       is root of a sub tree that most being heapify.
     */
    void change(int loc) {
        if (loc >= max)
            return;
        int c1 = (loc + 1) * 2 - 1;
        int c2 = (loc + 1) * 2;

        if (c1 >= max)
            return;
        if (c2 >= max) {
            Order *t = new Order();
            t->priority = INT8_MAX;
            max_heap.at(c2) = t;
        }

        //
        if (max_heap.at(loc)->priority < max_heap.at(c1)->priority &&
            max_heap.at(loc)->priority < max_heap.at(c2)->priority)
            return;

        if (max_heap.at(loc)->priority == max_heap.at(c1)->priority &&
            max_heap.at(loc)->priority < max_heap.at(c2)->priority) {
            if (max_heap.at(loc)->time <= max_heap.at(c1)->time)return;
            swap(loc, c1);
            change(c1);
        }

        if (max_heap.at(loc)->priority > max_heap.at(c1)->priority &&
            max_heap.at(loc)->priority < max_heap.at(c2)->priority) {
            swap(loc, c1);
            change(c1);
        }

        //

        if (max_heap.at(loc)->priority < max_heap.at(c1)->priority &&
            max_heap.at(loc)->priority == max_heap.at(c2)->priority) {
            if (max_heap.at(loc)->time <= max_heap.at(c2)->time)return;
            swap(loc, c2);
            change(c2);
        }

        if (max_heap.at(loc)->priority == max_heap.at(c1)->priority &&
            max_heap.at(loc)->priority == max_heap.at(c2)->priority) {
            if (max_heap.at(loc)->time < max_heap.at(c1)->time && max_heap.at(loc)->time < max_heap.at(c2)->time)return;
            if (max_heap.at(c1)->time < max_heap.at(loc)->time && max_heap.at(c1)->time < max_heap.at(c2)->time) {
                swap(loc, c1);
                change(c1);
            }
            if (max_heap.at(c2)->time < max_heap.at(loc)->time && max_heap.at(c2)->time < max_heap.at(c1)->time) {
                swap(loc, c2);
                change(c2);
            }
        }

        if (max_heap.at(loc)->priority > max_heap.at(c1)->priority &&
            max_heap.at(loc)->priority == max_heap.at(c2)->priority) {
            swap(loc, c1);
            change(c1);
        }

        //

        if (max_heap.at(loc)->priority < max_heap.at(c1)->priority &&
            max_heap.at(loc)->priority > max_heap.at(c2)->priority) {
            swap(loc, c2);
            change(c2);
        }

        if (max_heap.at(loc)->priority == max_heap.at(c1)->priority &&
            max_heap.at(loc)->priority > max_heap.at(c2)->priority) {
            swap(loc, c2);
            change(c2);
        }

        if (max_heap.at(loc)->priority > max_heap.at(c1)->priority &&
            max_heap.at(loc)->priority > max_heap.at(c2)->priority) {
            if (max_heap.at(c1)->priority > max_heap.at(c2)->priority) {
                swap(loc, c2);
                change(c2);
            }
            if (max_heap.at(c1)->priority < max_heap.at(c2)->priority) {
                swap(loc, c1);
                change(c1);
            }
            if (max_heap.at(c1)->time > max_heap.at(c2)->time) {
                swap(loc, c2);
                change(c2);
            }
            if (max_heap.at(c1)->time < max_heap.at(c2)->time) {
                swap(loc, c1);
                change(c1);
            } else {
                swap(loc, c1);
                change(c1);
            }
        }
    }

    /**
     * swap index a content and index b content in Vector oreder.
     * @param a
     * @param b
     */
    void swap(int a, int b) {
        Order *temp = max_heap.at(a);
        max_heap.at(a) = max_heap.at(b);
        max_heap.at(b) = temp;
    }

public:
    string agency_name;
    ANode *next;
    vector<Node *> nodes;
    vector<Order *> max_heap;
    int max = 0;
    int index = 0;

    void castToMaxHeap() {
        castToMaxHeap(max);
    }

    /**
     * This method replaces the first element of order Victor with last element
     * then decreases max 1 unit , then heapify Vector with calling change(0).
     */
    void satisfy_max_heap() {
        if (max == 0)
            return;
        delete (max_heap.at(0));
        max_heap.at(0) = max_heap.at(max - 1);
        max--;
        change(0);
    }
};

class Agency {
private:
    ANode *root;
    //an instance of Service class for doing some operation like add Offer , ...
    Service *se;

    /**
     * Find intended agency and return a reference to it.
     * @param agency_name
     * @return
     */
    ANode *whereIsAgency(string agency_name) {
        ANode *p = root;
        while (p = p->next)
            if (p->agency_name == agency_name)
                return p;
        return p;
    }

    /**
     * Is there any Service with name service_name among services of intended agency?
     * if yes , return true
     * else return false.
     * also determine location of Service among services Vector of intended agency.
     * @param service_name
     * @param agency
     * @param loc
     * @return
     */
    bool contain(string service_name, ANode *agency, int &loc) {
        for (int i = 0; i < agency->index; i++)
            if (agency->nodes.at(i)->service_name == service_name) {
                loc = i;
                return true;
            }

        return false;
    }

public:

    /**
     * Constructor of class Agency
     * in this section ,
     * create a redundant node for adding in first of agencies Linked List
     * to simplify deletion and iteration and ... on Linked List.
     * also
     * getting an instance of Service class to do next operations.
     * @param s
     */
    Agency(Service *s) {
        root = new ANode();
        root->next = nullptr;
        se = s;
        if (!se) {
            cout << "Error : Null service class to Agency constructor ." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
        }
    }


    /**
     * Add an agency to linked list of agencies.
     * also prevent form adding two Agency with same name.
     * @param agency_name
     */
    void addAgency(string agency_name) {

        ANode *p = root;
        ANode *q = root;
        while (p = p->next) {
            if (p->agency_name == agency_name) {
                cout << "Error : Agency " << agency_name << " exists." << endl;
                cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
                return;
            }
            q = q->next;
        }

        ANode *temp = new ANode();
        temp->agency_name = agency_name;
        temp->next = nullptr;

        q->next = temp;
        cout << "Agency " << agency_name << " added successfully." << endl;
        cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
    }

    /**
     * Print all agencies names.
     */
    void listAgencies() {
        if (!root->next) {
            cout << "No agency is in list." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
            return;
        }
        cout << "list of agencies :\n";
        ANode *q = root;
        while (q = q->next)
            cout << q->agency_name + " , ";
        cout << endl;
        cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
    }

    /**
     * Print all services of each agency respectively.
     * This process is executed by calling DFSServices method on each service of each agency.
     */
    void listServices() {
        if (!root->next) {
            cout << "No agency is in list." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
            return;
        }
        ANode *p = root;
        while (p = p->next) {
            cout << " - - - - - - -" << endl;
            cout << p->agency_name << " services : " << endl;
            for (int i = 0; i < p->index; i++) {
                cout << p->nodes.at(i)->service_name << " ---> ";
                se->DFSServices(p->nodes.at(i)->child);
                cout << "\n";
            }
        }
    }

    /**
     * Add an service to service Vector of intended agency.
     * with handling undefined behaviours like adding a service twice to an agency , ...
     * @param service_name
     * @param agency_name
     */
    void addOffer(string service_name, string agency_name) {

        ANode *p = whereIsAgency(agency_name);

        if (!p) {
            cout << "Error : There is no agency named " << agency_name << " ." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
            return;
        }

        int r;// no usage
        if (contain(service_name, p, r)) {
            cout << "Error : This service is available in this agency." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
            return;
        }

        Node *node = se->getRefrenceToMainService(service_name);
        if (!node) {
            cout << "Error : There is no service named " << service_name << " ." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
            return;
        }

        p->nodes.push_back(node);
        p->index++;
        cout << "Service " << service_name << " added to agency " << agency_name << " successfully." << endl;
        cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
    }

    /**
     * Delete a service from service Vector of agency
     * also if no agency points to that service , delete service
     * by calling deleteMainService Method of Service Class.
     * @param service_name
     * @param agency_name
     */
    void deleteService(string service_name, string agency_name) {
        ANode *p = whereIsAgency(agency_name);
        if (!p) {
            cout << "Error : There is no agency named " << agency_name << " ." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
            return;
        }

        int loc = -1;
        if (!contain(service_name, p, loc)) {
            cout << "Error : This agency does not contain service " << service_name << " ." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
            return;
        }

        try {
            p->nodes.at(loc) = p->nodes.at(p->index - 1);
        } catch (out_of_range &ex) {
            cout << ex.what() << endl;
        }
        p->index--;

        se->deleteMainService(service_name);
        cout << "Service " << service_name << " deleted from agency " << agency_name << " successfully." << endl;
    }

    /**
     * Order to agency.
     * Create an instance of Order and set values and add it to order Vector of agency.
     * with handling errors which may occur.
     * After operation , heapify the order vector.
     * @param service_name
     * @param agency_name
     * @param customer_name
     * @param priority
     * @param time
     */
    void order(string service_name, string agency_name, string customer_name, int priority,
               __int64 time, int identifier) {
        ANode *p = root;
        bool flag = false;
        while (p = p->next) {
            if (p->agency_name == agency_name) {
                flag = true;
                break;
            }
        }

        if (!flag) {
            cout << "Error : There is no agency named " << agency_name << " ." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
            return;
        }

        bool res = 0;
        for (int i = 0; i < p->index; i++) {
            res = res || se->contain(service_name, p->nodes.at(i), identifier);
            if (res)
                break;
        }

        if (!res) {
            cout << "Error : There is no service named " << service_name << " with input index." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
            return;
        }

//        if (p->max == MAX_SIZE) {
//            cout << "Error : list of orders is full . try later ." << endl;
//            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
//            return;
//        }


        Order *order = new Order();
        order->service_name = service_name;
        order->agency_name = agency_name;
        order->customer_name = customer_name;
        order->priority = priority;
        order->time = time;
        order->identifier = identifier;

        p->max_heap.push_back(order);
        p->max++;
        p->castToMaxHeap();
        cout << "Your order added to list of orders of agency successfully." << endl;
        cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
    }

    /**
     * Printing Orders of agency.
     * Time Complexity is O( n log n ) . because at first iterate on Vector of orders - O(n)
     * then heapify the max_heap of agency - O(nlogn).
     * @param agency_name
     */
    void listOrder(string agency_name) {
        ANode *p = root;
        bool flag = false;
        while (p = p->next) {
            if (p->agency_name == agency_name) {
                flag = true;
                break;
            }
        }

        if (!flag) {
            cout << "Error : There is no agency named " << agency_name << " for doing its orders ." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
            return;
        }

        cout << "Agency " << agency_name << " orders : " << endl;
        int counter = p->max;
        for (int i = 0; i < counter; i++) {
            cout << i + 1 << "- " << endl << "service name : " << p->max_heap.at(0)->service_name
                 << p->max_heap.at(0)->identifier
                 << " , " <<
                 "customer name : " << p->max_heap.at(0)->customer_name << endl << "priority : " <<
                 p->max_heap.at(0)->priority << " , " << "time : " << p->max_heap.at(0)->time << endl;
            p->satisfy_max_heap();
        }
        cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;

        p->max = 0;
    }
};


#endif //MIDTERMPRO_AGENCY_H
