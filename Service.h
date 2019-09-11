//
// Created by Yana on 09/12/2017.
//

#ifndef MIDTERMPRO_SERVICE_H
#define MIDTERMPRO_SERVICE_H


#include <iostream>
#include <string>
#include <stdlib.h>
#include <stack>

using namespace std;

/**
 * class Node is built for storing data of a service or sub service.
 * we create a Node for each Service or Sub Service .
 */
class Node {
private:
    string car_model;
    string customer_description;
    string special_description;
    string agency_cost;
public:
    string service_name;
    Node *next = nullptr;
    Node *child = nullptr;
    int identifier = 0;

    //Number of agencies that point to this service ,
    //if Node is used as Sub Service , no need to use this field
    int agency = 0;

    const string &getCar_model() const;

    void setCar_model(const string &car_model);

    const string &getCustomer_description() const;

    void setCustomer_description(const string &customer_description);

    const string &getSpecial_description() const;

    void setSpecial_description(const string &special_description);

    const string &getAgency_cost() const;

    void setAgency_cost(const string &agency_cost);
};

/**
 * This class contains the major methods which used for handling Services and Sub Services ,
 * contains the root of Services ( alternatively this root is used for accessing Sub Services. )
 */
class Service {
private:
    Node *root;

    //a and b for storing indexes.
    //a and b are used for avoiding creation 2 Node with same name.
    //if you try to build 2 Nodes with same names , program tries to add an index
    //to end of second Node to distinguish between them .
    string a[100];
    int b[100];


    //This index is used for determining last section of array of a or b which is full.
    int index = 0;

    /**
     * Create a Node which can be interpreted as Service or Sub Service.
     * This method is used while adding a Service or Sub Service .
     * @param service_name  name of Service or Sub Service
     * @param i             is used for distinguish between 2 Nodes which have same names
     * @return              the address of new Node
     */
    Node *createNode(string service_name, int i) {
        Node *node = new Node();
        node->service_name = service_name;
        node->next = nullptr;
        node->child = nullptr;
        node->identifier = i;
        return node;
    }


    /**
     * Find parent of Sub Service.
     * More information in PDF file.
     * @param service_name
     * @param sub_service_name
     * @param start
     * @return
     */
    Node *findParent(string service_name, string sub_service_name, Node *start, int ind) {
        //The stack is created for checking that adding this sub service
        //to its parent may create a loop or not
        stack<Node *> *s = new stack<Node *>();

        Node *node = findParent(service_name, start, s, ind);

        if (node)
            while (!s->empty()) {
                //Because of creating loop with adding this sub service
                //terminating the function and call back to caller by sending pointer -1
                //to it.
                if (s->top()->service_name == sub_service_name) {
                    cout << "Error : " << service_name << " is sub service of " << sub_service_name << " ." << endl
                         << "Can not create loop." << endl;
                    delete (s);
                    cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
                    return (Node *) -1;
                }
                s->pop();
            }
        delete (s);
        return node;
    }

    /**
     * Find Parent of Sub Service with using an algorithm like DFS algorithm in Graph theory.
     * also set the path from root to parent in stack for other operations.
     * @param name
     * @param p
     * @param s
     * @param ind
     * @return
     */
    Node *findParent(string name, Node *p, stack<Node *> *s, int ind) {
        //if p is NULL
        //pop from stack and resuming dfs processing
        if (!p) {
            if (s->empty())
                return nullptr;
            p = s->top()->next;
            s->pop();
            if (!p)
                return findParent(name, nullptr, s, ind);
            s->push(p);
            return findParent(name, p, s, ind);
        }

        if (p->service_name == name && p->identifier == ind)
            return p;

        s->push(p);
        return findParent(name, p->child, s, ind);
    }

    /**
     * Print information of all Sub Services of a Node.
     * In other words, print information of all children of a Node and
     * recursively print information of children of that children.
     * @param p     starting point of print
     */
    void print(Node *p) {
        if (!p)
            return;
        while (p) {
            cout << p->service_name << p->identifier << " ( ";
            print(p->child);
            cout << " ) ";
            p = p->next;
        }
    }

    /**
     * Delete all Sub Services of a Node and itself
     * @param p     starting point of delete
     */
    void deleteNode(Node *p) {
        if (!p)
            return;
        deleteNode(p->next);
        deleteNode(p->child);
        delete (p);
    }

public:

