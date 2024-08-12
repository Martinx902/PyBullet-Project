/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#include "../headers/Scene.hpp"
#include "../headers/Tank.hpp"
#include "../headers/CollsionsID.hpp"
#include "../headers/Bullet.hpp"

#include <Model_Obj.hpp>
#include <Model.hpp>
#include <Cube.hpp>

namespace Mgine3D
{
	Tank::Tank(Scene* given_scene, btVector3 given_initial_position, float given_movement_speed, float given_aiming_speed, float given_shoot_force)
		:
		movement_speed(given_movement_speed),
		initial_position(given_initial_position),
		aiming_speed(given_aiming_speed),
		shoot_force(given_shoot_force),
		Entity(given_scene)
	{
		initialize();
	}

	void Tank::initialize()
	{
		//----------------------------CHASIS----------------------------//

		btScalar chassisPosX = initial_position.getX();
		btScalar chassisPosY = initial_position.getY();
		btScalar chassisPosZ = initial_position.getZ();

		btScalar chassisWidth = 3.f;
		btScalar chassisHeight = 1.f;
		btScalar chassisLength = 2.5f;

		create_cube(chassisWidth, chassisHeight, chassisLength, initial_position, "chasis_cube", false);

		//----------------------------TURRET----------------------------//

		btScalar turretWidth = 1.5f;
		btScalar turretHeight = 1.2f;
		btScalar turretLength = 1.5f;

		btVector3 turretPosition = btVector3(initial_position.getX(), initial_position.getY() + turretHeight, initial_position.getZ());

		{
			create_cube(turretWidth, turretHeight, turretLength, turretPosition, "turret_cube", true);

			std::shared_ptr<btHingeConstraint> hingeConstraint
			(new btHingeConstraint(
				*rigidBodies[0],
				*rigidBodies[1],
				btVector3(0, chassisHeight, 0),   //PIVOT A
				btVector3(0, -turretHeight, 0),   //PIVOT B
				btVector3(0, 1, 0),  //AXIS A
				btVector3(0, 1, 0)	  //AXIS B
			)
			);

			hingeConstraint->enableMotor(true);

			hingeConstraint->setLimit(-1.5708f, 1.5708f);

			scene->get_dynamics_world()->addConstraint(hingeConstraint.get(), true);

			cannon_constraints.push_back(hingeConstraint);
		}

		//----------------------------CANNON----------------------------//

		{
			btScalar cannonWidth = 2.5f;
			btScalar cannonHeight = 0.2f;
			btScalar cannonLength = 0.1f;

			btVector3 cannonPosition = btVector3(turretPosition.getX() + cannonWidth, turretPosition.getY(), turretPosition.getZ());

			create_cube(cannonWidth, cannonHeight, cannonLength, cannonPosition, "cannon_cube", true);

			std::shared_ptr<btHingeConstraint> hingeConstraint2
			(new btHingeConstraint(
				*rigidBodies[1],
				*rigidBodies[2],
				btVector3(turretWidth, 0, 0),   //PIVOT A
				btVector3(-cannonWidth, 0, 0),  //PIVOT B
				btVector3(0, 0, 1),  //AXIS A
				btVector3(0, 0, 1)	 //AXIS B
			)
			);

			hingeConstraint2->enableMotor(true);

			hingeConstraint2->setLimit(-0.5f, 0.f);

			scene->get_dynamics_world()->addConstraint(hingeConstraint2.get(), true);

			cannon_constraints.push_back(hingeConstraint2);
		}

		//----------------------------WHEELS----------------------------//

		//Las ruedas por algún motivo, da igual cuantos valores añada y pruebe, sigue sin funcionar.
		//Ya no hay tiempo suficiente como para arreglarlo con tan poco margen. La documentación es
		//nefasta en respecto a esto y a como se crean los objetos.

		//{
		//	btScalar wheelWidth = 2.5f;
		//	btScalar wheelHeight = 1.f;
		//	btScalar wheelLength = 0.5f;

		//	// Calculate the position for the left wheel
		//	btVector3 leftWheelPos = btVector3
		//	(
		//		chassisPosX,
		//		chassisPosY - chassisHeight + wheelHeight,
		//		chassisPosZ - (chassisLength + wheelLength)
		//	);

		//	create_cube(wheelWidth, wheelHeight, wheelLength, leftWheelPos, "left_wheel");

		//	std::shared_ptr<btHingeConstraint> hingeConstraint3
		//	(new btHingeConstraint(
		//		*rigidBodies[0],
		//		*rigidBodies[3],
		//		btVector3(0, -chassisHeight / 2, -(chassisLength + wheelLength)),   //PIVOT A
		//		btVector3(0, 0, 0),  //PIVOT B
		//		btVector3(0, 1, 0),  //AXIS A
		//		btVector3(0, 1, 0)	 //AXIS B
		//	)
		//	);

		//	hingeConstraint3->enableMotor(true);

		//	hingeConstraint3->setLimit(-1.2f, 1.2f);

		//	scene->get_dynamics_world()->addConstraint(hingeConstraint3.get(), true);

		//	wheel_constrains.push_back(hingeConstraint3);

		//	// Calculate the position for the right wheel
		//	btVector3 rightWheelPos = btVector3
		//	(
		//		chassisPosX,
		//		chassisPosY - chassisHeight + wheelHeight,
		//		chassisPosZ + (chassisLength + wheelLength)
		//	);

		//	create_cube(wheelWidth, wheelHeight, wheelLength, rightWheelPos, "right_wheel");

		//	std::shared_ptr<btHingeConstraint> hingeConstraint4
		//	(new btHingeConstraint(
		//		*rigidBodies[0],
		//		*rigidBodies[4],
		//		btVector3(0, -chassisHeight / 2, (chassisLength + wheelLength)),   //PIVOT A
		//		btVector3(0, 0, 0),  //PIVOT B
		//		btVector3(0, 1, 0),  //AXIS A
		//		btVector3(0, 1, 0)	 //AXIS B
		//	)
		//	);

		//	hingeConstraint4->enableMotor(true);

		//	hingeConstraint4->setLimit(-1.6f, 1.6f);

		//	scene->get_dynamics_world()->addConstraint(hingeConstraint4.get(), true);

		//	wheel_constrains.push_back(hingeConstraint4);
		//}
	}

