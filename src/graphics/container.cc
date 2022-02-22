//
// Created by Gisella Kontaria on 20/04/21.
//

#include "graphics/container.h"
#include "particles/particle.h"

namespace zuma {

Container::Container(const vec2& top_left, const vec2& bottom_right, const Basket& basket) :
  top_left_(top_left), bottom_right_(bottom_right), basket_(basket) {
    srand (time(0));
    basket_default_top_left_ = basket.GetTopLeftCoordinates();
    basket_default_bottom_right_ = basket.GetBottomRightCoordinates();
}

void Container::Clear() {
  particles_.clear();
}

void Container::Display() const {
  // draw container walls
  ci::gl::ScopedColor color { black_};
  ci::gl::drawStrokedRect(ci::Rectf(top_left_, bottom_right_));

  // draw difficulty level boxes
  ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(buttons_x_coor_,easy_button_y_coor_),
  glm::vec2(buttons_y_coor_, easy_button_y_coor_ + buttons_width_)));
  ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(buttons_x_coor_,normal_button_y_coor_),
  glm::vec2(buttons_y_coor_, normal_button_y_coor_ + buttons_width_)));
  ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(buttons_x_coor_,hard_button_y_coor_),
  glm::vec2(buttons_y_coor_, hard_button_y_coor_ + buttons_width_)));

  // draw basket
  ci::gl::drawSolidRect(ci::Rectf(basket_.GetTopLeftCoordinates(), basket_.GetBottomRightCoordinates()));

  // draw restart button
  ci::gl::drawSolidRect(ci::Rectf(glm::vec2(buttons_x_coor_,restart_button_y_coor),
  glm::vec2(buttons_y_coor_, restart_button_y_coor + buttons_width_)));

  // draw particles
  for (const Particle& particle : particles_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPos(), particle.GetRadius());
  }

  // draw difficulty levels to choose from
  ci::gl::drawStringCentered(
    difficulty_selection_, glm::vec2(text_x_coor_, level_selection_text_y_coor_), ci::Color(black_));
  ci::gl::drawStringCentered(
    easy_level_, glm::vec2(text_x_coor_, easy_text_y_coor_), ci::Color(black_));
  ci::gl::drawStringCentered(
    normal_level_,glm::vec2(text_x_coor_, easy_text_y_coor_ + buttons_width_), ci::Color(black_));
  ci::gl::drawStringCentered(
    hard_level_,glm::vec2(text_x_coor_, easy_text_y_coor_ + 2 * buttons_width_), ci::Color(black_));
  ci::gl::drawStringCentered(
    restart_, glm::vec2(text_x_coor_,restart_text_y_coor_), white_);

  // display current points
  ci::gl::drawStringCentered(
  current_points_ + std::to_string(player_points_), glm::vec2(text_x_coor_, buttons_x_coor_ - buttons_width_), ci::Color(black_));

  // display life count
  ci::gl::drawStringCentered(
  life_count_ + std::to_string(player_life_), glm::vec2(text_x_coor_, buttons_x_coor_), ci::Color(black_));

  // display mission
  ci::gl::drawStringCentered(
  mission_ + GetMission(difficulty_level_), mission_text_pos_, ci::Color(black_));

  // show win / lose notifications
  if (player_life_ == game_over_life_count_) {
    ci::gl::drawStringCentered(
      game_over_, glm::vec2(text_x_coor_, level_selection_text_y_coor_ - buttons_width_), ci::Color(black_));
  } else if (player_points_ >= winning_points_) {
    ci::gl::drawStringCentered(
      win_, glm::vec2(text_x_coor_, level_selection_text_y_coor_ - buttons_width_), ci::Color(black_));
  }

  // display particle points gained / deducted
  if (particle_missed_) {
    ci::gl::drawStringCentered(
      particle_missed_text_, glm::vec2(easy_button_y_coor_, top_left_.y + buttons_width_), black_);
  } else if (particle_caught_) {
    ci::gl::drawStringCentered(
      particle_caught_text_, glm::vec2(easy_button_y_coor_, top_left_.y + buttons_width_), black_);
  } else if (bomb_caught_) {
    ci::gl::drawStringCentered(
      bomb_caught_text_, glm::vec2(easy_button_y_coor_, top_left_.y + buttons_width_), black_);
  } else if (recovery_caught_) {
    ci::gl::drawStringCentered(
      recovery_caught_text_, glm::vec2(easy_button_y_coor_, top_left_.y + buttons_width_), black_);
  }
}

