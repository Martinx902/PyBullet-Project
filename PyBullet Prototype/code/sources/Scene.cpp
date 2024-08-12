/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#include <Camera.hpp>
#include <Light.hpp>

#include "../headers/Scene.hpp"

namespace Mgine3D
{
	Scene::Scene(sf::Window* given_window)
		:
		window(given_window),
		customCollisionDispatcher(new CollisionDispatcher(this)),
		collisionDispatcher(&collisionConfiguration),
		dynamicsWorld
		(
			&collisionDispatcher,
			&overlappingPairCache,
			&constrainSolver,
			&collisionConfiguration
		),
		render_node(new glt::Render_Node)
	{
		initialize_scene();

		message_dispatcher = new Message_Dispatcher();

		window->setVerticalSyncEnabled(true);

		dynamicsWorld.setGravity(btVector3(0, -10, 0));

		exit = false;

		glClearColor(0.3f, 0.3f, 0.6f, 1.f);
	}

	void Scene::run()
	{
		exit = false;

		const float target_fps = 60.f;
		const float target_time = 1.f / target_fps;

		float delta_time = target_time;

		sf::Clock timer;

		reset_viewport();

		do
		{
			timer.restart();

			//Window events
			process_events();

			//Physics update
			dynamicsWorld.stepSimulation(delta_time);

			//Rendering SFML
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			update_entities(delta_time);

			render_entities();

			render_node->render();

			//Check for collisions

			customCollisionDispatcher->check_collisions();

			//Send messages

			message_dispatcher->execute();

			window->display();

			//Updating the timer and stopping for a few frames if we are execing the desired framerate
			float elapsed = timer.getElapsedTime().asSeconds();

			if (elapsed < target_time)
			{
				sf::sleep(sf::seconds(target_time - elapsed));
			}

			delta_time = timer.getElapsedTime().asSeconds();
		} while (!exit);
	}

	void Scene::process_events()
	{
		sf::Event event;

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				exit = true;
			}
		}
	}

	void Scene::update_entities(float delta_time)
	{
		for (auto& item : entities)
		{
			item.second->update(delta_time);
		}
	}

	void Scene::render_entities()
	{
		for (auto& item : entities)
		{
			item.second->render();
		}
	}

	void Scene::reset_viewport()
	{
		GLsizei width = GLsizei(window->getSize().x);
		GLsizei height = GLsizei(window->getSize().y);

		render_node->get_active_camera()->set_aspect_ratio(float(width) / height);

		glViewport(0, 0, width, height);
	}

	void Scene::initialize_scene()
	{
		for (auto& item : entities)
		{
			item.second->initialize();
		}
	}

	Scene::~Scene()
	{
		delete customCollisionDispatcher;
		delete message_dispatcher;
	}
}