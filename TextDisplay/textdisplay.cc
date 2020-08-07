#include "textdisplay.h"

#include <memory>
#include <string>

#include "tile.h"
#include "walkabletile.h"

#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"
#include "halfling.h"

#include "gold.h"
#include "potion.h"


void TextDisplay::drawFloor(std::ostream& out, Board& board, std::string action) {
    // Print out floor diagram

    // Iterate through the current floor
    for(auto it_i = board.floors[board.getFloorNum - 1].begin(); it_i != board.floors[board.getFloorNum - 1].end(); ++ it_i) {
        for (auto it_j = it_i->begin(); it_j != it_i->end(); ++ it_j) {
            
            // Determine if Walkable Tile
            if (std::dynamic_pointer_cast<WalkableTile>(*it_j)) {
                // Walkable Tile 
                // Determine symbol to print
                
                // Check for Exit, Gold, Potion, or Character
                if ((*it_j)->isExit()) {
                    // Print "/" for stairs
                    out << "/";
                } else if ((*it_j)->getPotion != nullptr) {
                    // Print "P" for potion
                    out << "P";
                } else if ((*it_j)->getGold != nullptr) {
                    // Print "G" for gold
                    out << "G";
                } else {
                    // Determine Player or Enemy
                    
                    // Check if player
                    if ((*it_j) == board.player) {
                        // Print "@" for player
                        out << "@";
                        continue;
                    }

                    // Determine enemy type 
                    std::shared_ptr<Enemy> enemy = (*it_j)->getOccupant();

                    if (std::dynamic_pointer_cast<Human>(enemy)) {
                        // Print "H" for Human
                        out << "H";
                    } else if (std::dynamic_pointer_cast<Dwarf>(enemy)) {
                        // Print "W" for Dwarf
                        out << "W";
                    } else if (std::dynamic_pointer_cast<Elf>(enemy)) {
                        // Print "E" for Elf
                        out << "E";
                    } else if (std::dynamic_pointer_cast<Orc>(enemy)) {
                        // Print "O" for Orc
                        out << "O";
                    } else if (std::dynamic_pointer_cast<Merchant>(enemy)) {
                        // Print "M" for Merchant
                        out << "M";
                    } else if (std::dynamic_pointer_cast<Dragon>(enemy)) {
                        // Print "D" for Dragon
                        out << "D";
                    } else if (std::dynamic_pointer_cast<Halfling>(enemy)) {
                        // Print "L" for Halfling
                        out << "L";
                    }
                }

            } else {
                // Regular Tile, print type
                out << i(*it_j)->getType;
            }

        } // End of inner loop

        // Print new line
        out << std::endl;

    } // End of outer loop


    // Print status

    // Print Status format
    // Race: XXXXX  Gold: XXX             Floor: XX
    // HP: XXX
    // Atk: XXX
    // Def: XXX
    // Action:

    // Convert Player race to full name
    std::string fullRace;
    if (board.race == "s") {
        fullRace = "Shade";
    } else if (board.race == "d") {
        fullRace = "Drow";
    } else if (board.race == "v") {
        fullRace = "Vampire";
    } else if (board.race == "g") {
        fullRace = "Goblin";
    } else if (board.race == "t") {
        fullRace = "Troll";
    }

    // Race: XXXXX  Gold: XXX             Floor: XX
    // 24 chars Race + Gold & 9 Chars for Floor: XX
    out << "Race: " << std::setw(7) << fullRace << "  Gold: " << std::setw(3) << board.playerPtr->getGold() << std::setw(board.floors[floorNum -1][0].size() - 33) << "Floor: " << std::setw(2) << board.floorNum << std::endl; 
    // HP: XXX
    out << "HP: " << playerPtr->getHP() << std::endl;
    // Atk: XXX
    out << "Atk: " << playerPtr->getAtk() << std::endl;
    // Def: XXX
    out << "Def: " << playerPtr->getDef() << std::endl;
    // Action:
    out << "Action: " << action << std::endl;
} 