void Container::UpdateFrame() {
  if (!IfGameEnded() && difficulty_level_ != default_level_) {
    Particle yellow = Particle::YELLOW;
    Particle red = Particle:: RED;
    Particle blue = Particle::BLUE;
    Particle bomb = Particle::BOMB;
    Particle recovery = Particle::RECOVERY;

    size_t random_pos;
    size_t random;

    // for easy level, only this portion of the code will execute
    if (frame_count_ % particle_drop_interval_ == 0) {
      // generate a random number to set particle position in the container
      random_pos = (rand() % container_width_) + 1;

      // generate random number to choose which particle to add
      random = (rand() % 5) + 1;
      if (random == 1) {
        AddParticle(Particle(
        glm::vec2(random_pos + container_margin_, container_top_y_coor_), yellow.GetVel(), yellow.GetRadius(), yellow.GetColor()));
      } else if (random == 2){
        AddParticle(Particle(
        glm::vec2(random_pos + container_margin_, container_top_y_coor_), red.GetVel(), red.GetRadius(), red.GetColor()));
      } else if (random == 3) {
        AddParticle(Particle(
        glm::vec2(random_pos + container_margin_, container_top_y_coor_), blue.GetVel(), blue.GetRadius(), blue.GetColor()));
      }
    }

    // for normal level, both bombs and recovery is added. hard level only adds balls to make it harder
    if (difficulty_level_ == normal_level_ || difficulty_level_ == hard_level_) {
      if (random == 4) {
        AddParticle(Particle(
          glm::vec2(random_pos + container_margin_, container_top_y_coor_), bomb.GetVel(), bomb.GetRadius(), bomb.GetColor()));
        }
    }
    if (difficulty_level_ == normal_level_) {
      if (random == 5) {
        AddParticle(Particle(
        glm::vec2(random_pos + container_margin_, container_top_y_coor_), recovery.GetVel(), recovery.GetRadius(), recovery.GetColor()));
      }
    }

    frame_count_++;

    // reset all bools to false before checking if any is caught
    particle_caught_ = false;
    particle_missed_ = false;
    bomb_caught_ = false;
    recovery_caught_ = false;

    // updates particle position and check if any is caught
    for (Particle& particle : particles_) {
      IfParticleCaught(particle);
      particle.UpdatePosition();
    }
  }
}

void Container::AddParticle(const Particle &particle) {
  particles_.push_back(particle);
}

void Container::RemoveParticle(const Particle &particle) {
  for (size_t index = 0; index < particles_.size(); index++) {
    if (particles_.at(index).GetPos() == particle.GetPos() && particles_.at(index).GetColor() == particle.GetColor()
      && particles_.at(index).GetRadius() == particle.GetRadius()) {
      particles_.erase(particles_.begin() + index);
    }
  }
}

