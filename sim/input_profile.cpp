#include "input_profile.hpp"
#include <chrono>

InputProfile::InputProfile(float initial_value)
 : initial_value_(initial_value) {
  rng_.seed(std::chrono::steady_clock::now().time_since_epoch().count());
}

void InputProfile::addStep(float start_time, float value) {
  events_.push_back( { Type::STEP, start_time, value });
}

void InputProfile::addRamp(float start_time, float slope) {
  events_.push_back({ Type::RAMP, start_time, slope, 0.0f, 0.0f });
}

void InputProfile::addSine(float start_time, float amplitude, float frequency, float offset) {
  events_.push_back({ Type::SINE, start_time, amplitude, frequency, offset });
}

void InputProfile::enableNoise(float stddev) {
  noise_ = true;
  gauss_std_ = stddev;
  gauss_dist_ = std::normal_distribution<float>(0.0f, stddev);
}

float InputProfile::getValue(float sim_time) {
  float output = initial_value_;
    
  for (const Event& e : events_) {
    if (sim_time >= e.start_time) {
      switch (e.type) {
          case Type::STEP:
              output = e.value;
              break;
          case Type::RAMP:
              output = output + e.value * (sim_time - e.start_time);
              break;
          case Type::SINE:
              output += e.offset + e.value * std::sin(2.0f * M_PI * e.frequency * (sim_time - e.start_time));
              break;
      }
  }
}
  if (noise_) {
    output += gauss_dist_(rng_);
  }
  return output;
}


