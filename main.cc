#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <memory>
#include "./ReadFile/readPlan.h"
#include "./Tile/tile.h"
#include "./Tile/walkabletile.h"
#include "./Board/board.h"
#include "./TextDisplay/textdisplay.h"

int main(int argc, char* argv[]) {
    bool restart = true;

    while (restart) {
        restart = false;

        std::ifstream infile;
        std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors;
        std::vector<std::shared_ptr<WalkableTile>> playerSpawns;
        std::vector<std::vector<std::shared_ptr<WalkableTile>>> enemies;
        std::vector<std::vector<std::shared_ptr<WalkableTile>>> dragonHoards;
        std::vector<bool> filled;
        int winner = -1; // code 0 for restart, code 1 for win, code 2 for loss

        // if no file is passed in command line
        if (argc == 1) {
            try { 
                infile.open("./default.txt");
            } catch (...) {
               std::cerr << "Error reading in default file" << std::endl;
               infile.close();
               return 1;
            }
            
        } else { // if there are at least one command line argument (only take the first one and try to open it as a file)
            try {
                // get file name 
                const std::string fileName {argv[1]};

                infile.open(fileName);
            } catch (...) {
                std::cerr << "Error reading in given file" << std::endl;
                infile.close();
                return 1;
            }
        } 

        // read in file for floor plan
        readFloorPlan(infile, floors, playerSpawns, enemies, dragonHoards, filled);

        // close file
        infile.close();

        TextDisplay td;

        // Ask player to enter one of the specified races or quit
        std::string race, in;

        std::cout << "Welcome to ChamberCrawler3000, prepare to enter the unknown!" << std::endl;
        
        // Extra Features menu
        std::cout << "Enter settings menu? (y or n): ";
        std::cin >> in;

        while (in != "y" && in != "n") {
            std::cerr << "Invalid option" << std::endl;
            std::cout << "Enter here: ";

            if (std::cin.fail()) {
                if (std::cin.eof()) return 0;

                std::cin.clear();
                std::cin.ignore();
            }

            std::cin >> in;
        }

        int seed = -1;
        bool enemyTracking = false;
        int radius = -1;

        if (in == "y") {
            std::cout << "Settings menu"<< std::endl;
            
            // Get seed
            std::cout << "Enter seed (int) or -1 to skip: ";
            std::cin >> seed;
            
            while (std::cin.fail()) {
                if (std::cin.eof()) return 0;

                std::cin.clear();
                std::cin.ignore();
                std::cout << "Invalid int."<< std::endl;
                std::cout << "Enter seed (int) or -1 to skip:";
                std::cin >> seed;
            }

            if (seed != -1) {
                std::cout << "Seed entered: " << std::to_string(seed) << std::endl;
            }


            // Get enemy tracking option
            std::cout << "Enable Enemy Tracking? (y or n): ";

            std::cin >> in;

            while (in != "y" && in != "n") {
                std::cerr << "Invalid option" << std::endl;
                std::cout << "Enter here: ";

                if (std::cin.fail()) {
                    if (std::cin.eof()) return 0;

                    std::cin.clear();
                    std::cin.ignore();
                }
                
                std::cin >> in;
            }

            if (in == "y") {
                enemyTracking = true;
                std::cout << "Enemy Tracking Enabled" << std::endl;
            } else if (in == "n") {
                enemyTracking = false;
                std::cout << "Enemy Tracking Disabled" << std::endl;
            }

            
            // If enemy tracking option activated, get difficulty
            if (enemyTracking) {
                std::cout << "Set Enemy Tracking difficulty (e, m, h): ";
                std::cin >> in;

                while (in != "e" && in != "m" && in != "h") {
                    std::cerr << "Invalid option" << std::endl;
                    std::cout << "Enter here: ";

                    if (std::cin.fail()) {
                        if (std::cin.eof()) return 0;

                        std::cin.clear();
                        std::cin.ignore();
                    }

                    std::cin >> in;
                }

                if (in == "e") {
                    radius = 2;
                    std::cout << "Enemy Tracking Difficulty: Easy (radius 2)" << std::endl;
                } else if (in == "m") {
                    radius = 3;
                    std::cout << "Enemy Tracking Difficulty: Medium (radius 3)" << std::endl;
                } else if (in == "h") {
                    radius = 4;
                    std::cout << "Enemy Tracking Difficulty: Hard (radius 4)" << std::endl;
                }

            }

            std::cout << "End of Settings menu." << std::endl;

        } else if (race == "n") {
            // Continue
            std::cout << "Settings menu bypassed." << std::endl;

        }



        std::cout << "Choose your character: Shade 's' (default), Drow 'd', Vampire 'v', Goblin 'g', Troll 't'" << std::endl;
        std::cout << "Enter here: ";

        std::getline(std::cin, race);
        std::getline(std::cin, race);



        while (race != "" && race != "s" && race != "d" && race != "v" && race != "g" && race != "t") {
            std::cerr << "Invalid race" << std::endl;
            std::cout << "Enter here: ";

            if (std::cin.fail()) {
                if (std::cin.eof()) return 0;

                std::cin.clear();
                std::cin.ignore();
            }

            std::cin >> std::noskipws >> race;
        }

        if (race == "q") {
            return 0; // NOTE: MAYBE HAVE IT SO A NEW GAME STARTS??
        } else if (race == "r") {
            restart = true; // Sort of useless LOL
            continue;
        } else if (race == "") { // default race
            race = "s";
        }

        std::cout << "Race selected: " + race << std::endl;
/*
    int seed = -1;
        bool enemyTracking = false;
        int radius = -1;
*/

        Board b = Board {floors, filled, playerSpawns, enemies, dragonHoards, race, seed, enemyTracking, radius};


        td.drawFloor(std::cout, b, "The adventure begins");

        // clear input stream
        std::cin.clear();
        std::cin.ignore();

        std::string cmd;

        while (true) {
            std::cout << "Enter command: ";
            getline(std::cin, cmd);

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

                if (message == "Dungeon cleared. You win!") {
                    // Game Won by Player
                    winner = 1;

                    break;
                } 

            } else if (static_cast<int>(cmd.length()) == 4 && cmd[0] == 'u') {
                // Use potion in given direction
                message = b.usePotion(cmd.substr(cmd.length() - 2));

            } else if (static_cast<int>(cmd.length()) == 4 && cmd[0] == 'a') {
                // Attack enemy in the given direction
                message = b.attackEnemy(cmd.substr(cmd.length() - 2));

            } else if (cmd == "f") {
                // Freeze enemies
                bool isFrozen = b.toggleFreeze();

                message = "Enemies Frozen: ";
                
                if (isFrozen) {
                    message += "Enabled ";
                 } else {
                    message += "Disabled ";
                 }

            } else if (cmd == "r") {
                // Restart game
                std::cout << "Resetting the game..." << std::endl;
                restart = true;
                winner = 0;

                break;
            } else if (cmd == "q") {
                // Quit Game
                std::cout << "You gave up! Better luck next time!" << std::endl;;

                return 0;
            } else {
                // Invalid Command
                std::cerr << "Invalid Command" << std::endl;
                continue;
            }

            // Move Enemies
            if (message.length () > 30 && message.substr(message.length()-26) == "Proceeding to next floor. ") {

            } else {
                std::string e_message = b.moveEnemies();

                if (e_message.length() == 0) {
                    e_message = "Enemies moved.";
                }

                message +=e_message;
            }
            

            td.drawFloor(std::cout, b, message);

            if (message.length() > 12 && message.substr(message.length()-10) == "Game Over!") {
                // Player killed and lost
                winner = 2;
                break;
            }

        } // End of Command Interpreter

        if (winner == 1) {
            // Print winner stuff
            
            std::cout << "Congratulations! You won!" << std::endl;
        } else if (winner == 2) {
            // Print loser stuff
            
            std::cout << "You have been defeated!" << std::endl;

        }

        if (winner != 0) {
            // Ask Player if they want to play again
            std::cout << "Play again? y or n" << std::endl;
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
