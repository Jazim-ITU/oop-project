#include "ShoppingCart.h"
using namespace std;

ShoppingCart::ShoppingCart(int id) : cartId(id), totalAmount(0.0) {}

void ShoppingCart::addItem(Product* product, int quantity) {
    if (product == nullptr || quantity <= 0) {
        cout << "Invalid product or quantity!" << endl;
        return;
    }

    if (product->getStockQuantity() < quantity) {
        cout << "Insufficient stock! Available: " << product->getStockQuantity() << endl;
        return;
    }

   
    for (CartItem& item : items) {
        if (item.product->getProductId() == product->getProductId()) {
            item.quantity += quantity;
            calculateTotal();
            return;
        }
    }

   
    items.push_back(CartItem(product, quantity));
    calculateTotal();
}

void ShoppingCart::removeItem(int productId) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->product->getProductId() == productId) {
            items.erase(it);
            calculateTotal();
            cout << "Item removed from cart." << endl;
            return;
        }
    }
    cout << "Item not found in cart." << endl;
}

void ShoppingCart::updateQuantity(int productId, int newQuantity) {
    if (newQuantity <= 0) {
        removeItem(productId);
        return;
    }

    for (CartItem& item : items) {
        if (item.product->getProductId() == productId) {
            if (item.product->getStockQuantity() < newQuantity) {
                cout << "Insufficient stock! Available: " << item.product->getStockQuantity() << endl;
                return;
            }
            item.quantity = newQuantity;
            calculateTotal();
            cout << "Quantity updated." << endl;
            return;
        }
    }
    cout << "Item not found in cart." << endl;
}

double ShoppingCart::calculateTotal() {
    totalAmount = 0.0;
    for (const CartItem& item : items) {
        double itemPrice = item.product->getPrice();
        double discount = item.product->calculateDiscount();
        double discountedPrice = itemPrice * (1.0 - discount);
        totalAmount += discountedPrice * item.quantity;
    }
    return totalAmount;
}

void ShoppingCart::clearCart() {
    items.clear();
    totalAmount = 0.0;
    cout << "Cart cleared." << endl;
}

void ShoppingCart::displayCart() const {
    cout << "=== Shopping Cart ===" << endl;
    cout << "Cart ID: " << cartId << endl;

    if (items.empty()) {
        cout << "Cart is empty." << endl;
        return;
    }

    for (const CartItem& item : items) {
        cout << "Product: " << item.product->getName()
            << ", Quantity: " << item.quantity
            << ", Price: $" << item.product->getPrice()
            << ", Discount: " << (item.product->calculateDiscount() * 100) << "%" << endl;
    }

    cout << "Total Amount: $" << totalAmount << endl;
}
