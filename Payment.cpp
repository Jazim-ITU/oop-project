#include "Payment.h"
using namespace std;

Payment::Payment(int id, const string& method, double paymentAmount)
    : paymentId(id), paymentMethod(method), amount(paymentAmount), isProcessed(false) {
    if (amount <= 0) {
        throw "Payment amount must be positive";
    }
}

void Payment::refund() {
    if (!isProcessed) {
        cout << "Cannot refund unprocessed payment." << endl;
        return;
    }

    isProcessed = false;
    cout << "Refund of $" << amount << " processed successfully." << endl;
}


CreditCardPayment::CreditCardPayment(int id, double amount, const string& cardNum,
    const string& expiry, const string& cvvCode)
    : Payment(id, "Credit Card", amount), cardNumber(cardNum),
    expiryDate(expiry), cvv(cvvCode) {
}

bool CreditCardPayment::processPayment() {
    cout << "Processing credit card payment..." << endl;

    if (cardNumber.length() != 16) {
        throw "Payment failed: Invalid card number length";
    }

    if (cvv.length() != 3) {
        throw "Payment failed: Invalid CVV";
    }

   
    cout << "Credit card payment of $" << amount << " processed successfully." << endl;
    isProcessed = true;
    return true;
}


PayPalPayment::PayPalPayment(int id, double amount, const string& paypalEmail,
    const string& paypalPassword)
    : Payment(id, "PayPal", amount), email(paypalEmail), password(paypalPassword) {
}

bool PayPalPayment::processPayment() {
    cout << "Processing PayPal payment..." << endl;

   
    if (email.find("@") == string::npos) {
        throw "Payment failed: Invalid email format";
    }

    if (password.length() < 6) {
        throw "Payment failed: Password too short";
    }

   
    cout << "PayPal payment of $" << amount << " processed successfully." << endl;
    isProcessed = true;
    return true;
}
