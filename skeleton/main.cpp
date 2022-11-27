#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include <list>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>
#include "Particle.h"
#include "Proyectil.h"
#include "ParticleSystem.h"
#include <time.h>



using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
Particle* part;
Particle* suelo;
Particle* diana;
std::vector<Proyectil*> bullet;
ParticleSystem* pSystem;
WindForceGenerator* wGen;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	/*auto floor = CreateShape(physx::PxBoxGeometry(300, 1, 300));
	suelo = new Particle({ 5,40,5 }, { 0,0,0 }, { 0,0,0 }, 0,10000, floor, {0,0.9,0,1});*/

	/*auto round = CreateShape(physx::PxBoxGeometry(10, 10, 1));
	diana = new Particle({ 7,50,7 }, { 0,0,0 }, { 0,0,0 }, 0,10000, round, {0.8,0.8,0.8,1});*/

	pSystem = new ParticleSystem();

}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	for (int i = 0; i < bullet.size(); i++)
	{
		if (bullet[i]->getLifetime()>0) {
			bullet[i]->integrate(t);
		
		}
		else {
			delete bullet[i];
			bullet.erase(bullet.begin() + i);
			--i;
		}
	}

	pSystem->update(t);

}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	for (int i = 0; i < bullet.size(); i++)
	{
		delete bullet[i];
	}

}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case '1': 
		//pSystem->generateFireworkSystem(0);
		//bullet.push_back(new Proyectil(Proyectil::BULLET, GetCamera()->getTransform().p, GetCamera()->getDir(), {0.3,0.3,0.3,1}));

		//Sin gravedad
		pSystem->creaFuente();
		//Gravedad
		pSystem->creaFuenteGravedad({ 0,-10.0,0 }, { 15,50,7 }, { 0.9,0.1,0.47,1 }, 1);
		//Gravedad y dir
		pSystem->creaFuenteGravedad({ 0,2.0,0 }, { 23,50,7 }, { 1,0.5,0,1 }, 1);
		//Gravedad y masa
		pSystem->creaFuenteGravedad({ 0,-10.0,0 }, { 30,50,7 }, { 0,0.8,0.3,1 }, 10);

		break;
	case '2':
		//pSystem->generateFireworkSystem(1);
		//bullet.push_back(new Proyectil(Proyectil::CANNON, GetCamera()->getTransform().p, GetCamera()->getDir(), { 0.2,0.2,0.2,1 }));

		//viento
		pSystem->creaViento();
		break;
	case '3':
		//pSystem->generateFireworkSystem(2);
		//bullet.push_back(new Proyectil(Proyectil::FIREBALL, GetCamera()->getTransform().p, GetCamera()->getDir(), {0.9,0.1,0.2,1}));
		pSystem->creaTornado();
		break;
	case '4':
		//pSystem->generateFireworkSystem(3);
		//bullet.push_back(new Proyectil(Proyectil::BULLET, GetCamera()->getTransform().p, GetCamera()->getDir(), {0.3,0.3,0.3,1}));
		pSystem->creaExplosion();
		break;
	case '5':
	
		pSystem->muelleFijo();
		pSystem->deactivateSpringWind();
		break;
	//case '6': //desactiva viento muelle
	//	pSystem->deactivateSpringWind();
	//	break;
	case '6': //activa viento muelle
		
		pSystem->activaViento();
		break;
	case '7':
		//pSystem->muelleDoble();
		break;
	case 'X':
		pSystem->addK();
		break;
	case 'C':
		pSystem->subK();
		break;
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}