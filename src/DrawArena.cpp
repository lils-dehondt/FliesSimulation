// C++ Standard Libraries
#include <iostream>
#include <string>

// Third party
#if defined(WIN32) || defined(_WIN32)
#include <SDL2/SDL.h>
#elif __APPLE__

#include <SDL.h>

#endif
// Project files
#include "Utility_SDL.h"
#include "Wall.h"
#include "Food.h"
#include "Arena3D.h"
#include "Simulation.h"

int main(int argc, char *argv[]) {
    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window *window = nullptr;

    // Grab the window surface.
    SDL_Surface *screen;

    // Initialize the video subsystem.
    // If it returns less than 1, then an
    // error code will be received.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    } else {
        std::cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C++ SDL2 Window",
                              350,
                              100,
                              1100,
                              1100,
                              SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    // Create a rectangle
    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 100;
    rectangle.w = 400;
    rectangle.h = 400;

    /// Simulation variables 
    unsigned int nb_flies = 40;
    unsigned int nb_rooms = 4;
    unsigned int nb_ent = 4;
    int s_room = 0;
    int f_room = s_room + 1;
    double maxtime = 20000.0;
    double dt = 0.03;
    double food_shift = 600.0;
    double wall_width = 10.0;
    bool nfood = 0;
    bool dataR = 0;
    bool start_sim = true;

    for (int i = 0; i < argc; ++i) {
        // Help command
        if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
            start_sim = false;
            std::cout << "\n\n";
            std::cout << "-h , --help             Help command, shows and describes all simulation parameters";
            std::cout << "\n";
            std::cout << "-f , --flies            Number of flies in simulation, >0";
            std::cout << "\n";
            std::cout << "-T , --time             Duration of simulation, >0";
            std::cout << "\n";
            std::cout << "-fs , --food_shifting   Food shifting time, >0";
            std::cout << "\n";
            std::cout << "-nf, --no_food          If food has to be simulated or not, 1 or 0";
            std::cout << "\n";
            std::cout << "During simulation, type P to pause, L to go faster and K to slow down.";
            std::cout << "\n";



        }
        // Number of simulation

        // Number of flies
        if (std::string(argv[i]) == "-f" || std::string(argv[i]) == "--flies") {
            if (std::stoi(argv[i + 1]) > 0) {
                nb_flies = std::stoi(argv[i + 1]);
            }
        }



        // Time of simulation
        if (std::string(argv[i]) == "-T" || std::string(argv[i]) == "--time") {
            if (std::stod(argv[i + 1]) > 0.0) {
                maxtime = std::stod(argv[i + 1]);
            }
        }
        // Food shifting time
        if (std::string(argv[i]) == "-fs" || std::string(argv[i]) == "--food_shifting") {
            if (std::stod(argv[i + 1]) > 0.0 && std::stod(argv[i + 1]) < maxtime) {
                food_shift = std::stod(argv[i + 1]);
            }
        }
        // Food/No food
        if (std::string(argv[i]) == "-nf" || std::string(argv[i]) == "--no_food") {
            if (std::stoi(argv[i + 1]) == 0) { nfood = 0; }
            if (std::stoi(argv[i + 1]) == 1) { nfood = 1; }
        }

    }

    if(start_sim) {


        Arena3D arena(Vector3d<double>(550, 550, 250), 500, 500, nb_rooms, nb_ent, wall_width);
        if (f_room >= arena.GetNbWalls()) { f_room = 0; }
        if (!nfood) {
            Food food(&arena, f_room, food_shift);
            arena.SetFood(&food);
        }

        Simulation Sim2D(&arena, nb_flies, s_room, maxtime, dt, false, false, true, false, true);

        std::cout << " Simulation start  \n";

        // Infinite loop for our application
        bool simIsRunning = true;
        bool restart = false;
        bool pause = false;

        // height variable increment
        int z = 50;
        // Main application loop
        while(simIsRunning){
            SDL_Event event;

            int x, y;
            Uint32 buttons;
            buttons = SDL_GetMouseState(&x,&y);

            // (1) Handle Input
            // Start our event loop
            while(SDL_PollEvent(&event)){
                // Handle each specific event
                if(event.key.keysym.sym == SDLK_r){
                    restart = true;
                    simIsRunning = false;
                }
                // Pause
                if(event.key.keysym.sym == SDLK_p && event.type == SDL_KEYDOWN){
                    if(pause) pause = false;
                    else if(!pause) pause = true;
                }
                // Change height in window
                //if(event.key.keysym.sym == SDLK_o && event.type == SDL_KEYDOWN){
                    //z +=  50;
                    //std::cout<<"z : "<<z<<"\n";
                //}
                if(event.key.keysym.sym == SDLK_i && event.type == SDL_KEYDOWN){
                    z -= 50;
                    std::cout<<"z : "<<z<<"\n";
                }
                // Change timestep during simulation
                if(event.key.keysym.sym == SDLK_l && event.type == SDL_KEYDOWN){
                    dt += 0.1;
                    std::cout<<"timestep :  "<<dt<<"\n";
                }
                if(event.key.keysym.sym == SDLK_k && event.type == SDL_KEYDOWN){
                    if(dt > 0.0){ dt -= 0.1;}
                    std::cout<<"timestep :  "<<dt<<"\n";
                }
                // Quit event
                if(event.type == SDL_QUIT){
                    simIsRunning= false;
                }
                if(event.type == SDL_KEYDOWN){
                    if(event.key.keysym.sym == SDLK_ESCAPE){
                        simIsRunning = false;
                    }
                }
                // Print mouse position in simulation
                if ((buttons & SDL_BUTTON_LMASK) != 0) {
                    std::cout<< "Clicked on ( " << x << ", "<< y <<" , "<< z << " ) \n";
                    std::cout<<" Clicked in room : "<<arena.GetRoomFromPosition(Vector3d<double>(x, y, z))<<"\n";
                }
                // Change aim of flies in simulation
                if((buttons & SDL_BUTTON_RMASK) != 0){
                    std::cout<< "Clicked on ( " << x << ", "<< y <<" , "<< z <<" ) \n";
                    for( auto fly : Sim2D.GetFlies()){
                        fly->SetAim(Vector3d<double>(x, y, z));
                    }
                }
            }

            if (!Sim2D.IsRunning()) {
                simIsRunning = false;
            }


            // (2) Handle Updates

            // (3) Clear Draw the Screen
            // Gives us a clear canvas
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);


            // Arena drawing
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_Utility::DrawArena(renderer, &arena);

            for (int i = 0; i < Sim2D.GetFlies().size(); i++) {
                SDL_Utility::DrawAgent(renderer, Sim2D.GetFlies()[i], &arena);
                SDL_SetRenderDrawColor(renderer, 255, 255, 100, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLineF(renderer, Sim2D.GetFlies()[i]->GetAim().x - 5,
                                    Sim2D.GetFlies()[i]->GetAim().y - 5,
                                    Sim2D.GetFlies()[i]->GetAim().x + 5, Sim2D.GetFlies()[i]->GetAim().y + 5);
                SDL_RenderDrawLineF(renderer, Sim2D.GetFlies()[i]->GetAim().x - 5,
                                    Sim2D.GetFlies()[i]->GetAim().y + 5,
                                    Sim2D.GetFlies()[i]->GetAim().x + 5, Sim2D.GetFlies()[i]->GetAim().y - 5);


            }

            // Finally show what we've drawn
            SDL_RenderPresent(renderer);

            if (!pause) {
                // Update simulation
                Sim2D.Update(dt);
            }
        }

        // SDL_DestroyTexture(texture);
        // We destroy our window. We are passing in the pointer
        // that points to the memory allocated by the
        // 'SDL_CreateWindow' function. Remember, this is
        // a 'C-style' API, we don't have destructors.
        SDL_DestroyWindow(window);

        // Create datafile in csv format
        // Utility::MakeCSVFromSim(Sim2D);

        // Quit program.
        SDL_Quit();

        if (restart) return main(argc, argv);
        return 0;
    }
};