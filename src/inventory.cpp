#include "inventory.h"
#include "electronics.h"
#include "grocery.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>


void Inventory::addItem(std::shared_ptr<Item> item) {
    for (const auto& existing : items_) {
        if (existing->itemId() == item->itemId()) {
            throw DuplicateItemException{item->itemId()};
        }
    }
    items_.push_back(std::move(item));
}

void Inventory::removeItem(const std::string& item_id) {
    auto it = std::remove_if(items_.begin(), items_.end(),
        [&item_id](const auto& item) {
            return item->itemId() == item_id;
        });
    if (it == items_.end()) {
        throw ItemNotFoundException{item_id};
    }
    items_.erase(it, items_.end());
}

void Inventory::updateQuantity(const std::string& item_id, int quantity) {
    for (auto& item : items_) {
        if (item->itemId() == item_id) {
            item->setQuantity(quantity);
            return;
        }
    }
    throw ItemNotFoundException{item_id};
}

void Inventory::displayInventory() const {
    for (const auto& item : items_) {
        item->display();
    }
}

void Inventory::readFromFile(const std::string& filename) {
    std::ifstream file{filename};
    if (!file.is_open()) {
        throw InventoryException{"Cannot open file for reading: " + filename};
    }
    std::vector<std::shared_ptr<Item>> parsed_items;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream ss{line};
        std::string id, category, name, qty_str, price_str, extra;
        std::getline(ss, id, ',');
        std::getline(ss, category, ',');
        std::getline(ss, name, ',');
        std::getline(ss, qty_str, ',');
        std::getline(ss, price_str, ',');
        std::getline(ss, extra);
        try {
            auto qty = std::stoi(qty_str);
            auto price = std::stod(price_str);
            if (category == "Electronics") {
                parsed_items.push_back(
                    std::make_shared<Electronics>(id, name, qty, price, std::stoi(extra)));
            } else if (category == "Grocery") {
                parsed_items.push_back(
                    std::make_shared<Grocery>(id, name, qty, price, extra));
            }
        } catch (const std::exception& e) {
            throw InventoryException{"Error parsing line: " + line};
        }
    }
    for (auto& item : parsed_items) {
        addItem(std::move(item));
    }
}

void Inventory::writeToFile(const std::string& filename) const {
    std::ofstream file{filename};
    if (!file.is_open()) {
        throw InventoryException{"Cannot open file for writing: " + filename};
    }
    for (const auto& item : items_) {
        std::string extra;
        if (item->category() == "Electronics") {
            extra = item->findAttribute("warranty").value_or("");
        } else if (item->category() == "Grocery") {
            extra = item->findAttribute("expiration").value_or("");
        }
        file << item->itemId() << ","
             << item->category() << ","
             << item->name() << ","
             << item->quantity() << ","
             << std::fixed << std::setprecision(2) << item->price() << ","
             << extra << "\n";
    }
}

const std::vector<std::shared_ptr<Item>>& Inventory::items() const noexcept {
    return items_;
}

std::vector<std::shared_ptr<Item>>& Inventory::items() noexcept {
    return items_;
}
