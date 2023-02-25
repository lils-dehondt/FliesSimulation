#ifndef EGG_H
#define EGG_H

#include <iostream>

#include "Arena3D.h"
#include "Fly3D.h"


class Simulation;

class Egg {


    // Egg laid during simulation
private:


    // Parents
    Fly3D *mother;
    Fly3D *father;

    double max_ls;
    // Learning rate
    double lr;
    double fecundity;
    double speed;



public:
    //Constructor
    /**
     * @brief Constructs a new Egg object
     *
     * @param mother
     * @param father
     */
    Egg(Fly3D *mother, Fly3D *father);




    /**
     * @brief Constructs a new Egg object
     * @param max_ls
     * @param lr
     * @param fecundity
     * @param speed
     */
    Egg(const double &max_ls = 0.8, const double &lr = 0.4, const double &fecundity = 5, const double &speed = 1.0);

    //Getters and Setters

    /**
     * @brief Getter for maximum learning strength
     * @return maximum learning strength
     */
    double GetMaximumLearningStrength() const;

    /**
    * @brief Getter for learning rate
    * @return maximum learning learning rate
    */
    double GetLearningRate() const;

    /**
    * @brief Getter for fecundity
    * @return fecundity
    */
    double GetFecundity() const;

    /**
    * @brief Getter for speed
    * @return speed
    */
    double GetSpeed() const;


    /**
    * @brief Getter for maximum learning strength
    * @return maximum learning strength
    */
    void SetMaximumLearningStrength(double &max_ls);

    /**
    * @brief Setter for learning rate
    * @return learning rate
    */
    void SetLearningRate(const double &lr);

    /**
    * @brief Setter for fecundity
    * @return fecundity
    */
    void SetFecundity(const double &fecundity);

    /**
    * @brief Setter for speed
    * @return speed
    */
    void SetSpeed(const double &speed);

    /**
   * @brief Setter for genotype
   * @return genotype
   */

    /**
    * @brief Getter for maximum learning strength
    * @return maximum learning strength
    */
    Fly3D *GetMother();

};

#endif