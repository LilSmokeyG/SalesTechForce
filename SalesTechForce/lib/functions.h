#pragma once
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <vector>
#include "JSON/json.hpp"

using json = nlohmann::json;

struct Client {
    std::string name;
    std::string address;
    std::string phoneNumber;

    Client(std::string name, std::string phoneNumber, std::string address)
            : name(name), phoneNumber(phoneNumber), address(address) {}

    Client(const Client& other) {
        Client temp(other);
        swap(temp);
    }

    void swap(Client& other) {
        std::swap(name, other.name);
        std::swap(address, other.address);
        std::swap(phoneNumber, other.phoneNumber);
    }

    Client& operator=(Client other) {
        swap(other);
        return *this;
    }
};

struct SalesRep {
    std::string name;
    std::string email;
    std::string phoneNumber;

    SalesRep(std::string name, std::string phoneNumber, std::string email)
            : name(name), phoneNumber(phoneNumber), email(email) {}

    // Define the copy-and-swap idiom for assignment operator
    SalesRep& operator=(SalesRep other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(SalesRep& first, SalesRep& second) {
        using std::swap;
        swap(first.name, second.name);
        swap(first.email, second.email);
        swap(first.phoneNumber, second.phoneNumber);
    }
};

struct Product {
    std::string name;
    std::string description;
    double price;

    Product(std::string n, std::string d, double p)
            : name(n), description(d), price(p) {}
};

struct Sale {
    Client client;
    Product product;
    SalesRep salesRep;
    int quantity;
    double price; // add an additional parameter for price
    Sale(Client c, Product p, SalesRep s, int q, double pr) :
            client(c), product(p), salesRep(s), quantity(q), price(pr) {}
};

extern void addClient(std::vector<Client>& clients, json& clientsJson);
extern void displayClientList(const std::vector<Client>& clients);
extern void addSalesRep(std::vector<SalesRep> *salesReps, json& salesRepsJson);
extern void displaySalesRepList(const std::vector<SalesRep>& salesReps);
extern void addProduct(std::vector<Product>& products, json& productsJson);
extern void displayProductList(const std::vector<Product>& products);
extern void addSale(std::vector<Sale>& sales, json& salesJson, const std::vector<Client>& clients, const std::vector<SalesRep>& salesReps, const std::vector<Product>& products);
extern void displaySalesList(const std::vector<Sale>& sales, const std::vector<Client>& clients, const std::vector<SalesRep>& salesReps, const std::vector<Product>& products);

[[maybe_unused]] json getClientJson(const std::vector<Client>& clients);

[[maybe_unused]] json getSalesJson(const std::vector<Sale>& sales);

[[maybe_unused]] json getProductJson(const std::vector<Product>& products);

[[maybe_unused]] json getSalesRepJson(const std::vector<SalesRep>& salesReps);