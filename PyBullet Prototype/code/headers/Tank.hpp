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
 * @brief Represents a Tank entity in the scene, inheriting from Entity.
 */
	class Tank : public Entity
	{
		btVector3 initial_position; ///< The initial position of the tank.

		float movement_speed;       ///< The movement speed of the tank.
		float aiming_speed;         ///< The speed at which the tank's cannon aims.
		float shoot_force;          ///< The force with which the tank shoots.

		std::vector<std::shared_ptr<btHingeConstraint>> wheel_constraints; ///< Constraints for the tank's wheels.
		std::vector<std::shared_ptr<btHingeConstraint>> cannon_constraints; ///< Constraints for the tank's cannon.

		// rb[0] = chassis
		// rb[1] = turret
		// rb[2] = cannon
		// rb[3] = right wheel
		// rb[4] = left wheel

		// cannon_constraints[0] = turret (union with the chassis)
		// cannon_constraints[1] = cannon (union with the turret)

		// wheel_constraints[0] = right wheel (union with the chassis)
		// wheel_constraints[1] = left wheel (union with the chassis)

	public:

		/**
		 * @brief Constructor for the Tank class.
		 *
		 * @param given_scene Pointer to the parent scene.
		 * @param given_initial_position Initial position of the tank.
		 * @param given_movement_speed Movement speed of the tank.
		 * @param given_aiming_speed Speed at which the cannon aims.
		 * @param given_shoot_force Force with which the tank shoots.
		 */
		Tank(Scene* given_scene, btVector3 given_initial_position, float given_movement_speed, float given_aiming_speed, float given_shoot_force);

		/**
		 * @brief Initializes the tank, setting up its configurations and visuals. Chasis, Turret and Cannon.
		 */
		void initialize() override;

		/**
		 * @brief Creates a cube for the tank's components with a given ID. Basic cube Bullet py creation.
		 *
		 * @param width Width of the cube.
		 * @param height Height of the cube.
		 * @param length Length of the cube.
		 * @param position Position of the cube.
		 * @param id Identifier for the cube.
		 * @param dynamic Whether the cube is dynamic.
		 */
		void create_cube(btScalar& width, btScalar& height, btScalar& length, btVector3 position, const std::string& id, bool dynamic);

		/**
		 * @brief Listen for inputs of the player.
		 *
		 * @param delta_time Time elapsed since the last update.
		 */
		void update(float delta_time) override;

	private:

		/**
		 * @brief Aims the cannon horizontally, rotating it along the Y axis.
		 *
		 * @param direction Direction to aim the cannon.
		 */
		void aim_cannon_horizontal(int direction);

		/**
		 * @brief Aims the cannon vertically, rotating it along the Z axis.
		 *
		 * @param direction Direction to aim the cannon.
		 */
		void aim_cannon_vertical(int direction);

		/**
		 * @brief Creates a bullet object with a given direction, force and position.
		 */
		void shoot();
	};
}