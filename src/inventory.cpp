#include "inventory.h"
#include <algorithm>
#include <iostream>

void Inventory::addItem(std::shared_ptr<Item> item) {
    items_.push_back(std::move(item));
}

void Inventory::removeItem(const std::string& item_id) {
    auto it = std::remove_if(items_.begin(), items_.end(),
        [&item_id](const auto& item) {
            return item->itemId() == item_id;
        });
    items_.erase(it, items_.end());
}

void Inventory::updateQuantity(const std::string& item_id, int quantity) {
    for (auto& item : items_) {
        if (item->itemId() == item_id) {
            item->setQuantity(quantity);
            return;
        }
    }
}

void Inventory::displayInventory() const {
    for (const auto& item : items_) {
        item->display();
    }
}

const std::vector<std::shared_ptr<Item>>& Inventory::items() const noexcept {
    return items_;
} 
