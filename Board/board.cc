#include "board.h"

#include <utility>
#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "../Tile/tile.h"
#include "../Tile/walkabletile.h"

#include "../Enemy/enemy.h"
#include "../Enemy/human.h"
#include "../Enemy/dwarf.h"
#include "../Enemy/elf.h"
#include "../Enemy/orc.h"
#include "../Enemy/merchant.h"
#include "../Enemy/dragon.h"
#include "../Enemy/halfling.h"

#include "../Player/player.h"
#include "../Player/shade.h"
#include "../Player/drow.h"
#include "../Player/vampire.h"
#include "../Player/troll.h"
#include "../Player/goblin.h"

#include "../Potion/potion.h"
#include "../Potion/rh.h"
#include "../Potion/ba.h"
#include "../Potion/bd.h"
#include "../Potion/ph.h"
#include "../Potion/wa.h"
#include "../Potion/wd.h"

#include "../Gold/gold.h"
#include "../Gold/dragonhoard.h"

// Include all player and enemy races

/*
    std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors;
    std::vector<bool> filled; 
    std::vector<std::vector<std::shared_ptr<WalkableTile>>> chambers;
    std::shared_ptr<WalkableTile> player;
    std::vector<std::vector<std::shared_ptr<WalkableTile>>> enemies;
    std::vector<std::vector<std::shared_ptr<WalkableTile>>> dragonHoards;
    std::vector<std::string> potionsUsed;

    std::vector<std::shared_ptr<WalkableTile>> playerSpawns;
    std::shared_ptr<Player> playerPtr;
    std::string race;
    int floorNum;
    bool merchantAgro;
    bool enemiesFrozen;
*/

Board::Board(
        std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors, 
        std::vector<bool> filled, 
        std::vector<std::shared_ptr<WalkableTile>> playerSpawns,
        std::vector<std::vector<std::shared_ptr<WalkableTile>>> enemies,
        std::vector<std::vector<std::shared_ptr<WalkableTile>>> dragonHoards,
        std::string race
) : floors{floors}, filled{filled}, playerSpawns{playerSpawns}, enemies{enemies}, dragonHoards{dragonHoards}, player{static_cast<int>(playerSpawns.size()) > 0 ? playerSpawns[0] : nullptr}, floorNum{1} {
    
    // Generate Player by given Race
    if (race == "s") {
        playerPtr = std::make_shared<Shade>();
        defaultAtk = 25;
        defaultDef = 25;
    } else if (race == "d") {
        playerPtr = std::make_shared<Drow>();
        defaultAtk = 25;
        defaultDef = 15;
    } else if (race == "v") {
        playerPtr = std::make_shared<Vampire>();
        defaultAtk = 25;
        defaultDef = 25;
    } else if (race == "g") {
        playerPtr = std::make_shared<Goblin>();
        defaultAtk = 15;
        defaultDef = 20;
    } else if (race == "t") {
        playerPtr = std::make_shared<Troll>();
        defaultAtk = 25;
        defaultDef = 15;
    }

    this->race = playerPtr->getRace(); 

    // First need to identify which tiles are a part of which chamber
    assignChambers();
    
    // If not filled, generate floor pieces
    if (!filled[floorNum - 1]) {
        generateFloor();
    } else {
        // If generated, store player into given tile
        player->setOccupant(playerPtr);
    }

}

std::string Board::getRace() const {
    return race;
}

int Board::getFloorNum() const {
    return floorNum;
}

