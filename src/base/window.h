//
// Created by Valentin Kofman on 05/08/16.
//
#pragma once
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <cstdint>

namespace ge {

class XWindow {
public:
  XWindow();
  ~XWindow();

  void InitWindow();
  void CloseWindow();
  void Redraw();
  void Loop();

private:
  Display* m_pDisplay;
  int m_screen;
  Window m_window;
  GC m_gc;
};

}  // namespace ge
