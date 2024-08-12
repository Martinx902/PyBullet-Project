/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#include "../headers/Platform.hpp"
#include "../headers/Scene.hpp"

#include <Model.hpp>
#include <Cube.hpp>

namespace Mgine3D
{
	Platform::Platform(Scene* given_scene, btVector3 given_position, btVector3 given_final_position, btVector3 given_scale, btScalar given_platform_speed)
		:
		Entity(given_scene),
		initial_position(given_position),
		final_position(given_final_position),
		scale(given_scale),
		platform_speed(given_platform_speed)
	{
		initialize();
	}

	void Platform::initialize()
	{
		std::shared_ptr<btCollisionShape> shape(new btBoxShape(btVector3(1, 1, 1)));

		shape->setLocalScaling(scale);

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(initial_position);

		std::shared_ptr<btDefaultMotionState> motionState(new btDefaultMotionState(transform));

		btVector3 localInertia(0, 0, 0);

		shape->calculateLocalInertia(1.f, localInertia);

		btRigidBody::btRigidBodyConstructionInfo rbInfo(0, motionState.get(), shape.get(), localInertia);

		std::shared_ptr<btRigidBody> body(new btRigidBody(rbInfo));

		// Set the kinematic flag for the rigid body
		body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);

		body->setRestitution(1.0f);

		scene->get_dynamics_world()->addRigidBody(body.get());

		// Save the smart pointers for automatic cleanup.

		rigidBodies.push_back(body);
		motionStates.push_back(motionState);
		collisionShapes.push_back(shape);

		//Model

		std::shared_ptr< glt::Model > cube(new glt::Model);
		cube->add(std::shared_ptr<glt::Drawable>(new glt::Cube), glt::Material::default_material());

		cube->get_pieces().front().material->set("material_color", glt::Vector3(0.2f, 0.2f, 0.8f));

		models.push_back(cube);

		scene->get_render_node()->add("platform", cube);
	}

	void Platform::update(float delta_time)
	{
		btTransform newTrans;

		static int direction = 1;

		//Esto no funciona por algún motivo

		/*rigidBodies[0]->setLinearVelocity(btVector3(1, 0, 0));

		rigidBodies[0]->applyImpulse
		(
			btVector3(-platform_speed, rigidBodies[0]->getLinearVelocity().getY(), rigidBodies[0]->getLinearVelocity().getZ()),
			btVector3(1, 0, 0)
		);*/

		rigidBodies[0]->getMotionState()->getWorldTransform(newTrans);

		newTrans.getOrigin().setX(newTrans.getOrigin().getX() + (platform_speed * direction));

		if (rigidBodies[0]->getWorldTransform().getOrigin().getX() <= final_position.getX())
		{
			direction = 1;
		}

		if (rigidBodies[0]->getWorldTransform().getOrigin().getX() >= initial_position.getX())
		{
			direction = -1;
		}

		rigidBodies[0]->setWorldTransform(newTrans);
		rigidBodies[0]->getMotionState()->setWorldTransform(newTrans);
	}
}