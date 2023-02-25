#include "Fly3D.h"
#include "Arena3D.h"
#include "Simulation.h"
#include "FliesConfig.h"
#include "Utility.h"

#include <cmath>

#include <iostream>
#include <string>
#include <random>


Simulation::Simulation(Arena3D *arena, const int &nb_flies, const int &starting_room, const double &maxtime,
                       const double &dt, const bool &datarec, const int &record_step, const int &rep_time,
                       const bool &v, const bool &draw)
        : maxtime(maxtime), time(0.0), dt(dt), dataRec(datarec), record_step(record_step), record_step_counter(0),
          VERBOSE(v), draw(draw), nb_flies(nb_flies), rep_time(rep_time) {
    this->arena = arena;

    //-----------

    std::string fliesFile = "FliesConfig/Flies_000.csv";

    // filename
    std::string directory("FliesConfig/");
    std::string filename("Flies_");
    std::string number("000");
    std::string ext(".csv");

    for (int i = 0; i < 1000; i++) {
        // Initialize file number
        if (i < 10) { number = "00" + std::to_string(i); }
        if (i >= 10 && i < 100) { number = "0" + std::to_string(i); }
        if (i >= 100) { number = std::to_string(i); }
        // Check existence of datafile
        if (!fileExists(directory + filename + number + ext)) {
            break;
        } else {
            fliesFile = directory + filename + number + ext;
        }
    }

    std::string skipline, i, female, lr, max_ls, fecundity, speed, genotype = "";
    if (!fileExists(fliesFile) and !draw) {
        std::vector<Egg *> eggs;
        int nb_females = nb_flies / 2;
        for (int i = 0; i < nb_flies; i++) {
            eggs.push_back(new Egg());
        };
        if (datarec) {
            FliesConfig *fliesConfig = new FliesConfig(eggs, nb_females);
            fliesConfig->CreateFile();
        }

    }


    if (fileExists(fliesFile) and !draw) {
        Fliesfile.open(fliesFile);
        getline(Fliesfile, skipline);

        nb_females = 0;

        while (Fliesfile.good()) {
            getline(Fliesfile, i, ',');
            getline(Fliesfile, female, ',');
            getline(Fliesfile, max_ls, ',');
            getline(Fliesfile, lr, ',');
            getline(Fliesfile, fecundity, ',');


            getline(Fliesfile, speed);


            bool boolFemale = (bool) (stoi(female));
            if (boolFemale) {
                nb_females += 1;
            }

            this->flies.push_back(new Fly3D(boolFemale, starting_room, stoi(i), this->arena, stod(lr), stod(max_ls),
                                            stoi(fecundity), rep_time, stod(speed)));

        }


        this->nb_flies = stoi(i) + 1;
        Fliesfile.close();
    } else {
        int midpoint = nb_flies / 2;
        for (int i = 0; i < midpoint; i++) {
            this->flies.push_back(new Fly3D(1.0, starting_room, i, this->arena, 0.1));
        }
        for (int i = midpoint; i < nb_flies; i++) {
            this->flies.push_back(new Fly3D(0.0, starting_room, i, this->arena, 0.1));
        }

    }


    if (dataRec) { InitializeFile(); }

}

Simulation::~Simulation() {
    std::cout << "Total Running Time : " << time << "\n";
    for (int i = 0; i < this->flies.size(); i++) delete (this->flies[i]);

    if (dataRec) {
        //this->GetSummaryFile();
        this->CloseFile();
    }


}

Vector3d<double> Simulation::GetArenaCenter() const { return (*arena).GetCenter(); }

double Simulation::GetArenaRadius() const { return (*arena).GetRadius(); }

void Simulation::Update(double dt) {


    if (time < maxtime) {
        // Flies update
        for (int i = 0; i < this->flies.size(); i++) {

            flies[i]->Update(dt);

        }
        // Food update
        if (arena->GetFood() != nullptr) {
            arena->GetFood()->Update(dt);
        }

        // Data recording
        if (dataRec and record_step_counter == 0) {
            // Values of variables
            Simfile << time << ", " << this->arena->GetFood()->GetRoom() << ", ";
            for (int i = 0; i < this->GetFlies().size(); i++) {
                Simfile << this->flies[i]->GetPosition().x << ", " << this->flies[i]->GetPosition().y << ", "
                        << this->flies[i]->GetRoom() << ", " << this->flies[i]->GetTimeOnFood() << ", "
                        << this->flies[i]->GetNbSuccesses();
                if (i < this->flies.size() - 1) { Simfile << ", "; }
            }
            Simfile << "\n";

            record_step_counter = record_step;
        }
        record_step_counter -= 1;

        //if (VERBOSE) Verbose();

        time += dt;
    }


}

