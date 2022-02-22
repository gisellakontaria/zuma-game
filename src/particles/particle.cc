//
// Created by Gisella Kontaria on 20/04/21.
//

#include "../../include/particles/particle.h"


namespace zuma {

Particle::Particle(const vec2& pos, const vec2 &vel, const size_t& radius, const ci::Color& color) :
  kRadius(radius), position_(pos), velocity_(vel), color_(color) {}

void Particle::UpdatePosition() {
  position_ += velocity_;
}

// Enums of particle types with default positions
const Particle Particle::RED = Particle(vec2(100,50),vec2(0,5), 15, "red");
const Particle Particle::YELLOW = Particle(vec2(100,50),vec2(0,3), 15, "yellow");
const Particle Particle::BOMB = Particle(vec2(100,50),vec2(0,10), 25, "black");
const Particle Particle::RECOVERY = Particle(vec2(100,50),vec2(0,7), 25, "white");
const Particle Particle::BLUE = Particle(vec2(100,50),vec2(0,8), 10, "blue");

const size_t& Particle::GetRadius() const {
  return kRadius;
}

const vec2& Particle::GetPos() const {
  return position_;
}

const vec2& Particle::GetVel() const {
  return velocity_;
}

const ci::Color & Particle::GetColor() const {
  return color_;
}

}