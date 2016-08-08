//
// Created by Valentin Kofman on 05/08/16.
//
#include <base/window.h>
#include <base/matrix.h>
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
  std::thread event_thread(RunMainLoop);
  event_thread.join();

  Matrix<int> a({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<int> b({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
  Matrix<int> c = a + b;
  std::cerr << c << std::endl;

  return 0;
}
