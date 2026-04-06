#include "grocery.h"

#include <iomanip>
#include <iostream>

Grocery::Grocery(std::string item_id, std::string name,
                 int quantity, double price, std::string expiration_date)
    : Item{std::move(item_id), std::move(name), quantity, price}
    , expiration_date_{std::move(expiration_date)}
{}

std::string Grocery::category() const { return "Grocery"; }

void Grocery::display() const {
    std::cout << "[Grocery] ID: " << itemId()
              << "| Name: " << name()
              << "| Qty: " << quantity()
              << "| Price: " << std::fixed << std::setprecision(2) << price()
              << "| Expires: " << expiration_date_ << "\n";
}

std::optional<std::string> Grocery::findAttribute(const std::string& key) const {
    if (key == "expiration") {
        return expiration_date_;
    }
    return Item::findAttribute(key);
}

const std::string& Grocery::expirationDate() const noexcept { return expiration_date_; }

void Grocery::setExpirationDate(std::string date) { expiration_date_ = std::move(date); }