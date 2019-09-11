//
// Created by Yana on 09/12/2017.
//

#include "Service.h"

const string &Node::getCar_model() const {
    return car_model;
}

void Node::setCar_model(const string &car_model) {
    Node::car_model = car_model;
}

const string &Node::getCustomer_description() const {
    return customer_description;
}

void Node::setCustomer_description(const string &customer_description) {
    Node::customer_description = customer_description;
}

const string &Node::getSpecial_description() const {
    return special_description;
}

void Node::setSpecial_description(const string &special_description) {
    Node::special_description = special_description;
}

const string &Node::getAgency_cost() const {
    return agency_cost;
}

void Node::setAgency_cost(const string &agency_cost) {
    Node::agency_cost = agency_cost;
}
