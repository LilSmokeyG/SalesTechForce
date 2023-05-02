#include "functions.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "JSON/json.hpp"

using json = nlohmann::json;

[[maybe_unused]] void addClient(std::vector<Client> &clients, const json &clientJson) {
    // Parse the data from the json object
    std::string name = clientJson["name"];
    std::string address = clientJson["address"];
    std::string phone = clientJson["phone"];

    // Check if the phone number already exists in the vector
    bool exists = false;
    for (const auto &client: clients) {
        if (client.phoneNumber == phone) {
            exists = true;
            break;
        }
    }

    // If the phone number doesn't exist, create a new Client object with the parsed data and add it to the vector
    if (!exists) {
        clients.emplace_back(name, phone, address);
    } else {
        std::cout << "Error: Phone number already exists for another client." << std::endl;
    }
}

void displayClientList(const std::vector<Client> &clients) {
    std::cout << "List of Clients:" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    for (const auto &client: clients) {
        std::cout << "Name: " << client.name << std::endl;
        std::cout << "Phone Number: " << client.phoneNumber << std::endl;
        std::cout << "Address: " << client.address << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
}

[[maybe_unused]] void addSalesRep(std::vector<SalesRep> &salesReps, const json &salesRepsJson) {
    // Parse the data from the json object
    std::string name = salesRepsJson["name"];
    std::string email = salesRepsJson["email"];
    std::string phoneNumber = salesRepsJson["phone"];

    // Create a new SalesRep object with the parsed data and add it to the vector
    salesReps.emplace_back(name, phoneNumber, email);
}

void displaySalesRepList(const std::vector<SalesRep> &salesReps) {
    std::cout << "List of Sales Representatives:" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    for (const auto &salesRep: salesReps) {
        std::cout << "Name: " << salesRep.name << std::endl;
        std::cout << "Phone Number: " << salesRep.phoneNumber << std::endl;
        std::cout << "Email: " << salesRep.email << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
}

[[maybe_unused]] void addProduct(std::vector<Product> &products, const json &productJson) {
    // Parse the data from the json object
    std::string name = productJson["name"];
    std::string description = productJson["description"];
    double price = productJson["price"];

    // Create a new Product object with the parsed data and add it to the vector
    products.emplace_back(name, description, price);
}

void displayProductList(const std::vector<Product> &products) {
    std::cout << "List of Products:" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    for (const auto &product: products) {
        std::cout << "Name: " << product.name << std::endl;
        std::cout << "Price: " << product.price << std::endl;
        std::cout << "Description: " << product.description << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
}

[[maybe_unused]] void addSale(std::vector<Sale> &sales, const json &saleJson, const std::vector<Client> &clients,
             const std::vector<Product> &products, const std::vector<SalesRep> &salesReps) {
    // Check if the required fields are present in the JSON object
    if (!saleJson.contains("client_name") || !saleJson.contains("product_name") ||
        !saleJson.contains("sales_rep_name") || !saleJson.contains("quantity") || !saleJson.contains("price")) {
        std::cerr << "Error: Sale is missing required field" << std::endl;
        return;
    }

    // Parse the data from the JSON object
    std::string clientName = saleJson["client_name"].get<std::string>();
    std::string productName = saleJson["product_name"].get<std::string>();
    std::string salesRepName = saleJson["sales_rep_name"].get<std::string>();
    int quantity = saleJson["quantity"].get<int>();
    double price = saleJson["price"].get<double>();

    // Find the index of the corresponding Client, Product and SalesRep objects
    int clientIndex = -1;
    int productIndex = -1;
    int salesRepIndex = -1;

    for (const auto &client: clients) {
        if (client.name == clientName) {
            clientIndex = &client - &clients.front();
            break;
        }
    }

    for (const auto &product: products) {
        if (product.name == productName) {
            productIndex = &product - &products.front();
            break;
        }
    }

    for (const auto &salesRep: salesReps) {
        if (salesRep.name == salesRepName) {
            salesRepIndex = &salesRep - &salesReps.front();
            break;
        }
    }

    if (clientIndex == -1 || productIndex == -1 || salesRepIndex == -1) {
        std::cerr << "Error: Sale contains invalid client, product or sales rep name" << std::endl;
        return;
    }

    if (quantity <= 0) {
        std::cerr << "Error: Sale contains invalid quantity" << std::endl;
        return;
    }

    if (price <= 0) {
        std::cerr << "Error: Sale contains invalid price" << std::endl;
        return;
    }

    // Check if the vector has reached its maximum size
    if (sales.size() == sales.capacity()) {
        std::cerr << "Error: Maximum sales limit reached" << std::endl;
        return;
    }

    // Create a new Sale object with the parsed data and add it to the vector
    sales.emplace_back(clients[clientIndex], products[productIndex], salesReps[salesRepIndex], quantity, price);
}

void displaySalesList(const std::vector<Sale> &sales, const std::vector<Client> &clients,
                      const std::vector<SalesRep> &salesReps, const std::vector<Product> &products) {
    std::cout << "List of Sales:" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    for (const auto &sale: sales) {
        std::cout << "Product: " << sale.product.name << std::endl;
        std::cout << "Price: " << sale.price << std::endl;
        std::cout << "Quantity: " << sale.quantity << std::endl;
        std::cout << "Sold by: " << sale.salesRep.name << std::endl;
        std::cout << "Sold to: " << sale.client.name << std::endl;
        std::cout << "Total Price: " << sale.price * sale.quantity << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
}

[[maybe_unused]] json getClientJson(const std::vector<Client> &clients) {
    json clientsJson;
    for (const auto &client: clients) {
        json clientJson = {
                {"name",    client.name},
                {"address", client.address},
                {"phone",   client.phoneNumber}
        };
        clientsJson.push_back(clientJson);
    }
    return clientsJson;
}

[[maybe_unused]] json getSalesRepJson(const std::vector<SalesRep> &salesReps) {
    json salesRepsJson;
    for (const auto &salesRep: salesReps) {
        json salesRepJson = {
                {"name",        salesRep.name},
                {"phoneNumber", salesRep.phoneNumber},
                {"email",       salesRep.email}
        };
        salesRepsJson.push_back(salesRepJson);
    }
    return salesRepsJson;
}

[[maybe_unused]] json getProductJson(const std::vector<Product> &products) {
    json productsJson;
    for (const auto &product: products) {
        json productJson = {
                {"name",        product.name},
                {"price",       product.price},
                {"description", product.description}
        };
        productsJson.push_back(productJson);
    }
    return productsJson;
}

[[maybe_unused]] json getSalesJson(const std::vector<Sale> &sales) {
    json salesJson;
    for (const auto &sale: sales) {
        json saleJson(json::value_t::object);
        saleJson["clientName"] = sale.client.name;
        saleJson["salesRepName"] = sale.salesRep.name;
        saleJson["productName"] = sale.product.name;
        saleJson["quantity"] = sale.quantity;
        salesJson.push_back(saleJson);
    }
    return salesJson;
}
