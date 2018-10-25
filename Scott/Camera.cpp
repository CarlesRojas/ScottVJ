#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

void Camera::init(glm::vec2 windowSize, glm::vec2 backgroundSize)
{
	pos = glm::vec2(windowSize.x / 2.f, windowSize.y / 2.f);
	winSize = windowSize;
	bgSize = backgroundSize;
	halfWidth = winSize.x / 2.f;
	maxX = halfWidth / 2.f;
	projection = glm::ortho(0.f, float(winSize.x - 1), float(winSize.y - 1), 0.f);
}

void Camera::update(int deltaTime, glm::vec2 playerPos)
{
	if (playerPos.x - pos.x > maxX) pos.x = playerPos.x - maxX;
	else if (pos.x - playerPos.x > maxX) pos.x = playerPos.x + maxX;

	if (pos.x < halfWidth) pos.x = winSize.x / 2.f;
	if (pos.x > bgSize.x - halfWidth) pos.x = bgSize.x - halfWidth;

	projection = glm::ortho((float)pos.x - halfWidth, (float)pos.x + halfWidth, float(winSize.y - 1), 0.f);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return projection;
}

glm::vec2 Camera::getPos()
{
	return pos;
}
