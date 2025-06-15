#include "Food.h"


Food::Food(int id, const string& name, double price, int stock, const string& desc,
    time_t expiry, const string& foodCategory, const string& nutrition, bool perishable)
    : Product(id, name, price, stock, desc), expiryDate(expiry),
    category(foodCategory), nutritionalInfo(nutrition), isPerishable(perishable) {
}


double Food::calculateDiscount() const {
    int daysUntilExpiry = getDaysUntilExpiry();

    if (daysUntilExpiry <= 0) {
        return 0.0; 
    }
    else if (daysUntilExpiry <= 3) {
        return 0.50; 
    }
    else if (daysUntilExpiry <= 7) {
        return 0.30; 
    }
    else if (daysUntilExpiry <= 14) {
        return 0.15; 
    }

    return 0.0; 
}


string Food::getDetails() const {
    string details = Product::getDetails(); 
    details += "\nCategory: " + category;
    details += "\nNutritional Info: " + nutritionalInfo;
    details += "\nPerishable: ";
    details += (isPerishable ? "Yes" : "No");

   
    struct tm* timeinfo = localtime(&expiryDate);
    char dateBuffer[20];
    sprintf(dateBuffer, "%04d-%02d-%02d",
        timeinfo->tm_year + 1900,
        timeinfo->tm_mon + 1,
        timeinfo->tm_mday);

    details += "\nExpiry Date: ";
    details += dateBuffer;

    int daysLeft = getDaysUntilExpiry();
    if (daysLeft > 0) {
        char daysBuffer[50];
        sprintf(daysBuffer, " (%d days remaining)", daysLeft);
        details += daysBuffer;
    }
    else if (daysLeft == 0) {
        details += " (Expires today!)";
    }
    else {
        char expiredBuffer[50];
        sprintf(expiredBuffer, " (EXPIRED %d days ago)", abs(daysLeft));
        details += expiredBuffer;
    }

    return details;
}


bool Food::checkFreshness() const {
    time_t currentTime = time(0);

    if (expiryDate < currentTime) {
      
        throw string("Product " + getName() + " has expired");
    }

    return true; 
}


int Food::getDaysUntilExpiry() const {
    time_t currentTime = time(0);
    double secondsDiff = difftime(expiryDate, currentTime);
    return static_cast<int>(secondsDiff / (24 * 60 * 60)); 
}
