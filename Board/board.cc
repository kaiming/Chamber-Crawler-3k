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
#include "ph.h"
#include "wa.h"
#include "wd.h"

#include "gold.h"
#include "dragonhoard.h"

// Include all player and enemy races

/*
    std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors;
    std::vector<bool> filled; 
    std::vector<std::vector<std::shared_ptr<WalkableTile>>> chambers;
    std::shared_ptr<WalkableTile> player;
    std::vector<std::shared_ptr<WalkableTile>> enemies;
    std::vector<std::shared_ptr<WalkableTile>> dragonHoards;
    std::vector<std::string> potionsUsed;

    std::vector<std::shared_ptr<WalkableTile>> playerSpawns;
    std::shared_ptr<Player> playerPtr;
    int floorNum;
    bool merchantAgro;
*/

Board(
        std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors, 
        std::vector<bool> filled, 
        std::vector<std::shared_ptr<WalkableTile>> playerSpawns,
        std::vector<std::shared_ptr<WalkableTile>> enemies,
        std::vector<std::shared_ptr<WalkableTile>> dragonHoards,
        std::string race
) : floors{floors}, filled{filled}, playerSpawns{playerSpawns}, player{playerSpawns[0]}, enemies{enemies}, dragonHoards{dragonHoards}, floorNum{1} {
    
    // Generate Player by given Race
    if (race == "s") {
        playerPtr = std::make_shared<Shade>();
    } else if (race == "d") {
        playerPtr = std::make_shared<Drow>();
    } else if (race == "v") {
        playerPtr = std::make_shared<Vampire>();
    } else if (race == "g") {
        playerPtr = std::make_shared<Goblin>();
    } else if (race == "t") {
        playerPtr = std::make_shared<Troll>();
    }

    // First need to identify which tiles are a part of which chamber
    assignChambers();
    
    // If not filled, generate floor pieces
    if (!filled[floorNum - 1]) {
        generateFloor();
    } else {
        // If generated, store player into given tile
        player.setOccupant(playerPtr);
    }

}

int Board::getFloorNum() const {
    return floorNum;
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

        destination = floors[floorNum-1][current.second - 1][current.first];
    } else if (direction == "so") {
        // so = South/Down
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.second + 1 >= floors[floorNum-1].size()) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second + 1][current.first];
    } else if (direction == "ea") {
        // ea = East/Right
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.first + 1 >= floors[floorNum-1][0].size()) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second][current.first + 1];
    } else if (direction == "we") {
        // we = West/Left
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.first - 1 < 0) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second][current.first - 1];
    } else if (direction == "ne") { // ----------------------------------------------------------------------
        // ne = North East/Right and Up
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.first + 1 >= floors[floorNum-1][0].size() || current.second - 1 < 0) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second - 1][current.first + 1];
    } else if (direction == "nw") {
        // nw = North West/Left and Up 
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.first - 1 < 0 || current.second - 1 < 0) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second - 1][current.first - 1];
    } else if (direction == "se") {
        // se = South East/Right and Down
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.first + 1 >= floors[floorNum-1][0].size() || current.second + 1 >= floors[floorNum-1].size()) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second + 1][current.first + 1];
    } else if (direction == "sw") {
        // sw = South West/Left and Down
        std::pair current = package.getCoord();

        // Check if in bounds
        if (current.first - 1 < 0 || current.second + 1 >= floors[floorNum-1].size()) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second + 1][current.first - 1];
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

