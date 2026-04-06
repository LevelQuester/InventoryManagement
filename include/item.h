#ifndef ITEM_H
#define ITEM_H

#include<string>
#include<optional>

class Item {
    public:
        Item(std::string item_id, std::string name, int quantity, double price);
        virtual ~Item() = default;
        Item(const Item&) = default;
        Item& operator=(const Item&) = default;
        Item(Item&&) noexcept = default;
        Item& operator=(Item&&) noexcept = default;
        [[nodiscard]] const std::string& itemId() const noexcept;
        [[nodiscard]] const std::string& name() const noexcept;
        [[nodiscard]] int quantity() const noexcept;
        [[nodiscard]] double price() const noexcept;
        void setName(const std::string& name);
        void setQuantity(int quantity);
        void setPrice(double price);
        [[nodiscard]] virtual std::string category() const = 0;
        virtual void display() const = 0;
        [[nodiscard]] virtual std::optional<std::string> findAttribute(const std::string& key) const;
    private:
        std::string item_id_;
        std::string name_;
        int quantity_;
        double price_;
};

#endif // ITEM_H