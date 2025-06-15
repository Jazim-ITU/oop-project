#include "Product.h"
using namespace std;

Product::Product(int id, const string& productName, double productPrice,
    int stock, const string& desc)
    : productId(id), name(productName), price(productPrice),
    stockQuantity(stock), description(desc) {
    if (price < 0) {
        throw "Product price cannot be negative";
    }
    if (stock < 0) {
        throw "Stock quantity cannot be negative";
    }
}

double Product::calculateShipping() const {
    
    if (price < 50.0) {
        return 5.99;
    }
    else if (price < 100.0) {
        return 3.99;
    }
    else {
        return 0.0; 
    }
}

string Product::getDetails() const {
    return "ID: " + to_string(productId) +
        ", Name: " + name +
        ", Price: $" + to_string(price) +
        ", Stock: " + to_string(stockQuantity) +
        ", Description: " + description;
}

void Product::updateStock(int quantity) {
    if (stockQuantity + quantity < 0) {
        throw "Insufficient stock available";
    }
    stockQuantity += quantity;
}
