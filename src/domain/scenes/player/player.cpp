#include "player.h"

namespace Game
{
    Player::Player(
        RendererPort *_renderer, EventManagerPort *_eventManager) : Character(_renderer, 50, 70, "#00ADEF"), eventManager(_eventManager)
    {
    }

    void Player::update()
    {
        if (this->eventManager->isKeyPressed(KeyCode::ARROW_UP))
        {
            if (this->keyAlreadyPressed)
            {
                return;
            }
            this->keyAlreadyPressed = true;

            if (this->tileRowIndex - 1 < 0)
            {
                return;
            }
            this->tileRowIndex -= 1;
            return;
        }

        if (this->eventManager->isKeyPressed(KeyCode::ARROW_DOWN))
        {
            if (this->keyAlreadyPressed)
            {
                return;
            }
            this->keyAlreadyPressed = true;

            if (this->tileRowIndex + 1 > this->tileRowLimit)
            {
                return;
            }
            this->tileRowIndex += 1;
            return;
        }

        if (this->eventManager->isKeyPressed(KeyCode::ARROW_LEFT))
        {
            if (this->keyAlreadyPressed)
            {
                return;
            }
            this->keyAlreadyPressed = true;

            if (this->tileColumnIndex - 1 < 0)
            {
                return;
            }
            this->tileColumnIndex -= 1;
            return;
        }

        if (this->eventManager->isKeyPressed(KeyCode::ARROW_RIGHT))
        {
            if (this->keyAlreadyPressed)
            {
                return;
            }
            this->keyAlreadyPressed = true;

            if (this->tileColumnIndex + 1 > this->tileColumnIndexLimit)
            {
                return;
            }

            this->tileColumnIndex += 1;
            return;
        }

        this->keyAlreadyPressed = false;
    }

}
