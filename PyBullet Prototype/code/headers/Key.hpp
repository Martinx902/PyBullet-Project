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
	 * @brief Represents a Key entity in the scene, inheriting from Entity and Message_Listener.
	 */
	class Key : public Entity, public Message_Listener
	{
		btVector3 position; ///< The position of the key in the scene.

	public:
		/**
		 * @brief Constructor for the Key class.
		 *
		 * @param given_scene Pointer to the parent scene.
		 * @param given_position Position of the key in the scene.
		 */
		Key(Scene* given_scene, btVector3 given_position);

		/**
		 * @brief Initializes the key, setting up its configurations and visuals.
		 */
		void initialize() override;

		/**
		 * @brief When it interacts with the tank it sends a message to deactivate the collisions and visuals of the key.
		 *
		 * @param message The message to handle.
		 */
		void handle(const Message& message) override;
	};
}