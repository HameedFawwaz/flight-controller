#pragma once

class PitchAngleController { 

  public:
  struct Params {
    float kp;
    float ki;
    float kd;
    float output_limit;
    };

    PitchAngleController(const Params& params);

  void reset();
  float update(float angle_cmd, float angle_meas, float q_meas);

private:
  Params params_;
};
