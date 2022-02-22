//
// Created by Gisella Kontaria on 20/04/21.
//

#pragma once

#include "cinder/gl/gl.h"
#include <particles/particle.h>
#include <basket/basket.h>

using glm::vec2;
using std::vector;
using std::string;

namespace zuma {

/***
 * Container class storing and constantly updating movement of particles in it
 */
class Container {
public:
  /***
   * Container constructor
   * @param top_left
   * @param bottom_right
   */
  Container(const vec2& top_left, const vec2& bottom_right, const Basket& basket);

  /***
   * Displays particles and container
   */
  void Display() const;

  /***
   * Updates particle position and checks if particle is caught
   */
  void UpdateFrame();

  /***
   * Clears the container from all particles
   */
  void Clear();

  /***
   * Add particle to the container
   * @param particle to be added
   */
  void AddParticle(const Particle& particle);

  /***
   * Commands basket to move left or right
   * @param direction of movement
   */
  void MoveBasket(const string& direction);

  /***
   * Checks if basket hit right container wall
   * @return true if basket is on the edge
   */
  bool IfBasketReachesRightWall();

  /***
   * Checks if basket hit left container wall
   * @return true if basket is on the edge
   */
  bool IfBasketReachesLeftWall();

  /***
   * Handles player's mouse click when choosing difficulty level
   * @param pos of the click
   */
  void HandleClick(const glm::vec2& pos);

  /***
   * Called when button clicked. Restores lives and clears points.
   */
  void RestartGame();

  // setters, getters
  void SetLevel(const string& difficulty);

  const string& GetMission(const string& level) const;

  // Sets player points, used for testing
  void SetPoints(const size_t& points);

  // Sets player life count, used for testing
  void SetLifeCount(const size_t& life);

  // Returns player's current level, used for testing
  const string& GetLevel() const;

  // Returns particles in container, used for testing
  const vector<Particle>& GetParticles() const;

  // Returns player current points, used for testing
  const size_t& GetPoints() const;

  // Returns current life count, used for testing
  const size_t& GetLives() const;

  // Returns frame count, used for testing
  const size_t& GetFrameCount() const;

  // Return basket used in this game, used for testing
  const Basket& GetBasket() const;

private:
  vector<Particle> particles_;

  const vec2 top_left_;
  const vec2 bottom_right_;

  Basket basket_;

  const string easy_mission_ = "Reach 100 points before your lives run out!";
  const string normal_mission_ = "Reach 100 points before your lives run out! Avoid BLACK BOMBS, get an extra life from WHITE recovery balls!";
  const string hard_mission_ = "Reach 100 points before your lives run out! Avoid BLACK BOMBS that robs 1 life!";
  const string no_difficulty_chosen_mission_ = "Choose a level to begin";
  const string default_level_ = "n/a";
  const string easy_level_ = "EASY";
  const string normal_level_ = "NORMAL";
  const string hard_level_ = "HARD";
  const string restart_ = "RESTART";
  const string difficulty_selection_ = "Select a difficulty level to start the game:";
  const string current_points_ = "Current Points: ";
  const string life_count_ = "Life Count: ";
  const string mission_ = "Mission: ";
  const string game_over_ = "GAME OVER! YOU LOST";
  const string win_ = "CONGRATULATIONS! YOU WON";
  const string particle_caught_text_ = "+10 pts";
  const string particle_missed_text_ = "-1 life";
  const string bomb_caught_text_ = "YOU HIT A BOMB! -1 life";
  const string recovery_caught_text_ = "RECOVERY BALL CAUGHT! +1 life";
  const string right_ = "RIGHT";
  const string left_ = "LEFT";

  const size_t default_points_ = 0;
  const size_t default_life_count_ = 3;
  const size_t winning_points_ = 100;
  const size_t game_over_life_count_ = 0;
  const size_t particle_points_ = 10;
  const size_t particle_drop_interval_ = 100;

  const size_t buttons_width_ = 50;
  const size_t buttons_x_coor_ = 550;
  const size_t buttons_y_coor_ = 750;
  const size_t easy_button_y_coor_ = 250;
  const size_t normal_button_y_coor_ = 300;
  const size_t hard_button_y_coor_ = 350;
  const size_t restart_button_y_coor = 420;

  const size_t level_selection_text_y_coor_ = 200;
  const size_t easy_text_y_coor_ = 275;
  const size_t restart_text_y_coor_ = 445;
  const size_t text_x_coor_ = 650;

  const size_t container_top_y_coor_ = 50;
  const size_t container_width_ = 400;
  const size_t container_margin_ = 70;

  const ci::Color black_ = "black";
  const ci::Color white_ = "white";

  const vec2 mission_text_pos_ = vec2(400, 700);
  vec2 basket_default_top_left_;
  vec2 basket_default_bottom_right_;

  size_t player_points_ = default_points_;
  size_t player_life_ = default_life_count_;
  string difficulty_level_ = default_level_;
  size_t frame_count_ = 0;

  bool bomb_caught_ = false;
  bool recovery_caught_ = false;
  bool particle_caught_ = false;
  bool particle_missed_ = false;

  // Returns true if game is over, clears screen
  bool IfGameEnded();

  // If particle hits basket, points earned
  void IfParticleCaught(const Particle& particle);

  // returns true if particle hits basket
  bool IfParticleHitsBasket(double basket_left_edge, double basket_right_edge, double particle_pos);

  // Delete a particle from the container
  void RemoveParticle(const Particle& particle);
};

}