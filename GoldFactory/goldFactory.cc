#include "goldFactory.h"
#include "../Gold/gold.h"

GFactory::GFactory(std::string type, int value) : type {type}, value{value} {

}

std::shared_ptr<Gold> GFactory::spawnGold() {
    return std::make_shared<Gold>();
}