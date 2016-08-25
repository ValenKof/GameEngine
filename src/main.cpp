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
    m_cube_to_world = Transformation::Scale(100);
    m_cube_inside_world = Transformation::Identity();
  }

protected:
  void ButtonPressed(int x, int y) override
  {
    m_cube_inside_world = Transformation::Translate(x, y, 0);
    DrawCube();
  }

  void KeyPressed(char c) override
  {
    if (c == 'q') {
      Stop();
    }
    int dx = (c == 'a' ? -1 : (c == 'd' ? +1 : 0));
    int dy = (c == 's' ? -1 : (c == 'w' ? +1 : 0));
    m_cube_inside_world = m_cube_inside_world * Transformation::Translate(dx, dy, 0);
    DrawCube();
  }

private:
  void DrawCube()
  {
    Clear();
    DrawMesh(m_cube.Transformed(m_cube_to_world * m_cube_inside_world));
  }

  Mesh m_cube;
  Matrix m_cube_to_world;
  Matrix m_cube_inside_world;
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
