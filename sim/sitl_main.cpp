#include <fstream>
#include <iostream>

#include "control/pitch_rate_controller.hpp"
#include "plant.hpp"
#include "input_profile.hpp"

int main()
{
  constexpr float dt = 0.0002f; // 500 Hz
  constexpr float sim_time = 15.0f;

  // Controller params
  PitchRateController::Params ctrl_params{
    .kp = 50.0f,
    .ki = 50.0f,
    .integrator_limit = 0.2f,
    .output_limit = 0.35f
  };

  PitchRateController controller (ctrl_params);

  InputProfile q_cmd_profile (0.0f);

  q_cmd_profile.addStep(0.5f, 0.03f);

  q_cmd_profile.addRamp(5.0f, -0.01f);

  q_cmd_profile.addSine(12.0f, 0.05f, 3.0f);

  // Plant Params
  PitchRatePlant::Params plant_params{
    .tau = 0.15f,
    .gain = 3.5f
  };

  PitchRatePlant plant(plant_params);

  std::ofstream log("pitch_rate_sitl2.csv");
  log << "time,q_cmd,q_meas,elevator\n";

  float q_cmd = 0.0f;
  float time = 0.0f;

  while (time < sim_time) {
 
    // Step Input at t = 0.5s
    if (time > 0.5f) {
      q_cmd = q_cmd_profile.getValue(time);
    }

    
    // Get measured rotation from the plant approximation
    float q_meas = plant.getRate();

    // Compute new elavator position based on PID Controller
    float elevator = controller.update(q_cmd, q_meas, dt);

    // Update plant based on new output from pitchratecontroller
    plant.update(elevator, dt);
   

    // Log new time to the csv file
    log << time << ","
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
