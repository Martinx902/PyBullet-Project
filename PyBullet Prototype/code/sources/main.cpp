/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

 /* -- -- -- -- --  -- -- -- -- -- -- -- -- +\
 |				  							 |
 |	  TO OPEN THE DOOR, TURN THE CANNON	     |
 |	  TO THE KEY ON YOUR LEFT.			     |
 |											 |
 \+ -- -- -- -- --  -- -- -- -- -- -- -- -- */

 /* -- -- -- -- --  -- -- -- -- -- -- -- -- +\
 |				  							 |
 |					CONTROLS				 |
 |											 |
 |	 LEFT/RIGHT ARROW -> AIM HORIZONTALLY	 |
 |	 UP/DOWN ARROW -> AIM VERTICALLY		 |
 |	 Q -> SHOOT								 |
 |											 |
 \+ -- -- -- -- --  -- -- -- -- -- -- -- -- */

#include "../headers/Key.hpp"
#include "../headers/Door.hpp"
#include "../headers/Tank.hpp"
#include "../headers/Scene.hpp"
#include "../headers/Camera.hpp"
#include "../headers/Entity.hpp"
#include "../headers/Terrain.hpp"
#include "../headers/Platform.hpp"

#include <memory>
#include <vector>
#include <iostream>

#include <Light.hpp>

#include <SFML/Window.hpp>
#include <btBulletDynamicsCommon.h>

using namespace std;
using namespace glt;

using namespace Mgine3D;

void create_tank(Mgine3D::Scene& scene)
{
	//INITIAL POSITION, MOVEMENT SPEED, AIMIGN SPEED, SHOOT FORCE

	auto tank = make_shared<Tank>(&scene, btVector3(-43.f, 3.f, -4.f), 1.f, 0.5f, 100.f);

	scene.add_entity("tank", tank);
}

void create_light(Mgine3D::Scene& scene)
{
	std::shared_ptr< glt::Light  > light(new glt::Light);

	light->set_color(glt::Vector3(0.5f, 0.5f, 0.5f));

	light->set_intensity(1.5f);

	scene.get_render_node()->add("light", light);

	light->translate(glt::Vector3(0.f, 20.f, 0.f));
}

void create_terrain(Mgine3D::Scene& scene)
{
	auto terrain = make_shared<Terrain>(&scene);

	scene.add_entity("terrain", terrain);
}

void create_camera(Mgine3D::Scene& scene)
{
	//FOV, NEAR, FAR, ASPECT RATION, POSITION, ROTATION

	//Close Up Camera
	//auto camera = make_shared<Mgine3D::Camera>(&scene, 20.f, 1.f, 100.f, 1.f, 0.f, 0.f, glt::Vector3(-43.f, 20.f, 10.f), glt::Vector3(-0.65f, 0.f, 0.f));

	//Main Camera
	auto camera = make_shared<Mgine3D::Camera>(&scene, 20.f, 1.f, 500.f, 1.f, 0.f, 0.f, glt::Vector3(-83.f, 20.f, -4.f), glt::Vector3(0.f, -1.5708f, 0.f));

	//Tank Camera
	//auto camera = make_shared<Mgine3D::Camera>(&scene, 20.f, 1.f, 500.f, 1.f, 0.f, 0.f, glt::Vector3(13.f, 25.f, -4.2f), glt::Vector3(-1.5708f, 0.f, 0.f));

	scene.add_entity("camera", camera);
}

void create_door(Mgine3D::Scene& scene)
{
	//POSITION, SCALE

	auto door = make_shared<Door>(&scene, btVector3(13.f, 7.f, -4.2f), btVector3(3.f, 10.f, 8.7f));

	scene.add_entity("door", door);
}

void create_platform(Mgine3D::Scene& scene)
{
	//INITIAL POSITION, FINAL POSITION, SCALE

	auto platform = make_shared<Platform>(&scene, btVector3(-11.f, 0.5f, -4.f), btVector3(-28.f, 0.5f, -4.f), btVector3(8.f, 2.f, 15.f), 0.05f);

	scene.add_entity("platform", platform);
}

void create_key(Mgine3D::Scene& scene)
{
	//INITIAL POSITION

	//Initial correct positon: btVector3(-45.f, 3.5f, -17.f)

	auto key = make_shared<Key>(&scene, btVector3(-43.f, 5.f, -10.f));

	scene.add_entity("key", key);
}

void configure_scene(Mgine3D::Scene& scene)
{
	create_light(scene);

	create_camera(scene);

	create_terrain(scene);

	create_door(scene);

	create_platform(scene);

	create_tank(scene);

	create_key(scene);
}

int main()
{
	/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
	|											SIMULATION											 |
	\+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

	sf::Window window(sf::VideoMode(1000, 700), "Bullet Tank", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(32));

	if (!glt::initialize_opengl_extensions())
	{
		exit(-1);
	}

	Scene scene(&window);

	configure_scene(scene);

	scene.run();

	return EXIT_SUCCESS;
}