#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Product.h"
using namespace std;

class Electronics : public Product {
private:
    int warranty; 
    string brand;
    string model;

public:
    Electronics(int id, const string& name, double price, int stock,
        const string& desc, int warrantyMonths, const string& brandName,
        const string& modelName);

    double calculateDiscount() const override;
    double calculateShipping() const override;
    string getDetails() const override;
    void extendWarranty(int months);
    bool checkCompatibility(const string& deviceType) const;

    
    int getWarranty() const { return warranty; }
    string getBrand() const { return brand; }
};

#endif
