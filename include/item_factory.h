#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include "electronics.h"
#include "grocery.h"

#include <memory>
#include <string>

inline std::shared_ptr<Item> makeElectronics(const std::string& id, const std::string& name,
                                             int qty, double price, int warrantyMonths) {
    return std::make_shared<Electronics>(id, name, qty, price, warrantyMonths);
}

inline std::shared_ptr<Item> makeGrocery(const std::string& id, const std::string& name,
                                         int qty, double price, const std::string& expDate) {
    return std::make_shared<Grocery>(id, name, qty, price, expDate);
}



#endif // ITEM_FACTORY_H