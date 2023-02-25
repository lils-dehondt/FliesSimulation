#ifndef SIMULATION2D_H
#define SIMULATION2D_H

#include <iostream>
#include <fstream>
#include <sstream>


#include "Fly3D.h"
#include "Egg.h"
#include "Arena3D.h"

class Simulation {

public:

    //Constructor
    /**
     * @brief Construct a new Simulation object
     *
     * @param c center position
     * @param r radius
     * @param nb_walls number of walls/rooms
     * @param nb_ent number of entrances in each wall
     * @param nb_flies number of flies in the arena
     * @param starting_room starting room of the flies
     * @param maxtime maximum running time
     * @param dt timestep
     * @param datarec indicates if simulation records data
     */
    Simulation(const Vector3d<double> &c, const double &r, int nb_walls = 0, const int &nb_ent = 2,
               const int &nb_flies = 0, const int &starting_room = 0, const double &maxtime = 1000.0,
               const double &dt = 0.1, const bool &datarec = 0, const bool &v = false);

    /**
     * @brief Construct a new Simulation object
     *
     * @param c1 x center coordinate
     * @param c2 y center coordinate
     * @param r radius
     * @param nb_walls number of walls/rooms
     * @param nb_ent number of entrances in each wall
     * @param nb_flies number of flies in the arena
     * @param starting_room starting room of the flies
     * @param maxtime maximum running time
     * @param dt timestep
     * @param datarec indicates if simulation records data
     */
    Simulation(const double &c1, const double &c2, const double &r, int nb_walls = 0, const int &nb_ent = 2,
               const int &nb_flies = 0, const int &starting_room = 0, const double &maxtime = 1000.0,
               const double &dt = 0.1, const bool &datarec = 0, const bool &v = false);

    /**
     * @brief Construct a new Simulation object
     *
     * @param arena arena object
     * @param nb_flies number of flies in the arena
     * @param starting_room starting room of the flies
     * @param maxtime maximum running time
     * @param dt timestep
     * @param datarec indicates if simulation records data
     */
    Simulation(Arena3D *arena, const int &nb_flies = 0, const int &starting_room = 0, const double &maxtime = 1000.0,
               const double &dt = 0.1, const bool &datarec = 0, const int &record_step = 1, const int &rep_time = 1000, const bool &v = false,
               const bool &draw = false);

    //Destructor
    /**
     * @brief Destroy the Simulation 2D object
     * Specially all associated pointers
     */
    ~Simulation();

    /**
     * @brief Get the Arena Center
     *
     * @return Vector2d<double> center of arena
     */
    Vector3d<double> GetArenaCenter() const;

    /**
     * @brief Get the Arena Radius
     *
     * @return double arena radius
     */
    double GetArenaRadius() const;

    /**
     * @brief Update one step of the simulation
     *
     * @param dt timestep
     */
    void Update(double dt);

    /**
     * @brief Get arena of simulation
     *
     * @return Arena2D*
     */
    Arena3D *GetArena();

    /**
     * @brief Get the fly vector
     *
     * @return std::vector<Fly3D* >
     */
    std::vector<Fly3D *> GetFlies() const;

    /**
     * @brief Get time of simulation
     *
     * @return double
     */
    double GetTime() const;

    /**
     * @brief Get timestep of simulation
     *
     * @return double
     */
    double Getdt() const;

    /**
     * @brief Get maximum running time of simulation
     *
     * @return double
     */
    double GetMaxTime() const;

    /**
     * @brief Get number of flies
     *
     * @return number of flies
     */
    int GetNbFlies();

    /**
     * @brief Get number of females
     *
     * @return number of females
     */
    int GetNbFemales();

    /**
     * @brief Check if simulation is running
     *
     * @return true simulation is running
     * @return false simulation has ended
     */
    bool IsRunning() const;

    /**
     * @brief Adds an egg to the pool of eggs
     *
     * @param egg
     */
    void AddEgg(Egg *egg);

    /**
     * @brief Adds several eggs to the pool of eggs
     *
     * @param eggs
     */
    void AddEggs(std::vector<Egg *> eggs);

    /**
     * @brief Gets a random male fly from the simulation
     *
     * @return a random male fly from the simulation
     */
    Fly3D *GetRandomFather();

    /**
     * @brief Add eggs to egg pool for given parents
     *
     * @param mother
     * @param father
     */
    void LayEggs(Fly3D *mother, Fly3D *father);

    /**
     * Get the eggs laid in the simulation
     *
     * @return eggs laid in the simulation
     */
    std::vector<Egg *> GetEggs();

    /**
     * @brief Creates all eggs that have been laid during the simulation and creates a vector
     */
    void FillEggsPool();

    /**
     * @brief Generates summary file
     *
     * @param number
     */
    void GetSummaryFile(const std::string &number);



private:

    Arena3D *arena;
    std::vector<Fly3D *> flies;
    std::vector<Egg *> eggs;
    int nb_flies;
    int nb_females;
    double maxtime;
    double time;
    double dt;
    bool dataRec;
    bool draw;
    int record_step;
    int record_step_counter;
    int rep_time;
    std::ofstream Simfile;
    std::ofstream Configfile;
    std::ofstream Summaryfile;
    std::ifstream Fliesfile;
    bool VERBOSE;


    /**
         * @brief print advancement of simulation
         * 
         */
    void Verbose();

    /**
     * @brief Open and start datafiles for data recording and config file
     *
     */
    void InitializeFile();

    /**
     * @brief Open and write simulation configuration
     *
     * @param number number in filename
     */
    void WriteConfig(const std::string &number);

    /**
     * @brief Close already open file
     *
     */
    void CloseFile();


    void WriteConfigAndSummary(const std::string &number);

    void GetSummaryFile();

};


#endif