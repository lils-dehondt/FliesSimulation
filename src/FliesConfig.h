#ifndef FLIESCONFIG_H
#define FLIESCONFIG_H

#include <iostream>

#include "Arena3D.h"
#include "Egg.h"


class Simulation;

class FliesConfig {


private:

    std::vector<Egg *> eggs;
    int nb_females;


public:
    /**
     * @brief Constructs a new FliesCOnfig object
     * @param eggs
     * @param nb_females
     */
    FliesConfig(std::vector<Egg *> eggs, int &nb_females);

    /**
     * @brief Getter for number of eggs
     * @return
     */
    int GetNbEggs();

    /**
     * @brief Getter for number of females
     * @return
     */
    int GetNbFemales();


    /**
     * @brief Creates new flies file
     */
    void CreateFile();


};


#endif