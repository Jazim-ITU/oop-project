
#include "User.h"
#include "Customer.h"
#include "Admin.h"
#include "Electronics.h"
#include "Clothing.h"
#include "Food.h"
#include "Inventory.h"
#include "Payment.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;


vector<Customer*> customers;
vector<Admin*> admins;
Inventory* mainInventory;
ofstream logFile;


void initializeSystem();
void cleanupSystem();
void writeLog(const string& message);
string getCurrentTimestamp();
void displayMainMenu();
void handleCustomerLogin();
void handleAdminLogin();
void customerMenu(Customer* customer);
void adminMenu(Admin* admin);
void viewProducts();
void createSampleData();
Customer* findCustomer(const string& username);
Admin* findAdmin(const string& username);

int main() {
    cout << "=== Welcome to E-Commerce Management System ===" << endl;


    initializeSystem();
    createSampleData();

    int choice;
    do {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            handleCustomerLogin();
            break;
        case 2:
            handleAdminLogin();
            break;
        case 3:
            viewProducts();
            break;
        case 4:
            cout << "Thank you for using E-Commerce Management System!" << endl;
            writeLog("System shutdown initiated");
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
            writeLog("Invalid menu choice attempted: " + to_string(choice));
        }
    } while (choice != 4);

    cleanupSystem();
    return 0;
}

void initializeSystem() {

    logFile.open("ecommerce_log.txt", ios::app);
    if (!logFile.is_open()) {
        cout << "Warning: Could not open log file!" << endl;
    }

    writeLog("E-Commerce System started");


    mainInventory = new Inventory(1, "Main Warehouse");
    writeLog("Main inventory initialized");
}

void cleanupSystem() {
    writeLog("System cleanup initiated");


    for (Customer* customer : customers) {
        delete customer;
    }
    customers.clear();


    for (Admin* admin : admins) {
        delete admin;
    }
    admins.clear();


    delete mainInventory;

    writeLog("System cleanup completed");

    if (logFile.is_open()) {
        logFile.close();
    }
}

void writeLog(const string& message) {
    if (logFile.is_open()) {
        logFile << getCurrentTimestamp() << " - " << message << endl;
        logFile.flush();
    }
}

string getCurrentTimestamp() {
    time_t now = time(0);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    char timestamp[100];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return string(timestamp);
}

void displayMainMenu() {
    cout << "\n=== MAIN MENU ===" << endl;
    cout << "1. Customer Login" << endl;
    cout << "2. Admin Login" << endl;
    cout << "3. View Products" << endl;
    cout << "4. Exit" << endl;
    cout << "==================" << endl;
}

void handleCustomerLogin() {
    cout << "\n=== CUSTOMER LOGIN ===" << endl;

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    writeLog("Customer login attempt - Username: " + username);

    Customer* customer = findCustomer(username);

    if (customer != nullptr && customer->login(username, password)) {
        cout << "Login successful! Welcome " << customer->getUsername() << endl;
        writeLog("Customer login successful - Username: " + username);
        customerMenu(customer);
    }
    else {
        cout << "Invalid credentials! Would you like to register? (y/n): ";
        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            cout << "Enter email: ";
            string email;
            cin >> email;
            cout << "Enter address: ";
            cin.ignore();
            string address;
            getline(cin, address);
            cout << "Enter phone number: ";
            string phone;
            cin >> phone;

            Customer* newCustomer = new Customer(static_cast<int>(customers.size()) + 1, username, email, password, address, phone);
            customers.push_back(newCustomer);

            cout << "Registration successful! Welcome " << username << endl;
            writeLog("New customer registered - Username: " + username + ", Email: " + email);
            customerMenu(newCustomer);
        }
        else {
            writeLog("Customer login failed - Username: " + username);
        }
    }
}

