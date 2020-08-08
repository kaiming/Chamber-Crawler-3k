#include <iostream>
#include "readPlan.h"
#include "tile.h"
#include "walkabletile.h"
#include "board.h"
#include "textdisplay.h"
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
    bool winner = false;

    // if no file is passed in command line
    if (argc == 0) {
        infile.open("default.txt");
    } else { // if there are at least one command line argument (only take the first one and try to open it as a file)
        try {
            // get file name
            const std::string fileName {argv[0]};

            std::ifstream infile {fileName};
        } catch (std::ios_base::failure& fail) {
            std::cerr << "Unable to open file" << std::endl;
            infile.close();
            return;
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
                if (std::cin.eof()) return;

                std::cin.clear();
                std::cin.ignore();
            }

            std::cin >> race;
        }

        if (race == "q") {
            return; // NOTE: MAYBE HAVEIT SO A NEW GAME STARTS??
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
                    return;
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
                    restart = false;
                    winner = true;
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
                bool isFrozen = b.toggleFreeze;

                message = "Enemies Frozen: " + (isFrozen? "True" : "False");

                td.drawFloor(std::cout, b, message);
            } else if (cmd == "r") {
                // Restart game
                restart = true;
                winner = false;

                break;
            } else if (cmd == "q") {
                // Quit Game
                std::cout << "You gave up! Better luck next time!";
                restart = false;
                winner = false;
                break;
            } else {
                // Invalid Command
                std::cout << "Invalid Command" << std::endl;

            }


        } // End of Command Interpreter

        if (winner) {
            // Print winner stuff
            
            std::cout << "Congratulations! You won!";

            // Ask Player if they want to play again
            std::cout << "Play again? y or n";
            std::string replay;
            std::cin >> replay;

            if (replay == "y") {
                restart = true;
            }

        }


    } // End of restart loop

    
    
}
