#include "Clothing.h"
using namespace std;

Clothing::Clothing(int id, const string& name, double price, int stock,
    const string& desc, const string& clothingSize,
    const string& clothingColor, const string& clothingMaterial)
    : Product(id, name, price, stock, desc), size(clothingSize),
    color(clothingColor), material(clothingMaterial) {

    availableSizes = { "XS", "S", "M", "L", "XL", "XXL" };
    availableColors = { "Black", "White", "Red", "Blue", "Green", "Gray" };
}

double Clothing::calculateDiscount() const {
   
    if (price > 100.0) {
        return 0.20; 
    }
    else if (price > 50.0) {
        return 0.15; 
    }
    else {
        return 0.10; 
    }
}

string Clothing::getDetails() const {
    return Product::getDetails() +
        ", Size: " + size +
        ", Color: " + color +
        ", Material: " + material;
}

bool Clothing::checkSizeAvailability(const string& requestedSize) const {
    for (const string& availableSize : availableSizes) {
        if (availableSize == requestedSize) {
            return true;
        }
    }
    return false;
}

void Clothing::changeSize(const string& newSize) {
    if (!checkSizeAvailability(newSize)) {
        throw "Size " + newSize + " is not available";
    }
    size = newSize;
    cout << "Size changed to: " << newSize << endl;
}
