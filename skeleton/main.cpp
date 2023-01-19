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
#include "RBSystem.h"
#include "Lampara.h"
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
Particle* diana;
std::vector<Proyectil*> bullet;
ParticleSystem* pSystem;
RBSystem* rbSystem;
WindForceGenerator* wGen;
Particle* suelo; Particle* frente;
Particle* techo; Particle* der;
Particle* cabezero; Particle* izq;

void crearHabitacion()
{
	auto floor = CreateShape(physx::PxBoxGeometry(300, 1, 300));
	suelo = new Particle({ 5,40,5 }, { 0,0,0 }, { 0,0,0 }, 0, -1, floor, { 0.5, 0.2, 0.0, 1 }, 1);

	auto techoObj = CreateShape(physx::PxBoxGeometry(300, 1, 300));
	techo = new Particle({ 5,130,5 }, { 0,0,0 }, { 0,0,0 }, 0, -1, techoObj, { 1, 1, 1, 1 }, 1);

	auto p1Obj = CreateShape(physx::PxBoxGeometry(1, 100, 300));
	cabezero = new Particle({ 7,50,7 }, { 0,0,0 }, { 0,0,0 }, 0, -1, p1Obj, { 0.99, 0.71, 0.29, 1 }, 1); //cabezero
	

	frente= new Particle({ 150,50,7 }, { 0,0,0 }, { 0,0,0 }, 0, -1, p1Obj, { 0.99, 0.71, 0.29, 1 }, 1);//frente


	auto p2Obj = CreateShape(physx::PxBoxGeometry(300, 100, 1));
	der = new Particle({ 5,50,150 }, { 0,0,0 }, { 0,0,0 }, 0, -1, p2Obj, { 0.99, 0.71, 0.29, 1 }, 1); //der
	izq = new Particle({ 5,50,-150 }, { 0,0,0 }, { 0,0,0 }, 0, -1, p2Obj, { 0.99, 0.71, 0.29, 1 }, 1); //izq

	auto camaObj = CreateShape(physx::PxBoxGeometry(30, 5, 20));
	Particle* cama = new Particle({ 30,45,7 }, { 0,0,0 }, { 0,0,0 }, 0, -1, camaObj, { 1, 0, 0, 1 }, 1);

	auto almObj = CreateShape(physx::PxBoxGeometry(10, 1, 20));
	Particle* almohada = new Particle({ 15,50,7 }, { 0,0,0 }, { 0,0,0 }, 0, -1, almObj, { 1, 1, 1, 1 }, 1);

	auto mObj = CreateShape(physx::PxBoxGeometry(4, 1, 10));
	Particle* m1 = new Particle({ 146,62,-7 }, { 0,0,0 }, { 0,0,0 }, 0, -1, mObj, { 0.5, 0.2, 0.0, 1 }, 1);
	pSystem->creaBolaNieve(Vector3(146, 67, -7));

	auto mObj1 = CreateShape(physx::PxBoxGeometry(10, 1, 4));
	Particle* m2 = new Particle({ 80,70,-146 }, { 0,0,0 }, { 0,0,0 }, 0, -1, mObj1, { 0.5, 0.2, 0.0, 1 }, 1);

	auto mesaObj1 = CreateShape(physx::PxBoxGeometry(30, 2, 15));
	Particle* mesa = new Particle({ 80,60,138 }, { 0,0,0 }, { 0,0,0 }, 0, -1, mesaObj1, { 0.5, 0.2, 0.0, 1 }, 1);

	auto pataObj = CreateShape(physx::PxBoxGeometry(2, 15, 2));
	Particle* mesaPata1 = new Particle({ 100,45,142 }, { 0,0,0 }, { 0,0,0 }, 0, -1, pataObj, { 0.5, 0.2, 0.0, 1 }, 1);
	Particle* mesaPata2 = new Particle({ 56,45,142 }, { 0,0,0 }, { 0,0,0 }, 0, -1, pataObj, { 0.5, 0.2, 0.0, 1 }, 1);
	Particle* mesaPata3 = new Particle({ 100,45,128 }, { 0,0,0 }, { 0,0,0 }, 0, -1, pataObj, { 0.5, 0.2, 0.0, 1 }, 1);
	Particle* mesaPata4 = new Particle({ 56,45,128 }, { 0,0,0 }, { 0,0,0 }, 0, -1, pataObj, { 0.5, 0.2, 0.0, 1 }, 1);

	auto mesillaObj = CreateShape(physx::PxBoxGeometry(8, 6, 8));
	Particle* mesilla = new Particle({ 16,45,-27 }, { 0,0,0 }, { 0,0,0 }, 0, -1, mesillaObj, { 0.5, 0.2, 0.0, 1 }, 1);

	pSystem->creaLampara(Vector3(16, 54, -27));
	pSystem->creaPeces(Vector3(80, 70, 138));
}
void checkCamera() {

	//auto cam = GetCamera()->getTransform().p;
	//if (cam.y > techo->getPos().y) {
	//	//GetCamera()->handleMotion()
	//	//techo->getPos().y - 1;
	//	std::cout << "techo\n";
	//}
}
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
	gScene->setGravity(sceneDesc.gravity);

	//Plane as a solid rigid
	
	
	pSystem = new ParticleSystem();

	rbSystem = new RBSystem(gScene, gPhysics);


	crearHabitacion();
	
	//checkCamera();

	/*rbSystem->addUniformGenerator({ -150,0,-250 }, { 0,0,0 }, { 0,0,0 }, 10, 20, 1, 2, 1, 1,
		0.99f, 4000, { 1,0,0,1 }, { 8,8,8 }, 1, gScene, gPhysics, true, { 0.5, 0.5, 0.02 });*/
	
	//rbSystem->createRoom();
	
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
	//rbSystem->generatePerSeconds();
	rbSystem->update(t);
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
		pSystem->agitaBolaNieve();
		//pSystem->generateFireworkSystem(0);
		//bullet.push_back(new Proyectil(Proyectil::BULLET, GetCamera()->getTransform().p, GetCamera()->getDir(), {0.3,0.3,0.3,1}));

		//Sin gravedad
		//pSystem->creaFuente();
		////Gravedad
		//pSystem->creaFuenteGravedad({ 0,-10.0,0 }, { 15,50,7 }, { 0.9,0.1,0.47,1 }, 1);
		////Gravedad y dir
		//pSystem->creaFuenteGravedad({ 0,2.0,0 }, { 23,50,7 }, { 1,0.5,0,1 }, 1);
		////Gravedad y masa
		//pSystem->creaFuenteGravedad({ 0,-10.0,0 }, { 30,50,7 }, { 0,0.8,0.3,1 }, 10);

		break;
	case '2':
		//pSystem->generateFireworkSystem(1);
		//bullet.push_back(new Proyectil(Proyectil::CANNON, GetCamera()->getTransform().p, GetCamera()->getDir(), { 0.2,0.2,0.2,1 }));

		//viento
		//pSystem->creaViento();
		break;
	case '3':
		//pSystem->generateFireworkSystem(2);
		//bullet.push_back(new Proyectil(Proyectil::FIREBALL, GetCamera()->getTransform().p, GetCamera()->getDir(), {0.9,0.1,0.2,1}));
		//pSystem->creaTornado();
		break;
	case '4':
		//pSystem->generateFireworkSystem(3);
		//bullet.push_back(new Proyectil(Proyectil::BULLET, GetCamera()->getTransform().p, GetCamera()->getDir(), {0.3,0.3,0.3,1}));
		//pSystem->creaExplosion();
		break;
	case '5':
	
		//pSystem->muelleFijo();
		//pSystem->deactivateSpringWind();
		break;
	//case '6': //desactiva viento muelle
	//	pSystem->deactivateSpringWind();
	//	break;
	case '6': //activa viento muelle
		
		//pSystem->activaViento();
		break;
	case '7':
		//pSystem->muelleDoble();
		break;
	case '8':
		//pSystem->gomaElastica();
		break;
	case '9':
		//pSystem->flotaTest();
		break;
	case '0':
		//pSystem->creaSlinky();
		break;
	case 'X':
		//pSystem->addK();
		break;
	case 'C':
		//pSystem->subK();
		break;
	case 'O':
		
		break;
	case 'P':
		
		//rbSystem->deactivateWind();

	break;
	case 'I':

		//rbSystem->activateWind();

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