void Board::assignChambers() {
    // Iterate through floor
    for (auto it_y = floors[floorNum-1].begin(); it_y != floors[floorNum-1].end(); ++it_y) {
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
}

void Board::tileDFS(std::pair<int, int> coords, int floorNum, std::vector<std::shared_ptr<WalkableTile>>& chamber) {
    
    // Store current tile
    floors[floorNum-1][coords.second][coords.first].setRoom(floorNum);
    chamber.emplace_back(floors[floorNum-1][coords.second][coords.first]); 


    // Check all directions around for matching unidentified chamber floor tiles

    // Check to the right
    if (coords.first + 1 < floors[floorNum-1][coords.second].size()) {
        std::shared_ptr<WalkableTile> right = floors[floorNum-1][coords.second][coords.first+1];
        
        if (std::dynamic_pointer_cast<WalkableTile>(right) && (right)->getType() == '.' && (right)->getRoom() < 0) {
            tileDFS(right->getCoord(), floorNum, chamber);
        }
    }

    // Check below
    if (coords.second + 1 < floors[floorNum-1].size()) {
        std::shared_ptr<WalkableTile> down = floors[floorNum-1][coords.second+1][coords.first];
        
        if (std::dynamic_pointer_cast<WalkableTile>(down) && (down)->getType() == '.' && (down)->getRoom() < 0) {
            tileDFS(down->getCoord(), floorNum, chamber);
        }
    }
    
    // Check to the left
    if (coords.first - 1 >= 0) {
        std::shared_ptr<WalkableTile> left = floors[floorNum-1][coords.second][coords.first-1];
    
        if (std::dynamic_pointer_cast<WalkableTile>(left) && (left)->getType() == '.' && (left)->getRoom() < 0) {
            tileDFS(left->getCoord(), floorNum, chamber);
        }
    }

    // Check above
    if (coords.second -1 >= 0) {
        std::shared_ptr<WalkableTile> above = floors[floorNum-1][coords.second - 1][coords.first];
     
        if (std::dynamic_pointer_cast<WalkableTile>(above) && (above)->getType() == '.' && (above)->getRoom() < 0) {
            tileDFS(above->getCoord(), floorNum, chamber);
        }
    }
    
}

void Board::changeFloor() {
    // Change Floor, floorNum has already been updated

    // Check if floors[floorNum-1] is populated
    if (filled[floorNum-1]) {
        // Floor has been pre-generated
        player = playerSpawns[floorNum-1];
        player.setOccupant(playerPtr);
    } else {
        // Floor has not been pre-generated
        generateFloor();
    }

}

//--------------------------------------------------------------------------------

int Board::movePlayer(std::string direction) {
    std:shared_ptr<WalkableTile> destination = validDest(player, direction);

    // Check if valid destination
    if (destination == nullptr) {
        return 0;
    }

    // Check if destination is exit
    if (destination->isStairs()) {
        // EXIT REACHED, FIND A WAY TO TRIGGER NEW FLOOR GENERATION
        if (floorNum == floorLimit) {
            // Game completed
            return 2;
        } else {
            // Proceed to next floor
            floorNum += 1;
            changeFloor();
            return 1;
        }
        
    }

    // Check if destination is occupied by an enemy
    if (destination->getOccupant() != nullptr) {
        return 0;
    }

    // Check if destination is occupied by a potion
    if (destination->getPotion() != nullptr) {
        // DLC EXTENSION LOCATION: Change this behaviour if we want to make potions walk-over to use
        return 0;
    }

    // Check if destination is occupied by gold
    if (destination->getGold().size() != 0) {
        
        // Get gold reference
        std::vector<std::shared_ptr<Gold>>& gold = destination->getGold();
        
        // Loop over gold vector
        for (auto it = gold.begin(); it != gold.end(); ++it) {
            // Check if Dragon Hoard
            if (std::dynamic_pointer_cast<DragonHoard>((*it)) {
                // Check if dragon is dead
                if ((*it)->getDragon()->isAlive()) {
                    // Dragon is dead
                    // Player picks up gold
                    player->occupant->setGold(player->occupant->getGold() + (*it)->getSize());
                    // Gold is consumed
                    gold.erase(it); 
                }

                // Else do nothing

            } else {
                // Player picks up gold
                player->occupant->setGold(player->occupant->getGold() + (*it)->getSize());
                // Gold is consumed
                gold.erase(it); 
            }
        }
    }

    // Move the Player
    player = player.move(destination);

    // Exit not reached
    return 0;
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
        bool EnemyKilled = target->getOccupant()->getAttacked(*(player->getOccupant()));
    
        if (EnemyKilled) {
            // Enemy killed, determine Enemy type to generate gold dropped

            // Check if target is dragon
            if (std::dynamic_pointer_cast<Dragon>(target->getOccupant())) {
                // Dragon Type, drop nothing
                
                // Remove this dragon from dragons
                for (auto it = dragonHoards.begin(); it != dragonHoards.end(); ++it) {
                    if ((*it)->getDragon() == target->getOccupant()) {
                        (*it)->getDragon()->setState(false);
                    }
                }

            } else {
                
                // Check if target is human or merchant
                if (std::dynamic_pointer_cast<Human>(target->getOccupant())) {
                    // Human type, drop 2 Normal Piles
                    target->setGold(std::make_shared<Gold>("Normal Pile", 2)):
                    target->setGold(std::make_shared<Gold>("Normal Pile", 2));

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
                        if ((*it)->getCoord() == target->getCoord()) {
                            enemies.erase(it); 
                        }
                    }
            }


        }
    }

}

bool Board::moveEnemies() {
    // Iterate through enemies and dragons to execute their turn
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {

        // Check if merchant
        if (std::dynamic_pointer_cast<Merchant>((*it)->getOccupant())) {
            
            // Check if merchants are hostile
            if (!merchantAgro) {
                // Not hostile, just move
                std:shared_ptr<WalkableTile> destination == nullptr;

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

                    // Check in chamber (not a doorway or hallway)
                    if (destination.getRoom() < 0) {
                        destination = nullptr;
                        continue;
                    }

                    // Check for gold
                    if (destination->getGold().size() != 0) {
                        // Occupied by gold, loop again
                        // DLC EXTENSION LOCATION: Change this behaviour if we want to make gold walk-overable
                        destination = nullptr;
                        continue;
                    }

                    // Check for potions
                    if (destination->getPotion() != nullptr) {
                        // Occupied by potion, loop again
                        // DLC EXTENSION LOCATION: Change this behaviour if we want to make potions walk-overable
                        destination = nullptr;
                        continue;
                    }

                    // Check for exit
                    if (destination->isExit()) {
                        // Occupied by exit stairs, loop again
                        destination = nullptr; 
                        continue;
                    }
                }

                // Swap Merchant pointers
                (*it) = (*it).move(destination);

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
            bool killed = player->getOccupant()->getAttacked(*((*it)->getOccupant()));

            if (killed) {
                // Player is dead, game is over
                return true;
            }
        } else {
            // Too far away to attack, do a random move
            std:shared_ptr<WalkableTile> destination == nullptr;

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

                // Check in chamber (not a doorway or hallway)
                if (destination.getRoom() < 0) {
                    destination = nullptr;
                    continue;
                }

                // Check for gold
                if (destination->getGold().size() != 0) {
                    // Occupied by gold, loop again
                    // DLC EXTENSION LOCATION: Change this behaviour if we want to make gold walk-overable
                    destination = nullptr;
                    continue;
                }

                // Check for potions
                if (destination->getPotion() != nullptr) {
                    // Occupied by potion, loop again
                    // DLC EXTENSION LOCATION: Change this behaviour if we want to make potions walk-overable
                    destination = nullptr;
                    continue;
                }

                // Check for exit
                if (destination->isExit()) {
                    // Occupied by exit stairs, loop again
                    destination = nullptr; 
                    continue;
                }
            }

            // Swap Enemy pointers
            (*it) = (*it).move(destination);


        }

        // Print to Text Display here

    } // end of Enemies loop

    // Iterate through dragons to see if they attack the player
    for (auto it = dragonHoards.begin(); it != dragonHoards.end(); ++it) {
        // Check dragon distance from player
        std::pair<int, int> pCoord = player->getCoord();
        std::pair<int, int> eCoord = (*it)->getDragonTile->getCoord();

        double distance = std::floor(std::sqrt(std::pow((pCoord.first - eCoord.first), 2) + std::pow((pCoord.second - eCoord.second), 2))); 

        std::pair<int, int> hoardCoord = (*it)->getCoord();
        double hoardDistance = std::floor(std::sqrt(std::pow((hoardCoord.first - eCoord.first), 2) + std::pow((hoardCoord.second - eCoord.second), 2)));


        if (distance == 1 || hoardDistance == 1) {
            // 1 tile away from either the dragon or the dragon hoard, attack player
            bool killed = player->getOccupant()->getAttacked(*((*it)->getOccupant()));

            if (killed) {
                // Player is dead, game is over
                return true;
            }
        }

        // DLC EXTENSION HERE: Make dragons roam around the hoard
        
        // Print to Text Display here
    } // end of Dragons loop

    // End of Enemies turn
    // Player is still alive
    return false;
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
    // Begin RNG piece generation


    // Generate player
    int pChamber = std::rand() % chambers.size();
    int tile = std::rand() % chambers[pChamber].size();

    // Insert Player
    chambers[pChamber][tile].setOccupant(playerPtr);
    player = chambers[pChamber][tile];


    // Generate exit stairs
    int chamber;

    // Ensure exit stairs are not in the same chamber as the player
    do {
        chamber = std::rand() % chambers.size();
    } while (chamber == pChamber);

    tile = std::rand() % chambers[chamber].size();

        // Insert exit stairs
    chambers[chamber][tile].setExit(true);


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
            dragonHoards.emplace_back(temp); 
        }

        // Generate location (make sure not occupied)
        do {
            chamber = std::rand() % chambers.size();
            tile = std::rand() % chambers[chamber].size();
        } while (chambers[chamber][tile].getPotion() || chambers[chamber][tile].getGold().size() != 0); // DLC EXTENSION HERE: if gold can stack, remove second if clause
        

        // Place type at location
        chambers[chamber][tile].setGold(temp);

        // If dragonHoard type, place Dragon around it
        if (type == 7) {
            // Allocate dragon spawn destination
            std:shared_ptr<WalkableTile> destination == nullptr;

            // Generate direction around DragonHoard
            do {
                int rng = std::rand() % 8;

                if (rng == 0) {
                    destination = validDest(chambers[chamber][tile], "no");
                } else if (rng == 1) {
                    destination = validDest(chambers[chamber][tile]), "so");
                } else if (rng == 2) {
                    destination = validDest(chambers[chamber][tile], "ea");
                } else if (rng == 3) {
                    destination = validDest(chambers[chamber][tile], "we");
                } else if (rng == 4) {
                    destination = validDest(chambers[chamber][tile], "ne");
                } else if (rng == 5) {
                    destination = validDest(chambers[chamber][tile], "nw");
                } else if (rng == 6) {
                    destination = validDest(chambers[chamber][tile], "se");
                } else if (rng == 7) {
                    destination = validDest(chambers[chamber][tile], "sw");
                }
            } while (destination == nullptr);

            // Place dragon at location and store in DragonHoard
            destination.setOccupant(temp->getDragon());
            temp.setDragonTile(destination);
        }
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
