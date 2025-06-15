#include "Order.h"
#include <ctime>
using namespace std;

Order::Order(int id, const ShoppingCart& cart, const string& address)
    : orderId(id), status(ORDER_PENDING), shippingAddress(address), payment(nullptr) {

    orderDate = time(nullptr);
    orderItems = cart.getItems();
    totalAmount = cart.getTotalAmount();

    cout << "Order created with ID: " << orderId << endl;
}

Order::~Order() {
    delete payment;
}

void Order::processOrder() {
    if (status != ORDER_PENDING) {
        cout << "Order cannot be processed. Current status: " << getStatusString() << endl;
        return;
    }

    try {
        
        for (const CartItem& item : orderItems) {
            item.product->updateStock(-item.quantity);
        }

        status = ORDER_CONFIRMED;
        cout << "Order processed successfully!" << endl;

        
        if (payment != nullptr && payment->processPayment()) {
            status = ORDER_PROCESSING;
            cout << "Payment processed. Order is now being prepared." << endl;
        }

    }
    catch (const string& error) {
        cout << "Order processing failed: " << error << endl;
        status = ORDER_CANCELLED;
    }
}

void Order::cancelOrder() {
    if (status == ORDER_DELIVERED) {
        cout << "Cannot cancel delivered order." << endl;
        return;
    }

    if (status == ORDER_CANCELLED) {
        cout << "Order is already cancelled." << endl;
        return;
    }

  
    if (status == ORDER_CONFIRMED || status == ORDER_PROCESSING) {
        for (const CartItem& item : orderItems) {
            item.product->updateStock(item.quantity);
        }
    }

  
    if (payment != nullptr && payment->getProcessStatus()) {
        payment->refund();
    }

    status = ORDER_CANCELLED;
    cout << "Order cancelled successfully." << endl;
}

void Order::updateStatus(OrderStatus newStatus) {
    status = newStatus;
    cout << "Order status updated to: " << getStatusString() << endl;
}

void Order::setPayment(Payment* paymentMethod) {
    delete payment; 
    payment = paymentMethod;
    cout << "Payment method set: " << payment->getPaymentMethod() << endl;
}

string Order::getStatusString() const {
    switch (status) {
    case ORDER_PENDING: return "Pending";
    case ORDER_CONFIRMED: return "Confirmed";
    case ORDER_PROCESSING: return "Processing";
    case ORDER_SHIPPED: return "Shipped";
    case ORDER_DELIVERED: return "Delivered";
    case ORDER_CANCELLED: return "Cancelled";
    default: return "Unknown";
    }
}

void Order::displayOrderDetails() const {
    cout << "=== Order Details ===" << endl;
    cout << "Order ID: " << orderId << endl;
    cout << "Status: " << getStatusString() << endl;
    cout << "Total Amount: $" << totalAmount << endl;
    cout << "Shipping Address: " << shippingAddress << endl;
    cout << "Order Date: " << ctime(&orderDate);

    cout << "Items:" << endl;
    for (const CartItem& item : orderItems) {
        cout << "  - " << item.product->getName()
            << " (Qty: " << item.quantity << ")" << endl;
    }

    if (payment != nullptr) {
        cout << "Payment Method: " << payment->getPaymentMethod()
            << " (Status: " << (payment->getProcessStatus() ? "Processed" : "Pending") << ")" << endl;
    }
}
