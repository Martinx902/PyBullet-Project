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
	 * @brief Represents a moving Platform entity in the scene, inheriting from Entity.
	 */
	class Platform : public Entity
	{
		btVector3 scale;            ///< The scale of the platform.
		btVector3 initial_position; ///< The initial position of the platform.
		btVector3 final_position;   ///< The final position of the platform.

		btScalar platform_speed;    ///< The speed at which the platform moves.

	public:
		/**
		 * @brief Constructor for the Platform class.
		 *
		 * @param given_scene Pointer to the parent scene.
		 * @param given_position Initial position of the platform.
		 * @param given_final_position Final position of the platform.
		 * @param given_scale Scale of the platform.
		 * @param given_platform_speed Speed at which the platform moves.
		 */
		Platform(Scene* given_scene, btVector3 given_position, btVector3 given_final_position, btVector3 given_scale, btScalar given_platform_speed);

		/**
		 * @brief Initializes the platform, setting up its configurations and visuals.
		 */
		void initialize() override;

		/**
		 * @brief Updates the platform's position based on the elapsed time going the initial X position to the final X positions back and force.
		 *
		 * @param delta_time Time elapsed since the last update.
		 */
		void update(float delta_time) override;
	};
}