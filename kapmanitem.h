/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KAPMANITEM_H
#define KAPMANITEM_H

#include "characteritem.h"
#include "kapman.h"

#include <QTimeLine>

/**
 * @brief This class manage the display of the Kapman.
 */
class KapmanItem : public CharacterItem {

	Q_OBJECT

	private:

		/** Number of frames to animate the KapmanItem */
		static const int NB_FRAMES;

		/** Animation update interval */
		static const int ANIM_LOW_SPEED;
		static const int ANIM_MEDIUM_SPEED;
		static const int ANIM_HIGH_SPEED;

		/** Timer used to animate the KapmanItem */
		QTimeLine * m_animationTimer;

	public:

		/**
		 * Creates a new KapmanItem instance.
		 * @param p_model the Kapman model
		 */
		KapmanItem(Kapman* p_model);

		/**
		 * Deletes the KapmanItem instance.
		 */
		~KapmanItem();

	public slots:

		/**
		 * Rotates the image function of the Kapman direction.
		 */
		void updateDirection();

		/**
		 * Manages the collisions with any Element.
		 */
		void manageCollision();
		
		/**
		 * Updates the KapmanItem coordinates.
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		void update(qreal p_x, qreal p_y);

		/**
		 * Starts the KapmanItem animation.
		 */
		void startAnim();

		/**
		 * Pauses the KapmanItem animation.
		 */
		void pauseAnim();

		/**
		 * Resumes the KapmanItem animation.
		 */
		void resumeAnim();

		/**
		 * Stops the KapmanItem animation.
		 */
		void stopAnim();

		/**
		 * Sets the given frame to the KapmanItem.
		 * @param p_frame the frame to set
		 */
		void setFrame(const int p_frame);

		/**
		 * Implements the CharacterItem method.
		 */
		void startBlinking();

		/**
		 * Implements the CharacterItem method.
		 */
		void blink();
};

#endif

