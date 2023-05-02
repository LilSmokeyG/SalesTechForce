#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include "lib/JSON/json.hpp"
#include "lib/functions.h"

using json = nlohmann::json;

int main() {
    // Load client data from clientJson.json
    std::ifstream clientFile("jsonfiles/clientJson.json");
    json clientJson;
    clientFile >> clientJson;
    std::vector<Client> clients;
    for (const auto &client: clientJson["clients"]) {
        addClient(clients, clientJson);
    }

    // Load sales rep data from salesRepsJson.json
    std::ifstream salesRepFile("jsonfiles/salesRepsJson.json");
    json salesRepsJson;
    salesRepFile >> salesRepsJson;
    std::vector<SalesRep> salesReps;
    for (const auto &salesRep: salesRepsJson["salesReps"]) {
        addSalesRep(&salesReps, salesRepsJson);
    }

    // Load product data from productJson.json
    std::ifstream productFile("jsonfiles/productJson.json");
    json productJson;
    productFile >> productJson;
    std::vector<Product> products;
    for (const auto &product: productJson["products"]) {
        addProduct(products, productJson);
    }

    // Load sale data from saleJson.json
    std::ifstream saleFile("jsonfiles/saleJson.json");
    json saleJson;
    saleFile >> saleJson;
    std::vector<Sale> sales;
    for (const auto &sale: saleJson["sales"]) {
        addSale(sales, saleJson, clients, salesReps, products);
    }

    // Display main menu
    while (true) {
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1. Manage Clients" << std::endl;
        std::cout << "2. Manage Sales Reps" << std::endl;
        std::cout << "3. Manage Products" << std::endl;
        std::cout << "4. Manage Sales" << std::endl;
        std::cout << "5. Save and Quit" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Code for managing clients
                std::cout << "What would you like to do with clients?" << std::endl;
                std::cout << "1. Add a new client" << std::endl;
                std::cout << "2. Display list of clients" << std::endl;

                int clientChoice;
                std::cin >> clientChoice;

                switch (clientChoice) {
                    case 1: {
                        // Add new client
                        std::cout << "Enter client name: ";
                        std::string clientName;
                        std::cin.ignore();
                        std::getline(std::cin, clientName);

                        std::cout << "Enter client address: ";
                        std::string clientAddress;
                        std::getline(std::cin, clientAddress);

                        std::cout << "Enter client phone number: ";
                        std::string clientPhone;
                        std::getline(std::cin, clientPhone);

                        json clientJson = {
                                {"name",    clientName},
                                {"address", clientAddress},
                                {"phone",   clientPhone}
                        };

                        addClient(clients, clientJson);

                        std::cout << "New client added successfully!" << std::endl;
                        std::ofstream clientOutputFile("jsonfiles/clientJson.json");
                        clientOutputFile << std::setw(4) << clientJson;
                        clientOutputFile.close();
                        break;
                    }
                    case 2: {
// Display list of clients
                        displayClientList(clients);
                        break;
                    }
                    default: {
                        std::cout << "Invalid choice. Please try again." << std::endl;
                        break;
                    }
                }
                break;
            case 2:
// Code for managing sales reps
                std::cout << "What would you like to do with sales reps?" << std::endl;
                std::cout << "1. Add a new sales rep" << std::endl;
                std::cout << "2. Display list of sales reps" << std::endl;
                int salesRepChoice;
                std::cin >> salesRepChoice;

                switch (salesRepChoice) {
                    case 1: {
                        // Add new sales rep
                        std::cout << "Enter sales rep name: ";
                        std::string salesRepName;
                        std::cin.ignore();
                        std::getline(std::cin, salesRepName);

                        std::cout << "Enter sales rep email: ";
                        std::string salesRepEmail;
                        std::getline(std::cin, salesRepEmail);

                        json salesRepsJson = {
                                {"name",  salesRepName},
                                {"email", salesRepEmail},
                        };

                        addSalesRep(&salesReps, salesRepsJson);

                        std::cout << "New sales rep added successfully!" << std::endl;
                        std::ofstream salesRepOutputFile("jsonfiles/salesRepsJson.json");
                        salesRepOutputFile << std::setw(4) << salesRepsJson;
                        salesRepOutputFile.close();
                        break;
                    }
                    case 2: {
                        // Display list of sales reps
                        displaySalesRepList(salesReps);
                        break;
                    }
                    default: {
                        std::cout << "Invalid choice. Please try again." << std::endl;
                        break;
                    }
                }
                break;
            case 3:
                // Code for managing products
                std::cout << "What would you like to do with products?" << std::endl;
                std::cout << "1. Add a new product" << std::endl;
                std::cout << "2. Display list of products" << std::endl;

                int productChoice;
                std::cin >> productChoice;

                switch (productChoice) {
                    case 1: {
                        // Add new product
                        std::cout << "Enter product name: ";
                        std::string productName;
                        std::cin.ignore();
                        std::getline(std::cin, productName);

                        std::cout << "Enter product price: ";
                        double productPrice;
                        std::cin >> productPrice;

                        json productJson = {
                                {"name",  productName},
                                {"price", productPrice},
                        };

                        addProduct(products, productJson);

                        std::cout << "New product added successfully!" << std::endl;
                        std::ofstream productOutputFile("jsonfiles/productJson.json");
                        productOutputFile << std::setw(4) << productJson;
                        productOutputFile.close();
                        break;
                    }
                    case 2: {
                        // Display list of products
                        displayProductList(products);
                        break;
                    }
                    default: {
                        std::cout << "Invalid choice. Please try again." << std::endl;
                        break;
                    }
                }
                break;
            case 4:
                // Code for managing sales
                std::cout << "What would you like to do with sales?" << std::endl;
                std::cout << "1. Add a new sale" << std::endl;
                std::cout << "2. Display list of sales" << std::endl;

                int saleChoice;
                std::cin >> saleChoice;

                switch (saleChoice) {
                    case 1: {
                        // Add new sale
                        std::cout << "Enter sale client name: ";
                        std::string saleClientName;
                        std::cin.ignore();
                        std::getline(std::cin, saleClientName);

                        std::cout << "Enter sales rep name: ";
                        std::string saleSalesRepName;
                        std::getline(std::cin, saleSalesRepName);

                        std::cout << "Enter product name: ";
                        std::string saleProductName;
                        std::getline(std::cin, saleProductName);
                        std::cout << "Enter sale quantity: ";
                        int saleQuantity;
                        std::cin >> saleQuantity;

                        json saleJson = {
                                {"client name",    saleClientName},
                                {"sales rep name", saleSalesRepName},
                                {"product name",   saleProductName}
                        };

                        addSale(sales, saleJson, clients, salesReps, products);

                        std::cout << "New sale added successfully!" << std::endl;
                        std::ofstream saleOutputFile("jsonfiles/saleJson.json");
                        saleOutputFile << std::setw(4) << saleJson;
                        saleOutputFile.close();
                        break;
                    }
                    case 2: {
                        // Display list of sales
                        displaySalesList(sales, clients, salesReps, products);
                        break;
                    }
                    default: {
                        std::cout << "Invalid choice. Please try again." << std::endl;
                        break;
                    }
                }
                break;
            case 5:
                // Exit program
                std::cout << "Exiting program..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}