	void Tank::create_cube(btScalar& width, btScalar& height, btScalar& length, btVector3 position, const std::string& id, bool dynamic)
	{
		std::shared_ptr< btRigidBody > body;

		std::shared_ptr< btCollisionShape > shape(new btBoxShape(btVector3(1, 1, 1)));

		shape->setLocalScaling(btVector3(width, height, length));

		shape->setUserIndex(int(CollisionsID::TANK_ID));

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(position);

		btScalar mass = 5.f;

		if (!dynamic)
			mass = 0.f;

		btVector3 localInertia(0, 0, 0);

		shape->calculateLocalInertia(mass, localInertia);

		std::shared_ptr< btDefaultMotionState >  state(new btDefaultMotionState(transform));
		btRigidBody::btRigidBodyConstructionInfo info(mass, state.get(), shape.get(), localInertia);

		body.reset(new btRigidBody(info));

		body->setRestitution(0.3f);

		body->setActivationState(DISABLE_DEACTIVATION);

		// Add the body to the dynamics world.

		scene->get_dynamics_world()->addRigidBody(body.get());

		// Save the smart pointers for automatic cleanup.

		rigidBodies.push_back(body);
		motionStates.push_back(state);
		collisionShapes.push_back(shape);

		//Model

		std::shared_ptr< glt::Model > cube(new glt::Model);
		cube->add(std::shared_ptr<glt::Drawable>(new glt::Cube), glt::Material::default_material());

		models.push_back(cube);

		scene->get_render_node()->add(id, cube);
	}

	void Tank::update(float delta_time)
	{
		static float shootDelay = 0.5f;
		static float actualShootDelay = 0.f;
		static bool canShoot = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			aim_cannon_horizontal(1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			aim_cannon_horizontal(-1);
		}
		else
			aim_cannon_horizontal(0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			aim_cannon_vertical(-1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			aim_cannon_vertical(1);
		}
		else
			aim_cannon_vertical(0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (canShoot)
			{
				shoot();
				canShoot = false;
				actualShootDelay = shootDelay;
			}
		}

		if (actualShootDelay <= 0.f && !canShoot)
		{
			canShoot = true;
		}

		actualShootDelay -= delta_time;
	}

	void Tank::aim_cannon_horizontal(int direction)
	{
		cannon_constraints[0]->enableAngularMotor(true, 1.f * direction, 30.f);
	}

	void Tank::aim_cannon_vertical(int direction)
	{
		cannon_constraints[1]->enableAngularMotor(true, 1.f * direction, 30.f);
	}

	void Tank::shoot()
	{
		static int bulletIndex = 0;

		btQuaternion orientation = rigidBodies[2]->getOrientation();

		btMatrix3x3 rotationMatrix(orientation);

		btVector3 forwardVector = rotationMatrix.getColumn(0); // Assuming Z-axis is forward

		forwardVector.normalize();

		// Apply the offset to the position along the forward vector
		btVector3 shoot_position = rigidBodies[2]->getCenterOfMassPosition() + forwardVector * 3.f;

		std::shared_ptr< Bullet >  bullet(new Bullet(scene, shoot_force, shoot_position, bulletIndex, rigidBodies[2]->getCenterOfMassPosition()));

		scene->add_entity("bullet_" + std::to_string(bulletIndex), bullet);

		bulletIndex++;
	}
}