bool Board::toggleFreeze() {
    enemiesFrozen = !enemiesFrozen;
    return enemiesFrozen;
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
        std::pair<int, int> current = package->getCoord();

        // Check if in bounds
        if (current.second - 1 < 0) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second - 1][current.first];
    } else if (direction == "so") {
        // so = South/Down
        std::pair<int, int> current = package->getCoord();

        // Check if in bounds
        if (current.second + 1 >= static_cast<int>(floors[floorNum-1].size())) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second + 1][current.first];
    } else if (direction == "ea") {
        // ea = East/Right
        std::pair<int, int> current = package->getCoord();

        // Check if in bounds
        if (current.first + 1 >= static_cast<int>(floors[floorNum-1][0].size())) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second][current.first + 1];
    } else if (direction == "we") {
        // we = West/Left
        std::pair<int, int> current = package->getCoord();

        // Check if in bounds
        if (current.first - 1 < 0) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second][current.first - 1];
    } else if (direction == "ne") { // ----------------------------------------------------------------------
        // ne = North East/Right and Up
        std::pair<int, int> current = package->getCoord();

        // Check if in bounds
        if (current.first + 1 >= static_cast<int>(floors[floorNum-1][0].size()) || current.second - 1 < 0) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second - 1][current.first + 1];
    } else if (direction == "nw") {
        // nw = North West/Left and Up 
        std::pair<int, int> current = package->getCoord();

        // Check if in bounds
        if (current.first - 1 < 0 || current.second - 1 < 0) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second - 1][current.first - 1];
    } else if (direction == "se") {
        // se = South East/Right and Down
        std::pair<int, int> current = package->getCoord();

        // Check if in bounds
        if (current.first + 1 >= static_cast<int>(floors[floorNum-1][0].size()) || current.second + 1 >= static_cast<int>(floors[floorNum-1].size())) {
            return nullptr;
        }

        destination = floors[floorNum-1][current.second + 1][current.first + 1];
    } else if (direction == "sw") {
        // sw = South West/Left and Down
        std::pair<int, int> current = package->getCoord();

        // Check if in bounds
        if (current.first - 1 < 0 || current.second + 1 >= static_cast<int>(floors[floorNum-1].size())) {
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
        // Destination is a valid, WalkableTile 
        return typeCheck;        
    }

    return nullptr;

}

void Board::assignChambers() {
    // Iterate through floor
    for (auto it_y = floors[floorNum-1].begin(); it_y != floors[floorNum-1].end(); ++it_y) {
        for (auto it_x = it_y->begin(); it_x != it_y->end(); ++it_x) {
            // Check if walkable tile and unidentified chamber floor
            if (std::dynamic_pointer_cast<WalkableTile>(*it_x) && (*it_x)->getType() == '.' && std::static_pointer_cast<WalkableTile>(*it_x)->getRoom() < 0) {
                // Begin depth first search algorithm, call helper function
                // Determine current chamber
                int chamberNum = static_cast<int>(chambers.size()) + 1;
                std::vector<std::shared_ptr<WalkableTile>> chamber; 
                
                // Enter recursive function
                tileDFS((*it_x)->getCoord().first, (*it_x)->getCoord().second, chamberNum, chamber);
                
                // Store current chamber
                chambers.emplace_back(chamber);
            } 

        }
    } // Finished identifying tiles to their chambers
}

void Board::tileDFS(int x, int y, int chamberNum, std::vector<std::shared_ptr<WalkableTile>>& chamber) {
    
    // Store current tile
    std::dynamic_pointer_cast<WalkableTile>(floors[floorNum - 1][y][x])->setRoom(chamberNum);
    chamber.emplace_back(std::dynamic_pointer_cast<WalkableTile>(floors[floorNum-1][y][x])); 


    // Check all directions around for matching unidentified chamber floor tiles

    // Check to the right
    if (x + 1 < static_cast<int>(floors[floorNum-1][y].size())) {
        std::shared_ptr<WalkableTile> right = std::dynamic_pointer_cast<WalkableTile>(floors[floorNum-1][y][x+1]);
        
        if (right && (right)->getType() == '.' && (right)->getRoom() < 0) {
            tileDFS(right->getCoord().first, right->getCoord().second, chamberNum, chamber);
        }
    }

    // Check below
    if (y + 1 < static_cast<int>(floors[floorNum-1].size())) {
        std::shared_ptr<WalkableTile> down = std::dynamic_pointer_cast<WalkableTile>(floors[floorNum-1][y+1][x]);
        
        if (down && (down)->getType() == '.' && (down)->getRoom() < 0) {
            tileDFS(down->getCoord().first, down->getCoord().second, chamberNum, chamber);
        }
    }
    
    // Check to the left
    if (x - 1 >= 0) {
        std::shared_ptr<WalkableTile> left = std::dynamic_pointer_cast<WalkableTile>(floors[floorNum-1][y][x-1]);
    
        if (left && (left)->getType() == '.' && (left)->getRoom() < 0) {
            tileDFS(left->getCoord().first, left->getCoord().second, chamberNum, chamber);
        }
    }

    // Check above
    if (y -1 >= 0) {
        std::shared_ptr<WalkableTile> above = std::dynamic_pointer_cast<WalkableTile>(floors[floorNum-1][y - 1][x]);
     
        if (above && (above)->getType() == '.' && (above)->getRoom() < 0) {
            tileDFS(above->getCoord().first, above->getCoord().second, chamberNum, chamber);
        }
    }
    
}

