#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include <memory>
#include <string>
#include <vector>

class Inventory {
    public:
        Inventory() = default;

        Inventory(const Inventory&) = delete;
        Inventory& operator=(const Inventory&) = delete;
        Inventory(Inventory&&) noexcept = default;
        Inventory& operator=(Inventory&&) noexcept = default;
        ~Inventory() = default;

        void addItem(std::shared_ptr<Item> item);
        void removeItem(const std::string& item_id);
        void updateQuantity(const std::string& item_id, int quantity);
        void displayInventory() const;

        [[nodiscard]] const std::vector<std::shared_ptr<Item>>& items() const noexcept;
        [[nodiscard]] std::vector<std::shared_ptr<Item>>& items() noexcept;
    private:
        std::vector<std::shared_ptr<Item>> items_;
};

#endif // INVENTORY_H