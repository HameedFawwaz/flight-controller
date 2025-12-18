#pragma once
#include <vector>
#include <cmath>

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

  float getValue(float sim_time) const;

private:
  float initial_value_;
  std::vector<Event> events_;
};
