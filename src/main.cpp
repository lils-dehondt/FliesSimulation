#include <iostream>
#include <vector>
#include <chrono>
#include <stdlib.h>
#include <algorithm>

#include "Wall.h"
#include "Arena3D.h"
#include "Simulation.h"
#include "Egg.h"
#include "FliesConfig.h"


using namespace std;
using namespace std::chrono;


int main(int argc, char **argv) {

    // Simulation variables 
    bool start_sim = true;
    unsigned int number_sim = 1;
    unsigned int nb_flies = 6;
    unsigned int nb_rooms = 4;
    unsigned int nb_ent = 4;
    int s_room = 0;
    int f_room = s_room + 1;
    double maxtime = 5000.0;
    double dt = 0.1;
    double food_shift = 500.0;
    double wall_width = 10.0;
    bool nfood = 0;
    bool dataR = 1;
    bool v = 0;
    int rep_time = 1000;
    int record_step = 1;
    bool verbose = 0;

    for (int i = 0; i < argc; ++i) {
        // Help command
        if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
            start_sim = false;
            std::cout << "\n\n";
            std::cout << "-h , --help             Help command, shows and describes all simulation parameters";
            std::cout << "\n";
            std::cout << "-n , --number           Number of simulation, >0";
            std::cout << "\n";
            std::cout << "-f , --flies            Number of flies in simulation, >0";
            std::cout << "\n";
            std::cout << "-r , --rooms            Number of rooms in simulation, >=0";
            std::cout << "\n";
            std::cout << "-sr , --start_room      Starting room for flies, >=0";
            std::cout << "\n";
            std::cout
                    << "-e , --entrances        Number of entrances on each wall, 1st entrance is real, next ones are fake, >0";
            std::cout << "\n";
            std::cout << "-t , --timestep         Timestep of simulation, >0";
            std::cout << "\n";
            std::cout << "-T , --time             Duration of simulation, >0";
            std::cout << "\n";
            std::cout << "-fs , --food_shifting   Food shifting time, >0";
            std::cout << "\n";
            std::cout << "-d , --data             Data recording, 1 to record data,  0 not to";
            std::cout << "\n";
            std::cout << "-rs , --record_step     Number of data step between data recording, >0, default is 1";
            std::cout << "\n";
            std::cout
                    << "-rt , --rep_time          Time necessary for a fly to lay eggs again. defaut: 2 x food_shifting";
            std::cout << "\n\n";

        }
        // Number of simulation
        if (std::string(argv[i]) == "-n" || std::string(argv[i]) == "--number") {
            if (stoi(argv[i + 1]) > 0) {
                number_sim = stoi(argv[i + 1]);
            }
        }
        // Number of flies
        if (std::string(argv[i]) == "-f" || std::string(argv[i]) == "--flies") {
            if (stoi(argv[i + 1]) > 0) {
                nb_flies = stoi(argv[i + 1]);
            }
        }
        // Number of rooms
        if (std::string(argv[i]) == "-r" || std::string(argv[i]) == "--rooms") {
            if (stoi(argv[i + 1]) > 0) {
                nb_rooms = stoi(argv[i + 1]);
            }
        }
        // Starting room
        if (std::string(argv[i]) == "-sr" || std::string(argv[i]) == "--start_room") {
            if (stoi(argv[i + 1]) >= 0 && stoi(argv[i + 1]) < nb_rooms) {
                s_room = stoi(argv[i + 1]);
                f_room = s_room + 1;
            }
        }
        // Number of entrances
        if (std::string(argv[i]) == "-e" || std::string(argv[i]) == "--entrances") {
            if (stoi(argv[i + 1]) > 0) {
                nb_ent = stoi(argv[i + 1]);
            }
        }
        // Timestep
        if (std::string(argv[i]) == "-t" || std::string(argv[i]) == "--timestep") {
            if (stod(argv[i + 1]) > 0.0) {
                dt = stod(argv[i + 1]);
            }
        }
        // Time of simulation
        if (std::string(argv[i]) == "-T" || std::string(argv[i]) == "--time") {
            if (stod(argv[i + 1]) > 0.0) {
                maxtime = stod(argv[i + 1]);
            }
        }
        // Food shifting time
        if (std::string(argv[i]) == "-fs" || std::string(argv[i]) == "--food_shifting") {
            if (stod(argv[i + 1]) > 0.0 && stod(argv[i + 1]) < maxtime) {
                food_shift = stod(argv[i + 1]);
                rep_time = (int) food_shift * 2;
            }
        }
        // Food/No food
        if (std::string(argv[i]) == "-nf" || std::string(argv[i]) == "--no_food") {
            if (stoi(argv[i + 1]) == 0) { nfood = 0; }
            if (stoi(argv[i + 1]) == 1) { nfood = 1; }
        }
        // Data recording
        if (std::string(argv[i]) == "-d" || std::string(argv[i]) == "--data") {
            if (stoi(argv[i + 1]) == 0) { dataR = 0; }
            if (stoi(argv[i + 1]) == 1) { dataR = 1; }
        }
        // Record step
        if (std::string(argv[i]) == "-rs" || std::string(argv[i]) == "--record_step") {
            if (stoi(argv[i + 1]) > 0) {
                record_step = stoi(argv[i + 1]);
            }
        }
        // Force run
        if (std::string(argv[i]) == "-R" || std::string(argv[i]) == "--run") {
            start_sim = true;
        }

        // Reproduction timer
        if (std::string(argv[i]) == "-rt" || std::string(argv[i]) == "--rep_time") {
            rep_time = stoi(argv[i + 1]);
        }




    }
    if (start_sim) {
        for (int i = 0; i < number_sim; i++) {


            // Create an arena
            Arena3D arena(Vector3d<double>(500, 500, 250), 500, 500, nb_rooms, nb_ent, wall_width);
            if (f_room >= arena.GetNbWalls()) { f_room = 0; }

            if (!nfood) {
                Food food(&arena, f_room, food_shift);
                arena.SetFood(&food);
            }
            Simulation Sim2D(&arena, nb_flies, s_room, maxtime, dt, dataR, record_step, rep_time, verbose);


            auto start = high_resolution_clock::now();

            std::cout << " ----Simulation " << i << " start---- \n";
            // Line to limit system clear command in Simualtion3D::Verbose()
            if(verbose) std::cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            for (int i = 0; i < maxtime / dt; i++) {

                Sim2D.Update(dt);
            }

            Sim2D.FillEggsPool();
            std::vector<Egg *> pool_eggs = Sim2D.GetEggs();

            nb_flies = Sim2D.GetNbFlies();

            int nb_females = Sim2D.GetNbFemales();


            std::random_shuffle(pool_eggs.begin(), pool_eggs.end());


            std::cout << "Simulation ran with " << nb_flies << " flies, and " << pool_eggs.size()
                      << " eggs were laid.\n";
            if (pool_eggs.size() < nb_flies) {
                if (pool_eggs.size() < nb_flies / 2) {
                    std::cout
                            << "The number of eggs is less than half the required number of flies. \nSimulation stopping. \nPlease consider changing your input parameters to increase the number of eggs laid!\n";
                    return 0;
                } else {
                    nb_flies = pool_eggs.size();
                    std::cout
                            << "The number of eggs is less than the required number of flies. \nSimulation will continue with "
                            << pool_eggs.size()
                            << "flies . \nPlease consider changing your input parameters to increase the number of eggs laid!\n";

                }
            }

            std::vector<Egg *> chosen_eggs;
            for (int j = 0; j < nb_flies; j++) {
                chosen_eggs.push_back(pool_eggs[i]);
            }


            if (i != number_sim - 1) {
                FliesConfig *fliesConfig = new FliesConfig(chosen_eggs, nb_females);
                fliesConfig->CreateFile();
            }


            std::cout << " ----Simulation " << i << " end----  \n";
            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(stop - start);

            std::cout << " Simulation duration : " << duration.count() / pow(10.0, 6) << " s \n";

        }
    }



    return 0;
};

