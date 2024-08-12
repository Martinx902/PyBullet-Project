/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#include "../headers/Scene.hpp"
#include "../headers/CollisionDispatcher.hpp"
#include "../headers/CollsionsID.hpp"

namespace Mgine3D
{
	void CollisionDispatcher::check_collisions()
	{
		int manifold_count = scene->get_dynamics_world()->getDispatcher()->getNumManifolds();

		for (int i = 0; i < manifold_count; i++)
		{
			btPersistentManifold* manifold = scene->get_dynamics_world()->getDispatcher()->getManifoldByIndexInternal(i);

			const btCollisionShape* object_a = manifold->getBody0()->getCollisionShape();

			const btCollisionShape* object_b = manifold->getBody1()->getCollisionShape();

			if (object_a->getUserIndex() != int(CollisionsID::NONE) && object_b->getUserIndex() != int(CollisionsID::NONE))
			{
				//KEY COLLISION -> OPEN DOOR
				if ((object_a->getUserIndex() == int(CollisionsID::KEY_ID) ||
					(object_b->getUserIndex() == int(CollisionsID::KEY_ID))))
				{
					Message* message = new Message;
					message->id = "doorTrigger";
					message->trigger = "doorTrigger";

					scene->get_message_dispatcher()->send(*message);
				}

				//BULLET COLLISION -> PLAY PARTICLE SYSTEM
			}
		}
	}
}