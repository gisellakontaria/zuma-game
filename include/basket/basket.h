//
// Created by Gisella Kontaria on 20/04/21.
//

#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace zuma {

/***
 * Basket class modelling behavior of the basket in the game
 */
class Basket {

public:
  /***
   * Basket constructor
   * @param top_left position
   * @param bottom_right position
   * @param vel of basket initially
   */
  Basket(const vec2& top_left, const vec2& bottom_right, const vec2& vel);

  /***
   * Moves basket to the right each time key right is pressed
   */
  void MoveRight();

  /***
   * Moves basket to the left each time key left is pressed
   */
  void MoveLeft();

  // getters, setters
  const vec2& GetTopLeftCoordinates() const;

  const vec2& GetBottomRightCoordinates() const;

  void SetTopLeftCoordinates(const vec2& top_left);

  void SetBottomRightCoordinates(const vec2& bottom_right);

private:
  vec2 top_left_;
  vec2 bottom_right_;
  vec2 vel_;
};

}
