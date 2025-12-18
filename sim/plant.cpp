#include "plant.hpp"

PitchRatePlant::PitchRatePlant(const Params& params)
  : params_(params)
{
  reset();
}

void PitchRatePlant::reset()
{
  q_ = 0.0f;
}

float PitchRatePlant::update(float elavator_cmd, float dt)
{
  float q_dot = (-1.0f / params_.tau) * q_ + params_.gain * elavator_cmd;

  q_ += q_dot * dt;
  return q_;
}

float PitchRatePlant::getRate() const
{
  return q_;
}
