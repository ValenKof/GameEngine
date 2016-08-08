//
// Created by Valentin Kofman on 05/08/16.
//
#include "base/window.h"
#include <base/color.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

namespace ge {

XWindow::XWindow() {
  InitWindow();
}

XWindow::~XWindow() {
  CloseWindow();
}

void XWindow::InitWindow() {
/* get the colors black and white (see section for details) */
  m_pDisplay = XOpenDisplay(nullptr);
  m_screen = DefaultScreen(m_pDisplay);
  const auto black = BlackPixel(m_pDisplay, m_screen);
  const auto white = WhitePixel(m_pDisplay, m_screen);
  m_window = XCreateSimpleWindow(
      m_pDisplay,
      DefaultRootWindow(m_pDisplay),
      0,
      0,
      300,
      300,
      5,
      black,
      white
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
  XSetBackground(m_pDisplay, m_gc, white);
  XSetForeground(m_pDisplay, m_gc, black);
  XClearWindow(m_pDisplay, m_window);
  XMapRaised(m_pDisplay, m_window);
};

void XWindow::CloseWindow() {
  XFreeGC(m_pDisplay, m_gc);
  XDestroyWindow(m_pDisplay, m_window);
  XCloseDisplay(m_pDisplay);
};

void XWindow::Redraw() {
  XClearWindow(m_pDisplay, m_window);
};

void XWindow::Loop() {
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
    if (event.type == KeyPress &&
        XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
      /* use the XLookupString routine to convert the invent
         KeyPress data into regular text.  Weird but necessary...
      */
      if (text[0] == 'q') {
        break;
      }
      printf("You pressed the %c key!\n", text[0]);
    }
    if (event.type == ButtonPress) {
      /* tell where the mouse Button was Pressed */
      int x = event.xbutton.x,
          y = event.xbutton.y;

      strcpy(text, "X is FUN!");
      XSetForeground(m_pDisplay, m_gc, Color::BLACK().Rgb());//rand() % event.xbutton.x % 255);
      XDrawPoint(m_pDisplay, m_window, m_gc, x, y);
//      XDrawString(dis,win,gc,x,y, text, strlen(text));
    }
  }
}


}  // namespace ge
