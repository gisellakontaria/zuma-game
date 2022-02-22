//
// Created by Gisella Kontaria on 20/04/21.
//

#pragma once

#include "cinder/gl/gl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using glm::vec2;

namespace zuma {

/***
 * Particle class modelling the behavior of each particle
 */
class Particle {

public:
  /***
   * Particle constructor
   * @param pos default position before being randomized in AddParticle()
   * @param vel initially
   * @param radius of particle
   */
  Particle(const vec2& pos, const vec2& vel, const size_t& radius, const ci::Color& color);

  /***
   * Updates pos by adding velocity to current pos everytime this fcn is called
   */
  void UpdatePosition();

  // Enums of types of particles
  static const Particle RED;

  static const Particle YELLOW;

  static const Particle BLUE;

  static const Particle BOMB;

  static const Particle RECOVERY;

  // getters
  const size_t& GetRadius() const;

  const vec2& GetPos() const;

  const vec2& GetVel() const;

  const ci::Color& GetColor() const;

private:
  size_t kRadius;
  vec2 position_;
  vec2 velocity_;
  ci::Color color_;
};

}