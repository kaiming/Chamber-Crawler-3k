#include "board.h"

#include <utility>
#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

#include "tile.h"
#include "walkabletile.h"

#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"
#include "halfling.h"

#include "dwarf.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"

#include "potion.h"
#include "rh.h"
#include "ba.h"
#include "bd.h"
#include "pg.h"
#include "wa.h"
#include "wd.h"

#include "gold.h"
#include "dragonhoard.h"

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
*/

Board::Board(std::vector<std::vector<std::shared_ptr<Tile>>> floor, bool filled) : floor{floor} {
    
    if (!filled) {
        generateFloor();
    }

}

int Board::getFloorNum() {
    return floorNum;
}

void Board::setFloorNum(int num) : floorNum{num} {

}

void Board::setFloor(std::vector<std::vector<std::shared_ptr<Tile>>> floor) : floor{floor} {

}

//--------------------------------------------------------------------------------

std::shared_ptr<WalkableTile> Board::validDest(std::shared_ptr<WalkableTile> package, std::string direction) {
    
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

void Board::tileDFS(std::pair<int, int> coords, int floorNum, std::vector<std::shared_ptr<WalkableTile>>& chamber) {
    
    // Store current tile
    floor[coords.first][coords.second].setRoom(floorNum);
    chamber.emplace_back(floor[coords.first][coords.second]); 


    // Check all directions around for matching unidentified chamber floor tiles

    // Check to the right
    std::shared_ptr<WalkableTile> right = floor[coords.first+1][coords.second];
    if (std::dynamic_pointer_cast<WalkableTile>(right) && (right)->getType() == '.' && (right)->getRoom() < 0) {
        tileDFS(right->getCoord(), floorNum, chamber);
    }

    // Check below
    std::shared_ptr<WalkableTile> down = floor[coords.first][coords.second+1];
    if (std::dynamic_pointer_cast<WalkableTile>(down) && (down)->getType() == '.' && (down)->getRoom() < 0) {
        tileDFS(down->getCoord(), floorNum, chamber);
    }

    // Check to the left
    std::shared_ptr<WalkableTile> left = floor[coords.first-1][coords.second];
    if (std::dynamic_pointer_cast<WalkableTile>(left) && (left)->getType() == '.' && (left)->getRoom() < 0) {
        tileDFS(left->getCoord(), floorNum, chamber);
    }

    // Check above
    std::shared_ptr<WalkableTile> above = floor[coords.first+1][coords.second];
    if (std::dynamic_pointer_cast<WalkableTile>(above) && (above)->getType() == '.' && (above)->getRoom() < 0) {
        tileDFS(above->getCoord(), floorNum, chamber);
    }
}

//--------------------------------------------------------------------------------

void Board::movePlayer(std::string direction) {
    std:shared_ptr<WalkableTile> destination = validDest(player, direction);

    // Check if valid destination
    if (destination == nullptr) {
        return;
    }

    // Check if destination is exit
    if (destination->isStairs()) {
        // EXIT REACHED, FIND A WAY TO TRIGGER NEW FLOOR GENERATION
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

void Board::attackEnemey(std::string direction) {
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

void Board::moveEnemies() {
    // Iterate through enemies and dragons to execute their turn
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {

        // Check if merchant
        if (std::dynamic_pointer_cast<Merchant>(it->getOccupant())) {
            
            // Check if merchants are hostile
            if (!merchantAgro) {
                // Not hostile, just move
                std:shared_ptr<WalkableTile> destination;

                while (destination == nullptr) {
                    int rng = std::rand() % 8;

                    if (rng == 0) {
                        destination = validDest(*it, "no");
                    } else if (rng == 1) {
                        destination = validDest(*it, "so");
                    } else if (rng == 2) {
                        destination = validDest(*it, "ea");
                    } else if (rng == 3) {
                        destination = validDest(*it, "we");
                    } else if (rng == 4) {
                        destination = validDest(*it, "ne");
                    } else if (rng == 5) {
                        destination = validDest(*it, "nw");
                    } else if (rng == 6) {
                        destination = validDest(*it, "se");
                    } else if (rng == 7) {
                        destination = validDest(*it, "sw");
                    }
                }

                // Swap Merchant pointers
                destination->setOccupant((*it)->getOccupant);
                (*it)->setOccupant(nullptr);
                (*it) = destination; // is this legal LOL

                // End Merchant turn
                continue;
            } // If agro, then check for attack
        }// Not a merchant

        // Check distance from player
        std::pair<int, int> p_coord = player->getCoord();
        std::pair<int, int> e_coord = (*it)->getCoord();

        double distance = std::floor(std::sqrt(std::pow((p_coord.first - e_coord.first), 2) + std::pow((p_coord.second - e_coord.second), 2)));

        // DLC EXTENSION HERE: add else if (distance < radius) -> move towards player

        if (distance == 1) {
            // 1 tile away, attack player
            bool killed = player->getOccupant()->getAttacked((*it)->getOccupant());

            if (killed) {
                // Player is dead, game is over
                // DO SOMETHING HERE
            }
        } else {
            // Too far away to attack, do a random move
            std:shared_ptr<WalkableTile> destination;

            while (destination == nullptr) {
                int rng = std::rand() % 8;

                if (rng == 0) {
                    destination = validDest(*it, "no");
                } else if (rng == 1) {
                    destination = validDest(*it, "so");
                } else if (rng == 2) {
                    destination = validDest(*it, "ea");
                } else if (rng == 3) {
                    destination = validDest(*it, "we");
                } else if (rng == 4) {
                    destination = validDest(*it, "ne");
                } else if (rng == 5) {
                    destination = validDest(*it, "nw");
                } else if (rng == 6) {
                    destination = validDest(*it, "se");
                } else if (rng == 7) {
                    destination = validDest(*it, "sw");
                }
            }

            // Swap Enemy pointers
            destination->setOccupant((*it)->getOccupant);
            (*it)->setOccupant(nullptr);
            (*it) = destination; // is this legal LOL

        }

        // Print to Text Display here

    } // end of Enemies loop

    // Iterate through dragons to see if they attack the player
    for (auto it = dragons.begin(); it != dragons.end(); ++it) {
        // Check dragon distance from player
        std::pair<int, int> pCoord = player->getCoord();
        std::pair<int, int> eCoord = (*it)->getCoord();

        double distance = std::floor(std::sqrt(std::pow((pCoord.first - eCoord.first), 2) + std::pow((pCoord.second - eCoord.second), 2)));

        // Check dragon hoard distance from player
        // Find the dragon hoard 
        std:shared_ptr<WalkableTile> dragonHoard;

        for (int i = 0; i < 8; i++) {
            if (i == 0) {
                dragonHoard = validDest(*it, "no");
            } else if (i == 1) {
                dragonHoard = validDest(*it, "so");
            } else if (i == 2) {
                dragonHoard = validDest(*it, "ea");
            } else if (i == 3) {
                dragonHoard = validDest(*it, "we");
            } else if (i == 4) {
                dragonHoard = validDest(*it, "ne");
            } else if (i == 5) {
                dragonHoard = validDest(*it, "nw");
            } else if (i == 6) {
                dragonHoard = validDest(*it, "se");
            } else if (i == 7) {
                dragonHoard = validDest(*it, "sw");
            }

            // Check if direction has the hoard
            if (dragonHoard && std::dynamic_pointer_cast<DragonHoard>(dragonHoard->getGold())) {
                break;
            }
        } 

        std::pair<int, int> hoardCoord = dragonHoard->getCoord();
        double hoardDistance = std::floor(std::sqrt(std::pow((hoardCoord.first - eCoord.first), 2) + std::pow((hoardCoord.second - eCoord.second), 2)));


        if (distance == 1 || hoardDistance == 1) {
            // 1 tile away from either the dragon or the dragon hoard, attack player
            bool killed = player->getOccupant()->getAttacked((*it)->getOccupant());

            if (killed) {
                // Player is dead, game is over
                // DO SOMETHING HERE
            }
        }

        // DLC EXTENSION HERE: Make dragons roam around the hoard
        
        // Print to Text Display here
    } // end of Dragons loop

}


void Board::usePotion(std::string direction) {
    std:shared_ptr<WalkableTile> target = validDest(player, direction);

    // Check if valid destination
    if (target == nullptr) {
        return;
    }

    // Check if destination is occupied by a potion
    if (destination->getPotion() != nullptr) {
        // Use potion
        player->getOccupant()->usePotion(target->getPotion());

        // Add potion to memory, if new
        bool usedBefore = false;

        for (auto it = potions.begin(); it != potions.end(); ++it) {
            if (it->getType() == target->getPotion()->getType()) {
                usedBefore = true;
                break;
            }
        }

        if (!usedBefore) {
            potions.emplace_back(target->getPotion()->getType());
        }

        // Remove potion from board
        target->setPotion(nullptr);
    }

}


void Board::generateFloor() {
    // First need to identify which tiles are a part of which chamber

    // Iterate through floor
    for (auto it_y = floor.begin(); it_y != floor.end(); ++it_y) {
        for (auto it_x = it_y->begin(); it_x != it_y->end(); ++it_x) {
            // Check if walkable tile and unidentified chamber floor
            if (std::dynamic_pointer_cast<WalkableTile>(*it_x) && (*it_x)->getType() == '.' && (*it_x)->getRoom() < 0) {
                // Begin depth first search algorithm, call helper function
                // Determine current chamber
                int floorNum = chambers.size();
                std::vector<std::shared_ptr<WalkableTile>> chamber; 
                
                // Enter recursive function
                tileDFS((*it_x)->getCoord(), floorNum, chamber);
                
                // Store current chamber
                chambers.emplace_back(chamber);
            } 

        }
    } // Finished identifying tiles to their chambers


    // Begin RNG piece generation


    // Generate player
    int pChamber = std::rand() % chambers.size();
    int tile = std::rand() % chambers[pChamber].size();

        // Insert Player
    chambers[pChamber][tile].setOccupant(); // NEED A WAY TO DETERMINE WHICH PLAYER TYPE TO PLACE INSIDE
    player = chambers[pChamber][tile];


    // Generate exit stairs
    int chamber = pChamber;

    // Ensure exit stairs are not in the same chamber as the player
    while (chamber == pChamber) {
        chamber = std::rand() % chambers.size();
    }

    tile = std::rand() % chambers[chamber].size();

        // Insert exit stairs
    chambers[chamber][tile].setExit();


    // Generate 10 Potions
    for (int i = 0; i < 10; i++) {
        // Generate type
        int type = std::rand() % 6;
        std::shared_ptr<Potion> temp;

        if (type == 0) {
            temp = std::make_shared<RH>();
        } else if (type == 1) {
            temp = std::make_shared<BA>();
        } else if (type == 2) {
            temp = std::make_shared<BD>();
        } else if (type == 3) {
            temp = std::make_shared<PH>();
        } else if (type == 4) {
            temp = std::make_shared<WA>();
        } else if (type == 5) {
            temp = std::make_shared<WD>();
        }

        // Generate location (make sure not occupied)
        do {
            chamber = std::rand() % chambers.size();
            tile = std::rand() % chambers[chamber].size();
        } while (chambers[chamber][tile].getPotion());

        // Place type at location
        chambers[chamber][tile].setPotion(temp);
    }


    // Generate 10 Gold
    for (int i = 0; i < 10; i++) {
        // Generate type
        int type = std::rand() % 8;
        std::shared_ptr<Gold> temp;

        if (type >= 0 && type <= 4) {
            temp = std::make_shared<Gold>("Normal", 2);
        } else if (type == 5 || type == 6) {
            temp = std::make_shared<Gold>("Small", 1);
        } else if (type == 7) {
            temp = std::make_shared<DragonHoard>();
            dragons.emplace_back(temp->getDragon()); 
        }

        // Generate location (make sure not occupied)
        do {
            chamber = std::rand() % chambers.size();
            tile = std::rand() % chambers[chamber].size();
        } while (chambers[chamber][tile].getPotion() || chambers[chamber][tile].getGold());

        // Place type at location
        chambers[chamber][tile].setGold(temp);
    }


    // Generate 20 Enemies
    for (int i = 0; i < 20; i++) {
        // Generate type
        int type = std::rand() % 18;
        std::shared_ptr<Enemy> temp;

        if (type >= 0 && type <= 3) {
            temp = std::make_shared<Human>();
        } else if (type >= 4 && type <= 6) {
            temp = std::make_shared<Dwarf>();
        } else if (type >= 7 && type <= 11) {
            temp = std::make_shared<Halfling>();
        } else if (type >= 12 && type <= 13) {
            temp = std::make_shared<Elf>();
        } else if (type >= 14 && type <= 15) {
            temp = std::make_shared<Orc>();
        } else if (type >= 16 && type <= 17) {
            temp = std::make_shared<Merchant>();
        }

        // Generate location (make sure not occupied)
        do {
            chamber = std::rand() % chambers.size();
            tile = std::rand() % chambers[chamber].size();
        } while (chambers[chamber][tile].getPotion() || chambers[chamber][tile].getGold() || chambers[chamber][tile].getOccupant());

        // Place type at location
        chambers[chamber][tile].setOccupant(temp);

    }
}

