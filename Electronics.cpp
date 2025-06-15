#include "Electronics.h"
using namespace std;

Electronics::Electronics(int id, const string& name, double price, int stock,
    const string& desc, int warrantyMonths,
    const string& brandName, const string& modelName)
    : Product(id, name, price, stock, desc), warranty(warrantyMonths),
    brand(brandName), model(modelName) {
}

double Electronics::calculateDiscount() const {
    
    if (price > 1000.0) {
        return 0.15; 
    }
    else if (price > 500.0) {
        return 0.10; 
    }
    else {
        return 0.05;
    }
}

double Electronics::calculateShipping() const {
    
    double baseShipping = Product::calculateShipping();
    return baseShipping + 2.50; 
}

string Electronics::getDetails() const {
    return Product::getDetails() +
        ", Brand: " + brand +
        ", Model: " + model +
        ", Warranty: " + to_string(warranty) + " months";
}

void Electronics::extendWarranty(int months) {
    warranty += months;
    cout << "Warranty extended by " << months << " months. New warranty: "
        << warranty << " months." << endl;
}

bool Electronics::checkCompatibility(const string& deviceType) const {
   
    if (brand == "Apple" && deviceType == "iOS") return true;
    if (brand == "Samsung" && deviceType == "Android") return true;
    if (brand == "Dell" && deviceType == "Windows") return true;
    return false;
}
