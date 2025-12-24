# Fixed-Wing Pitch Control — SITL Implementation

This project implements and validates a cascaded pitch control system for a fixed-wing aircraft using a custom Software In The Loop (SITL) simulation environment written in C++.

The controller architecture follows industry-standard flight control design practices, consisting of:
- An inner **pitch rate control loop**
- An outer **pitch angle control loop**

The system is designed, implemented, and tested with realistic plant dynamics, actuator limits, integrator anti-windup, and variable command profiles.

### Motivation

This project was developed to:
 - Better my understanding of how control systems for aircraft work to be applied to tuning aircraft in ArduPilot with UAARG (University of Alberta Aerial Robotics Group)
 - Get hands-on experience with flight control system design
 - Get hands-on experience in developing a meaningful C++ project that wasn't just boilerplate code found online


