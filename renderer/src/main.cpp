
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#include "datatypes.hpp"
#include "renderer.cpp"


// cube 

std::vector<Point3d> points
{
    Point3d{-1.0f, -1.0f, -1.0f}, Point3d{-1.0f, -1.0f, 1.0f},
    Point3d{1.0f, -1.0f, -1.0f}, Point3d{-1.0f, 1.0f, -1.0f},
    Point3d{-1.0f, 1.0f, 1.0f}, Point3d{1.0f, -1.0f, 1.0f},
    Point3d{1.0f, 1.0f, -1.0f}, Point3d{1.0f, 1.0f, 1.0f} 
};

std::vector<Vertex> vertices {
    Vertex{0, 1}, Vertex{0, 2}, Vertex{0, 3},
    Vertex{2, 5}, Vertex{3, 6}, Vertex{3, 4},
    Vertex{4, 7}, Vertex{6, 7}, Vertex{7, 5},
    Vertex{5, 1}, Vertex{4, 1}, Vertex{2, 6}, 
};

int main() {

    SDL_Window * window;
    SDL_Renderer* renderer;
    SDL_Event event;

    window = SDL_CreateWindow("3D object render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Renderer3d Renderer3d1(window, renderer, points, vertices);

    // create the renderer where
    bool running = true;

    //while (running) {
    //    if (SDL_QuitRequested()) {
    //        running = false;
    //    }
    //    Renderer3d1.render();
    //}

    bool isMousePressed = false;
    int previousMouseX = 0; // Store previous mouse position
    int previousMouseY = 0; // Store previous mouse position
    bool scrollInProgress = false;
    Uint32 lastScrollTime = 0;
    const Uint32 scrollDelay = 70; // Adjust as needed

    while (running)
    {
        //SDL_Delay(10);
        SDL_PollEvent(&event);
        Renderer3d1.render();
        //Renderer3d1.render(); //
        
        switch (event.type)
        {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_SPACE) {
                    Renderer3d1.translation = 0.1;
                    Renderer3d1.translate();
                }
            break;

                
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    isMousePressed = true;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    isMousePressed = false;
                }
                break;
            case SDL_MOUSEMOTION:
                if (isMousePressed) {

                        int mouseX = event.motion.x;
                        int mouseY = event.motion.y;
                    if (previousMouseX != 0) {

                        int mouseXDifference = mouseX - previousMouseX;
                        int mouseYDifference = mouseY - previousMouseY;
                        Renderer3d1.rotationY = - mouseXDifference * 0.001;
                        Renderer3d1.rotationX = mouseYDifference * 0.001;

                        previousMouseX = mouseX;
                        previousMouseY = mouseY;

                        Renderer3d1.rotate();
                    }
                    else {
                        previousMouseX = mouseX;
                        previousMouseY = mouseY;
                    }
                    
                    //std::cout << mouseX << std::endl;
                    // Handle mouse movement here while the left mouse button is pressed
                    // You can use the values of mouseX and mouseY for your logic
                }
                break;

            
            case SDL_MOUSEWHEEL:
                if (!scrollInProgress || SDL_GetTicks() - lastScrollTime > scrollDelay) {
                    scrollInProgress = true;
                    lastScrollTime = SDL_GetTicks();
                    
                if (event.wheel.y > 0)
                {
                    // Handle scroll up (e.g., zoom in)
                    std::cout << "translation" << std::endl;
                    Renderer3d1.translationZ = 0.05;
                    Renderer3d1.translate();
                }
                else if (event.wheel.y < 0) {
                    // Handle scroll down (e.g., zoom out)
                    Renderer3d1.translationZ = -0.05;
                    Renderer3d1.translate();
                    // You can adjust the zoom level or other actions based on the scroll event.
                }

                // You can adjust the zoom level or other actions based on the scroll event.
                break;
            }
        }
     
        //SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        //SDL_RenderClear(renderer);
        // 
        //SDL_RenderPresent(renderer);
    }

    return 0;
}