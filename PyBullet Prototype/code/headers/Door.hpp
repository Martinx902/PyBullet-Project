/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include "Entity.hpp"
#include "Message_Listener.hpp"

namespace Mgine3D
{
	/**
	 * @brief Represents a Door entity in the scene, inheriting from Entity and Message_Listener.
	 */
	class Door : public Entity, public Message_Listener
	{
		bool open;                   ///< Indicates whether the door is open or closed.

		btVector3 position;          ///< The position where the door is positioned in the scene
		btVector3 scale;             ///< The scale of the door.

	public:

		/**
		 * @brief Constructor for the Door class.
		 *
		 * @param given_scene Pointer to the parent scene.
		 * @param given_position Position of the door in the scene.
		 * @param given_scale Scale of the door.
		 */
		Door(Scene* given_scene, btVector3 given_position, btVector3 given_scale);

		/**
		 * @brief Initializes the door, setting up its Bullet Physics configurations and visuals.
		 */
		void initialize() override;

		/**
		 * @brief Checks to see if the door is open to move it out of the way.
		 *
		 * @param delta_time Time elapsed since the last update.
		 */
		void update(float delta_time) override;

		/**
		 * @brief When the tank interacts with the key it sends a message to open the door
		 *
		 * @param message The message to handle.
		 */
		void handle(const Message& message) override;

		/**
		 * @brief Sets the flag to true so the update can move the door.
		 */
		void open_door()
		{
			open = true;
		}
	};
}