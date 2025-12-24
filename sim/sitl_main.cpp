#include <fstream>
#include <iostream>

#include "control/pitch_rate_controller.hpp"
#include "control/pitch_angle_controller.hpp"
#include "plant.hpp"
#include "input_profile.hpp"

int main()
{
  constexpr float dt = 0.002f; // 500 Hz
  constexpr float sim_time = 15.0f;

  // Controller params
  PitchRateController::Params ctrl_params{
    .kp = 5.0f,
    .ki = 5.0f,
    .integrator_limit = 0.2f,
    .output_limit = 0.35f
  };

  PitchAngleController::Params angle_params{
    .kp = 5.0f,
    .ki = 0.0f,
    .kd = 0.0f,
    .output_limit = 1.5f
  };


  PitchRateController controller (ctrl_params);
  PitchAngleController angle_ctrl (angle_params);

  InputProfile theta_cmd_profile (0.0f);

  theta_cmd_profile.addStep(0.5f, 0.03f);

  theta_cmd_profile.addRamp(5.0f, -0.01f);

  theta_cmd_profile.enableNoise(0.0005f);

  // Plant Params
  PitchRatePlant::Params plant_params{
    .tau = 0.15f,
    .gain = 3.5f
  };

  PitchRatePlant plant(plant_params);

  std::ofstream log("pitch_rate_sitl2.csv");
  log << "time,angle_cmd,angle_meas,q_cmd,q_meas,elavator\n";

  float theta_cmd = 0.0f;
  float time = 0.0f;

  while (time < sim_time) {
 
    // Step Input at t = 0.5s
    theta_cmd = theta_cmd_profile.getValue(time);

    
    // Get measured rotation from the plant approximation
    float q_meas = plant.getRate();
    float theta_meas = plant.getAngle();

    // Compute angle to be turned into rate (q)
    float q_cmd = angle_ctrl.update(theta_cmd, theta_meas, q_meas);

    // Compute new elavator position based on inner loop
    float elevator = controller.update(q_cmd, q_meas, dt);

    // Update plant based on new output from pitchratecontroller
    plant.update(elevator, dt);
   

    // Log new time to the csv file
   log << time << ","
            << theta_cmd << ","
            << theta_meas << ","
            << q_cmd << ","
            << q_meas << ","
            << elevator << "\n";
 
    // Update the time
    time += dt;
  }

  log.close();
  std::cout << "SITL COMPLETE.\n";
  return 0;
};
