//
// Created by Valentin Kofman on 05/08/16.
//
#pragma once
#include <base/color.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <cstdint>

namespace ge {

class XWindow {
public:
  XWindow(size_t width, size_t height);
  ~XWindow();

  void InitWindow();
  void CloseWindow();
  void Redraw();
  void Loop();

  void SetForeground(Color color);
  void SetBackground(Color color);

  void DrawPoint(int x, int y);
  void DrawRectangle(int x, int y, size_t width, size_t height);
  void FillRectangle(int x, int y, size_t width, size_t height);

protected:
  virtual void ButtonPressed(int x, int y) = 0;

private:
  const size_t m_width;
  const size_t m_height;
  Display* m_pDisplay;
  int m_screen;
  Window m_window;
  GC m_gc;
};

}  // namespace ge
