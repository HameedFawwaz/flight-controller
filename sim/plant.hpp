#pragma once

class PitchRatePlant {
public:
    struct Params {
        float tau;
        float gain;
    };

    PitchRatePlant(const Params& params);

    void reset();

    // ✅ Declaration
    void update(float elevator_cmd, float dt);

    float getRate() const;
    float getAngle() const;

private:
    Params params_;

    float q_;
    float theta_;
};

