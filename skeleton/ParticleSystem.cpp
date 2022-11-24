#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	forceReg_ = new ParticleForceRegistry();
	
	/*humo_ = new GaussianParticleGenerator({ 7,50,7 }, { 5,5,2 }, { 0,2,0 }, {4, 4, 0}, { 2,2,0 }, 1, 1, 0.99, 3000, { 0.8,0.8,0.8,1 },0.8);
	_particle_generators.push_back(humo_);*/
	//createFireworkRules();
	iniTime_ = glutGet(GLUT_ELAPSED_TIME);

}

void ParticleSystem::creaFuente()
{

	fuente_ = new UniformParticleGenerator({ 7,50,7 }, { 0,0,0 }, { 0,-10.0,0 }, 2, 5, 1, 2, 1, 1, 0.99, 4000, { 0,0,1,1 }, 1.0,1);
	
	_particle_generators.push_back(fuente_);
}
void ParticleSystem::creaFuenteGravedad(Vector3 g, Vector3 pos, Vector4 color, double mass)
{
	gravGen_ = new GravityForceGenerator(g);
	fuente_ = new UniformParticleGenerator(pos, { 0,0,0 }, { 0,0,0 }, 2, 5, 1, 2, 1, 1, 0.99, 4000, color, 1.0, mass);
	fuente_->addForceGenerator(gravGen_);
	_particle_generators.push_back(fuente_);
}
void ParticleSystem::creaViento() {

	auto nube= new GaussianParticleGenerator({ 7,50,7 }, { 0,0,0 }, { 0,0,0 }, { 0, 0, 0 }, {0.5 ,0.5,0.5 }, 1, 8, 0.99, 9000, { 0.8,0.8,0.8,1 }, 0.9, 1);
	gravGen_ = new GravityForceGenerator({0,-10.0,0});
	windGen_ = new WindForceGenerator(-1, 0, Vector3(10, 100, -10), { 7,50,7 },10);
	auto lluvia = new GaussianParticleGenerator({ 7,50,7 }, { 1,1,1 }, { 0,-1,0 }, { 5, 2, 5 }, { 2,2,0 }, 1, 10, 0.99, 3000, { 0.2,0.2,1,1 }, 0.3,1);
	lluvia->addForceGenerator(gravGen_);
	lluvia->addForceGenerator(windGen_);
	_particle_generators.push_back(lluvia);
	_particle_generators.push_back(nube);
}

void ParticleSystem::creaTornado()
{
	
	whirlwindGen_ = new WhirlwindForceGenerator(1, 0, 1.0, Vector3(0.1, 0.1, .1), {7,50,7});
	auto lluvia = new GaussianParticleGenerator({ 7,50,7 }, { 1,1,1 }, { 0,0,0 }, { 3, 3, 3 }, { 2,2,0 }, 1, 10, 0.99, 12000, { 0.8,0.8,0.8,1 }, 0.3, 1);
	lluvia->addForceGenerator(whirlwindGen_);
	_particle_generators.push_back(lluvia);
	

}
void ParticleSystem::creaExplosion()
{
	explosionGen_ = new ExplosionForceGenerator(2000,1000,1000, Vector3( 7,50,7));
	auto exp = new GaussianParticleGenerator({ 7,50,7 }, { 10,10,10 }, { 0,0,0 }, { 2, 2, 2 }, { 1,1,0 }, 1, 10, 0.99, 5000, randomColour(), 0.3, 1);
	exp->addForceGenerator(explosionGen_);
	_particle_generators.push_back(exp);
	
	
}
void ParticleSystem::muelleFijo()
{
	auto cube = CreateShape(physx::PxBoxGeometry(4, 2, 4));
	Particle* pFija = new Particle({ 7,80,7 }, { 0,0,0 }, { 0,0,0 }, 1, 30000, cube, {0,1,0,1},1);
	_particles.push_back(pFija);

	Particle* pMuelle = new Particle({ 7,80,7 }, { 0,0,0 }, { 0,0,0 }, 0.99f, 30000, {0,0,1,1},1,1);
	_particles.push_back(pMuelle);

	springGen_= new SpringForceGenerator(1,10,pFija);
	GravityForceGenerator* gGen = new GravityForceGenerator({ 0.0, -10, 0.0 });

	windGen_= new WindForceGenerator(-1, 0, Vector3(5, 1, 10), { 7,50,7 }, 10);

	forceReg_->addRegistry(springGen_, pMuelle);
	forceReg_->addRegistry(gGen, pMuelle);
	forceReg_->addRegistry(windGen_, pMuelle);

}
void ParticleSystem::activaViento()
{
	double actualTime = glutGet(GLUT_ELAPSED_TIME);
	if (actualTime - iniTime_ >= 100) {
		activateSpringWind();
	}
}
void ParticleSystem::addK()
{
	springGen_->setK(springGen_->getK() + 0.2);
}
void ParticleSystem::subK()
{
	springGen_->setK(springGen_->getK() - 0.2);

}
ParticleSystem::~ParticleSystem()
{
	for (auto gens : _particle_generators) {
		delete gens;
	}
	for (auto p :_particles) {
		delete p;
	}

	forceReg_->deleteForce();
	delete forceReg_;
}

