/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#include "../headers/Entity.hpp"
#include "../headers/Scene.hpp"

namespace Mgine3D
{
	void Entity::render()
	{
		btTransform physics_transform;

		glm::mat4 graphics_transform;

		for (size_t i = 0; i < rigidBodies.size(); i++)
		{
			rigidBodies[i]->getMotionState()->getWorldTransform(physics_transform);

			physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

			models[i]->set_transformation(graphics_transform);

			models[i]->scale(collisionShapes[i]->getLocalScaling().x(), collisionShapes[i]->getLocalScaling().y(), collisionShapes[i]->getLocalScaling().z());
		}
	}
}