void Board::changeFloor() {
    // Change Floor
    floorNum += 1;

    // Check if floors[floorNum-1] is populated
    if (filled[floorNum-1]) {
        // Floor has been pre-generated
        player = playerSpawns[floorNum-1];
        player->setOccupant(playerPtr);
    } else {
        // Floor has not been pre-generated
        enemies.clear();
        chambers.clear();
        dragonHoards.clear();
        assignChambers();
        generateFloor();
    }

    player->getOccupant()->setAtk(defaultAtk);
    player->getOccupant()->setDef(defaultDef);
}

//--------------------------------------------------------------------------------

std::string Board::movePlayer(std::string direction) {
    std::shared_ptr<WalkableTile> destination = validDest(player, direction);
    std::string message = "";

    // Check if valid destination
    if (destination == nullptr) {
        return "Invalid Move Target. ";
    }

    // Check if destination is exit
    if (destination->isExit()) {
        if (floorNum == static_cast<int>(floors.size())) {
            // Game completed
            return "Dungeon cleared. You win! ";
        } else {
            // Proceed to next floor
            changeFloor();
            return "Floor " + std::to_string(floorNum - 1) + " cleared. Proceeding to next floor. ";
        }
        
    }

    // Check if destination is occupied by an enemy
    if (destination->getOccupant() != nullptr) {
        return "Target Tile occupied by Enemy. ";
    }

    // Check if destination is occupied by a potion
    if (destination->getPotion() != nullptr) {
        // DLC EXTENSION LOCATION: Change this behaviour if we want to make potions walk-over to use
        return "Target Tile occupied by Potion. ";
    }

    // Check if destination is occupied by gold
    if (destination->getGold() != nullptr) {
        
        // Get gold pointer
        std::shared_ptr<Gold> gold = destination->getGold();
        
        // Check if Dragon Hoard
        if (std::dynamic_pointer_cast<DragonHoard>(gold)) {
            // Check if dragon is dead
            if (std::dynamic_pointer_cast<DragonHoard>(gold)->getDragon()->getState() == false) {
                // Dragon is dead
                // Player picks up gold
                std::dynamic_pointer_cast<Player>(player->getOccupant())->setGold(std::dynamic_pointer_cast<Player>(player->getOccupant())->getGold() + gold->getSize());
                // Gold is consumed
                message = gold->getType() + ", value " + std::to_string(gold->getSize()) + ", picked up. ";

                // Remove from dragonHoards
                for (auto it = dragonHoards[floorNum-1].begin(); it != dragonHoards[floorNum-1].end(); it++) {
                    if ((*it)->getGold() == gold) {
                        dragonHoards[floorNum-1].erase(it);
                        break;
                    }
                }

                destination->setGold(nullptr); 
            }

            // Dragon is still alive; Else do nothing

        } else {
            // Player picks up gold
            std::dynamic_pointer_cast<Player>(player->getOccupant())->setGold(std::dynamic_pointer_cast<Player>(player->getOccupant())->getGold() + gold->getSize());
            // Gold is consumed
            message = gold->getType() + ", value " + std::to_string(gold->getSize()) + ", picked up. ";
            destination->setGold(nullptr); 
        }
    

    }

    // Move the Player
    player = player->move(destination);
    message = playerPtr->getRace() + " moved " + direction + ". " + message;

    // Exit not reached
    return message;
}

