//
// Created by Valentin Kofman on 05/08/16.
//
#include "base/window.h"
#include <base/color.h>
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
  XEvent event; // the XEvent declaration !!!
  KeySym key; // a dealie-bob to handle KeyPress Events
  char text[255]; // a char buffer for KeyPress Events
  /* look for events forever... */
  while (!m_asked_to_stop) {
    /* get the next event and stuff it into our event variable.
       Note:  only events we set the mask for are detected!
    */
    XNextEvent(m_pDisplay, &event);

    if (event.type == Expose && event.xexpose.count == 0) {
      /* the window was exposed redraw it! */
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

void XWindow::Stop()
{ m_asked_to_stop = true; }

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
