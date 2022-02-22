//
// Created by Gisella Kontaria on 20/04/21.
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "container.h"

namespace zuma {

/***
 * Zuma app rendering the game interface
 */
class ZumaApp : public ci::app::App {
public:
  ZumaApp();

  void draw() override;
  void update() override;
  void setup() override;
  void keyDown(ci::app::KeyEvent event) override;
  void mouseDown(ci::app::MouseEvent) override;

  const size_t kWindowSize = 800;
  const size_t kMargin = 50;
  const size_t kBasketHeight = 20;
  const size_t kContainerHeight = 600;
  const vec2 basket_vel_ = vec2(25,0);
  const vec2 basket_top_left_ = vec2(kMargin, kMargin + kContainerHeight - kBasketHeight);
  const vec2 basket_bottom_right_ = vec2(3 * kMargin, kMargin + kContainerHeight);

private:
  Container container_;
  ci::gl::Texture2dRef bg_;
  const string bg_path_ = "bg.png";
  const string right_ = "RIGHT";
  const string left_ = "LEFT";
};

}