#ifndef GROCERY_H
#define GROCERY_H

#include "item.h"
#include <string>

class Grocery : public Item {
    public:
        Grocery(std::string item_id, std::string name,
                int quantity, double price, std::string expiration_date);
        [[nodiscard]] std::string category() const override;
        void display() const override;
        [[nodiscard]] std::optional<std::string> findAttribute(const std::string& key) const override;
        [[nodiscard]] const std::string& expirationDate() const noexcept;
        void setExpirationDate(std::string date);
    private:
        std::string expiration_date_;
};

#endif // GROCERY_H