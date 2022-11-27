#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringForceGenerator :public SpringForceGenerator
{
  public:
    AnchoredSpringForceGenerator(double k, double resting, const Vector3& anchor_pos);
    ~AnchoredSpringForceGenerator();
    Particle* getParticle() { return other_; }
};

