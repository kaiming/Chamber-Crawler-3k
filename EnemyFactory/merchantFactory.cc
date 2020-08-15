#include "merchantFactory.h"
#include "../Enemy/enemy.h"
#include "../Enemy/merchant.h"

std::shared_ptr<Enemy> MerchantFactory::spawnEnemy() {
    return std::make_shared<Merchant>();
}