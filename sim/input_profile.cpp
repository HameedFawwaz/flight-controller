#include "input_profile.hpp"
#include <vector>

InputProfile::InputProfile(float initial_value)
 : initial_value_(initial_value) {}

void InputProfile::addStepEvent(float time, float value) {
  events_.push_back( { time, value });
}

float InputProfile::getValue(float sim_time) const {
  float output = initial_value_;

  for (const StepEvent& e : events_) {
    if (sim_time >= e.time) {
      output = e.value;
    }
  }
  return output;
}
