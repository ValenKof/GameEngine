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
  MyGame() : XWindow(800, 600), m_index(0)
  {
    cube_.LoadTxt("../meshes/cube.txt");
    cube_.Transform(Transformation::Scale(100));
  }

protected:
  void ButtonPressed(int x, int y) override
  {
    m_xs[m_index] = x;
    m_ys[m_index] = y;
    m_index = (m_index + 1) % 3;
    if (m_index == 0) {
      FillPolygon(m_xs[0], m_ys[0], m_xs[1], m_ys[1], m_xs[2], m_ys[2]);
    }

    DrawMesh(cube_);
  }

private:
  size_t m_index;
  std::array<int, 3> m_xs;
  std::array<int, 3> m_ys;
  Mesh cube_;
};

void RunMainLoop() {
  MyGame game;
  game.Loop();
}

int main() {
  std::thread event_thread(RunMainLoop);
  event_thread.join();

//  Point3D x{1, 2, 3};
//  Point3D y{4, 5, 6};
//  Row m = (Point3D{0, 0, 0} + (y - x)).ToRowVector() * Transformation::Translate(1, 1, 1);
//  std::cerr << m << std::endl;


  return 0;
}