Vector4 ParticleSystem::randomColour()
{
	std::random_device rd;
	std::default_random_engine gen_(rd());
	std::uniform_real_distribution<> distr(0, 1); // define the range
	Vector4 col;

	col.x = distr(gen_);
	col.y = distr(gen_);
	col.z = distr(gen_);
	col.w = 1.0;
	return col;
}

void ParticleSystem::update(double t)
{
	std::list<Particle*>::iterator it = _particles.begin();

	while (it != _particles.end()) {
		Particle* p = *it;
		if (p->isAlive()) {
			p->integrate(t);
			++it;
		}
		else {
			if (p->isFirework()) {
				auto part=p->explode();
				for (auto a : part) {
					_particles.push_back(a);
				}
				
			}
			it = _particles.erase(it);
			forceReg_->deleteParticleRegistry(p);
			delete p;
		}
	}
	
	for (auto e : _particle_generators)
	{
		auto list = e->generateParticle();
		
		std::vector<ForceGenerator*> force = e->returnForce();
	
		for (auto i : list)
		{
			_particles.push_back(i);

			for (auto s : force) {
			
				if (s->forceType == ForceGenerator::GRAVITY) {
					GravityForceGenerator* grav = static_cast<GravityForceGenerator*>(s);
					if (grav != nullptr) {
						forceReg_->addRegistry(grav, i);
					}
				}
				else if(s->forceType == ForceGenerator::WIND) {
					WindForceGenerator* w = static_cast<WindForceGenerator*>(s);
					if (w != nullptr) {
						forceReg_->addRegistry(w, i);
					}
				}
				else if (s->forceType == ForceGenerator::WHIRLWIND) {
					WhirlwindForceGenerator* w = static_cast<WhirlwindForceGenerator*>(s);
					if (w != nullptr) {
						forceReg_->addRegistry(w, i);
					}
				}
				else if (s->forceType == ForceGenerator::EXPLOSION) {
					ExplosionForceGenerator* exp = static_cast<ExplosionForceGenerator*>(s);
					if (exp != nullptr) {
						forceReg_->addRegistry(exp, i);
					}
				}
				
			}
		}

	}
	forceReg_->updateForces(t);
}

ParticleGenerator* ParticleSystem::getParticleGenerator(std::string name)
{
	for (auto e : _particle_generators) {

		if (name == e->getGeneratorName()) return e;
	}
	return nullptr;
}

void ParticleSystem::createFireworkRules()
{
	firework_rules_ = std::vector<FireworkRule>(4);

	firework_rules_[0].set({ 7,50,7 }, { 1,1,1 }, { 0,-2,0 }, 0.99, 4000, randomColour(), 0.4, 10,1, 0); //Fuego básico, sube y explota //gravedad
	firework_rules_[1].set({ 10,40,10 }, { 10,10,0 }, { 0,8.0,0 }, 0.99, 2000, {0.1,0.9,0.9,1}, 0.4, 50,1, 1); //Fuego circular
	firework_rules_[2].set({ 15,60,15 }, { 10,10,0 }, { 0,8.0,0 }, 0.99, 1000, {0.9,0.1,0.47,1}, 0.4, 60,1, 2); //Fuego esfera
	

}
void ParticleSystem::generateFireworkSystem(unsigned type)
{
	if (type >= firework_rules_.size()) {
		return;
	}
	ParticleGenerator* g;
	gravGen_ = new GravityForceGenerator({ 0,-10.0,0 });

	switch (type) {
	case 0:
	
		g =new GaussianParticleGenerator(firework_rules_[type].pos_, firework_rules_[type].vel_,
			firework_rules_[type].acc_, { 4, 4, 0 }, { 1,1,0 }, 1, firework_rules_[type].payload_, firework_rules_[type].damping_, firework_rules_[type].lifeTime_,
			randomColour(), firework_rules_[type].size_, firework_rules_[type].mass_);
		g->addForceGenerator(gravGen_);
		break;
	case 1:
		 g=new CircleParticleGenerator(firework_rules_[type].pos_,{4,4,0},1,15,firework_rules_[type].payload_);

		break;
	case 2:
		g = new SphereParticleGenerator({ 20,20,0 }, 1, 15, firework_rules_[type].payload_);
		break;
	case 3:
		g = new GaussianParticleGenerator(firework_rules_[type].pos_, firework_rules_[type].vel_,
			firework_rules_[type].acc_, { 4, 4, 0 }, { 1,1,0 }, 1, firework_rules_[type].payload_, firework_rules_[type].damping_, firework_rules_[type].lifeTime_,
			randomColour(), firework_rules_[type].size_, firework_rules_[type].mass_);
		break;
	}
	
	Firework* p = new Firework(firework_rules_[type],g);
	g->setParticle(p);
	_particles.push_back(p);
}


