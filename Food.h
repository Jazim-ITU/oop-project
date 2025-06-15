#ifndef FOOD_H
#define FOOD_H

#include "Product.h"
#include <ctime>

using namespace std;

class Food : public Product {
private:
    time_t expiryDate;
    string category;
    string nutritionalInfo;
    bool isPerishable;

public:
    Food(int id, const string& name, double price, int stock, const string& desc,
        time_t expiry, const string& foodCategory, const string& nutrition, bool perishable);

    double calculateDiscount() const override;
    string getDetails() const override;

   
    bool checkFreshness() const;

    string getNutritionalInfo() const { return nutritionalInfo; }
    int getDaysUntilExpiry() const;

   
    time_t getExpiryDate() const { return expiryDate; }
    string getCategory() const { return category; }
    bool getIsPerishable() const { return isPerishable; }
};

#endif
