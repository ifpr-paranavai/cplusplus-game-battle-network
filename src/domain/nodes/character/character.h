#pragma once
#include <string>
#include <list>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../global/global-services/global-services.h"
#include "../../dto/vector/vector.h"
#include "../tile-based-body/tile-based-body.h"
#include "../animated-sprited/animated-sprited.h"
#include "../../../utils/subject/subject.h"

namespace Game
{
	class Character : public TileBasedBody
	{
	private:
		AnimatedSprite *currentAnimation = nullptr;
		AnimatedSprite *pendingAnimation = nullptr;

		void applyPendingAnimation();

	protected:
		Subject<int> onDeath;
		int life = 100;

		void queueAnimationChange(AnimatedSprite *newAnimation)
		{
			this->pendingAnimation = newAnimation;
		}

	public:
		Character(const int width, const int height);

		virtual ~Character();

		void update() override
		{
			this->applyPendingAnimation();
		}

		virtual void render()
		{
			this->currentAnimation->renderSprite(this->position);
		}

		int getLife()
		{
			return this->life;
		}

		void subscribeToDeath(Observer<int> *observer)
		{
			onDeath.subscribe(observer);
		}

		void unsubscribeFromDeath(Observer<int> *observer)
		{
			onDeath.unsubscribe(observer);
		}
	};
}