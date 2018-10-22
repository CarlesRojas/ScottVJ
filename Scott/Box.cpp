#include "Box.h"
#include "Player.h"
#include "Enemy.h"


Box * Box::createBox(BoxOwner owner, BoxType type, const glm::vec2 & bottomMidPoint, const glm::vec2 &size)
{
	Box *b = new Box(owner, type, bottomMidPoint, size);
	return b;
}

Box * Box::createBox(BoxOwner owner, BoxType type, float left, float right, float top, float bot)
{
	Box *b = new Box(owner, type, glm::vec2((right + left) / 2.f, bot), glm::vec2(right - left, bot - top));
	return b;
}

Box::Box(BoxOwner owner, BoxType type, const glm::vec2 & bottomMidPoint, const glm::vec2 &size)
{
	this->active = true;
	this->owner = owner;
	this->type = type;
	this->size = size;
	this->bot = bottomMidPoint.y;
	this->top = bottomMidPoint.y - size.y;
	this->left = bottomMidPoint.x - size.x / 2;
	this->right = bottomMidPoint.x + size.x / 2;
}

glm::vec2 Box::getPos()
{
	return glm::vec2(left + (size.x / 2.f), bot);
}

void Box::increasePos(const glm::vec2 & deltaPos)
{
	bot += deltaPos.y;
	top += deltaPos.y;
	left += deltaPos.x;
	right += deltaPos.x;
}

void Box::moveTo(glm::vec2 bottomMidPoint)
{
	this->bot = bottomMidPoint.y;
	this->top = bottomMidPoint.y - size.y;
	this->left = bottomMidPoint.x - size.x / 2;
	this->right = bottomMidPoint.x + size.x / 2;
}





