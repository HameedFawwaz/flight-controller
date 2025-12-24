#include "plant.hpp"

PitchRatePlant::PitchRatePlant(const Params& params)
  : params_(params)
{
    reset();
}

void PitchRatePlant::reset()
{
    q_ = 0.0f;
    theta_ = 0.0f;
}

void PitchRatePlant::update(float elevator_cmd, float dt)
{
    // First-order pitch rate dynamics
    float q_dot = (-1.0f / params_.tau) * q_
                  + params_.gain * elevator_cmd;

    q_ += q_dot * dt;

    // Kinematic relation
    theta_ += q_ * dt;
}

float PitchRatePlant::getRate() const
{
    return q_;
}

float PitchRatePlant::getAngle() const
{
    return theta_;
}