void Simulation::Verbose() {


    std::cout << "%";
    for (int i = 0; i < 10; i++) {
        if (i <= floor(time / maxtime * 10)) {
            std::cout << "=";
        }
        if (i > floor(time / maxtime * 10)) {
            std::cout << " ";
        }
    }
    std::cout << "%   " << ceil(time / maxtime * 100.0) << " %";

    std::cout << "\n\n";
}


Arena3D *Simulation::GetArena() { return this->arena; }


std::vector<Fly3D *> Simulation::GetFlies() const { return this->flies; }

double Simulation::GetTime() const { return time; }

double Simulation::Getdt() const { return dt; }

double Simulation::GetMaxTime() const { return maxtime; }

int Simulation::GetNbFlies() { return this->nb_flies; }

int Simulation::GetNbFemales() { return this->nb_females; }

bool Simulation::IsRunning() const { return time < maxtime; }

void Simulation::AddEgg(Egg *egg) { this->eggs.push_back(egg); }

void Simulation::AddEggs(std::vector<Egg *> eggs) {
    for (int i = 0; i < eggs.size(); i++) {
        AddEgg(eggs[i]);
    }
}

Fly3D *Simulation::GetRandomFather() {
    bool male = false;
    Fly3D *fly;
    while (!male) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, flies.size() - 1);
        fly = flies[distr(gen)];
        male = !(fly->GetFemale());
    }
    return fly;
}

void Simulation::LayEggs(Fly3D *mother, Fly3D *father) {
    for (int i = 0; i < mother->GetFecundity(); i++) {

        AddEgg(new Egg(mother, father));

    }

}

void Simulation::FillEggsPool() {
    for (int i = 0; i < this->GetFlies().size(); i++) {
        if (flies[i]->GetFemale() && flies[i]->GetNbEggLayings() != 0) {
            Fly3D *father = GetRandomFather();
            for (int j = 0; j < flies[i]->GetNbEggLayings(); j++) {
                LayEggs(flies[i], father);
            }
        }
    }
}

std::vector<Egg *> Simulation::GetEggs() { return this->eggs; }

void Simulation::InitializeFile() {
    // filename
    std::string directory("SimData/");
    std::string filename("SimData_");
    std::string number("000");
    std::string ext(".csv");

    // Check if datafile already exists
    for (int i = 0; i < 1000; i++) {
        // Initialize file number
        if (i < 10) { number = "00" + std::to_string(i); }
        if (i >= 10 && i < 100) { number = "0" + std::to_string(i); }
        if (i >= 100) { number = std::to_string(i); }
        // Check existence of datafile
        if (!fileExists(directory + filename + number + ext)) {
            break;
        }
    }

    // Initialize datafile
    Simfile.open(directory + filename + number + ext);
    Simfile << "time, food room, ";
    for (int i = 0; i < this->flies.size(); i++) {
        std::string nb = std::to_string(i);
        Simfile << "fly" << i << ".x " << ", " << "fly" << i << ".y" << ", " << "fly" << i << ".room" << ", " << "fly"
                << i << ".TOF" << ", " << "fly" << i << ".successes";
        if (i < this->flies.size() - 1) { Simfile << ", "; }
    }
    Simfile << "\n";

    WriteConfigAndSummary(number);
}

void Simulation::WriteConfigAndSummary(const std::string &number) {
    // filename 
    std::string config_directory("SimConfig/");
    std::string config_filename("SimConfig_");
    std::string config_ext(".csv");

    // Initialize datafile
    Configfile.open(config_directory + config_filename + number + config_ext);
    Configfile << "time, timestep, flies, rooms, entrances, radius, center.x, center.y, food, food shifting \n";
    Configfile << maxtime << ", " << dt << ", " << flies.size();
    if (arena != nullptr) {
        Configfile << ", " << arena->GetNbWalls() << ", " << arena->GetWalls()[0].GetNbEnts() << ", "
                   << GetArenaRadius() << ", " << GetArenaCenter().x << ", " << GetArenaCenter().y;
    } else { Configfile << ", " << 0 << ", " << 0 << ", " << 0 << ", " << 0 << ", " << 0; }

    if (arena != nullptr && arena->GetFood() != nullptr) {
        Configfile << ", " << "yes" << ", " << arena->GetFood()->GetMaxLifetime() << "\n";
    } else { Configfile << ", " << "no" << ", " << 0; }


    // filename
    std::string sum_directory("SimSummary/");
    std::string sum_filename("SimSummary_");
    std::string sum_ext(".txt");

    // Initialize datafile
    //Summaryfile.open(sum_directory + sum_filename + number + sum_ext);
    //Summaryfile << "summary file \n";

    //Summaryfile << "\n";


}

void Simulation::CloseFile() {
    if (Simfile.is_open()) { Simfile.close(); }
    if (Configfile.is_open()) { Configfile.close(); }
    if (Summaryfile.is_open()) { Summaryfile.close(); }


};

void Simulation::GetSummaryFile() {
    Summaryfile << "filling of summary file \n";
}






