#pragma once
#include <vector>

class InputProfile {
public:
  
  struct StepEvent {
    float time;
    float value;
  };

  InputProfile(float initial_value);

  void addStepEvent(float time, float value);
  float getValue(float sim_time) const;

private:
  float initial_value_;
  std::vector<StepEvent> events_;
};
