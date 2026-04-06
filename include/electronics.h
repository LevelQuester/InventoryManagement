#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "item.h"
#include <string>

inline constexpr int defaultWarrantyMonths = 12;
class Electronics : public Item {
public:
    Electronics(std::string item_id, std::string name,
                int quantity, double price, int warranty_months = defaultWarrantyMonths);
    [[nodiscard]] std::string category() const override;
    void display() const override;
    [[nodiscard]] std::optional<std::string> findAttribute(const std::string& key) const override;
    [[nodiscard]] int warrantyMonths() const noexcept;
    void setWarrantyMonths(int months);
private:
    int warranty_months_;
};


#endif // ELECTRONICS_H