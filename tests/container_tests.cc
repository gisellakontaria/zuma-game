//
// Created by Gisella Kontaria on 20/04/21.
//

#include <graphics/container.h>
#include <particles/particle.h>

#include <catch2/catch.hpp>

using namespace zuma;
using glm::vec2;

TEST_CASE("Particle added correctly") {
  Container container(vec2(50, 50), vec2(500,650), Basket(vec2(50, 630),
  vec2(150, 650), vec2(25,0)));
  Particle p = Particle::RED;
  container.AddParticle(p);

  SECTION("Particle start at the top of the container") {
    REQUIRE(p.GetPos().y == 50);
  }

  SECTION("Particle positioned within container") {
    REQUIRE(p.GetPos().x <= 500);
    REQUIRE(p.GetPos().x >= 50);
  }

  SECTION("Particle position updates after every frame") {
    REQUIRE(p.GetVel() == glm::vec2(0,5));

    // require position to equal default position of enum
    REQUIRE(p.GetPos() == glm::vec2(100,50));

    container.UpdateFrame();
    REQUIRE(p.GetPos() == glm::vec2(100,55));
  }
}

TEST_CASE("Particles caught test") {
  Container container(vec2(50, 50), vec2(500,650), Basket(vec2(50, 630),
  vec2(150, 650), vec2(25,0)));

  SECTION("Particle deleted after caught") {
    // add particle that touches the basket on the center
    container.AddParticle(Particle(vec2(60,640), vec2(0,8), 10, "white"));
    REQUIRE(container.GetParticles().size() == 1);

    // update frame, container will detect it hits basket, clear the particle, add points
    container.UpdateFrame();
    REQUIRE(container.GetParticles().size() == 0);

    // since particle is white (recovery ball), it will add one life
    REQUIRE(container.GetLives() == 4);
  }

  SECTION("Player points added when a particle other than bomb/recovery is caught") {
    container.RestartGame();

    // add blue particle that touches the basket on the center
    container.AddParticle(Particle(vec2(60,640), vec2(0,8), 10, "blue"));

    REQUIRE(container.GetParticles().size() == 1);
    REQUIRE(container.GetPoints() == 0);

    container.UpdateFrame();
    REQUIRE(container.GetParticles().size() == 0);
    REQUIRE(container.GetPoints() == 10);
  }

  SECTION("Bombs caught, player life decrease") {
    container.RestartGame();

    // add bomb that touches the basket on the center
    container.AddParticle(Particle(vec2(60,640), vec2(0,8), 10, "black"));

    REQUIRE(container.GetParticles().size() == 1);
    REQUIRE(container.GetLives() == 3);

    container.UpdateFrame();
    REQUIRE(container.GetLives() == 2);
    }

  SECTION("Particle still caught by the edge of the basket") {
    container.RestartGame();

    // add blue particle that touches the basket on the left edge
    container.AddParticle(Particle(vec2(50,640), vec2(0,8), 10, "blue"));

    REQUIRE(container.GetParticles().size() == 1);

    container.UpdateFrame();
    REQUIRE(container.GetParticles().size() == 0);
  }
}

TEST_CASE("Particles uncaught test") {
  Container container(vec2(50, 50), vec2(500,650), Basket(vec2(50, 630),
vec2(150, 650), vec2(25,0)));

  // add particle that's far right from basket
  container.AddParticle(Particle(vec2(200,655), vec2(0,8), 10, "blue"));

  REQUIRE(container.GetParticles().size() == 1);
  REQUIRE(container.GetLives() == 3);
  REQUIRE(container.GetPoints() == 0);

  container.UpdateFrame();

  SECTION("Particle deleted when it reached the end and uncaught") {
    REQUIRE(container.GetParticles().size() == 0);
  }

  SECTION("Player life decreases when uncaught, points stay the same") {
    REQUIRE(container.GetLives() == 2);
    REQUIRE(container.GetPoints() == 0);
  }

  SECTION("Player life not decreased and points stay the same if bomb/recovery is not caught") {
    container.RestartGame();

    // add bomb far right from basket
    container.AddParticle(Particle(vec2(300,655), vec2(0,8), 10, "black"));

    // add recovery far right from basket
    container.AddParticle(Particle(vec2(400,655), vec2(0,8), 10, "white"));

    REQUIRE(container.GetParticles().size() == 2);
    REQUIRE(container.GetLives() == 3);
    REQUIRE(container.GetPoints() == 0);

    container.UpdateFrame();
    // particles deleted after frame updates
    REQUIRE(container.GetParticles().size() == 0);
    // others stay the same
    REQUIRE(container.GetPoints() == 0);
    REQUIRE(container.GetLives() == 3);
  }
}

