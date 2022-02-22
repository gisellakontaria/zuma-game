//
// Created by Gisella Kontaria on 20/04/21.
//

#include "basket/basket.h"

namespace zuma {

using glm::vec2;

Basket::Basket(const vec2& top_left, const vec2& bottom_right, const vec2& vel) :
  top_left_(top_left), bottom_right_(bottom_right), vel_(vel) {}

void Basket::MoveLeft() {
  if (vel_.x < 0) {
    top_left_ = vec2(top_left_.x += vel_.x, top_left_.y);
    bottom_right_ = vec2(bottom_right_.x += vel_.x, bottom_right_.y);
  } else {
    top_left_ = vec2(top_left_.x -= vel_.x, top_left_.y);
    bottom_right_ = vec2(bottom_right_.x -= vel_.x, bottom_right_.y);
  }
}

void Basket::MoveRight() {
  if (vel_.x < 0) {
    top_left_ = vec2(top_left_.x -= vel_.x, top_left_.y);
    bottom_right_ = vec2(bottom_right_.x -= vel_.x, bottom_right_.y);
  } else {
    top_left_ = vec2(top_left_.x += vel_.x, top_left_.y);
    bottom_right_ = vec2(bottom_right_.x += vel_.x, bottom_right_.y);
  }
}

const vec2 & Basket::GetTopLeftCoordinates() const {
  return top_left_;
}

const vec2 & Basket::GetBottomRightCoordinates() const {
  return bottom_right_;
}

void Basket::SetBottomRightCoordinates(const vec2 &bottom_right) {
  bottom_right_ = bottom_right;
}

void Basket::SetTopLeftCoordinates(const vec2 &top_left) {
  top_left_ = top_left;
}

}
