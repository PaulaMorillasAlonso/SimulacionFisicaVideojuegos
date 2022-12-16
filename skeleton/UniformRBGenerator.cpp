#include "UniformRBGenerator.h"

UniformRBGenerator::UniformRBGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc, double minPos,
    double maxPos, double minVel, double maxVel, double gen_prob, int numPart, double damping, double lifeTime,
    Vector4 colour, Vector3 scale, double mass, PxScene* scene, PxPhysics* gPhysics, bool isDynamic, Vector3 matValues)
{
    mean_pos_ = meanPos;
    mean_vel_ = meanVel;
    mean_acc = meanAcc;
    minPos_ = minPos;
    maxPos_ = maxPos;
    minVel_ = minVel;
    maxVel_ = maxVel;
    dist_pos = std::uniform_real_distribution<double>(minPos_, maxPos_);
    dist_vel = std::uniform_real_distribution<double>(minVel_, maxVel_);
    gen_prob_dist = std::uniform_real_distribution<double>(0, 1);
    generation_probability_= gen_prob;
    num_particles_ = numPart;
    damping_ = damping;
    lifeTime_ = lifeTime;
    colour_ = colour;
    scale_ = scale;
    mass_ = mass;
    scene_ = scene;
    gPhysics_ = gPhysics;
    isDynamic_ = isDynamic;
    matValues_ = matValues;
  
}

std::list<PxRigidDynamic*> UniformRBGenerator::generateRB()
{
    std::list<PxRigidDynamic*> lista;
  
   int genProbRnd = gen_prob_dist(gen_);

    if (genProbRnd < generation_probability_) {

        RBParticle* p = new RBParticle(mean_pos_, mean_vel_, mean_acc, damping_,
            lifeTime_, colour_, scale_, scene_, gPhysics_, mass_, matValues_);

        double newPosX = dist_pos(gen_);
        double newPosY = dist_pos(gen_);
        double newPosZ = dist_pos(gen_);
        p->setPos({ (float)(mean_pos_.x + newPosX),(float)(mean_pos_.y + newPosY),(float)(mean_pos_.z + newPosZ) });

        double newVelX = dist_vel(gen_);
        double newVelY = dist_vel(gen_);
        double newVelZ = dist_vel(gen_);
        p->setVel({ (float)(mean_vel_.x + newVelX),(float)(mean_vel_.y + newVelY),(float)(mean_vel_.z + newVelZ) });


        lista.push_back(p->getDynamicInstance());

    }
  
	return lista;
}