void Container::IfParticleCaught(const Particle& particle) {
  // if particle caught, add points. if bomb is caught, one life is lost
  if (IfParticleHitsBasket(basket_.GetTopLeftCoordinates().x, basket_.GetBottomRightCoordinates().x, particle.GetPos().x)
    && particle.GetPos().y >= bottom_right_.y - particle.GetRadius()) {
      if (particle.GetColor() == black_) {
      bomb_caught_ = true;
      player_life_--;
    } else if (particle.GetColor() == white_) {
      recovery_caught_ = true;
      player_life_++;
    } else {
      particle_caught_ = true;
      player_points_ += particle_points_;
    }
    RemoveParticle(particle);
  } else if (particle.GetPos().y >= bottom_right_.y - particle.GetRadius()) {
    // if particle reaches bottom line and uncaught, player loses a life (except for when it is a bomb / recovery)
    if (particle.GetColor() != black_ && particle.GetColor() != white_) {
      particle_missed_ = true;
      player_life_--;
    }
    RemoveParticle(particle);
  }
}

void Container::MoveBasket(const string& direction) {
  if (direction == right_) {
    basket_.MoveRight();
  } else if (direction == left_) {
    basket_.MoveLeft();
  }
}

bool Container::IfBasketReachesRightWall() {
  if (basket_.GetBottomRightCoordinates().x >= bottom_right_.x) {
    return true;
  }
  return false;
}

bool Container::IfBasketReachesLeftWall() {
  if (basket_.GetTopLeftCoordinates().x <= top_left_.x) {
    return true;
  }
  return false;
}

bool Container::IfGameEnded() {
  if (player_life_ == game_over_life_count_ || player_points_ >= winning_points_) {
    Clear();
    return true;
  }
  return false;
}

bool Container::IfParticleHitsBasket(double basket_left_edge, double basket_right_edge, double particle_pos) {
  return (basket_left_edge <= particle_pos && basket_right_edge >= particle_pos);
}

void Container::HandleClick(const glm::vec2 &pos) {
  // check which level player picks
  if (pos.x >= buttons_x_coor_ && pos.x <= buttons_y_coor_) {
    if (pos.y >= easy_button_y_coor_ && pos.y < easy_button_y_coor_ + buttons_width_) {
      SetLevel(easy_level_);
    } else if (pos.y >= normal_button_y_coor_ && pos.y < normal_button_y_coor_ + buttons_width_) {
      SetLevel(normal_level_);
    } else if (pos.y >= hard_button_y_coor_ && pos.y < hard_button_y_coor_ + buttons_width_) {
      SetLevel(hard_level_);
      basket_.SetTopLeftCoordinates(vec2(
      basket_.GetTopLeftCoordinates().x + container_top_y_coor_, basket_.GetTopLeftCoordinates().y));
    } else if (pos.y >= restart_button_y_coor && pos.y < restart_button_y_coor + buttons_width_) {
      RestartGame();
    }
  }
}

void Container::RestartGame() {
  difficulty_level_ = default_level_;
  player_points_ = default_points_;
  player_life_ = default_life_count_;
  basket_.SetTopLeftCoordinates(basket_default_top_left_);
  basket_.SetBottomRightCoordinates(basket_default_bottom_right_);
  particle_caught_ = false;
  particle_missed_ = false;
  bomb_caught_ = false;
  recovery_caught_ = false;
}

void Container::SetLevel(const string &difficulty) {
  difficulty_level_ = difficulty;
}

const string& Container::GetMission(const string& level) const {
  if (level == easy_level_) {
    return easy_mission_;
  } else if (level == normal_level_) {
    return normal_mission_;
  } else if (level == hard_level_) {
    return hard_mission_;
  }
  return no_difficulty_chosen_mission_;
}

void Container::SetPoints(const size_t &points) {
  player_points_ = points;
}

void Container::SetLifeCount(const size_t &life) {
  player_life_ = life;
}

const string& Container::GetLevel() const {
  return difficulty_level_;
}

const vector<Particle> & Container::GetParticles() const {
  return particles_;
}

const size_t & Container::GetLives() const {
  return player_life_;
}

const size_t & Container::GetPoints() const {
  return player_points_;
}

const size_t & Container::GetFrameCount() const {
  return frame_count_;
}

const Basket & Container::GetBasket() const {
  return basket_;
}
}