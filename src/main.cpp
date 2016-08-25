//
// Created by Valentin Kofman on 05/08/16.
//
#include <base/window.h>
#include <base/matrix.h>
#include <base/point.h>
#include <base/transformation.h>
#include <base/mesh.h>
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <iostream>
#include <string>

using namespace ge;

class MyGame : public XWindow {
public:
  MyGame() : XWindow(800, 600)
  {
    m_cube.LoadTxt("../meshes/cube.txt");

    m_transform_in_model = Transformation::Scale(100);
    m_model_to_world = Transformation::Identity();
    m_current_transform_in_world = Transformation::Identity();
    m_next_transform_in_world = Transformation::Identity();
  }

protected:
  void Render(float t) override
  {
    Matrix transform_in_world = m_current_transform_in_world +
        (m_next_transform_in_world - m_current_transform_in_world) * t;
    Matrix result = m_transform_in_model * m_model_to_world * transform_in_world;
    Clear();
    Mesh cube_in_camera = m_cube.Transformed(result);
    DrawMesh(cube_in_camera);
  }

  void Update() override
  {
    m_current_transform_in_world = m_next_transform_in_world;
  }

  void ButtonPressed(int x, int y) override
  {
    m_current_transform_in_world = Transformation::Translate(x, y, 0);
    m_next_transform_in_world = Transformation::Translate(x, y, 0);
  }

  void KeyPressed(char c) override
  {
    if (c == 'q') {
      Stop();
    }

    int dx = (c == 'a' ? -10 : (c == 'd' ? +10 : 0));
    int dy = (c == 's' ? -10 : (c == 'w' ? +10 : 0));
    m_next_transform_in_world =
        m_current_transform_in_world * Transformation::Translate(dx, dy, 0);

    double angle = (c == 'r' ? 1.0 : 0.0);
    m_transform_in_model = m_transform_in_model * Transformation::Rotate(angle, angle, angle);
  }

private:
  Mesh m_cube;

  Matrix m_transform_in_model;
  Matrix m_model_to_world;
  Matrix m_current_transform_in_world;
  Matrix m_next_transform_in_world;
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