std::string Board::attackEnemy(std::string direction) {
    std::shared_ptr<WalkableTile> target = validDest(player, direction);
    std::string message = "";

    // Check if valid destination
    if (target == nullptr) {
        return "Invalid Attack Target. ";
    }

    // Check if destination is occupied by an enemy
    if (target->getOccupant() != nullptr) {
        std::string merchantStatus = "";

        // Check if target is merchant, if merchants are not hostile
        if (!merchantAgro && std::dynamic_pointer_cast<Merchant>(target->getOccupant())) {
            // Merchants are now hostile
            merchantAgro = true;
            merchantStatus = "Merchants are now hostile. ";
        }

        // Begin attack sequence and store resulting enemy state
        double enemyOgHP = target->getOccupant()->getHP();
        bool EnemyKilled = std::dynamic_pointer_cast<Enemy>(target->getOccupant())->getAttacked(*(std::dynamic_pointer_cast<Player>(player->getOccupant())));
    
        if (EnemyKilled) {
            // Enemy killed, determine Enemy type to generate gold dropped

            // Check if target is dragon
            if (target->getOccupant()->getRace() == "Dragon") {
                // Dragon Type, drop nothing
                
                // Remove this dragon from dragons
                for (auto it = dragonHoards[floorNum-1].begin(); it != dragonHoards[floorNum-1].end(); ++it) {
                    if (std::dynamic_pointer_cast<DragonHoard>((*it)->getGold())->getDragon() == target->getOccupant()) {
                        std::dynamic_pointer_cast<DragonHoard>((*it)->getGold())->getDragon()->setState(false);
                    }
                }
                
                message = "Dragon killed. " + merchantStatus;

                // Remove enemy + move player to old spot
                target->setOccupant(nullptr);
                player = player->move(target);

            } else {
                
                std::string eRace = target->getOccupant()->getRace();
                message = eRace + " killed. ";

                // Check if target is human or merchant
                if (target->getOccupant()->getRace() == "Human") {
                    // Human type, drop 2 Normal Piles
                    playerPtr->setGold(playerPtr->getGold() + 2);
                    message += "Normal hoard picked up. ";

                    // RNG a second pile nearby
                    std::shared_ptr<WalkableTile> destination;
                    int i = 0;
                    while (true) {
                        
                        // Exit case in event that no suitable location found
                        if (i > 16) {
                            break;
                        } else {
                            i++;
                        }
                        
                        
                        do {
                            int rng = std::rand() % 8;

                            if (rng == 0) {
                                destination = validDest(target, "no");
                            } else if (rng == 1) {
                                destination = validDest(target, "so");
                            } else if (rng == 2) {
                                destination = validDest(target, "ea");
                            } else if (rng == 3) {
                                destination = validDest(target, "we");
                            } else if (rng == 4) {
                                destination = validDest(target, "ne");
                            } else if (rng == 5) {
                                destination = validDest(target, "nw");
                            } else if (rng == 6) {
                                destination = validDest(target, "se");
                            } else if (rng == 7) {
                                destination = validDest(target, "sw");
                            }
                        } while (!destination);
                        // Check in chamber (not a doorway or hallway)
                        if (destination->getRoom() < 0) {
                            destination = nullptr;
                            continue;
                        }

                        // Check for gold
                        if (destination->getGold() != nullptr) {
                            // Occupied by gold, loop again
                            destination = nullptr;
                            continue;
                        }

                        // Check for potions
                        if (destination->getPotion() != nullptr) {
                            // Occupied by potion, loop again
                            destination = nullptr;
                            continue;
                        }

                        // Check for exit
                        if (destination->isExit()) {
                            // Occupied by exit stairs, loop again
                            destination = nullptr; 
                            continue;
                        }

                        break;
                    }

                    destination->setGold(std::make_shared<Gold>("Normal Hoard", 2));

                } else if (target->getOccupant()->getRace() == "Merchant") {
                    // Merchant Type, drop Merchant Hoard
                    playerPtr->setGold(playerPtr->getGold() + 4);
                    message += "Merchant Hoard picked up. ";

                } else {
                    // Other type, RNG gold
                    if (std::rand() % 2 == 0) {
                        // Small pile
                        playerPtr->setGold(playerPtr->getGold() + 1);
                        message += "Small Hoard picked up. ";
                    } else {
                        // Normal pile
                        playerPtr->setGold(playerPtr->getGold() + 2);
                        message += "Normal Hoard picked up. ";
                    }
                }

                message += merchantStatus;

                // Remove this enemy from enemies
                for (auto it = enemies[floorNum-1].begin(); it != enemies[floorNum-1].end(); ++it) {
                    if ((*it)->getOccupant() == target->getOccupant()) {
                        enemies[floorNum-1].erase(it); 
                    }
                }

                // Remove enemy + move player to old spot
                target->setOccupant(nullptr);
                player = player->move(target);
                
            }

        } else {
            std::stringstream dealt, left;
            dealt << std::fixed << std::setprecision(2) << enemyOgHP - target->getOccupant()->getHP();
            left << std::fixed << std::setprecision(2) << target->getOccupant()->getHP();

            message = target->getOccupant()->getRace() + " attacked for " + dealt.str() + "HP (" + left.str() + "HP remaining). "  + merchantStatus;
        }
    } else {
        message = "No Enemy to Attack. ";
    }

    return message;
}

