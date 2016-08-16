//
// Created by Valentin Kofman on 05/08/16.
//
#include <base/window.h>
#include <base/matrix.h>
#include <base/point.h>
#include <base/transformation.h>
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <iostream>
#include <string>

using namespace ge;

void RunMainLoop() {
  XWindow xWindow;
  xWindow.Loop();
}

int main() {
//  std::thread event_thread(RunMainLoop);
//  event_thread.join();

  Point3D x{1, 2, 3};
  Point3D y{4, 5, 6};
  Row m = (Point3D{0, 0, 0} + (y - x)).ToRowVector() * Transformation::Translate(1, 1, 1);
  std::cerr << m << std::endl;


  return 0;
}
