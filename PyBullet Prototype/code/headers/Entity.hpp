/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include <Node.hpp>
#include <btBulletDynamicsCommon.h>

#include <memory>
#include <vector>

namespace Mgine3D
{
	class Scene;

	/**
	 * @brief Represents an Entity in the scene, an actor that can be rendered and have behaviors.
	 */
	class Entity
	{
	protected:

		Scene* scene; ///< Pointer to the parent scene.

		std::vector<std::shared_ptr<glt::Node>> models;                  ///< Vector of OpenGL Toolkit models associated with the entity.
		std::vector<std::shared_ptr<btRigidBody>> rigidBodies;           ///< Vector of Bullet rigid bodies associated with the entity.
		std::vector<std::shared_ptr<btDefaultMotionState>> motionStates; ///< Vector of motion states associated with the entity.
		std::vector<std::shared_ptr<btCollisionShape>> collisionShapes;  ///< Vector of collision shapes associated with the entity.

	public:

		/**
		 * @brief Constructor for the Entity class.
		 *
		 * @param given_scene Pointer to the parent scene.
		 */
		Entity(Scene* given_scene) : scene(given_scene) {}

		/**
		 * @brief Virtual function to initialize the entity.
		 */
		virtual void initialize() {}

		/**
		 * @brief Virtual function to update the entity.
		 *
		 * @param delta_time Time elapsed since the last update.
		 */
		virtual void update(float delta_time) {}

		/**
		 * @brief Virtual function to render the entity. It has a base render given that its mostly the same code for everything.
		 */
		virtual void render();
	};
}