/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#include "../headers/Key.hpp"
#include "../headers/Scene.hpp"
#include "../headers/CollsionsID.hpp"

#include <btBulletDynamicsCommon.h>

#include <Model_Obj.hpp>
#include <Model.hpp>

namespace Mgine3D
{
	Key::Key(Scene* given_scene, btVector3 given_position)
		:
		Entity(given_scene),
		position(given_position)
	{
		initialize();

		scene->get_message_dispatcher()->add(*this, "doorTrigger");
	}

	void Key::initialize()
	{
		std::shared_ptr<btCollisionShape> shape(new btBoxShape(btVector3(1, 1, 1)));

		shape->setLocalScaling(btVector3(1, 1, 1));

		shape->setUserIndex(int(CollisionsID::KEY_ID));

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(position);

		std::shared_ptr<btDefaultMotionState> motionState(new btDefaultMotionState(transform));

		btVector3 localInertia(0, 0, 0);

		shape->calculateLocalInertia(0.f, localInertia);

		btRigidBody::btRigidBodyConstructionInfo rbInfo(0, motionState.get(), shape.get(), localInertia);

		std::shared_ptr<btRigidBody> body(new btRigidBody(rbInfo));

		//This should be using Ghost Objects for the triggers but since its not that recurrent and the vectors from Entity are RB this is mainly the same.
		//And since the RB are also static it should not be a burden for the world to process the physics anyways.

		//Discard any physical contact
		body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);

		body->setRestitution(1.0f);

		scene->get_dynamics_world()->addRigidBody(body.get());

		// Save the smart pointers for automatic cleanup.

		rigidBodies.push_back(body);
		motionStates.push_back(motionState);
		collisionShapes.push_back(shape);

		//Model

		std::shared_ptr< glt::Model > key(new glt::Model_Obj("../../assets/key.obj"));

		key->get_pieces().front().material->set("material_color", glt::Vector3(0.7f, 0.7f, 0.f));

		models.push_back(key);

		scene->get_render_node()->add("key", key);
	}

	void Key::handle(const Message& message)
	{
		//Dissable the collisions and visuals of the key once taken

		if (message.trigger == "doorTrigger")
		{
			rigidBodies[0]->setCollisionFlags(rigidBodies[0]->getCollisionFlags() | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
			models[0]->set_visible(false);
		}
	}
}