void handleAdminLogin() {
    cout << "\n=== ADMIN LOGIN ===" << endl;

    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    writeLog("Admin login attempt - Username: " + username);

    Admin* admin = findAdmin(username);

    if (admin != nullptr && admin->login(username, password)) {
        cout << "Admin login successful! Welcome " << admin->getUsername() << endl;
        writeLog("Admin login successful - Username: " + username);
        adminMenu(admin);
    }
    else {
        cout << "Invalid admin credentials!" << endl;
        writeLog("Admin login failed - Username: " + username);
    }
}

void customerMenu(Customer* customer) {
    int choice;
    do {
        cout << "\n=== CUSTOMER MENU ===" << endl;
        cout << "1. View Profile" << endl;
        cout << "2. Browse Products" << endl;
        cout << "3. Add Product to Cart" << endl;
        cout << "4. View Shopping Cart" << endl;
        cout << "5. Place Order" << endl;
        cout << "6. View Order History" << endl;
        cout << "7. Update Profile" << endl;
        cout << "8. Logout" << endl;
        cout << "=====================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            customer->displayInfo();
            writeLog("Customer " + customer->getUsername() + " viewed profile");
            break;

        case 2:
            viewProducts();
            writeLog("Customer " + customer->getUsername() + " browsed products");
            break;

        case 3: {
            cout << "Enter product ID to add to cart: ";
            int productId;
            cin >> productId;

            Product* product = mainInventory->getProduct(productId);
            if (product != nullptr) {
                cout << "Enter quantity: ";
                int quantity;
                cin >> quantity;

                try {
                    customer->addToCart(product, quantity);
                    writeLog("Customer " + customer->getUsername() + " added product ID " +
                        to_string(productId) + " (qty: " + to_string(quantity) + ") to cart");
                }
                catch (const string& error) {
                    cout << "Error: " << error << endl;
                    writeLog("Add to cart failed for customer " + customer->getUsername() + ": " + error);
                }
            }
            else {
                cout << "Product not found!" << endl;
                writeLog("Customer " + customer->getUsername() + " tried to add non-existent product ID " + to_string(productId));
            }
            break;
        }

        case 4:
            customer->getCart()->displayCart();
            writeLog("Customer " + customer->getUsername() + " viewed shopping cart");
            break;

        case 5: {
            if (customer->getCart()->isEmpty()) {
                cout << "Your cart is empty!" << endl;
            }
            else {
                Order* order = customer->placeOrder();
                if (order != nullptr) {

                    cout << "Choose payment method:" << endl;
                    cout << "1. Credit Card" << endl;
                    cout << "2. PayPal" << endl;
                    int paymentChoice;
                    cin >> paymentChoice;

                    try {
                        Payment* payment = nullptr;
                        if (paymentChoice == 1) {
                            string cardNumber, expiry, cvv;
                            cout << "Enter card number (16 digits): ";
                            cin >> cardNumber;
                            cout << "Enter expiry date (MM/YY): ";
                            cin >> expiry;
                            cout << "Enter CVV: ";
                            cin >> cvv;

                            payment = new CreditCardPayment(order->getOrderId(), order->getTotalAmount(), cardNumber, expiry, cvv);
                            writeLog("Customer " + customer->getUsername() + " chose Credit Card payment");
                        }
                        else if (paymentChoice == 2) {
                            string email, password;
                            cout << "Enter PayPal email: ";
                            cin >> email;
                            cout << "Enter PayPal password: ";
                            cin >> password;

                            payment = new PayPalPayment(order->getOrderId(), order->getTotalAmount(), email, password);
                            writeLog("Customer " + customer->getUsername() + " chose PayPal payment");
                        }

                        if (payment != nullptr) {
                            order->setPayment(payment);
                            order->processOrder();
                            customer->addLoyaltyPoints(static_cast<int>(order->getTotalAmount() / 10));
                            writeLog("Order placed successfully by customer " + customer->getUsername() +
                                " - Order ID: " + to_string(order->getOrderId()) +
                                ", Amount: $" + to_string(order->getTotalAmount()));
                        }
                    }
                    catch (const string& error) {
                        cout << "Payment failed: " << error << endl;
                        writeLog("Payment failed for customer " + customer->getUsername() + ": " + error);
                    }
                }
            }
            break;
        }

        case 6:
            customer->viewOrderHistory();
            writeLog("Customer " + customer->getUsername() + " viewed order history");
            break;

        case 7: {
            cout << "Enter new email: ";
            string newEmail;
            cin >> newEmail;
            customer->updateProfile(newEmail);
            writeLog("Customer " + customer->getUsername() + " updated profile - New email: " + newEmail);
            break;
        }

        case 8:
            cout << "Logging out..." << endl;
            writeLog("Customer " + customer->getUsername() + " logged out");
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 8);
}

