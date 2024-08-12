/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#include "../headers/Scene.hpp"
#include "../headers/Bullet.hpp"

#include <Model_Obj.hpp>
#include <Model.hpp>
#include <Cube.hpp>

namespace Mgine3D
{
	Bullet::Bullet(Scene* given_scene, float given_shoot_force, btVector3 given_shoot_position, int given_bullet_id, btVector3 given_cannon_position)
		:
		Entity(given_scene),
		shoot_force(given_shoot_force),
		shoot_position(given_shoot_position),
		life_span(5.f),
		bullet_id(given_bullet_id),
		cannon_position(given_cannon_position)
	{
		shoot_bullet();
	}

	void Bullet::update(float delta_time)
	{
		static float actual_life_time = life_span;

		if (actual_life_time <= 0.f)
			destroy_bullet();
		else
			actual_life_time -= delta_time;
	}

	void Bullet::shoot_bullet()
	{
		btScalar mass = 1.0f;
		btVector3 localInertia(0, 0, 0);
		std::shared_ptr< btCollisionShape > shape(new btSphereShape(1));

		shape->setLocalScaling(btVector3(0.5f, 0.5f, 0.5f));

		shape->calculateLocalInertia(mass, localInertia);

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(shoot_position);
		std::shared_ptr< btDefaultMotionState > motionState(new btDefaultMotionState(transform));

		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState.get(), shape.get(), localInertia);
		std::shared_ptr< btRigidBody > rigidBody(new btRigidBody(rigidBodyCI));

		rigidBody->setRestitution(0.1f);

		rigidBody->setActivationState(DISABLE_DEACTIVATION);

		scene->get_dynamics_world()->addRigidBody(rigidBody.get());

		btVector3 targetPosition = rigidBody->getCenterOfMassPosition();

		btVector3 direction = targetPosition - cannon_position;

		direction.normalize();

		btVector3 impulse = direction * shoot_force;

		rigidBody->applyCentralImpulse(impulse);

		rigidBodies.push_back(rigidBody);
		motionStates.push_back(motionState);
		collisionShapes.push_back(shape);

		//Model

		std::shared_ptr< glt::Model > sphere(new glt::Model_Obj("../../assets/sphere.obj"));

		sphere->get_pieces().front().material->set("material_color", glt::Vector3(0.7f, 0.7f, 0.f));

		models.push_back(sphere);

		scene->get_render_node()->add(std::to_string(bullet_id), sphere);
	}

	void Bullet::destroy_bullet()
	{
		//TODO: Añadir la bala a una lista para quitar las balas después del render y update.

		//Eso por algún motivo da problemas, hace que después de la primera bala el resto no funcionen
		//No se muy bien como manejarlo sin usar una pool

		//scene->get_dynamics_world()->removeRigidBody(rigidBodies[0].get());
		//models[0]->set_visible(false);
	}
}