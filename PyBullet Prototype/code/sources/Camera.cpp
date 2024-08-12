/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#include "../headers/Camera.hpp"
#include "../headers/Scene.hpp"

namespace Mgine3D
{
	Camera::Camera(Scene* scene, float fov, float near, float far, float aspect_ratio, float given_movement_speed, float given_rotation_speed, glt::Vector3 startin_position, glt::Vector3 starting_rotation)
		:
		Entity(scene),
		camera(new glt::Camera(fov, near, far, aspect_ratio)),
		movement_speed(given_movement_speed),
		rotation_speed(given_rotation_speed),
		position(startin_position),
		rotation(starting_rotation)
	{
		camera->translate(position);

		camera->rotate_around_x(rotation.x);
		camera->rotate_around_y(rotation.y);
		camera->rotate_around_z(rotation.z);

		scene->get_render_node()->add("camera", camera);
	}

	void Camera::update(float delta_time)
	{
		static float pos_x = position.x;
		static float pos_y = position.y;
		static float pos_z = position.z;

		static float rot_x = rotation.x;
		static float rot_y = rotation.y;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			position.x = position.y = position.z = 0;
			rotation.x = rotation.y = 0;
		}

		process_movement(pos_y, pos_x, pos_z);

		process_rotation(rot_x, rot_y);

		//Aplicar rotaciones y movimiento pero con el código del glt es un poco engorroso entonces se deja para luego
	}
	void Camera::process_movement(float& pos_y, float& pos_x, float& pos_z)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			pos_y -= movement_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			pos_x -= movement_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			pos_y += movement_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			pos_x += movement_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			pos_z += movement_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			pos_z -= movement_speed;
		}
	}

	void Camera::process_rotation(float& rot_x, float& rot_y)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			rot_x -= rotation_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			rot_x += rotation_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			rot_y -= rotation_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			rot_y += rotation_speed;
		}
	}
}