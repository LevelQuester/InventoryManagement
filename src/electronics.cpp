#include "electronics.h"
#include <iostream>
#include <iomanip>
#include <string>

Electronics::Electronics(std::string item_id, std::string name,
    int quantity, double price, int warranty_months)
: Item{std::move(item_id), std::move(name), quantity, price}
, warranty_months_{warranty_months}
{}

std::string Electronics::category() const { return "Electronics"; }

void Electronics::display() const {
    std::cout << "[Electronics] ID: " << itemId()
              << "| Name: " << name()
              << "| Qty: " << quantity()
              << "| Price: " << std::fixed << std::setprecision(2) << price()
              << "| Warranty: " << warranty_months_ << " months\n";
}

std::optional<std::string> Electronics::findAttribute(const std::string& key) const {
    if (key == "warranty") {
        return std::to_string(warranty_months_);
    }
    return Item::findAttribute(key);
}

int Electronics::warrantyMonths() const noexcept { return warranty_months_; }
void Electronics::setWarrantyMonths(int months) { warranty_months_ = months; }

