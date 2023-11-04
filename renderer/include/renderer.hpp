#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "datatypes.hpp"

class Renderer3d
{

private:

    Point3d rotateX(Point3d point);
    Point3d rotateY(Point3d point);
    Point3d rotateZ(Point3d point);
    Point3d translate(Point3d point);
    Point2d projection(Point3d point);

    float FOV = 5.0;
    float DeltaTime = 0.0f;

    int WindowSizeX;
    int WindowSizeY;

    SDL_Renderer* renderer;

    std::vector<Point3d> points;
    std::vector<Vertex> vertices;


public:

    Renderer3d(SDL_Window* _window, SDL_Renderer* _rendered, std::vector<Point3d>& _points, std::vector<Vertex> _vertices);
    
    ~Renderer3d();

    void render();

    void rotate();

    void translate();

    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;
    float translationZ = 0.0f;
    float translation = 0.0f;


};


