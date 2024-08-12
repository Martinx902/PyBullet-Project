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
	 * @brief Represents a dynamic rigidbody impulsed with a force in the scene, inheriting from Entity.
	 */
	class Bullet : public Entity
	{
		int bullet_id;                 ///< The unique identifier for the bullet, used to add it to scene map of entites and to the render node.
		float life_span;               ///< The lifespan of the bullet.
		float shoot_force;             ///< The force with which the bullet is shot.
		btVector3 shoot_position;      ///< The position from where the bullet is shot.
		btVector3 cannon_position;     ///< The position of the cannon that shot the bullet, to get the direction of the bullet force.

	public:

		/**
		 * @brief Constructor for the Bullet class.
		 *
		 * @param given_scene Pointer to the parent scene.
		 * @param given_shoot_force Force with which the bullet is shot.
		 * @param given_shoot_position Position from where the bullet is shot.
		 * @param given_bullet_id Unique identifier for the bullet.
		 * @param given_cannon_position Position of the cannon that shot the bullet.
		 */
		Bullet(Scene* given_scene, float given_shoot_force, btVector3 given_shoot_position, int given_bullet_id, btVector3 given_cannon_position);

		/**
		 * @brief Checks the life span of the bullet and sees if its out of time to destroy it so it doesnt consume more memory.
		 *
		 * @param delta_time Time elapsed since the last update.
		 */
		void update(float delta_time) override;

	private:

		/**
		 * @brief Shoots the bullet from the specified position with the specified force.
		 */
		void shoot_bullet();

		/**
		 * @brief Destroys the bullet when its lifespan ends or when it hits a target.
		 */
		void destroy_bullet();
	};
}