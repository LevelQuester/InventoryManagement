#include "electronics.h"
#include "grocery.h"
#include "inventory.h"

#include <iostream>
#include <memory>

int main() {

    Inventory inventory;

    inventory.addItem(std::make_shared<Electronics>("E1", "Phone", 10, 699.99, 24));
    inventory.addItem(std::make_shared<Electronics>("E2", "Laptop", 5, 1099.99, 12));
    inventory.addItem(std::make_shared<Grocery>("G1", "Apple", 100, 0.99, "2026-06-01"));
    inventory.addItem(std::make_shared<Grocery>("G2", "Milk", 30, 1.49, "2026-04-10"));

    inventory.displayInventory();

    std::cout << "Removing E1\n";
    inventory.removeItem("E1");
    inventory.displayInventory();

    std::cout << "Updating quantity G1 to 50\n";
    inventory.updateQuantity("G1", 50);
    inventory.displayInventory();
}