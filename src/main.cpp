// Created by Valentin Kofman on 05/08/16.
#include "ge/base/window.h"
#include "ge/base/matrix.h"
#include "ge/base/point.h"
#include "ge/base/transformation.h"
#include "ge/base/mesh.h"
#include "ge/base/camera.h"
#include "ge/base/texture.h"
#include "ge/base/png.h"
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <iostream>
#include <string>

using namespace ge;

class MyGame : public XWindow {
public:
  MyGame()
    : XWindow(800, 600)
    , m_camera(Point3D(0, 0, 0), Vector3D(1, 0, 0), Vector3D(0, 0, 1))
  {
    m_cube.LoadObj("../meshes/wolf.obj");
    m_texture.LoadPng("../textures/ladybug_64.png");
    m_cube_location = Point3D(50, 0, 0);
    m_transform_in_model = Transformation::Scale(1);
    m_model_to_world = Transformation::Identity();
    m_transform_in_world = Transformation::Translate(m_cube_location - Point3D(0, 0, 0));
  }

protected:
  void Render(float t) override
  {
    Matrix result = m_transform_in_model * m_model_to_world * m_transform_in_world;
    Clear();

    for (uint32_t y = 0; y < m_texture.Height(); ++y) {
      for (uint32_t x = 0; x < m_texture.Width(); ++x) {
        SetForeground(m_texture.GetPixel(y, x));
        DrawPoint(x, y);
      }
    }

    Mesh cube_in_camera = m_cube.Transformed(result * m_camera.WorldToCamera());
    //std::cout << "CubeInCamera: " << cube_in_camera.GetPolygon(0)[0] << std::endl;
    DrawMesh(cube_in_camera, m_camera);
  }

  void Update() override
  {
  }

  void ButtonPressed(int x, int y) override
  {
    //m_current_transform_in_world = Transformation::Translate(x, y, 0);
    //m_next_transform_in_world = Transformation::Translate(x, y, 0);
  }

  void KeyPressed(char c) override
  {
    if (c == 'q') {
      Stop();
    }

    if (c == 'w') {
      m_camera = m_camera.TranslateLocation(m_camera.Direction());
    }
    if (c == 's') {
      m_camera = m_camera.TranslateLocation(-m_camera.Direction());
    }
    if (c == 'd') {
      m_camera = m_camera.TurnRight(0.01);
    }
    if (c == 'a') {
      m_camera = m_camera.TurnLeft(0.01);
    }
    //    int dx = (c == 'a' ? -1 : (c == 'd' ? +1 : 0));
//    int dy = (c == 's' ? -1 : (c == 'w' ? +1 : 0));
//    std::cout << "WorldToCamera: " << m_camera.WorldToCamera() << std::endl;

    double angle = (c == 'r' ? 1.0 : 0.0);
    m_transform_in_model = m_transform_in_model * Transformation::Rotate(angle, angle, angle);

    std::cout << "Camera.Location: " << m_camera.Location() << std::endl;
    std::cout << "Camera.Direction: " << m_camera.Direction() << std::endl;
    std::cout << "Camera.Right: " << m_camera.Right() << std::endl;
    std::cout << "Camera.Up: " << m_camera.Up() << std::endl;
    std::cout << "Cube.Location: " << m_cube_location << std::endl;
  }

private:
  Mesh m_cube;
  Image m_texture;
  Point3D m_cube_location;
  Matrix m_transform_in_model;
  Matrix m_model_to_world;
  Matrix m_transform_in_world;
  Camera m_camera;
};

void RunMainLoop()
{
  MyGame game;
  game.Start();
}

int main()
{
  std::thread event_thread(RunMainLoop);
  event_thread.join();

//  Point3D x{1, 2, 3};
//  Point3D y{4, 5, 6};
//  Row m = (Point3D{0, 0, 0} + (y - x)).ToRowVector() * Transformation::Translate(1, 1, 1);
//  std::cerr << m << std::endl;


  return 0;
}
