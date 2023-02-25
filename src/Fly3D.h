#ifndef FLY2D_H
#define FLY2D_H

#include <iostream>

#include "Vector3D.h"
#include "Arena3D.h"

class Simulation;

class Fly3D {

    friend class Simulation2D;

    // 2D agent navigating inside the arena
private:

    bool female;
    int room;
    // x, y position
    Vector3d<double> r;
    // velocity of agent
    Vector3d<double> v;
    // Velocity of preference
    Vector3d<double> v_pref;
    // Acceleration
    Vector3d<double> a;
    // orientation of agent
    double angle;
    //speed
    double speed;
    // Learning strength
    double ls;
    // Maximum learning strength
    double max_ls;
    // Learning rate
    double lr;
    // Cognition range
    double rcog;
    // index of agent in the simulation
    int index;
    // Time on food
    double timeonfood;
    // Access to arena
    Arena3D *arena;
    // Acces to simulation
    Simulation *simulation;
    // Forces applioed on agent, from ref paper
    Vector3d<double> Fint, Fres, Ffric, Fnoise;
    // Point of aim
    Vector3d<double> aim;
    //aim timer to reset aim if the fly can't reach
    int aimTimer;
    //number of successes
    int nb_successes;
    // Number of time a fly lays eggs
    int nb_egg_layings;
    //fecundity
    int fecundity;
    //Time necessary for a fly to lay eggs again
    int rep_time;
    //Timer for reproduction
    int rep_timer;



public:
    /**
     * @brief Construct a new Fly3D agent
     * 
     * @param position Vector3d starting position
     * @param index index of agent in list
     * @param arena arena in which agent is in
     */
    Fly3D(const Vector3d<double> &position, const int &index, Arena3D *arena = nullptr);

    /**
     * @brief Construct a new Fly3D
     * 
     * @param x x position
     * @param y y position
     * * @param z z position
     * @param index index of agent in list
     * @param arena arena in which agent is in
     */
    Fly3D(const bool &female, const double &x, const double &y, const double &z, const int &index, Arena3D *arena = nullptr);


    /**
 * @brief Construct a new Fly3D
 *
 * @param room starting room, center of the room
 * @param index index of agent in list
 * @param arena arena in which agent is in
  * @param lr learning rate of agent

 */
    Fly3D(const bool &female, const int &room, const int &index, Arena3D *arena = nullptr, const double &lr = 0.0,
          const double &max_ls = 0.0, const int &fecundity = 5, const int &rep_time = 2000, const double &speed = 1.0,
          const std::vector<int> &genotype = {});


    /**
     * @brief Get gender of agent (true if female)
     *
     * @return bool female
     */
    bool GetFemale() const;


    /**
     * @brief Get room of agent
     * 
     * @return int room
     */
    int GetRoom() const;

    /**
     * @brief Get the agent's position
     * 
     * @return Vector3D<double> position
     */
    Vector3d<double> GetPosition() const;

    /**
     * @brief Get the agent's cognition
     *
     * @return double cognition
     */
    double GetCognition() const;

    /**
     * @brief Get the agent's learning strength
     *
     * @return double leaning strength
     */
    double GetLearningStrength() const;

    /**
     * @brief Get the agent's maximum learning strength
     *
     * @return double leaning strength
     */
    double GetMaximumLearningStrength() const;

    /**
     * @brief Get the agent's learning rate
     *
     * @return double leaning rate
     */
    double GetLearningRate() const;

    /**
     * @brief Get the agent's velocity
     * 
     * @return Vector3d<double> velocity vector
     */
    Vector3d<double> GetVelocity() const;

    /**
     * @brief Get agent's prefered velocity
     * 
     * @return Vector3d<double> preferred velocity
     */
    Vector3d<double> GetVelocitypref() const;

    /**
     * @brief Get repsonse force, response to environment 
     * 
     * @return Vector3d<double> 
     */
    Vector3d<double> GetFres() const;

    /**
     * @brief Get agent's aim
     * 
     * @return Vector3d<double> aim
     */
    Vector3d<double> GetAim() const;

    /**
     * @brief Get agent's speed
     *
     * @return double speed
     */
    double GetSpeed() const;

    /**
     * @brief Get the Angle object
     * 
     * @return double 
     */
    double GetAngle() const;

    /**
     * @brief Get the arena in which the fly
     * 
     * @return Arena3D*
     */
    Arena3D *GetArena();

    /**
     * @brief Get the time spent on food by the agent
     * When the agent is in the same room as the food, time on food increases
     * 
     * @return double timeonfood
     */
    double GetTimeOnFood() const;

    /**
 * @brief Getter for genotype
 * @return genotype
 */
    std::vector<int> GetGenotype() const;

    /**
     * @brief Get number of successes
     *
     * @return the number of successes
     */
    int GetNbSuccesses();

    /**
     * @brief Get number of time a fly has laid eggs
     *
     * @return std::cout << "\n"
     */
    int GetNbEggLayings();

    /**
     * @brief Get fecundity
     *
     * @return fecundity
     */
    int GetFecundity();

    /**
     * @brief Set aiming point
     * 
     * @param point point of aim
     */
    void SetAim(const Vector3d<double> &point);

    /**
     * @brief Set aiming point
     * 
     * @param x coordinate
     * @param y coordinate
     */
    void SetAim(const double &x, const double &y, const double &z);

    /**
     * @brief Determines if a fly has reached food by going through an entrance
     *
     * @param x coordinate
     * @param y coordinate
     */
    bool Success();

    /**
     * @brief Update agent, updates each component of the agent
     * 
     * @param dt timestep
     */
    void Update(const double &dt);

    /**
     * @brief Update agent's angle
     * 
     */
    void UpdateAngle();

    /**
     * @brief Update forces
     * 
     */
    void UpdateForces();

    /**
     * @brief Updates response force
     * 
     */
    void UpdateFres();

    /**
     * @brief Updates learning strength
     *
     */
    void UpdateLearningStrength();

    /**
     * @brief Updates interaction force
     * 
     */
    void UpdateFint();

    /**
     * @brief Updates friction force 
     * 
     */
    void UpdateFfric();

    /**
     * @brief Updates noise force
     * 
     */
    void UpdateFnoise();


    /**
     * @brief Updates aim timer
     *
     */
    void UpdateAimTimer();

    /**
    * @brief Updates number of successes
    *
    */
    void UpdateNbSuccesses();


    /**
     * @brief Updates room index 
     * 
     */
    void UpdateRoom();

    /**
     * @brief Updates preferred velocity
     * 
     * @param dt timestep
     */
    void UpdateVpref(const double &dt);

    /**
     * @brief Updates velocity
     * 
     * @param dt timestep 
     */
    void UpdateV(const double &dt);

    /**
     * @brief Updates position
     * 
     * @param dt timestep
     */
    void UpdatePosition(const double &dt);

    /**
     * @brief Updates time on food
     * 
     * @param dt timestep
     */
    void UpdateTimeOmFood(const double &dt);

    /**
     * @brief Generate new aiming point for the agent
     * 
     */
    void GenerateNewAim();

    /**
     * @brief Updates aiming point
     * 
     * @param dt timestep 
     */
    void UpdateAim(const double &dt);

    /**
     * @brief Updates the reproduction timer
     */
    void UpdateRepTimer();

};

#endif