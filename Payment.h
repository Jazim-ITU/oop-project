#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <string>
using namespace std;

class Payment {
protected:
    int paymentId;
    string paymentMethod;
    double amount;
    bool isProcessed;

public:
    Payment(int id, const string& method, double paymentAmount);
    virtual ~Payment() = default;

    virtual bool processPayment() = 0; 
    virtual void refund();

    
    int getPaymentId() const { return paymentId; }
    string getPaymentMethod() const { return paymentMethod; }
    double getAmount() const { return amount; }
    bool getProcessStatus() const { return isProcessed; }
};


class CreditCardPayment : public Payment {
private:
    string cardNumber;
    string expiryDate;
    string cvv;

public:
    CreditCardPayment(int id, double amount, const string& cardNum,
        const string& expiry, const string& cvvCode);
    bool processPayment() override;
};

class PayPalPayment : public Payment {
private:
    string email;
    string password;

public:
    PayPalPayment(int id, double amount, const string& paypalEmail,
        const string& paypalPassword);
    bool processPayment() override;
};

#endif
