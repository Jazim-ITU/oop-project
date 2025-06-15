#ifndef INVENTORY_H
#define INVENTORY_H

#include "Product.h"
#include <vector>
using namespace std;

struct InventoryItem {
    int productId;
    Product* product;

    InventoryItem(int id, Product* prod) : productId(id), product(prod) {}
};

class Inventory {
private:
    int inventoryId;
    string location;
    vector<InventoryItem> products;

public:
    Inventory(int id, const string& loc);
    ~Inventory();

    void addProduct(Product* product);
    void removeProduct(int productId);
    void updateStock(int productId, int quantity);
    bool checkAvailability(int productId, int requestedQuantity) const;
    Product* getProduct(int productId) const;
    void generateReport() const;
    void displayInventory() const;

    
    int getInventoryId() const { return inventoryId; }
    string getLocation() const { return location; }
    size_t getProductCount() const { return products.size(); }
};

#endif
