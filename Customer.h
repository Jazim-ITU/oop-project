#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "ShoppingCart.h"
#include "Order.h"
#include <vector>
using namespace std;

class Customer : public User {
private:
    string address;
    string phoneNumber;
    int loyaltyPoints;
    ShoppingCart* cart;
    vector<Order*> orderHistory;

public:
    Customer(int id, const string& user, const string& mail,
        const string& pass, const string& addr, const string& phone);
    ~Customer();

    void displayInfo() const override;
    Order* placeOrder();
    void viewOrderHistory() const;
    void addToCart(Product* product, int quantity);
    void addLoyaltyPoints(int points) { loyaltyPoints += points; }

   
    ShoppingCart* getCart() const { return cart; }
    int getLoyaltyPoints() const { return loyaltyPoints; }
};

#endif