    /**
     * Constructor of class Service
     * in this section ,
     * create a redundant node for adding in first of Generalized Linked List
     * to simplify deletion and iteration and ... on Generalized Linked List.
     * also
     * set initial value for array a and b
     */
    Service() {
        root = new Node();
        root->next = nullptr;
        root->child = nullptr;
        for (int i = 0; i < 20; i++) {
            a[i] = " ";
            b[i] = 0;
        }
    }

    ~Service(){

    }

    /**
     * Add a Service to Generalized Linked List by creating a new Node.
     * with handling Errors which may occur during adding Service to Generalized Linked List.
     * Time Complexity: O(1) with ignoring number of Services in GList.
     * @param service_name      name of service for passing to createNode function .
     */
    void addService(string service_name) {

        //If this service is available , terminate the function.
        Node *start = root;
        Node *p = root;
        while (start = start->next) {
            if (start->service_name == service_name) {
                cout << "Can not add this service because the service is available." << endl;
                cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
                return;
            }
            p = start;
        }

        //This service is not in list , so add it to list.
        Node *node = createNode(service_name, 0);
        p->next = node;

        cout << "Service " << service_name << " added successfully.\n";
        cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
    }

//    add sub service to service not to sub service
//    void addSubService(string sub_service_name, string parent) {
//
//        //Check there is parent in list or not .
//        Node *p = nodeLocation(parent, root);
//        if (!p) {
//            cout << "Error : Parent is not in list." << endl;
//            return;
//        }
//
//        Node *father = p;
//        Node *midNode_in_child = nullptr;
//
//        //does parent contain sub ?
//        p = p->child;
//        bool tag = false;
//        while (p) {
//            if (p->service_name == sub_service_name) {
//                if (p->contain(parent)) {
//                    cout << "Error : Sub service " + sub_service_name + " is in list.\n";
//                    return;
//                }
//                tag = true;
//                break;
//            }
//            midNode_in_child = p;
//            p = p->next;
//        }
//
//
//        //parent contains sub
//        if (tag) {
//            p->addFather(father);
//            cout << "Sub service " + sub_service_name + " added to service " + parent << endl;
//            return;
//        }
//
//        //now parnet does not contain sub
//
//        //does <list> ( not parent ) contain sub ? *sub is answer , if null -> not contain else contain
//        Node *sub = nodeLocation(sub_service_name, root);
//
//        //list does not contain sub
//        if (!sub) {
//            Node *temp = new Node();
//            temp->service_name = sub_service_name;
//            temp->next = nullptr;
//            temp->child = nullptr;
//            temp->addFather(father);
//
//            //find last node in child
//            //not necessary
//            while (midNode_in_child->next)
//                midNode_in_child = midNode_in_child->next;
//
//            midNode_in_child->next = temp;
//            cout << "Sub service " + sub_service_name + " added to service " + parent << endl;
//            return;
//        }
//
//        //list contain sub
//
//        //check collision
//        bool path = false;
//        while (sub) {
//            if(sub == )
//        }
//    }

    /**
    * Add a Sub Service to a Service with handling Errors which may occur
    * during the operation .
    * For example , prevent creation of loop by adding this Sub Service to intended Service.
    * This Handling is implemented by using stack.
    * also
    * if there is a Sub Service in Generalized Linked List with same name to new Sub Service,
    * we distinguish between these Sub Services by adding identifier to those Nodes.
    * Time Complexity: in worst case , we most search all Nodes in GList to find parent,
    * so O(n) , n number of Nodes in GList.
    * More information in PDF file.
    * @param sub_service_name
    * @param parent
    * @param ind
    */
    void addSubService(string sub_service_name, string parent, int ind) {

        //Check there is parent in list or not .
        Node *p = findParent(parent, sub_service_name, root, ind);
        if (!p) {
            cout << "Error : The parent of this service is not in list." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
            return;
        }
        if (p == (Node *) -1)
            return;

//????
//        stack<Node *> *stack = new stack<Node *>();
//        Node *q = findParent(sub_service_name, p, stack);
//
//        if (q) {
//            cout << "Error : The sub service is in the list." << endl;
//            return;
//        }

        //Checking that sub service is already child of its parent or not.
        Node *q = p->child;
        while (q) {
            if (q->service_name == sub_service_name) {
                cout << "Error : The sub service " << sub_service_name << " is already child of its parent." << endl;
                cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
                return;
            }
            if (!q->next)
                break;
            q = q->next;
        }

        //Setting identifier for new node to distinguish between it and other sub services like it.
        bool flag = false;
        int identifier = 0;
        for (int i = 0; i < index; i++) {
            if (a[i] == sub_service_name) {
                b[i]++;
                identifier = b[i];
                flag = true;
                break;
            }
        }

        if (!flag) {
            a[index] = sub_service_name;
            index++;
            identifier = 0;
        }

        //Create new node.
        Node *node = createNode(sub_service_name, identifier);

        if (!p->child) {
            p->child = node;
            cout << "The sub service " << sub_service_name << " added to service " << parent << " successfully."
                 << endl;
            cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
            return;
        }

        q->next = node;
        cout << "The sub service " << sub_service_name << " added to service " << parent << "  successfully." << endl;
        cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
    }

