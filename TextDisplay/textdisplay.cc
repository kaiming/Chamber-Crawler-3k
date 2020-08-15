#include "textdisplay.h"

#include <memory>
#include <string>
#include <iomanip>

#include "../Tile/tile.h"
#include "../Tile/walkabletile.h"
#include "../Board/board.h"

#include "../Player/player.h"

#include "../Enemy/human.h"
#include "../Enemy/dwarf.h"
#include "../Enemy/elf.h"
#include "../Enemy/orc.h"
#include "../Enemy/merchant.h"
#include "../Enemy/dragon.h"
#include "../Enemy/halfling.h"

#include "../Gold/gold.h"
#include "../Potion/potion.h"


void TextDisplay::drawFloor(std::ostream& out, Board& board, std::string action) {
    // Print out floor diagram

    // Iterate through the current floor
    for(auto it_i = board.floors[board.getFloorNum() - 1].begin(); it_i != board.floors[board.getFloorNum() - 1].end(); ++ it_i) {
        for (auto it_j = it_i->begin(); it_j != it_i->end(); ++ it_j) {
            
            // Determine if Walkable Tile
            if (std::dynamic_pointer_cast<WalkableTile>(*it_j)) {
                // Walkable Tile 
                // Determine symbol to print
                
                // Check for Exit, Gold, Potion, or Character
                
                if (std::static_pointer_cast<WalkableTile>(*it_j)->getOccupant() != nullptr) {
                    // Determine Player or Enemy
                    
                    // Check if player
                    if ((*it_j) == board.player) {
                        // Print "@" for player
                        out << "@";
                        continue;
                    }

                    // Determine enemy type 
                    std::string enemy = std::static_pointer_cast<WalkableTile>(*it_j)->getOccupant()->getRace();

                    if (enemy == "Human") {
                        // Print "H" for Human
                        out << "H";
                    } else if (enemy == "Dwarf") {
                        // Print "W" for Dwarf
                        out << "W";
                    } else if (enemy == "Elf") {
                        // Print "E" for Elf
                        out << "E";
                    } else if (enemy == "Orc") {
                        // Print "O" for Orc
                        out << "O";
                    } else if (enemy == "Merchant") {
                        // Print "M" for Merchant
                        out << "M";
                    } else if (enemy == "Dragon") {
                        // Print "D" for Dragon
                        out << "D";
                    } else if (enemy == "Halfling") {
                        // Print "L" for Halfling
                        out << "L";
                    }

                } else if (std::static_pointer_cast<WalkableTile>(*it_j)->isExit()) {
                    // Print "/" for stairs
                    out << "/";
                } else if (std::static_pointer_cast<WalkableTile>(*it_j)->getPotion() != nullptr) {
                    // Print "P" for potion
                    out << "P";
                } else if (std::static_pointer_cast<WalkableTile>(*it_j)->getGold() != nullptr) {
                    // Print "G" for gold
                    out << "G";
                } else {
                    // Not occupied, print type
                    out << (std::static_pointer_cast<WalkableTile>(*it_j)->getType());
                }

            } else {
                // Regular Tile, print type
                out << (*it_j)->getType();
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

    // Race: XXXXX  Gold: XXX             Floor: XX
    // 24 chars Race + Gold & 9 Chars for Floor: XX
    out << "Race: " << std::left << std::setw(7) << board.playerPtr->getRace() << "  Gold: " << std::setw(3) << board.playerPtr->getGold() << std::setw(board.floors[board.floorNum -1][1].size() - 33) << "Floor: " << std::setw(2) << board.floorNum << std::endl; 
    // HP: XXX
    out << "HP: " << board.playerPtr->getHP() << std::endl;
    // Atk: XXX
    out << "Atk: " << board.playerPtr->getAtk() << std::endl;
    // Def: XXX
    out << "Def: " << board.playerPtr->getDef() << std::endl;
    // Action:
    out << "Action: " << action << std::endl;
} 
