#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Product.h"
#include "Inventory.h"
#include <vector>
using namespace std;

class Admin : public User {
private:
    string adminLevel;
    vector<string> permissions;

public:
    Admin(int id, const string& user, const string& mail,
        const string& pass, const string& level);
    ~Admin() = default;

    void displayInfo() const override;
    void addProduct(Product* product, Inventory& inventory);
    void removeProduct(int productId, Inventory& inventory);
    void manageOrders();
    void generateReports() const;
    void addPermission(const string& permission);
};

#endif

