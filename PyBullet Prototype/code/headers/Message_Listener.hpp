/**
 * @author    Martin P�rez Villabrille
 * @copyright Copyright (c) 2023 + UDIT
 * @details   Mgine -- All rights reserved
 */

#pragma once

namespace Mgine3D
{
	struct Message;

	/**
	 * @brief A listener interface for handling messages.
	 */
	class Message_Listener
	{
	public:

		/**
		 * @brief Handles a message. It will on the listener how to handle it.
		 *
		 * @param message The message to handle.
		 */
		virtual void handle(const Message& message) = 0;
	};
}