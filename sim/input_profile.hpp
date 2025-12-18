#pragma once
#include <vector>
#include <cmath>
#include <random>

class InputProfile {
public:
  enum class Type { STEP, RAMP, SINE };

  struct Event {
    Type type;
    float start_time;
    float value;
    float frequency;
    float offset;
  };


  InputProfile(float initial_value);

  void addStep(float start_time, float value);
  void addRamp(float start_time, float slope);
  void addSine(float start_time, float amplitude, float frequency, float offset=0.0f);
  void enableNoise(float stddev);

  float getValue(float sim_time);

private:
  float initial_value_;
  std::vector<Event> events_;

  bool noise_ = false;
  float gauss_std_ = 0.0f;

  std::mt19937 rng_;
  std::normal_distribution<float> gauss_dist_;
};
