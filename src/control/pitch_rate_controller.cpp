#include "control/pitch_rate_controller.hpp"
#include <algorithm>
PitchRateController::PitchRateController(const Params& params)
  : params_(params)
{
    reset();
}

void PitchRateController::reset() 
{
  integrator_ = 0.0f;
}

float PitchRateController::update(float q_cmd, float q_meas, float dt)
{

  // Compute rate err
  const float error = q_cmd - q_meas;

  // Integrate err
  integrator_ += error * dt;

  // PI Control
  float output = params_.kp * error + params_.ki * integrator_;

  output = std::clamp(output, -params_.output_limit, params_.output_limit);
  
  integrator_ = std::clamp(integrator_, -params_.integrator_limit, params_.integrator_limit);

  return output; 

}


