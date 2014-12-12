/*
 * Bullet Continuous Collision Detection and Physics Library
 * Copyright (c) 2003-2009 Erwin Coumans  http://bulletphysics.org
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 * Permission is granted to anyone to use this software for any purpose, 
 * including commercial applications, and to alter it and redistribute it freely, 
 * subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Copied and modified from btDiscreteDynamicsWorld.h by AndrewMeadows on 2014.11.12.
 * */

#ifndef hifi_ThreadSafeDynamicsWorld_h
#define hifi_ThreadSafeDynamicsWorld_h

#ifdef USE_BULLET_PHYSICS
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

class EntityTree;

ATTRIBUTE_ALIGNED16(class) ThreadSafeDynamicsWorld : public btDiscreteDynamicsWorld {
public:
    BT_DECLARE_ALIGNED_ALLOCATOR();

    ThreadSafeDynamicsWorld(
            btDispatcher* dispatcher,
            btBroadphaseInterface* pairCache,
            btConstraintSolver* constraintSolver,
            btCollisionConfiguration* collisionConfiguration,
            EntityTree* entities);

    // virtual overrides from btDiscreteDynamicsWorld
    int stepSimulation( btScalar timeStep, int maxSubSteps=1, btScalar fixedTimeStep=btScalar(1.)/btScalar(60.));
    void synchronizeMotionStates();

    // btDiscreteDynamicsWorld::m_localTime is the portion of real-time that has not yet been simulated
    // but is used for MotionState::setWorldTransform() extrapolation (a feature that Bullet uses to provide 
    // smoother rendering of objects when the physics simulation loop is ansynchronous to the render loop).
    float getLocalTimeAccumulation() const { return m_localTime; }

private:
    EntityTree* _entities;
};

#else // USE_BULLET_PHYSICS
// stubbery for ThreadSafeDynamicsWorld when Bullet not available
class ThreadSafeDynamicsWorld {
public:
    ThreadSafeDynamicsWorld() {}
};

#endif // USE_BULLET_PHYSICS

#endif // hifi_ThreadSafeDynamicsWorld_h
