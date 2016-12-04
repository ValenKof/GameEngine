// Created by Valentin Kofman on 05/08/16.
#include "window.h"
#include "base/color.h"
#include "base/time.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

namespace ge {

XWindow::XWindow(size_t width, size_t height)
  : m_width(width)
  , m_height(height)
  , m_asked_to_stop(false)
{ InitWindow(); }

XWindow::~XWindow()
{ CloseWindow(); }

int64_t XWindow::FramesPerSecond()
{ return 30; }

int64_t XWindow::TicksPerFrame()
{ return TicksPerSecond() / FramesPerSecond(); }

int64_t XWindow::UpdatesPerSecond()
{ return 10; }

int64_t XWindow::TicksPerUpdate()
{ return TicksPerSecond() / UpdatesPerSecond(); }

void XWindow::InitWindow()
{
  m_pDisplay = XOpenDisplay(nullptr);
  m_screen = DefaultScreen(m_pDisplay);
  m_window = XCreateSimpleWindow(
      m_pDisplay,
      DefaultRootWindow(m_pDisplay),
      0,
      0,
      m_width,
      m_height,
      5,
      Color::BLACK().Rgb(),
      Color::WHITE().Rgb()
  );
  XSetStandardProperties(
      m_pDisplay,
      m_window,
      "Howdy",
      "Hi",
      None,
      nullptr,
      0,
      nullptr
  );
  XSelectInput(
      m_pDisplay,
      m_window,
      ExposureMask | ButtonPressMask | KeyPressMask
  );
  m_gc = XCreateGC(m_pDisplay, m_window, 0, 0);
  SetBackground(Color::RED());
  SetForeground(Color::BLACK());
  XClearWindow(m_pDisplay, m_window);
  XMapRaised(m_pDisplay, m_window);
}

void XWindow::CloseWindow()
{
  XFreeGC(m_pDisplay, m_gc);
  XDestroyWindow(m_pDisplay, m_window);
  XCloseDisplay(m_pDisplay);
}

void XWindow::Clear()
{ XClearWindow(m_pDisplay, m_window); }

void XWindow::Start()
{
  int64_t previous = Ticks();
  int64_t updateLag = 0;
  int64_t renderLag = 0;
  while (!m_asked_to_stop) {
    int64_t current = Ticks();
    int64_t elapsed = current - previous;
    previous = current;
    updateLag += elapsed;
    renderLag += elapsed;
    int64_t wait_time = std::min(TicksPerFrame() - renderLag, TicksPerUpdate() - updateLag);
    if (wait_time > 0) {
      int64_t wait_started = Ticks();
      while (Ticks() < wait_started + wait_time) {
        // active waiting
      }
    }
    while (updateLag >= TicksPerUpdate()) {
      Update();
      HandleInput();
      updateLag -= TicksPerUpdate();
    }
    if (renderLag >= TicksPerFrame()) {
      Render(1.0 * updateLag / TicksPerUpdate());
      XFlush(m_pDisplay);
      renderLag = 0;
    }
  }
}

void XWindow::Stop()
{ m_asked_to_stop = true; }

void XWindow::HandleInput()
{
  XEvent event;
  KeySym key;
  char text[255];
  if (XCheckMaskEvent(m_pDisplay, ExposureMask | ButtonPressMask | KeyPressMask, &event)) {
    if (event.type == Expose && event.xexpose.count == 0) {
      Clear();
    }
    if (event.type == KeyPress && XLookupString(&event.xkey, text, sizeof(text), &key, 0) == 1) {
      std::cout << "KeyPressed: " << text[0] << std::endl;
      KeyPressed(text[0]);
    }
    if (event.type == ButtonPress) {
      int x = event.xbutton.x;
      int y = event.xbutton.y;
      std::cout << "ButtonPressed: " << x << " " << y << std::endl;
      ButtonPressed(x, y);
    }
  }
}

void XWindow::SetForeground(Color color)
{ XSetForeground(m_pDisplay, m_gc, color.Rgb()); }

void XWindow::SetBackground(Color color)
{ XSetBackground(m_pDisplay, m_gc, color.Rgb()); }

void XWindow::DrawPoint(int x, int y)
{ XDrawPoint(m_pDisplay, m_window, m_gc, x, y); }

void XWindow::DrawRectangle(int x, int y, size_t width, size_t height)
{ XDrawRectangle(m_pDisplay, m_window, m_gc, x, y, width, height); }

void XWindow::FillRectangle(int x, int y, size_t width, size_t height)
{ XFillRectangle(m_pDisplay, m_window, m_gc, x, y, width, height); }

void XWindow::FillPolygon(int x1, int y1, int x2, int y2, int x3, int y3)
{
  XPoint points[3]{
    {static_cast<short>(x1), static_cast<short>(y1)},
    {static_cast<short>(x2), static_cast<short>(y2)},
    {static_cast<short>(x3), static_cast<short>(y3)}
  };
  XFillPolygon(m_pDisplay, m_window, m_gc, points, 3, Convex, CoordModeOrigin);
}

}  // namespace ge
