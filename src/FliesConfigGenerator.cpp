#include <iostream>
#include <vector>
#include <stdlib.h>


using namespace std;

#include "Egg.h"
#include "FliesConfig.h"

int main(int argc, char **argv) {
    //default learning rate
    double def_lr = 0.1;
    double def_max_ls = 0.7;
    double def_speed = 1.0;
    int def_fecundity = 5;
    int nb_flies = 1000;
    int nb_females = 500;
    bool generate = true;


    for (int i = 0; i < argc; ++i) {
        // Help command
        if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
            std::cout << "\n\n";
            std::cout << "-h , --help             Help command, shows and describes all simulation paramters";
            std::cout << "\n";
            std::cout << "-f , --flies            Number of flies in simulation, >0";
            std::cout << "\n";
            std::cout << "-lr , --learning_rate            default leaning rate between 0 and 1";
            std::cout << "\n";
            std::cout << "-maxls , --maximum_learning_strength            maximum learning strength between 0 and 1";
            std::cout << "\n";
            std::cout << "-speed , --speed            maximum learning strength between 0 and 1";
            std::cout << "\n";
            std::cout << "-fec , --fecundity            number of eggs laid at a time";
            std::cout << "\n";
            std::cout << "-fem , --females           Number of females. Default is half the number of flies.";
            std::cout << "\n";



            generate = false;

        }


        if (std::string(argv[i]) == "-f" || std::string(argv[i]) == "--flies") {
            if (stoi(argv[i + 1]) > 0) {
                nb_flies = stoi(argv[i + 1]);
                nb_females = nb_flies / 2;
            }
        }


        if (std::string(argv[i]) == "-lr" || std::string(argv[i]) == "--learning_rate") {
            if (stod(argv[i + 1]) > 0.0 and stod(argv[i + 1]) <= 1.0) {
                def_lr = stod(argv[i + 1]);
            }
        }

        if (std::string(argv[i]) == "-speed" || std::string(argv[i]) == "--speed") {
            if (stod(argv[i + 1]) > 0.0 and stod(argv[i + 1]) <= 1.0) {
                def_speed = stod(argv[i + 1]);
            }
        }

        if (std::string(argv[i]) == "-maxls" || std::string(argv[i]) == "--fecundity") {
            if (stoi(argv[i + 1]) > 0) {
                def_fecundity = stoi(argv[i + 1]);
            }
        }

        if (std::string(argv[i]) == "-fec" || std::string(argv[i]) == "--maximum_learning_strength") {
            if (stod(argv[i + 1]) > 0.0 and stod(argv[i + 1]) <= 1.0) {
                def_max_ls = stod(argv[i + 1]);
            }
        }

        if (std::string(argv[i]) == "-fem" || std::string(argv[i]) == "--females") {
            if (stoi(argv[i + 1]) > 0) {
                nb_females = stoi(argv[i + 1]);
            }
        }


    }
    if (generate) {

        std::vector<Egg *> eggs;

        for (
                int i = 0;
                i < nb_flies;
                i++) {
            eggs.push_back(new
                                   Egg(def_max_ls, def_lr, def_fecundity, def_speed
            ));
        }

        std::vector<std::string> variantsIds;



        if (nb_females >= nb_flies) {
            nb_females = nb_flies / 2;
            std::cout
                    << "There are more (or as much) female flies than the total number of flies!\n The number of females was reduced to "
                    << nb_females << " ,half the number of flies. Please consider changing your input parameters.";

        }


        FliesConfig *fliesConfig = new FliesConfig(eggs, nb_females);


        fliesConfig->CreateFile();


        std::cout << "Generated flies config file with following values: \n" << "- Number of flies: " << nb_flies
                  << "\n"
                  << "- Default learning rate: " << def_lr << "\n" << "- Default fecundity: " << def_fecundity
                  << "\n";

    }
}