void adminMenu(Admin* admin) {
    int choice;
    do {
        cout << "\n=== ADMIN MENU ===" << endl;
        cout << "1. View Profile" << endl;
        cout << "2. View All Products" << endl;
        cout << "3. Add New Product" << endl;
        cout << "4. Remove Product" << endl;
        cout << "5. Update Stock" << endl;
        cout << "6. Generate Inventory Report" << endl;
        cout << "7. View System Logs" << endl;
        cout << "8. Manage Orders" << endl;
        cout << "9. Logout" << endl;
        cout << "==================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            admin->displayInfo();
            writeLog("Admin " + admin->getUsername() + " viewed profile");
            break;

        case 2:
            mainInventory->displayInventory();
            writeLog("Admin " + admin->getUsername() + " viewed all products");
            break;

        case 3: {
            cout << "Choose product type:" << endl;
            cout << "1. Electronics" << endl;
            cout << "2. Clothing" << endl;
            cout << "3. Food" << endl;
            int typeChoice;
            cin >> typeChoice;

            cout << "Enter product details:" << endl;
            cout << "Product ID: ";
            int id;
            cin >> id;

            cout << "Name: ";
            cin.ignore();
            string name;
            getline(cin, name);

            cout << "Price: ";
            double price;
            cin >> price;

            cout << "Stock: ";
            int stock;
            cin >> stock;

            cout << "Description: ";
            cin.ignore();
            string desc;
            getline(cin, desc);

            Product* product = nullptr;

            try {
                if (typeChoice == 1) {
                    cout << "Warranty (months): ";
                    int warranty;
                    cin >> warranty;
                    cout << "Brand: ";
                    string brand;
                    cin >> brand;
                    cout << "Model: ";
                    string model;
                    cin >> model;

                    product = new Electronics(id, name, price, stock, desc, warranty, brand, model);
                    writeLog("Admin " + admin->getUsername() + " created Electronics product: " + name);
                }
                else if (typeChoice == 2) {
                    cout << "Size: ";
                    string size;
                    cin >> size;
                    cout << "Color: ";
                    string color;
                    cin >> color;
                    cout << "Material: ";
                    string material;
                    cin >> material;

                    product = new Clothing(id, name, price, stock, desc, size, color, material);
                    writeLog("Admin " + admin->getUsername() + " created Clothing product: " + name);
                }
                else if (typeChoice == 3) {
                    cout << "Days until expiry: ";
                    int days;
                    cin >> days;
                    time_t expiry = time(nullptr) + (days * 24 * 60 * 60);

                    cout << "Category: ";
                    string category;
                    cin >> category;
                    cout << "Nutritional info: ";
                    cin.ignore();
                    string nutrition;
                    getline(cin, nutrition);
                    cout << "Is perishable? (1/0): ";
                    bool perishable;
                    cin >> perishable;

                    product = new Food(id, name, price, stock, desc, expiry, category, nutrition, perishable);
                    writeLog("Admin " + admin->getUsername() + " created Food product: " + name);
                }

                if (product != nullptr) {
                    admin->addProduct(product, *mainInventory);
                    writeLog("Product added to inventory by admin " + admin->getUsername() + " - ID: " + to_string(id));
                }
            }
            catch (const string& error) {
                cout << "Error creating product: " << error << endl;
                writeLog("Product creation failed by admin " + admin->getUsername() + ": " + error);
            }
            break;
        }

        case 4: {
            cout << "Enter product ID to remove: ";
            int productId;
            cin >> productId;
            admin->removeProduct(productId, *mainInventory);
            writeLog("Admin " + admin->getUsername() + " removed product ID: " + to_string(productId));
            break;
        }

        case 5: {
            cout << "Enter product ID: ";
            int productId;
            cin >> productId;
            cout << "Enter quantity change (+ to add, - to remove): ";
            int quantity;
            cin >> quantity;
            mainInventory->updateStock(productId, quantity);
            writeLog("Admin " + admin->getUsername() + " updated stock for product ID " +
                to_string(productId) + " by " + to_string(quantity));
            break;
        }

        case 6:
            admin->generateReports();
            mainInventory->generateReport();
            writeLog("Admin " + admin->getUsername() + " generated inventory report");
            break;

        case 7: {
            cout << "\n=== SYSTEM LOGS ===" << endl;
            ifstream readLog("ecommerce_log.txt");
            if (readLog.is_open()) {
                string line;
                int lineCount = 0;
                while (getline(readLog, line) && lineCount < 50) {
                    cout << line << endl;
                    lineCount++;
                }
                readLog.close();
            }
            else {
                cout << "Could not open log file!" << endl;
            }
            writeLog("Admin " + admin->getUsername() + " viewed system logs");
            break;
        }

        case 8:
            admin->manageOrders();
            writeLog("Admin " + admin->getUsername() + " accessed order management");
            break;

        case 9:
            cout << "Admin logging out..." << endl;
            writeLog("Admin " + admin->getUsername() + " logged out");
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 9);
}

