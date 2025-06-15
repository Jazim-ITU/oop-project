#include "Inventory.h"
using namespace std;

Inventory::Inventory(int id, const string& loc) : inventoryId(id), location(loc) {
    cout << "Inventory created at location: " << location << endl;
}

Inventory::~Inventory() {
    
    for (const InventoryItem& item : products) {
        delete item.product;
    }
}

void Inventory::addProduct(Product* product) {
    if (product == nullptr) {
        cout << "Cannot add null product to inventory." << endl;
        return;
    }

   
    for (const InventoryItem& item : products) {
        if (item.productId == product->getProductId()) {
            cout << "Product with ID " << product->getProductId() << " already exists." << endl;
            return;
        }
    }

    products.push_back(InventoryItem(product->getProductId(), product));
    cout << "Product added to inventory: " << product->getName() << endl;
}

void Inventory::removeProduct(int productId) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->productId == productId) {
            cout << "Removing product: " << it->product->getName() << endl;
            delete it->product;
            products.erase(it);
            return;
        }
    }
    cout << "Product with ID " << productId << " not found." << endl;
}

void Inventory::updateStock(int productId, int quantity) {
    Product* product = getProduct(productId);
    if (product != nullptr) {
        try {
            product->updateStock(quantity);
            cout << "Stock updated for product: " << product->getName() << endl;
        }
        catch (const string& error) {
            cout << "Stock update failed: " << error << endl;
        }
    }
}

bool Inventory::checkAvailability(int productId, int requestedQuantity) const {
    Product* product = getProduct(productId);
    if (product == nullptr) {
        return false;
    }
    return product->getStockQuantity() >= requestedQuantity;
}

Product* Inventory::getProduct(int productId) const {
    for (const InventoryItem& item : products) {
        if (item.productId == productId) {
            return item.product;
        }
    }
    return nullptr;
}

void Inventory::generateReport() const {
    cout << "=== Inventory Report ===" << endl;
    cout << "Location: " << location << endl;
    cout << "Total Products: " << products.size() << endl;
    cout << "Low Stock Items (< 10):" << endl;

    for (const InventoryItem& item : products) {
        if (item.product->getStockQuantity() < 10) {
            cout << "  - " << item.product->getName()
                << " (Stock: " << item.product->getStockQuantity() << ")" << endl;
        }
    }
}

void Inventory::displayInventory() const {
    cout << "=== Inventory Display ===" << endl;
    cout << "Location: " << location << endl;
    cout << "Inventory ID: " << inventoryId << endl;

    if (products.empty()) {
        cout << "No products in inventory." << endl;
        return;
    }

    for (const InventoryItem& item : products) {
        cout << item.product->getDetails() << endl;
    }
}
