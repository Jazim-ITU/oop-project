#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include "Product.h"
#include <vector>
using namespace std;

struct CartItem {
    Product* product;
    int quantity;

    CartItem(Product* prod, int qty) : product(prod), quantity(qty) {}
};

class ShoppingCart {
private:
    int cartId;
    vector<CartItem> items;
    double totalAmount;

public:
    ShoppingCart(int id);
    ~ShoppingCart() = default;

    void addItem(Product* product, int quantity);
    void removeItem(int productId);
    void updateQuantity(int productId, int newQuantity);
    double calculateTotal();
    void clearCart();
    void displayCart() const;

  
    const vector<CartItem>& getItems() const { return items; }
    double getTotalAmount() const { return totalAmount; }
    bool isEmpty() const { return items.empty(); }
};

#endif

