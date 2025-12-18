#pragma once

class PitchRatePlant
{
public:
  struct Params {
    float tau; // time constant [s]
    float gain; // q_dot / elavator
  };

  explicit PitchRatePlant(const Params& params);

  float update(float elevator_cmd, float dt);

  float getRate() const;

  void reset();

private:
  Params params_;
  float q_ = 0.0f;
};
