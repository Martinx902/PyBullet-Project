/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

namespace Mgine3D
{
	class Scene;

	/**
	 * @brief Manages collision detection within the scene.
	 */
	class CollisionDispatcher
	{
		Scene* scene; ///< Pointer to the scene to manage collisions in.

	public:

		/**
		 * @brief Constructor for the CollisionDispatcher class.
		 *
		 * @param given_scene Pointer to the scene to manage collisions in.
		 */
		CollisionDispatcher(Scene* given_scene) : scene(given_scene) {}

		/**
		 * @brief Checks for collisions within the scene and handles them, checking Collisions ID and sending messages when 2 objects collide with each other.
		 */
		void check_collisions();
	};
}