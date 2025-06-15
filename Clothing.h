#ifndef CLOTHING_H
#define CLOTHING_H

#include "Product.h"
#include <vector>
using namespace std;

class Clothing : public Product {
private:
    string size;
    string color;
    string material;
    vector<string> availableSizes;
    vector<string> availableColors;

public:
    Clothing(int id, const string& name, double price, int stock,
        const string& desc, const string& clothingSize,
        const string& clothingColor, const string& clothingMaterial);

    double calculateDiscount() const override;
    string getDetails() const override;
    bool checkSizeAvailability(const string& requestedSize) const;
    vector<string> getColorOptions() const { return availableColors; }
    void changeSize(const string& newSize); 

    string getSize() const { return size; }
    string getColor() const { return color; }
};
#endif
