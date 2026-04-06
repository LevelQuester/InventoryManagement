#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "inventory.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

template<typename Predicate>
std::vector<std::shared_ptr<Item>> filterItems(const Inventory& inv, Predicate pred) {
    std::vector<std::shared_ptr<Item>> result;
    std::copy_if(inv.items().begin(), inv.items().end(),
                 std::back_inserter(result), pred);
    return result;
}

template<typename Key>
void sortItems(Inventory& inv, Key keyFn) {
    std::sort(inv.items().begin(), inv.items().end(),
              [&keyFn](const auto& lhs, const auto& rhs) {
                  return keyFn(lhs) < keyFn(rhs);
              });
}
 
#endif // ALGORITHMS_H