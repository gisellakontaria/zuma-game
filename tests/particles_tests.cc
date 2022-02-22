//
// Created by Gisella Kontaria on 20/04/21.
//

#include <particles/particle.h>

#include <catch2/catch.hpp>

using namespace zuma;
using glm::vec2;

TEST_CASE("Enums added properly") {
  SECTION("Colors are accurate") {
    REQUIRE(Particle::RED.GetColor() == "red");
    REQUIRE(Particle::YELLOW.GetColor() == "yellow");
    REQUIRE(Particle::BLUE.GetColor() == "blue");
    REQUIRE(Particle::BOMB.GetColor() == "black");
    REQUIRE(Particle::RECOVERY.GetColor() == "white");
  }

  SECTION("Velocities are accurate") {
    REQUIRE(Particle::RED.GetVel() == vec2(0,5));
    REQUIRE(Particle::YELLOW.GetVel() == vec2(0,3));
    REQUIRE(Particle::BLUE.GetVel() == vec2(0,8));
    REQUIRE(Particle::BOMB.GetVel() == vec2(0,10));
    REQUIRE(Particle::RECOVERY.GetVel() == vec2(0,7));
  }

  SECTION("Radius are accurate") {
    REQUIRE(Particle::RED.GetRadius() == 15);
    REQUIRE(Particle::YELLOW.GetRadius() == 15);
    REQUIRE(Particle::BLUE.GetRadius() == 10);
    REQUIRE(Particle::BOMB.GetRadius() == 25);
    REQUIRE(Particle::RECOVERY.GetRadius() == 25);
  }
}
