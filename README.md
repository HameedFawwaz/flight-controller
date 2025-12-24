# Fixed-Wing Pitch Control — SITL Implementation

This project implements and validates a cascaded pitch control system for a fixed-wing aircraft using a custom Software In The Loop (SITL) simulation environment written in C++.

The controller architecture follows industry-standard flight control design practices, consisting of:
- An inner **pitch rate control loop**
- An outer **pitch angle control loop**

The system is designed, implemented, and tested with realistic plant dynamics, actuator limits, integrator anti-windup, and variable command profiles.

## Motivation

This project was developed to:
 - Better my understanding of how control systems for aircraft work to be applied to tuning aircraft in ArduPilot with UAARG (University of Alberta Aerial Robotics Group)
 - Get hands-on experience with flight control system design
 - Get hands-on experience in developing a meaningful C++ project that wasn't just boilerplate code found online

## High Level Architecture Overview

<img width="581" height="439" alt="Image" src="https://github.com/user-attachments/assets/016c6346-ab8e-42f0-b64f-2f6eefb1f1b5" />


## Control Architecture

The system combines two control loops to control rate and angle individually:

- The **outer loop** regulates pitch angle (θ) and outputs a pitch rate command (q_cmd)
- The **inner loop** regulates pitch rate (q) and outputs an elevator command

This architecture allows the rate loop to stabilize fast rotational dynamics before the angle loop commands slower attitude changes. This is important because managing rates is a higher priority as it impacts vehicle stability much greater than the angle. 


## Pitch Dynamics Model

The aircraft pitch dynamics are approximated using a first-order pitch rate model:

q̇ = (-1/τ) q + K · δ_e

Where:
- q is pitch rate
- τ is the pitch rate time constant
- K is elevator effectiveness
- δ_e is elevator deflection

Pitch angle is obtained via numerical integration:

θ̇ = q

This model was chosen for simplicity, the literature contains Pitch Dynamics Models which are rather complex and would potentially make this project more lengthy than necessary. By simplifying the model, it is much easier to work with and implementation can occur. If this project is to go forward and is going to be expected to fly on a real vehicle, then these dynamics would be reviisted. 

## Pitch Rate Controller (Inner Loop)

The pitch rate controller is implemented as a PI controller:

u = Kp (q_cmd - q) + Ki ∫(q_cmd - q) dt

Key features:
- Integral anti-windup via integrator clamping
- Output saturation to model actuator limits
- Tuned to be significantly faster than the angle loop

### Pitch Angle Controller (Outer Loop)

The pitch angle controller generates pitch rate commands:

q_cmd = Kp (θ_cmd - θ)

Design principles:
- Tuned after rate loop stabilization
- Only a P controller as the Inner Loop appeared to be stable with just a P value, D and I are 0

## Software-In-The-Loop (SITL) Framework

The SITL framework executes the control system at a fixed timestep (500 Hz) and simulates aircraft response in real time.

Key components:
- Deterministic fixed-step simulation loop
- Modular plant and controller interfaces
- CSV-based logging for intuitive analysis

## Command Profiles

The simulation supports multiple input profiles:
- Step commands
- Ramp commands
- Sinusoidal commands
- Random noise injection

This allows evaluation of:
- Transient response
- Tracking performance
- Disturbance rejection

## Validation

The system was validated using:
- Step response testing
- Rate and angle saturation scenarios
- Disturbance injection
- Variable command profiles

Performance metrics:
- Rise time
- Overshoot
- Steady-state error
- Stability margins (qualitative)

## Validation Plot

As you can see with the following plot, there was a step input and a ramp input applied, with random (gaussian) noise to simulate IMU noise and other sources of noise. The measured angle tracks the commanded angle pretty well, behaving very nicely even when there is noise. You may notice under reaction with the step input, but this is intended as real vehicles would not immediately snap to an angle if there is a step input applied. 

<img width="583" height="354" alt="Image" src="https://github.com/user-attachments/assets/bc7f2a1b-c746-4d82-a2ad-13fc85443753" />

## Repository Structure

.
├── src/
│   └── control/
│       ├── pitch_rate_controller.cpp
│       └── pitch_angle_controller.cpp
│
├── sim/
│   ├── sitl_main.cpp
│   ├── plant.cpp
│   ├── plant.hpp
│   ├── input_profile.cpp
│   └── input_profile.hpp
│
├── include/
│   └── control/
│       ├── pitch_rate_controller.hpp
│       └── pitch_angle_controller.hpp
│
├── CMakeLists.txt
└── README.md

## Build Instructions

```bash
mkdir build
cd build
cmake ..
make
./sitl_main

