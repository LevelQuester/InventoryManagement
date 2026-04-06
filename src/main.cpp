#include "item_factory.h"
#include "inventory.h"
#include "algorithms.h"

#include <iostream>
#include <memory>
#include <algorithm>
#include <string>

namespace {

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    if (!std::getline(std::cin, input)) {
        throw InventoryException{"Unexpected end of input"};
    }
    return input;
}

int readInt(const std::string& prompt) {
    auto input = readLine(prompt);
    std::size_t pos{};
    auto value = std::stoi(input, &pos);
    if (pos != input.size()) {
        throw InvalidValueException{"Expected an integer"};
    }
    return value;
}

double readDouble(const std::string& prompt) {
    auto input = readLine(prompt);
    std::size_t pos{};
    auto value = std::stod(input, &pos);
    if (pos != input.size()) {
        throw InvalidValueException{"Expected a number"};
    }
    return value;
}

void printMenu() {
    std::cout << "\n=== Inventory Management System ===\n"
              << " 1. Add Electronics\n"
              << " 2. Add Grocery\n"
              << " 3. Remove Item\n"
              << " 4. Update Quantity\n"
              << " 5. Display Inventory\n"
              << " 6. Read from File\n"
              << " 7. Write to File\n"
              << " 8. Find Most Expensive Item\n"
              << " 9. Find Items Below Quantity Threshold\n"
              << "10. Sort by Price\n"
              << "11. Exit\n";
} 

void addElectronics(Inventory& inv) {
    auto id    = readLine("Item ID: ");
    auto name  = readLine("Name: ");
    auto qty   = readInt("Quantity: ");
    auto price = readDouble("Price: ");
    auto warranty = readInt("Warranty (months): ");
    inv.addItem(makeElectronics(id, name, qty, price, warranty));
    std::cout << "Electronics item added\n";
}

void addGrocery(Inventory& inv) {
    auto id    = readLine("Item ID: ");
    auto name  = readLine("Name: ");
    auto qty   = readInt("Quantity: ");
    auto price = readDouble("Price: ");
    auto exp   = readLine("Expiration date (YYYY-MM-DD): ");
    inv.addItem(makeGrocery(id, name, qty, price, exp));
    std::cout << "Grocery item added\n";
}

void removeItem(Inventory& inv) {
    auto id = readLine("Item ID to remove: ");
    inv.removeItem(id);
    std::cout << "Item removed\n";
} 

void updateQuantity(Inventory& inv) {
    auto id  = readLine("Item ID: ");
    auto qty = readInt("New quantity: ");
    inv.updateQuantity(id, qty);
    std::cout << "Quantity updated\n";
}

void readFromFile(Inventory& inv) {
    auto filename = readLine("Filename: ");
    inv.readFromFile(filename);
    std::cout << "Inventory loaded from " << filename << "\n";
}

void writeToFile(const Inventory& inv) {
    auto filename = readLine("Filename: ");
    inv.writeToFile(filename);
    std::cout << "Inventory saved to " << filename << "\n";
}

void findMostExpensive(const Inventory& inv) {
    const auto& items = inv.items();
    if (items.empty()) {
        std::cout << "Inventory is empty\n";
        return;
    }
    auto it = std::max_element(items.begin(), items.end(),
        [](const auto& a, const auto& b) {
            return a->price() < b->price();
        });
    std::cout << "Most expensive item:\n";
    (*it)->display();
}

void findBelowThreshold(const Inventory& inv) {
    auto threshold = readInt("Quantity threshold: ");
    auto results = filterItems(inv, [threshold](const auto& item) {
        return item->quantity() < threshold;
    });
    if (results.empty()) {
        std::cout << "No items below threshold\n";
        return;
    }
    for (const auto& item : results) {
        item->display();
    }
}

void sortByPrice(Inventory& inv) {
    sortItems(inv, [](const auto& item) { return item->price(); });
    std::cout << "Inventory sorted by price\n";
    inv.displayInventory();
}

} // namespace

int main() {
    Inventory inventory;
    bool running = true;

    while (running) {
        printMenu();

        int choice{};
        try {
            choice = readInt("Choose [1-11]: ");
        } catch (const std::exception&) {
            std::cerr << "Error: Invalid menu choice\n";
            continue;
        }

        try {
            switch (choice) {
                case 1:  addElectronics(inventory);          break;
                case 2:  addGrocery(inventory);              break;
                case 3:  removeItem(inventory);              break;
                case 4:  updateQuantity(inventory);          break;
                case 5:  inventory.displayInventory();       break;
                case 6:  readFromFile(inventory);            break;
                case 7:  writeToFile(inventory);             break;
                case 8:  findMostExpensive(inventory);       break;
                case 9:  findBelowThreshold(inventory);     break;
                case 10: sortByPrice(inventory);             break;
                case 11: running = false;                    break;
                default: std::cout << "Invalid choice.\n";   break;
            }
        } catch (const InventoryException& e) {
            std::cerr << "Error: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Unexpected error: " << e.what() << "\n";
        }
    }
}
