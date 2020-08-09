#include <iostream>
#include "readPlan.h"
#include "../Tile/tile.h"
#include "../Tile/walkabletile.h"
#include "../Board/board.h"
#include "../TextDisplay/textdisplay.h"
// add includes

int main(int argc, char* argv[]) {
        std::ifstream infile;
        infile.exceptions(std::ifstream::failbit);
        std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors;
        std::vector<std::shared_ptr<WalkableTile>> playerSpawns;
        std::vector<std::shared_ptr<WalkableTile>> enemies;
        std::vector<std::shared_ptr<WalkableTile>> dragonHoards;
        std::vector<bool> filled;
        bool restart = true;
        int winner = -1; // code 0 for restart, code 1 for win, code 2 for loss

        // if no file is passed in command line
        if (argc == 0) {
            try {
                infile.open("../default.txt");
            } catch (...) {
                std::cout << "error" << std::endl;
            }
            
        } else { // if there are at least one command line argument (only take the first one and try to open it as a file)
            try {
                // get file name (MAKE SURE ITS FULL FILE PATH)
                const std::string fileName {argv[0]};

                std::ifstream infile {fileName};
            } catch (std::ios_base::failure& fail) {
                std::cerr << "Unable to open file" << std::endl;
                infile.close();
                return 0;
            }
        } 

        // read in file for floor plan
        readFloorPlan(infile, floors, playerSpawns, enemies, dragonHoards, filled);

        // close file
        infile.close();

    while (restart) {
        restart = false;

        Board b;
        TextDisplay td;

        // Ask player to enter one of the specified races or quit
        std::string race;

        std::cout << "Welcome to ChamberCrawler3000, prepare to enter the unknown!" << std::endl;
        std::cout << "Choose your character: Shade 's' (default), Drow 'd', Vampire 'v', Goblin 'g', Troll 't'" << std::endl;
        std::cout << "Enter here: ";

        std::cin >> race;

        while (race != "" || race != "s" || race != "d" || race != "v" || race != "g" || race != "t") {
            std::cerr << "Invalid race" << std::endl;
            std::cout << "Enter here: ";

            if (std::cin.fail()) {
                if (std::cin.eof()) return 0;

                std::cin.clear();
                std::cin.ignore();
            }

            std::cin >> race;
        }

        if (race == "q") {
            return 0; // NOTE: MAYBE HAVE IT SO A NEW GAME STARTS??
        } else if (race == "r") {
            restart = true; // Sort of useless LOL
            continue;
        } else if (race == "") { // default race
            b = Board {floors, filled, playerSpawns, enemies, dragonHoards, "s"};
        } else {
            b = Board {floors, filled, playerSpawns, enemies, dragonHoards, race};
        }

        td.drawFloor(std::cout, b, "The adventure begins");

        std::string cmd;

        while (true) {
            std::cout << "Enter command: ";
            std::cin >> cmd;

            // break clause
            if (std::cin.fail()) {
                if (std::cin.eof()) {
                    return 0;
                }
            }

            // Process commands
            std::string message;

            if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
                // Move player in given direction
                message = b.movePlayer(cmd);

                td.drawFloor(std::cout, b, message);

                if (message == "Dungeon cleared. You win!") {
                    // Game Won by Player
                    winner = 1;

                    break;
                } 

            } else if (cmd[0] == 'u') {
                // Use potion in given direction
                message = b.usePotion(cmd.substr(2));

                td.drawFloor(std::cout, b, message);
            } else if (cmd[0] == 'a') {
                // Attack enemy in the given direction
                message = b.attackEnemy(cmd.substr(2));

                td.drawFloor(std::cout, b, message);
            } else if (cmd == "f") {
                // Freeze enemies
                bool isFrozen = b.toggleFreeze();

                message = "Enemies Frozen: ";
                
                if (isFrozen) {
                    message += "Enabled";
                 } else {
                    message += "Disabled";
                 }

                td.drawFloor(std::cout, b, message);
            } else if (cmd == "r") {
                // Restart game
                restart = true;
                winner = 0;

                break;
            } else if (cmd == "q") {
                // Quit Game
                std::cout << "You gave up! Better luck next time!";

                return 0;
            } else {
                // Invalid Command
                std::cerr << "Invalid Command" << std::endl;

            }

            // Move Enemies
            message = b.moveEnemies();
            td.drawFloor(std::cout, b, message);
            
            if (message.substr(-10) == "Game Over!") {
                // Player killed and lost
                winner = 2;
                break;
            }

        } // End of Command Interpreter

        if (winner == 1) {
            // Print winner stuff
            
            std::cout << "Congratulations! You won!";
        } else if (winner == 2) {
            // Print loser stuff
            
            std::cout << "You have been defeated!";

        }

        if (winner != 0) {
            // Ask Player if they want to play again
            std::cout << "Play again? y or n";
            std::string replay = "";
            
            while (replay != "y" && replay != "n") {
                if (replay != "") {
                    std::cerr << "Invalid Answer" << std::endl;
                }
                
                std::cin >> replay;

                if (std::cin.fail()) {
                    if (std::cin.eof()) return 0;

                    std::cin.clear();
                    std::cin.ignore();
                }
            }

            if (replay == "y") {
                restart = true;
            }
        }

    } // End of restart loop

    

}
