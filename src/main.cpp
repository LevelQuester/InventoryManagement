#include "electronics.h"
#include "grocery.h"

#include <iostream>
#include <memory>

int main() {
    auto phone = std::make_shared<Electronics>("E1", "Phone", 10, 699.99, 24);
    auto laptop = std::make_shared<Electronics>("E2", "Laptop", 5, 1099.99, 12);
    auto apple = std::make_shared<Grocery>("G1", "Apple", 100, 0.99, "2026-06-01");
    auto milk = std::make_shared<Grocery>("G2", "Milk", 30, 1.49, "2026-04-10");

    phone->display();
    laptop->display();
    apple->display();
    milk->display();

    if (auto attr = phone->findAttribute("warranty")) {
        std::cout << "Phone warranty: " << *attr << " months\n";
    }
    if (auto attr = apple->findAttribute("expiration")) {
        std::cout << "Apple expires: " << *attr << "\n";
    }
    if (auto attr = phone->findAttribute("unknown")) {
        std::cout << "error\n";
    } else {
        std::cout << "Attribute 'unknown' not found\n";
    }
}