TEST_CASE("Container clears when game ends") {
  Container container(vec2(50, 50), vec2(500,650),
    Basket(vec2(50, 630),vec2(150, 650), vec2(25,0)));

  SECTION("Player wins: points reach 100") {
    container.SetPoints(100);
    container.UpdateFrame();

    // Container should clear after update frame as it recognizes that game has ended
    REQUIRE(container.GetParticles().size() == 0);
  }

  SECTION("Player lost: run out of life count") {
    container.SetLifeCount(0);
    container.UpdateFrame();

    // Container should clear after update frame as it recognizes that game has ended
    REQUIRE(container.GetParticles().size() == 0);
  }
}

TEST_CASE("Basket moves within container walls") {
  Container container(vec2(50, 50), vec2(500,650),
    Basket(vec2(50, 630),vec2(150, 650), vec2(25,0)));

  SECTION("Stop moving when right edge reached") {
    // when count is 14, right edge should have been reached
    for (size_t count = 0; count <= 15; count++) {
      container.MoveBasket("RIGHT");
    }
    size_t container_right_edge_x = 650;

    REQUIRE(container.IfBasketReachesRightWall());
    REQUIRE(container.GetBasket().GetBottomRightCoordinates().x == container_right_edge_x);
  }

  SECTION("Stop moving when left edge reached") {
    // when count is 1 left edge should have been reached
    for (size_t count = 0; count <= 5; count++) {
      container.MoveBasket("LEFT");
    }
    size_t container_left_edge_x = 50;

    REQUIRE(container.IfBasketReachesLeftWall());
    REQUIRE(container.GetBasket().GetTopLeftCoordinates().x == container_left_edge_x);
  }
}

TEST_CASE("Game doesn't start until a button clicked") {
  Container container(vec2(50, 50), vec2(500,650),
    Basket(vec2(50, 630),vec2(150, 650), vec2(25,0)));
  container.UpdateFrame();

  SECTION("Frame count increments but particle not added since level is not set") {
    // particle is added only once after 100 frame counts
    for (size_t count = 0; count <= 100; count++) {
      REQUIRE(container.GetFrameCount() == count);
      container.UpdateFrame();
    }

    REQUIRE(container.GetLevel() == "n/a");
    REQUIRE(container.GetParticles().size() == 0);
  }
}

TEST_CASE("Game starts only after button clicked / level is set") {
  Container container(vec2(50, 50), vec2(500,650),
    Basket(vec2(50, 630),vec2(150, 650), vec2(25,0)));

  // set to normal level
  container.HandleClick(vec2(660,330));

  // particle is added only once after 100 frame counts
  for (size_t count = 0; count <= 100; count++) {
    container.UpdateFrame();
  }

  REQUIRE(container.GetParticles().size() == 1);
}

TEST_CASE("Game restarts when restart button clicked") {
  Container container(vec2(50, 50), vec2(500,650),
    Basket(vec2(50, 630),vec2(150, 650), vec2(25,0)));

  container.SetLevel("NORMAL");

  // particle is added only once after 100 frame counts
  for (size_t count = 0; count <= 100; count++) {
    container.UpdateFrame();
  }

  // restart button clicked and RestartGame() called
  container.HandleClick(vec2(660,450));

  SECTION("Life restores") {
    REQUIRE(container.GetLives() == 3);
  }

  SECTION("Points cleared") {
    REQUIRE(container.GetPoints() == 0);
  }

  SECTION("Particles cleared") {
    REQUIRE(container.GetParticles().size() == 0);
  }

  SECTION("Level restarts") {
    REQUIRE(container.GetLevel() == "n/a");
  }

  SECTION("Basket size and position is default") {
    REQUIRE(container.GetBasket().GetTopLeftCoordinates() == vec2(50,630));
    REQUIRE(container.GetBasket().GetBottomRightCoordinates() == vec2(150,650));
  }
}

