/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#include "../headers/Scene.hpp"
#include "../headers/Terrain.hpp"

#include <Model.hpp>
#include <Cube.hpp>

namespace Mgine3D
{
	void Terrain::initialize()
	{
		//3 Ground Platforms

		btVector3 platform_scale = btVector3(10.f, 2.5f, 20.f);

		//RIGHT PLATFORM

		create_platform(btVector3(-45.f, 0.f, -4.f), platform_scale, "plat_1");

		rigidBodies[0]->getCollisionShape()->setUserIndex(10);

		//CENTER PLATFORM

		create_platform(btVector3(7.f, 0.f, -4.f), platform_scale, "plat_2");

		//LEFT PLATFORM

		create_platform(btVector3(40.f, 0.f, -4), platform_scale, "plat_3");

		//2 Walls

		//RIGTH WALL

		create_platform(btVector3(13.f, 7.f, -18.f), btVector3(0.2f, 4.f, 5.5f), "wall_1");

		//LEFT WALL

		create_platform(btVector3(13.f, 7.f, 10.f), btVector3(0.2f, 4.f, 5.5f), "wall_2");

		//3 Cubes Stacks

		//FIRST IS THE FURTHEST

		btScalar cube_stacks_height = 4;

		btVector3 initial_stack_position = btVector3(42.f, 0.75f, -11.f);

		for (size_t i = 0; i < cube_stacks_height; i++)
		{
			btScalar z_difference = 0;

			create_cube(btVector3(initial_stack_position.x(), i + initial_stack_position.y(), initial_stack_position.z() + z_difference), "stack_1_" + std::to_string(i));

			z_difference += 7;

			create_cube(btVector3(initial_stack_position.x(), i + initial_stack_position.y(), initial_stack_position.z() + z_difference), "stack_2_" + std::to_string(i));

			z_difference += 7;

			create_cube(btVector3(initial_stack_position.x(), i + initial_stack_position.y(), initial_stack_position.z() + z_difference), "stack_3_" + std::to_string(i));
		}
	}

	void Terrain::create_cube(const btVector3& position, const std::string& id)
	{
		std::shared_ptr< btRigidBody > cube_body;

		std::shared_ptr< btCollisionShape > shape(new btBoxShape(btVector3(1, 1, 1)));

		shape->setLocalScaling(btVector3(1, 1, 1));

		// Create Dynamic Objects.

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(position);

		btScalar  mass = 1.f;
		btVector3 localInertia(0, 0, 0);

		shape->calculateLocalInertia(mass, localInertia);

		std::shared_ptr< btDefaultMotionState >       state(new btDefaultMotionState(transform));
		btRigidBody::btRigidBodyConstructionInfo info(mass, state.get(), shape.get(), localInertia);

		cube_body.reset(new btRigidBody(info));

		cube_body->setRestitution(0.1f);

		cube_body->setActivationState(DISABLE_DEACTIVATION);

		scene->get_dynamics_world()->addRigidBody(cube_body.get());

		// Save the smart pointers for automatic cleanup.

		rigidBodies.push_back(cube_body);
		motionStates.push_back(state);
		collisionShapes.push_back(shape);

		//Model

		std::shared_ptr< glt::Model > cube(new glt::Model);
		cube->add(std::shared_ptr<glt::Drawable>(new glt::Cube), glt::Material::default_material());

		cube->get_pieces().front().material->set("material_color", glt::Vector3(0.5f, 0.2f, 0.4f));

		models.push_back(cube);
		scene->get_render_node()->add(id, cube);
	}

	void Terrain::create_platform(btVector3 position, btVector3 scale, const std::string& id)
	{
		//CREATES A STATIC RIGIDBODY

		std::shared_ptr< btRigidBody > platform_body;

		std::shared_ptr< btCollisionShape > shape(new btBoxShape(btVector3(1, 1, 1)));

		shape->setLocalScaling(scale);

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(position);

		std::shared_ptr< btDefaultMotionState >  state(new btDefaultMotionState(transform));
		btRigidBody::btRigidBodyConstructionInfo info(0, state.get(), shape.get());
		platform_body.reset(new btRigidBody(info));

		platform_body->setRestitution(1.f);

		platform_body->setActivationState(DISABLE_DEACTIVATION);

		scene->get_dynamics_world()->addRigidBody(platform_body.get());

		// Save the smart pointers for automatic cleanup.

		rigidBodies.push_back(platform_body);
		motionStates.push_back(state);
		collisionShapes.push_back(shape);

		//Model

		std::shared_ptr< glt::Model > cube(new glt::Model);
		cube->add(std::shared_ptr<glt::Drawable>(new glt::Cube), glt::Material::default_material());

		cube->get_pieces().front().material->set("material_color", glt::Vector3(0.2f, 0.4f, 0.2f));

		models.push_back(cube);
		scene->get_render_node()->add(id, cube);
	}
}