std::string Board::moveEnemies() {
    std::string message = "";
    
    // If enemies frozen, do nothing
    if (enemiesFrozen) {
        return "Enemies frozen. ";
    }

    // Iterate through enemies and dragons to execute their turn
    for (auto it = enemies[floorNum-1].begin(); it != enemies[floorNum-1].end(); ++it) {

        // Check if merchant
        if (std::dynamic_pointer_cast<Merchant>((*it)->getOccupant())) {
            
            // Check if merchants are hostile
            if (!merchantAgro) {
                // Not hostile, just move
                std::shared_ptr<WalkableTile> destination = nullptr;
                int i = 0; 

                while (true) {

                    // Exit case in event that no suitable location found
                    if (i > 40) {
                        break;
                    } else {
                        i++;
                    }

                    do {
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
                    } while (destination == nullptr);

                    // Check in chamber (not a doorway or hallway)
                    if (destination->getRoom() < 0) {
                        destination = nullptr;
                        continue;
                    }

                    // Check for gold
                    if (destination->getGold() != nullptr) {
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

                    break;
                }
                
                if (destination != nullptr) {
                    // Swap Merchant pointers
                    (*it) = (*it)->move(destination);
                }

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
            double ogHP = player->getOccupant()->getHP();

            // 1 tile away, attack player
            bool killed = std::dynamic_pointer_cast<Player>(player->getOccupant())->getAttacked(*(std::dynamic_pointer_cast<Enemy>((*it)->getOccupant())));
            std::stringstream dealt;
            dealt << std::fixed << std::setprecision(2) << ogHP - playerPtr->getHP();
            
            message += player->getOccupant()->getRace() + " attacked by " + std::dynamic_pointer_cast<Enemy>((*it)->getOccupant())->getRace() + " for " + dealt.str() + "HP. ";  
            
            if (killed) {
                // Player is dead, game is over
                return message += player->getOccupant()->getRace() + " was killed. Game Over!";
            }
        } else {
            // Too far away to attack, do a random move
            std::shared_ptr<WalkableTile> destination = nullptr;
            int i = 0;

            while(true) {
                // Exit case in event that no suitable location found
                if (i > 80) {
                    break;
                } else {
                    i++;
                }

                do {
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
                } while (destination == nullptr); 

                // Check in chamber (not a doorway or hallway)
                if (destination->getRoom() < 0) {
                    destination = nullptr;
                    continue;
                }

                // Check for gold
                if (destination->getGold() != nullptr) {
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
            if (destination != nullptr) {
                (*it) = (*it)->move(destination);
            }

        }

        // Print to Text Display here

    } // end of Enemies loop

    // Iterate through dragons to see if they attack the player
    for (auto it = dragonHoards[floorNum-1].begin(); it != dragonHoards[floorNum-1].end(); ++it) {

        // Check if associated dragon is still alive
        if (std::dynamic_pointer_cast<DragonHoard>((*it)->getGold())->getDragon()->getState() == false) {
            // Dragon is dead
            continue;
        }

        // Check dragon distance from player
        std::pair<int, int> pCoord = player->getCoord();
        std::pair<int, int> eCoord = std::dynamic_pointer_cast<DragonHoard>((*it)->getGold())->getDragonTile()->getCoord(); 

        double distance = std::floor(std::sqrt(std::pow((pCoord.first - eCoord.first), 2) + std::pow((pCoord.second - eCoord.second), 2))); 

        std::pair<int, int> hoardCoord = (*it)->getCoord();
        double hoardDistance = std::floor(std::sqrt(std::pow((pCoord.first - hoardCoord.first), 2) + std::pow((pCoord.second - hoardCoord.second), 2)));


        if (distance == 1 || hoardDistance == 1) {
            double ogHP = player->getOccupant()->getHP();
            std::stringstream dealt;
            dealt << std::fixed << std::setprecision(2) << ogHP - playerPtr->getHP();

            // 1 tile away from either the dragon or the dragon hoard, attack player
            bool killed = std::dynamic_pointer_cast<Player>(player->getOccupant())->getAttacked(*(std::dynamic_pointer_cast<Dragon>(std::static_pointer_cast<DragonHoard>((*it)->getGold())->getDragon())));
            message += player->getOccupant()->getRace() + " attacked by Dragon for "+ dealt.str() + "HP. "; 

            if (killed) {
                // Player is dead, game is over
                return message += player->getOccupant()->getRace() + " was killed. Game Over!";
            }
        }

        // DLC EXTENSION HERE: Make dragons roam around the hoard
        
        // Print to Text Display here
    } // end of Dragons loop

    // End of Enemies turn
    // Player is still alive
    return message;
}


std::string Board::usePotion(std::string direction) {
    std::shared_ptr<WalkableTile> target = validDest(player, direction);
    std::string message = "";

    // Check if valid destination
    if (target == nullptr) {
        return "Invalid Potion Target. ";
    }

    // Check if destination is occupied by a potion
    if (target->getPotion() != nullptr) {
        // Use potion
        std::dynamic_pointer_cast<Player>(player->getOccupant())->usePotion(target->getPotion());

        // Add potion to memory, if new
        bool usedBefore = false;

        if (std::find(potionsUsed.begin(), potionsUsed.end(), target->getPotion()->getType()) != potionsUsed.end()) {
            usedBefore = true;
        }

#if 0
        for (std::vector<std::string>::iterator it = potionsUsed.begin(); it != potionsUsed.end(); ++it) {
            if ((*it) == target->getPotion()->getType()) {
                usedBefore = true;
                break;
            }
        }
#endif

        if (!usedBefore) {
            potionsUsed.emplace_back(target->getPotion()->getType());
        }

        message = target->getPotion()->getType() + " was Used. ";

        // Remove potion from board
        target->setPotion(nullptr);
        player = player->move(target);
    } else {
        message = "No Potion to Use. ";
    }
    
    return message;
}


void Board::generateFloor() {
    // Begin RNG piece generation


    // Generate player
    int pChamber = std::rand() % static_cast<int>(chambers.size());
    int tile = std::rand() % static_cast<int>(chambers[pChamber].size());

    // Insert Player
    chambers[pChamber][tile]->setOccupant(playerPtr);
    player = chambers[pChamber][tile];


    // Generate exit stairs
    int chamber;

    // Ensure exit stairs are not in the same chamber as the player
    do {
        chamber = std::rand() % static_cast<int>(chambers.size());
    } while (chamber == pChamber);

    tile = std::rand() % static_cast<int>(chambers[chamber].size());

        // Insert exit stairs
    chambers[chamber][tile]->setExit(true);


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
            chamber = std::rand() % static_cast<int>(chambers.size());
            tile = std::rand() % static_cast<int>(chambers[chamber].size());
        } while (chambers[chamber][tile]->getPotion());

        // Place type at location
        chambers[chamber][tile]->setPotion(temp);
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
        }

        // Generate location (make sure not occupied)
        do {
            chamber = std::rand() % static_cast<int>(chambers.size());
            tile = std::rand() % static_cast<int>(chambers[chamber].size());
        } while (chambers[chamber][tile]->getPotion() || chambers[chamber][tile]->getGold()); // DLC EXTENSION HERE: if gold can stack, remove second if clause
        

        // Place type at location
        chambers[chamber][tile]->setGold(temp);

        // If dragonHoard type, place Dragon around it
        if (type == 7) {
            // Add to dragonHoards
            dragonHoards[floorNum-1].emplace_back(std::dynamic_pointer_cast<WalkableTile>(chambers[chamber][tile])); 

            // Allocate dragon spawn destination
            std::shared_ptr<WalkableTile> destination = nullptr;

            // Generate direction around DragonHoard
            do {
                int rng = std::rand() % 8;

                if (rng == 0) {
                    destination = validDest(chambers[chamber][tile], "no");
                } else if (rng == 1) {
                    destination = validDest(chambers[chamber][tile], "so");
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
            destination->setOccupant(std::dynamic_pointer_cast<DragonHoard>(temp)->getDragon());
            std::dynamic_pointer_cast<DragonHoard>(temp)->setDragonTile(destination);
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
            chamber = std::rand() % static_cast<int>(chambers.size());
            tile = std::rand() % static_cast<int>(chambers[chamber].size());
        } while (chambers[chamber][tile]->getPotion() != nullptr || chambers[chamber][tile]->getGold() != nullptr || chambers[chamber][tile]->getOccupant() != nullptr || chambers[chamber][tile]->isExit());

        // Place type at location
        chambers[chamber][tile]->setOccupant(temp);
        enemies[floorNum-1].emplace_back(chambers[chamber][tile]);
    }
}