TEST_CASE("Easy difficulty level") {
  Container container(vec2(50, 50), vec2(500,650),
    Basket(vec2(50, 630),vec2(150, 650), vec2(25,0)));

  SECTION("Easy button clicked within box") {
    for (size_t x = 550; x < 600; x++) {
      for (size_t y = 250; y < 300; y++) {
        container.HandleClick(vec2(x,y));
        REQUIRE(container.GetLevel() == "EASY");
      }
    }
  }

  SECTION("Particle added every 100 frames (not a black bomb / white recovery)") {
    for (size_t count = 0; count <= 500; count++) {
      container.UpdateFrame();
    }

    // particle no should be 5 or below since the random number generated might be 4 (bomb)
    // or 5 (recovery) which will not be added to easy level
    REQUIRE(container.GetParticles().size() <= 5);

    // particle not a black bomb / white recovery
    for (const Particle& particle : container.GetParticles()) {
      REQUIRE(particle.GetColor() != "white");
      REQUIRE(particle.GetColor() != "black");
    }
  }

  SECTION("Basket size is default") {
    container.SetLevel("EASY");
    size_t width = container.GetBasket().GetBottomRightCoordinates().x - container.GetBasket().GetTopLeftCoordinates().x;

    REQUIRE(width == 100);
  }
}

TEST_CASE("Normal difficulty test") {
  Container container(vec2(50, 50), vec2(500,650),
    Basket(vec2(50, 630),vec2(150, 650), vec2(25,0)));

  SECTION("Normal button clicked within box") {
    for (size_t x = 550; x < 600; x++) {
      for (size_t y = 300; y < 350; y++) {
        container.HandleClick(vec2(x,y));
        REQUIRE(container.GetLevel() == "NORMAL");
      }
    }
  }

  SECTION("Particle added every 100 frames (bomb / recovery / yellow / blue / red )") {
    container.SetLevel("NORMAL");
    for (size_t count = 0; count <= 500; count++) {
      container.UpdateFrame();
    }

    // particle should be 5 since in normal level 1 or 5 possible particle should be added every 100 frames
    REQUIRE(container.GetParticles().size() == 5);
  }

  SECTION("Basket size is default") {
    container.SetLevel("NORMAL");
    size_t width = container.GetBasket().GetBottomRightCoordinates().x - container.GetBasket().GetTopLeftCoordinates().x;

    REQUIRE(width == 100);
  }
}

TEST_CASE("Hard difficulty test") {
  Container container(vec2(50, 50), vec2(500,650),
    Basket(vec2(50, 630),vec2(150, 650), vec2(25,0)));

  SECTION("Hard button clicked within box and edges, sets level to hard") {
    for (size_t x = 550; x < 600; x++) {
      for (size_t y = 350; y < 400; y++) {
        container.HandleClick(vec2(x,y));
        REQUIRE(container.GetLevel() == "HARD");
      }
    }
  }

  SECTION("Particle added every 100 frames (not a black bomb / white recovery)") {
    for (size_t count = 0; count <= 500; count++) {
      container.UpdateFrame();
    }

    // particle no should be 5 or below since the random number generated might be 5 (recovery)
    // which will not be added to hard level
    REQUIRE(container.GetParticles().size() <= 5);

    // checks if no white recovery ball is added
    for (const Particle& particle : container.GetParticles()) {
     REQUIRE(particle.GetColor() != "white");
    }
  }

  SECTION("Basket shape is slimmer") {
    container.SetLevel("HARD");

    size_t width = container.GetBasket().GetBottomRightCoordinates().x - container.GetBasket().GetTopLeftCoordinates().x;

    REQUIRE(width == 50);
  }
}