void viewProducts() {
    cout << "\n=== AVAILABLE PRODUCTS ===" << endl;
    mainInventory->displayInventory();
}

void createSampleData() {
    writeLog("Creating sample data");


    customers.push_back(new Customer(1, "john_doe", "john@email.com", "password123", "123 Main St", "555-0101"));
    customers.push_back(new Customer(2, "jane_smith", "jane@email.com", "mypassword", "456 Oak Ave", "555-0102"));


    admins.push_back(new Admin(1, "admin", "admin@company.com", "admin123", "SUPER_ADMIN"));
    admins.push_back(new Admin(2, "manager", "manager@company.com", "manager123", "MANAGER"));


    try {
        Product* laptop = new Electronics(1, "Gaming Laptop", 1299.99, 15, "High-performance gaming laptop", 24, "TechBrand", "GB-2024");
        Product* shirt = new Clothing(2, "Cotton T-Shirt", 29.99, 50, "Comfortable cotton t-shirt", "M", "Blue", "Cotton");
        Product* apple = new Food(3, "Fresh Apples", 4.99, 100, "Organic red apples", time(nullptr) + (7 * 24 * 60 * 60), "Fruits", "Rich in vitamins", true);
        Product* phone = new Electronics(4, "Smartphone", 699.99, 25, "Latest smartphone with advanced features", 12, "PhoneCorp", "Smart-X");
        Product* jeans = new Clothing(5, "Denim Jeans", 79.99, 30, "Classic blue denim jeans", "32", "Blue", "Denim");

        mainInventory->addProduct(laptop);
        mainInventory->addProduct(shirt);
        mainInventory->addProduct(apple);
        mainInventory->addProduct(phone);
        mainInventory->addProduct(jeans);

        writeLog("Sample products created and added to inventory");
    }
    catch (const string& error) {
        writeLog("Error creating sample data: " + error);
    }

    cout << "Sample data created successfully!" << endl;
    cout << "Sample Customer Login - Username: john_doe, Password: password123" << endl;
    cout << "Sample Admin Login - Username: admin, Password: admin123" << endl;
}

Customer* findCustomer(const string& username) {
    for (Customer* customer : customers) {
        if (customer->getUsername() == username) {
            return customer;
        }
    }
    return nullptr;
}

Admin* findAdmin(const string& username) {
    for (Admin* admin : admins) {
        if (admin->getUsername() == username) {
            return admin;
        }
    }
    return nullptr;
}
