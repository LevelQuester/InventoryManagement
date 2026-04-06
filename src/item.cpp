#include "item.h"

Item::Item(std::string item_id, std::string name, int quantity, double price)
    : item_id_{std::move(item_id)}
    , name_{std::move(name)}
    , quantity_{quantity}
    , price_{price}
{}

const std::string& Item::itemId() const noexcept { return item_id_; }
const std::string& Item::name() const noexcept { return name_; }
int Item::quantity() const noexcept { return quantity_; }
double Item::price() const noexcept { return price_; }
void Item::setName(const std::string& name) { name_ = name; }
void Item::setQuantity(int quantity) { quantity_ = quantity; }
void Item::setPrice(double price) { price_ = price; }
std::optional<std::string> Item::findAttribute(const std::string& /*key*/) const {
    return std::nullopt;
}
