#include "board.h"
#include <utility>
#include "tile.h"
#include "walkabletile.h"

// Include all player and enemy races

/*
    std::vector<std::vector<std::shared_ptr<Tile>>> floor;
    std::vector<std::vector<std::shared_ptr<WalkableTile>>> chambers;
    std::shared_ptr<WalkableTile> player;
    std::vector<std::shared_ptr<WalkableTile>> enemies;
    std::vector<std::shared_ptr<WalkableTile>> dragons;
    std::vector<std::string> potionsUsed;
    int floorNum;
    bool merchantAgro;

    void generateItem(); // need to fill in inputs
*/

Board::Board(std::vector<std::vector<std::shared_ptr<Tile>>> floor, bool filled) : floor{floor} {
    
    if (!filled) {
        generateFloor();
    }

}

int Board::getFloorNum() {
    return floorNum;
}

void setFloorNum(int num) : floorNum{num} {

}

void setFloor (std::vector<std::vector<std::shared_ptr<Tile>>> floor) : floor{floor} {

}

//--------------------------------------------------------------------------------

std::shared_ptr<WalkableTile> validDest(std::shared_ptr<WalkableTile> package, std::string direction) {
    
    // Set up variable to hold destination
    std::shared_ptr<Tile> destination;

    // Coordinate system with (0,0) in the top left
    //   first int is x value, increases left to right
    //   second int is y value, increases top to bottom

    // std::pair<int x, int y>
    if (direction == "no") {
        // no = North/Up
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.second - 1 < 0) {
            return nullptr;
        }

        destination = floor[current.first][current.second - 1];
    } else if (direction == "so") {
        // so = South/Down
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.second + 1 >= floor[0].size()) {
            return nullptr;
        }

        destination = floor[current.first][current.second + 1];
    } else if (direction == "ea") {
        // ea = East/Right
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.second + 1 >= floor.size()) {
            return nullptr;
        }

        destination = floor[current.first + 1][current.second];
    } else if (direction == "we") {
        // we = West/Left
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.first - 1 < 0) {
            return nullptr;
        }

        destination = floor[current.first - 1][current.second];
    } else if (direction == "ne") { // ----------------------------------------------------------------------
        // ne = North East/Right and Up
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.first + 1 >= floor[0].size() || current.second - 1 < 0) {
            return nullptr;
        }

        destination = floor[current.first + 1][current.second - 1];
    } else if (direction == "nw") {
        // nw = North West/Left and Up 
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.first - 1 < 0 || current.second - 1 < 0) {
            return nullptr;
        }

        destination = floor[current.first - 1][current.second - 1];
    } else if (direction == "se") {
        // se = South East/Right and Down
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.first + 1 >= floor[0].size() || current.second + 1 >= floor.size()) {
            return nullptr;
        }

        destination = floor[current.first + 1][current.second + 1];
    } else if (direction == "sw") {
        // sw = South West/Left and Down
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.first + 1 >= floor[0].size() || current.second - 1 < 0) {
            return nullptr;
        }

        destination = floor[current.first + 1][current.second - 1];
    } else {
        // Invalid direction
        return nullptr;
    }

    // Check destination tile to see if it's a WalkableTile
    std::shared_ptr<WalkableTile> typeCheck = std::dynamic_pointer_cast<WalkableTile>(destination);
    if (typeCheck) {
        // Destination is a 
        return typeCheck;        
    }

    return nullptr;


}

//--------------------------------------------------------------------------------

void movePlayer(std::string direction) {
    std:shared_ptr<WalkableTile> destination = validDest(player, direction);

    // Check if valid destination
    if (destination == nullptr) {
        return;
    }

    // Check if destination is occupied by an enemy
    if (destination->getOccupant() != nullptr) {
        return;
    }

    // Check if destination is occupied by a potion
    if (destination->getPotion() != nullptr) {
        // DLC EXTENSION LOCATION: Change this behaviour if we want to make potions walk-over to use
        return;
    }

    // Check if destination is occupied by gold
    if (destination->getGold() != nullptr) {
        // Check if Dragon Hoard
        if (std::dynamic_pointer_cast<DragonHoard>(destination->getGold())) {
            // Check if dragon is dead
            if (!destination->getGold()->getDragon()->isAlive()) {
                // Dragon is dead
                // Player picks up gold
                player->occupant->setGold(player->occupant->getGold() + destination->gold->getSize());
                // Gold is consumed
                destination->setGold(nullptr); 
            }

            // Else do nothing

        } else {
            // Player picks up gold
            player->occupant->setGold(player->occupant->getGold() + destination->gold->getSize());
            // Gold is consumed
            destination->setGold(nullptr); 
        }
    }

    // Swap Player pointers
    destination->setOccupant(player->getOccupant);
    player->setOccupant(nullptr);
    player = destination;

}

void attackEnemey(std::string direction) {
    std:shared_ptr<WalkableTile> target = validDest(player, direction);

    // Check if valid destination
    if (target == nullptr) {
        return;
    }

    // Check if destination is occupied by an enemy
    if (target->getOccupant() != nullptr) {
        // Check if target is merchant, if merchants are not hostile
        if (!merchantAgro && std::dynamic_pointer_cast<Merchant>(target->getOccupant())) {
            // Merchants are now hostile
            merchantAgro = true;
        }

        // Begin attack sequence and store resulting enemy state
        bool EnemyKilled = target->getOccupant()->getAttacked(*this);
    
        if (EnemyKilled) {
            // Enemy killed, determine Enemy type to generate gold dropped

            // Check if target is dragon
            if (std::dynamic_pointer_cast<Dragon>(target->getOccupant())) {
                // Dragon Type, drop nothing
                
                // Remove this dragon from dragons
                for (auto it = dragons.begin(); it != dragons.end(); ++it) {
                    if (it->getCoord() == target->getCoord()) {
                        dragons.erase(it); 
                    }
                }

            } else {
                
                // Check if target is human or merchant
                if (std::dynamic_pointer_cast<Human>(target->getOccupant())) {
                    // Human type, drop 2 Normal Piles
                    target->setGold(std::make_shared<Gold>("Normal Pile", 4));

                } else if (std::dynamic_pointer_cast<Merchant>(target->getOccupant())) {
                    // Merchant Type, drop Merchant Hoard
                    target->setGold(std::make_shared<Gold>("Merchant Hoard", 4));

                } else {
                    // Other type, RNG gold
                    if (std::rand() % 2 == 0) {
                        target->setGold(std::make_shared<Gold>("Small Pile", 1));
                    } else {
                        target->setGold(std::make_shared<Gold>("Normal Pile", 2));
                    }
                }

                // Remove this enemy from enemies
                    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
                        if (it->getCoord() == target->getCoord()) {
                            enemies.erase(it); 
                        }
                    }
            }


        }
    }

}


void moveEnemies();
void usePotion(std::string direction);
void generateFloor();