# FliesHungerGames

Here is a first  version of a lab immersion project in Jaksic Laboratory at EPFL done during 02/22 to 02/23, as semester projects by students. It aims at reproducing and simulating an in vitro evolutionary biology expirement to identify genetic factors of cognition in *Drosophila Melanogaster*. Its purpose is to identify possible parameters values to run the in vitro experiment and explore models to explain drosophila's behaviour. 

### 1. Summary

#### Abstract

This project consists of a simulated 2D circular arena divided in multiple sections to form different rooms. Each room is connected to the next one by multiple one-way entrances in the wall separating them. It simulates agents within the arena over several generations, each one with a learning curve. The food object is a simple point of attraction located at the center of a room, shifting from room to room. The "null" model is a force based model with random attractor points drawn from a uniform distribution, and attraction to the right entrance depending on the learning stength.

#### Project executables

The project generates three executable files :

- *Sim*, the main part of the project. Can run multiple simulation and record data for analysis. Generates three directories : *SimConfig*, *SimData* & *SimSummary* that keep track of simulation configuration and simulation data respectively. 
- *DrawArena* - graphical representation of the simulation, does not save any data. Used to check correct behaviour of simulation and visualize it. 
- *FliesConfigGenerate* generates a CSV file with the phenotypes of the flies, that may be then modified before running the simulation.

### 2. Requierements

For all the project : 
- C++11 with standard libraries
- CMake : version >= 3.10
For graphics :
- SDL library

### 3. Setup

#### 3.1 Installing & Configuring CMake

##### Mac OS

Install the packages using *[Homebrew](https://brew.sh/)*. *CMakeLists.txt* should be already configured and working for the project.

##### Linux

Install the packages using *apt-get*. *CMakeLists.txt* should be already configured and working for the project.


#### 3.2 Building the executables

##### Mac OS & Linux

Be sure to run this following command line while being in the project directory.
After downloading the project and installing all the requirements, run these commands in the terminal

> $ mkdir build
> 
> $ cd build
>
> $ cmake ..
>
> $ cmake --build .

The result should be three executable file ready to be launched in the terminal. 

### 4. Classes, Object & Interactions

#### 4.1 Classes

List of classes and small description of there use/utility :

- **Vector2D**: Base utility class, defines 2D vectors and basic operations for the project.
- **Rectangle**: Defines a 2D polygon with 4 points. Base element to construct walls & entrances. Include many utility functions as well.
- **Wall**: Simulation object that divides the arena in multiple rooms.
- **Entrance**: Simulation object that is part of a wall and enables agents to cross walls.
- **Arena2D**: Forms circular arena built from walls, in which simulation takes place.
- **Fly2D**: Agent of the simulation, moves within the arena, going from room to room.
- **Food**: Attractor object for the agents, shift from room to room.
- **Simulation2D**: Regroup every element of the simulation and runs it.
- **Egg**: Defines an egg laid, with parents and phenotypic attributes.
- **FliesConfig**: Creates a configuration for the phenotype of the flies and creates a CSV file.

- **Utility_SDL** : Utility functions for graphic elements



##### Other

- **main.cpp**: Defines Sim2D executable
- **DrawArena2D.cpp**: Defines DrawArena2D executable
- **FLiesCOnfigGenerate.cpp**: Defines FliesConfigGenerate executable

#### Bibliography & Other resources

[Simulating Flying Insects](https://journals.plos.org/plosone/article?id=10.1371/journal.pone.0155698#sec025) main implementation idea

[SDL](https://www.libsdl.org/) library

[RVO2-3D](https://github.com/snape/RVO2-3D) 

[Reciprocal Velocity Obstacles for Real-Time Multi-Agent Navigation](https://gamma.cs.unc.edu/RVO/icra2008.pdf)
