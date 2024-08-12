/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include "Entity.hpp"

namespace Mgine3D
{
	/**
	 * @brief Represents the Terrain in the scene, inheriting from Entity.
	 */
	class Terrain : public Entity
	{
	public:
		/**
		 * @brief Constructor for the Terrain class.
		 *
		 * @param given_scene Pointer to the parent scene.
		 */
		Terrain(Scene* given_scene) : Entity(given_scene)
		{
			initialize();
		}

		/**
		 * @brief Initializes the terrain, setting up its platforms, doors and cubes.
		 */
		void initialize() override;

	private:

		/**
		 * @brief Creates a static platform on the terrain.
		 *
		 * @param position Position of the platform.
		 * @param scale Scale of the platform.
		 * @param id Identifier for the platform.
		 */
		void create_platform(btVector3 position, btVector3 scale, const std::string& id);

		/**
		 * @brief Creates a dynamic cube on the terrain.
		 *
		 * @param position Position of the cube.
		 * @param id Identifier for the cube.
		 */
		void create_cube(const btVector3& position, const std::string& id);
	};
}