    /**
     * Return a pointer to mentioned Service with name service_name
     * if there is no Service named service_name , return NULL.
     * The caller of this method is an agency ,
     * so service->agency++;
     * Time complexity: O(n)
     * n : number of Services in GList.
     * @param service_name
     * @return Node*
     */
    Node *getRefrenceToMainService(string service_name) {
        Node *p = root;
        while (p = p->next) {
            if (p->service_name == service_name) {
                p->agency++;
                return p;
            }
        }
        return nullptr;
    }

    /**
     * Find a service and delete it and its children by calling method deleteNode.
     * Time complexity: is same as time complexity of listServicesFrom method ,
     * that's mean O ( k + n )
     * k : number of Services in GList.
     * n : number of all Nodes in GList.
     * reason same as the reasons in documentation of listServicesFrom method
     * @param service_name
     */
    void deleteMainService(string service_name) {
        Node *p = root;
        Node *pre = root;
        while (p = p->next) {
            if (p->service_name == service_name) {
                if (!p->agency)
                    break;
                p->agency--;
                return;
            }
            pre = p;
        }

        if (!p)
            return;

        pre->next = p->next;
        deleteNode(p);
    }

    /**
     * Print all sub Services of the intended Service by calling print method.
     * time complexity: O(k + n )
     * k is Number of Services . O(k) for searching intended Service.
     * O(n) is time complexity of print method . n is Number of Sub Services of intended Service.
     * Because of our GList has long depth and short width , n is approximately equal with number of all Nodes in GList.
     * For checking time complexity , this assumption is true.
     * @param service_name
     */
    void listServicesFrom(string service_name) {

        Node *p = root;
        while (p = p->next) {
            if (p->service_name == service_name) {
                cout << "Sub services of " << service_name << p->identifier << " : " << endl;
                print(p->child);
                cout << endl << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
                return;
            }
        }
        cout << "There is not any main service named " << service_name << " ." << endl;
        cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
    }

    /**
     * Checks Service or Sub Service with service_name exists in Generalized Linked List or not
     * This operation is implemented by using this method recursively.
     * if exists , returning true
     * else returning false
     * For doing this operation in worst case , all Nodes in Generalized list most be visited
     * so the time complexity is O(n) . n is number of all Nodes in generalized Linked List.
     * @param service_name
     * @param parent
     * @return boolean
     */
    bool contain(string service_name, Node *parent, int identifier) {
        if (!parent)
            return 0;

        if (parent->service_name == service_name && parent->identifier == identifier)
            return 1;

        Node *child = parent->child;
        bool res = 0;
        while (child) {
            res = res || contain(service_name, child, identifier);
            if (res)
                return 1;
            child = child->next;
        }
        return res;
    }

    /**
     * Print all services of Generalized Linked List.
     * This process is executed by calling DFSServices method on each service.
     */
    void listServices() {
        if (!root->next) {
            cout << "No service is in list." << endl;
            cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
            return;
        }
        Node *p = root;
        while (p = p->next) {
            cout << " - - - - - - -" << endl;
            cout << p->service_name << " sub services : " << endl;
            DFSServices(p->child);
            cout << "\n";
        }
        cout << endl << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
    }

    /**
     * Iterate on all Services and print Sub Services names.
     * Algorithm which used for doing this operation is like DFS algorithm for calibration on a graph.
     * @param p
     */
    void DFSServices(Node *p) {
        if (!p)return;
        while (p) {
            cout << p->service_name << p->identifier << " ( ";
            DFSServices(p->child);
            cout << " ) ";
            p = p->next;
        }
    }

};


#endif //MIDTERMPRO_SERVICE_H
