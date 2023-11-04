#include "renderer.hpp"

Renderer3d::Renderer3d(SDL_Window *_window, SDL_Renderer * _rendered, std::vector<Point3d> & _points, std::vector<Vertex> _vertices)
{
    SDL_GetWindowSize(_window, &WindowSizeX, &WindowSizeY);
    renderer = _rendered;
    points = _points;
    vertices = _vertices;
}

Renderer3d::~Renderer3d()
{
}


Point3d Renderer3d::rotateX(Point3d point)
{   
    Point3d returnPoint;
    returnPoint.x = point.x;
    returnPoint.y = cos(rotationX) * point.y - sin(rotationX) * point.z;
    returnPoint.z = sin(rotationX) * point.y + cos(rotationX) * point.z;
    return returnPoint;
}


Point3d Renderer3d::rotateY(Point3d point)
{
    Point3d returnPoint;
    returnPoint.x = cos(rotationY) * point.x + sin(rotationY) * point.z;
    returnPoint.y = point.y;
    returnPoint.z = - sin(rotationY) * point.x + cos(rotationY) * point.z;
    return returnPoint;
}

Point3d Renderer3d::rotateZ(Point3d point)
{
    Point3d returnPoint;
    returnPoint.x = cos(rotationZ) * point.x - sin(rotationZ) * point.y;
    returnPoint.y = sin(rotationZ) * point.x + cos(rotationZ) * point.y;
    returnPoint.z = point.z;
    return returnPoint;
}

Point3d Renderer3d::translate(Point3d point)
{
    Point3d returnPoint;
    returnPoint.x = point.x + translation;
    returnPoint.y = point.y + translation;
    returnPoint.z = point.z + translationZ;

    return returnPoint;
}


Point2d Renderer3d::projection(Point3d point)
{
    
    return Point2d { WindowSizeX / 2 + (FOV * point.x) / (FOV + point.z) * 100, WindowSizeY / 2 + (FOV * point.y) / (FOV + point.z) * 100};
}

void Renderer3d::rotate() {
    for (auto &Vertex : vertices) 
    {
        points[Vertex.start] = rotateZ(rotateX(rotateY(points[Vertex.start])));
        points[Vertex.end] = rotateZ(rotateX(rotateY(points[Vertex.end])));
    }
}   


void Renderer3d::translate() {
    for (auto &Vertex : vertices) 
    {
        points[Vertex.start] = translate(points[Vertex.start]);
        points[Vertex.end] = translate(points[Vertex.end]);
    }
}   


void Renderer3d::render() 
{
    auto time1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration(0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    //rotation += 1 * DeltaTime;
    //tranlation += 0.0001 * DeltaTime;

    for (auto &Vertex : vertices) 
    {
        // project 3D object to screen
        Point2d start = projection(points[Vertex.start]);
        Point2d end = projection(points[Vertex.end]);
        SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
    }
    SDL_RenderPresent(renderer);

    auto time2 = std::chrono::high_resolution_clock::now();
    duration = time2 - time1;
    DeltaTime = duration.count();
    time1 = time2;

}