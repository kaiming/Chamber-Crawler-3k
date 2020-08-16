#include "merchantFactory.h"
#include "../Enemy/enemy.h"
#include "../Enemy/merchant.h"

std::shared_ptr<Enemy> MerchantFactory::spawn() {
    return std::make_shared<Merchant>();
}