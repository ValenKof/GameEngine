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

void XWindow::Redraw()
{ XClearWindow(m_pDisplay, m_window); }

void XWindow::Loop()
{
  XEvent event; // the XEvent declaration !!!
  KeySym key; // a dealie-bob to handle KeyPress Events
  char text[255]; // a char buffer for KeyPress Events
  /* look for events forever... */
  while (true) {
    /* get the next event and stuff it into our event variable.
       Note:  only events we set the mask for are detected!
    */
    XNextEvent(m_pDisplay, &event);

    if (event.type == Expose && event.xexpose.count == 0) {
      /* the window was exposed redraw it! */
      Redraw();
    }
    if (event.type == KeyPress && XLookupString(&event.xkey, text, sizeof(text), &key, 0) == 1) {
      /* use the XLookupString routine to convert the invent
         KeyPress data into regular text.  Weird but necessary...
      */
      if (text[0] == 'q') {
        break;
      }
      printf("You pressed the %c key!\n", text[0]);
    }
    if (event.type == ButtonPress) {
      int x = event.xbutton.x;
      int y = event.xbutton.y;
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

}  // namespace ge
