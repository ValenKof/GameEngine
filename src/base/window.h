// Created by Valentin Kofman on 05/08/16.
#pragma once
#include "base/color.h"
#include "base/mesh.h"
#include "base/camera.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <cstdint>

namespace ge {

class XWindow {
public:
  XWindow(size_t width, size_t height);
  ~XWindow();

  int64_t FramesPerSecond();
  int64_t TicksPerFrame();
  int64_t UpdatesPerSecond();
  int64_t TicksPerUpdate();

  void InitWindow();
  void CloseWindow();
  void Clear();
  void Start();
  void Stop();

  void HandleInput();

  void SetForeground(Color color);
  void SetBackground(Color color);

  void DrawPoint(int x, int y);
  void DrawRectangle(int x, int y, size_t width, size_t height);
  void FillRectangle(int x, int y, size_t width, size_t height);

  void FillPolygon(int x1, int y1, int x2, int y2, int x3, int y3);

  template <typename T>
  void FillPolygon(const std::array<BasicPoint3D<T>, 3>& polygon)
  {
    FillPolygon(
        static_cast<int>(polygon[0].x), static_cast<int>(polygon[0].y),
        static_cast<int>(polygon[1].x), static_cast<int>(polygon[1].y),
        static_cast<int>(polygon[2].x), static_cast<int>(polygon[2].y));
  }

  template <typename T>
  void DrawMesh(const BasicMesh<T>& mesh_in_camera, const Camera& camera)
  {
    auto calc_x = [this](double x)
    { return static_cast<int>((x + 1) * m_width / 2); };
    auto calc_y = [this](double y)
    { return static_cast<int>((y + 1) * m_height / 2); };

    BasicMesh<T> mesh_in_projection = mesh_in_camera.Transformed(camera.CameraToProjection());
    srand(0);
    for (size_t i = 0; i < mesh_in_camera.PolygonsNumber(); ++i) {
      SetForeground(Color::Random());
      if (mesh_in_camera.IsVisible(i)) {
        auto polygon = mesh_in_projection.GetPolygon(i);
        FillPolygon(
            calc_x(polygon[0].x), calc_y(polygon[0].y),
            calc_x(polygon[1].x), calc_y(polygon[1].y),
            calc_x(polygon[2].x), calc_y(polygon[2].y));
      }
    }
  }

protected:
  virtual void Update() = 0;
  virtual void Render(float t) = 0;
  virtual void ButtonPressed(int x, int y) = 0;
  virtual void KeyPressed(char c) = 0;

private:
  const size_t m_width;
  const size_t m_height;
  Display* m_pDisplay;
  int m_screen;
  Window m_window;
  GC m_gc;
  bool m_asked_to_stop;
};

}  // namespace ge
