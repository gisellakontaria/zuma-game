//
// Created by Gisella Kontaria on 20/04/21.
//

#include "graphics/zuma_simulation_app.h"

using glm::vec2;

namespace zuma {

ZumaApp::ZumaApp() : container_(vec2(kMargin, kMargin), vec2(10 * kMargin,kMargin + kContainerHeight),
  Basket(basket_top_left_, basket_bottom_right_, basket_vel_)) {
  ci::app::setWindowSize(kWindowSize,kWindowSize);
}

void ZumaApp::draw() {
  ci::gl::clear();
  ci::gl::draw(bg_);
  container_.Display();
}

void ZumaApp::update() {
  container_.UpdateFrame();
}

void ZumaApp::setup() {
  bg_ = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset(bg_path_)));
}

void ZumaApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT:
      if (!container_.IfBasketReachesRightWall()) {
        container_.MoveBasket(right_);
      }
      break;
    case ci::app::KeyEvent::KEY_LEFT:
      if (!container_.IfBasketReachesLeftWall()) {
        container_.MoveBasket(left_);
      }
      break;
  }
}

void ZumaApp::mouseDown(ci::app::MouseEvent event) {
  container_.HandleClick(event.getPos());
}

}
