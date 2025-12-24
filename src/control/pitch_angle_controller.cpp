#include "control/pitch_angle_controller.hpp"
#include <algorithm>

PitchAngleController::PitchAngleController(const Params& params) 
  : params_(params) {}

void PitchAngleController::reset() {}

float PitchAngleController::update(float angle_cmd, float angle_meas, float q_meas)
{
  // Compute the error between commanded angle and measured angle
  float err = angle_cmd - angle_meas;

  // PD Controller for Angle
  float q_cmd = params_.kp * err - params_.kd * q_meas;

  // Fix the computed commanded q between the output limits (Don't request a angle that cannot be provided)
  return std::clamp(q_cmd, -params_.output_limit, params_.output_limit);
}
