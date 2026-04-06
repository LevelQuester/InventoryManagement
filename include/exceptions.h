#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class InventoryException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class ItemNotFoundException : public InventoryException {
public:
    explicit ItemNotFoundException(std::string item_id)
        : InventoryException{"Item with ID '" + item_id + "' not found."}
        , item_id_{std::move(item_id)} {}

    [[nodiscard]] const std::string& itemId() const noexcept { return item_id_; }

private:
    std::string item_id_;
};


class DuplicateItemException : public InventoryException {
public:
    explicit DuplicateItemException(std::string item_id)
        : InventoryException{"Item with ID '" + item_id + "' already exists in inventory."}
        , item_id_{std::move(item_id)} {}

    [[nodiscard]] const std::string& itemId() const noexcept { return item_id_; }

private:
    std::string item_id_;
};

class InvalidValueException : public InventoryException {
public:
    using InventoryException::InventoryException;
};


#endif // EXCEPTIONS_H