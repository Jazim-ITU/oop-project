#ifndef ORDER_H
#define ORDER_H

#include "ShoppingCart.h"
#include "Payment.h"
#include <ctime>
using namespace std;

enum OrderStatus {
    ORDER_PENDING,
    ORDER_CONFIRMED,
    ORDER_PROCESSING,
    ORDER_SHIPPED,
    ORDER_DELIVERED,
    ORDER_CANCELLED
};

class Order {
private:
    int orderId;
    time_t orderDate;
    OrderStatus status;
    double totalAmount;
    vector<CartItem> orderItems;
    Payment* payment;
    string shippingAddress;

public:
    Order(int id, const ShoppingCart& cart, const string& address);
    ~Order();

    void processOrder();
    void cancelOrder();
    void updateStatus(OrderStatus newStatus);
    void setPayment(Payment* paymentMethod);
    string getStatusString() const;
    void displayOrderDetails() const;

  
    int getOrderId() const { return orderId; }
    OrderStatus getStatus() const { return status; }
    double getTotalAmount() const { return totalAmount; }
};

#endif

