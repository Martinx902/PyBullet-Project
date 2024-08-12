/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include "Entity.hpp"

#include <Camera.hpp>

namespace Mgine3D
{
	/**
	 * @brief Represents a Camera entity in the scene, inheriting from Entity.
	 */
	class Camera : public Entity
	{
		std::shared_ptr<glt::Camera> camera; ///< Shared pointer to the GLT camera.

		glt::Vector3 position; ///< The position of the camera in the scene.
		glt::Vector3 rotation; ///< The rotation of the camera in the scene.

		float movement_speed; ///< The speed at which the camera moves.
		float rotation_speed; ///< The speed at which the camera rotates.

	public:

		/**
		 * @brief Constructor for the Camera class.
		 *
		 * @param scene Pointer to the parent scene.
		 * @param fov Field of view for the camera.
		 * @param near Near clipping plane.
		 * @param far Far clipping plane.
		 * @param aspect_ratio Aspect ratio of the camera.
		 * @param given_movement_speed Movement speed of the camera.
		 * @param given_rotation_speed Rotation speed of the camera.
		 * @param starting_position Initial position of the camera.
		 * @param starting_rotation Initial rotation of the camera.
		 */
		Camera
		(
			Scene* scene,
			float fov,
			float near,
			float far,
			float aspect_ratio,
			float given_movement_speed,
			float given_rotation_speed,
			glt::Vector3 starting_position,
			glt::Vector3 starting_rotation
		);

		/**
		 * @brief Updates the camera's position and rotation based on the elapsed time.
		 *
		 * @param delta_time Time elapsed since the last update.
		 */
		void update(float delta_time) override;

	private:

		/**
		 * @brief Processes the camera's movement.
		 *
		 * @param pos_y Y-axis position change.
		 * @param pos_x X-axis position change.
		 * @param pos_z Z-axis position change.
		 */
		void process_movement(float& pos_y, float& pos_x, float& pos_z);

		/**
		 * @brief Processes the camera's rotation.
		 *
		 * @param rot_x X-axis rotation change.
		 * @param rot_y Y-axis rotation change.
		 */
		void process_rotation(float& rot_x, float& rot_y);
	};
}