#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
    int productId;
    string name;
    double price;
    int stockQuantity;
    string description;

public:
    Product(int id, const string& productName, double productPrice,
        int stock, const string& desc);
    virtual ~Product() = default;

    virtual double calculateDiscount() const = 0; 
    virtual double calculateShipping() const;
    virtual string getDetails() const;
    virtual void updateStock(int quantity);

    
    int getProductId() const { return productId; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stockQuantity; }
    void setPrice(double newPrice) { price = newPrice; }
};

#endif
