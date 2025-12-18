#pragma once

class PitchRateController {
public:
  struct Params {
    float kp;
    float ki;
    float integrator_limit;
    float output_limit;
  };

  explicit PitchRateController(const Params& params);

  void reset();
  float update(float q_cmd, float q_meas, float dt);


private:
  Params params_;
  float integrator_ = 0.0f;
};
