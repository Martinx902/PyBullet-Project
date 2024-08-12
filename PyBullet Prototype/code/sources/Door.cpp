/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#include "../headers/Door.hpp"
#include "../headers/Scene.hpp"

#include <Model_Obj.hpp>
#include <Cube.hpp>
#include <Model.hpp>

namespace Mgine3D
{
	Door::Door(Scene* given_scene, btVector3 given_position, btVector3 given_scale)
		: Entity(given_scene), open(false), position(given_position), scale(given_scale)
	{
		initialize();

		scene->get_message_dispatcher()->add(*this, "doorTrigger");
	}

	void Door::initialize()
	{
		std::shared_ptr<btCollisionShape> shape(new btBoxShape(btVector3(1, 1, 1)));

		shape->setLocalScaling(scale);

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(position);

		std::shared_ptr<btDefaultMotionState> motionState(new btDefaultMotionState(transform));

		btVector3 localInertia(0, 0, 0);

		shape->calculateLocalInertia(1.f, localInertia);

		btRigidBody::btRigidBodyConstructionInfo rbInfo(0, motionState.get(), shape.get(), localInertia);

		std::shared_ptr<btRigidBody> body(new btRigidBody(rbInfo));

		body->setRestitution(0.2f);

		scene->get_dynamics_world()->addRigidBody(body.get());

		// Save the smart pointers for automatic cleanup.

		rigidBodies.push_back(body);
		motionStates.push_back(motionState);
		collisionShapes.push_back(shape);

		//Model

		std::shared_ptr< glt::Model > door(new glt::Model_Obj("../../assets/newDoor.obj"));

		door->get_pieces().front().material->set("material_color", glt::Vector3(0.5f, 0.2f, 0.f));

		models.push_back(door);

		scene->get_render_node()->add("door", door);
	}

	void Door::update(float delta_time)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			open_door();
		}

		if (open)
		{
			if (rigidBodies[0]->getWorldTransform().getOrigin().getY() > -10.f)
			{
				btTransform newTrans;

				rigidBodies[0]->getMotionState()->getWorldTransform(newTrans);

				newTrans.getOrigin().setY(newTrans.getOrigin().getY() - 0.2f);

				rigidBodies[0]->setWorldTransform(newTrans);
				rigidBodies[0]->getMotionState()->setWorldTransform(newTrans);
			}
			else
				open = false;
		}
	}

	void Door::handle(const Message& message)
	{
		if (message.trigger == "doorTrigger")
			open_door();
	}
}