#include <iostream>
#include <random>
// #include <RVO.h>
// #include "../lib/RVO2/src/RVO.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <stdlib.h>

#include <fstream>
#include <sys/stat.h>

#include "FliesConfig.h"
#include "Simulation.h"
#include "Utility.h"


FliesConfig::FliesConfig(std::vector<Egg *> eggs, int &nb_females) : eggs(eggs), nb_females(nb_females) {}

int FliesConfig::GetNbEggs() { return this->eggs.size(); }

int FliesConfig::GetNbFemales() { return this->nb_females; }


void FliesConfig::CreateFile() {
    std::ofstream Fliesfile;

    std::string directory("FliesConfig/");
    std::string filename("Flies_");
    std::string number("000");
    std::string ext(".csv");

    // Check if datafile already exists
    for (int i = 0; i < 1000; i++) {
        // Initialize file number
        if (i < 10) { number = "00" + std::to_string(i); }
        if (i >= 10 && i < 100) { number = "0" + std::to_string(i); }
        if (i >= 100) { number = std::to_string(i); }
        if (!fileExists(directory + filename + number + ext)) {
            break;
        }
    }



    // Initialize datafile
    Fliesfile.open(directory + filename + number + ext);
    //Fliesfile.open(directory + filename + ext);
    Fliesfile << "id" << "," << "female" << "," << "maximum learning strenth" << "," << "learning rate" << ","
              << "fecundity" << "," << "speed";



    for (int i = 0; i < nb_females; i++) {
        Fliesfile << "\n";
        Fliesfile << i << "," << 1 << "," << eggs[i]->GetMaximumLearningStrength() << "," << eggs[i]->GetLearningRate()
                  << "," << (int) round(eggs[i]->GetFecundity()) << "," << eggs[i]->GetSpeed();
    }


    for (int i = nb_females; i < eggs.size(); i++) {
        Fliesfile << "\n";
        Fliesfile << i << "," << 0 << "," << eggs[i]->GetMaximumLearningStrength() << "," << eggs[i]->GetLearningRate()
                  << "," << (int) round(eggs[i]->GetFecundity()) << "," << eggs[i]->GetSpeed();

    }


    if (Fliesfile.is_open()) {
        Fliesfile.close();
    }

    std::cout << "The FliesConfig file was initiated.\n";
}
