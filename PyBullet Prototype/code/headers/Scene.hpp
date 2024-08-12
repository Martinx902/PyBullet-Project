/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include "Entity.hpp"

#include <map>
#include <memory>
#include <string>

#include "Message_Dispatcher.hpp"
#include "Message_Listener.hpp"

#include "CollisionDispatcher.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Render_Node.hpp>

namespace Mgine3D
{
	/**
	 * @brief Represents a Scene in the application, managing entities, physics simulation, and rendering.
	 */
	class Scene
	{
		std::map<std::string, std::shared_ptr<Entity>> entities;	///< Map of entities in the scene.

		Message_Dispatcher* message_dispatcher;						///< Manages message dispatching between listeners.

		CollisionDispatcher* customCollisionDispatcher;				///< Manages custom collision detection.

		btDefaultCollisionConfiguration		collisionConfiguration; ///< Default collision configuration.
		btCollisionDispatcher				collisionDispatcher;	///< Collision dispatcher.
		btDbvtBroadphase					overlappingPairCache;	///< Broadphase collision detection.
		btSequentialImpulseConstraintSolver constrainSolver;		///< Solver for constraints.
		btDiscreteDynamicsWorld				dynamicsWorld;			///< Dynamics world for physics simulation.

		std::shared_ptr<glt::Render_Node> render_node;				///< Render node for rendering entities.

		bool exit;													///< Flag indicating whether to exit the scene.

		sf::Window* window;											///< Pointer to the SFML render window.

	public:

		/**
		 * @brief Constructor for the Scene class.
		 *
		 * @param given_window Pointer to the SFML render window.
		 */
		Scene(sf::Window* given_window);

		/**
		 * @brief Runs the main loop of the scene, updating, rendering, and simulating physics.
		 */
		void run();

		/**
		 * @brief Adds an entity to the scene.
		 *
		 * @param id ID of the entity.
		 * @param entity Pointer to the entity object.
		 */
		void add_entity(const std::string& id, std::shared_ptr<Entity> entity)
		{
			if (!entities[id])
				entities[id] = entity;
		}

		/**
		 * @brief Adds a message listener to the message dispatcher.
		 *
		 * @param listener Reference to the listener object.
		 * @param id ID of the message to listen for.
		 */
		void add_message_listener(Message_Listener& listener, const std::string& id)
		{
			message_dispatcher->add(listener, id);
		}

		/**
		 * @brief Retrieves the message dispatcher.
		 *
		 * @return Pointer to the message dispatcher.
		 */
		Message_Dispatcher* get_message_dispatcher()
		{
			return message_dispatcher;
		}

		/**
		 * @brief Retrieves an entity from the scene by its ID.
		 *
		 * @param id ID of the entity to retrieve.
		 * @return Pointer to the entity if found, nullptr otherwise.
		 */
		std::shared_ptr<Entity> get_entity_by_id(const std::string& id)
		{
			return entities[id];
		}

		/**
		 * @brief Removes an object from the map based on the ID
		 *
		 * @param id ID of the entity to remove.
		 */
		void remove_entity_by_id(const std::string& id)
		{
			entities.erase(id);
		}

		/**
		 * @brief Retrieves a pointer to the SFML render window.
		 *
		 * @return Pointer to the render window.
		 */
		const sf::Window* get_window() const
		{
			return window;
		}

		/**
		 * @brief Retrieves a pointer to the SFML render window.
		 *
		 * @return Pointer to the render window.
		 */
		sf::Window* get_window()
		{
			return window;
		}

		/**
		 * @brief Retrieves a pointer to the dynamics world.
		 *
		 * @return Pointer to the dynamics world.
		 */
		btDiscreteDynamicsWorld* get_dynamics_world()
		{
			return &dynamicsWorld;
		}

		/**
		 * @brief Retrieves a pointer to the render node.
		 *
		 * @return Pointer to the render node.
		 */
		std::shared_ptr<glt::Render_Node> get_render_node()
		{
			return render_node;
		}

		/**
		 * @brief Destroys the new pointers created at the constructor
		 *
		 */
		~Scene();

	private:

		/**
		 * @brief Calls the initialize method of all entities in the scene to create the visuals and configurations.
		 */
		void initialize_scene();

		/**
		 * @brief Processes events such as user inputs.
		 */
		void process_events();

		/**
		 * @brief Updates all entities in the scene with the virtual method of the father.
		 *
		 * @param delta_time Time elapsed since the last update.
		 */
		void update_entities(float delta_time);

		/**
		 * @brief Renders all entities in the scene with the virtual method of the father.
		 */
		void render_entities();

		/**
		 * @brief Resets the viewport.
		 */
		void reset_viewport();
	};
}