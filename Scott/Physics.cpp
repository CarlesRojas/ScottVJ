#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "Physics.h"

void Physics::init(ShaderProgram * texProgram)
{
	program = texProgram;

	// Debug
	Physics::instance().loadOutlineTextures();
}

void Physics::render()
{
	// Debug
	Physics::instance().printBoxes(true);
}

bool Physics::overlap(Box * box1, Box * box2)
{
	if (!box1->active || !box2->active) return false;
	return box1->left < box2->right && box1->right > box2->left &&
		box1->top < box2->bot && box1->bot > box2->top;
}

bool Physics::correctPosition(Box * box)
{
	if (box->type == Box::BASE)
	{
		for (int i = 0; i < background->walls.size(); ++i)
			if (overlap(box, background->walls[i]))
				return false;

		if (box->owner == Box::PLAYER)
		{
			for (int i = 0; i < enemies.size(); ++i)
				if (overlap(box, enemies[i]->baseBox))
					return false;
		}

		else if (box->owner == Box::ENEMY)
		{
			if (overlap(box, player->baseBox))
				return false;
		}

		return true;
	}
	return false;
}

void Physics::attack(Attack * attack)
{
	if (attack->box->type == Box::ATTACK)
	{
		if (attack->box->owner == Box::PLAYER)
		{
			for (auto e : enemies)
				if (overlap(e->hitBox, attack->box))
				{
					e->kill();
					if (attack->entityHit()) break;
				}
		}
		else if (attack->box->owner == Box::ENEMY)
		{
			if (overlap(player->hitBox, attack->box)) player->kill();
		}
	}
}

void Physics::loadOutlineTextures()
{
	red.loadFromFile("sprites/debug/outline_red.png", TEXTURE_PIXEL_FORMAT_RGBA);
	red.setWrapS(GL_CLAMP_TO_EDGE);
	red.setWrapT(GL_CLAMP_TO_EDGE);
	red.setMinFilter(GL_NEAREST);
	red.setMagFilter(GL_NEAREST);

	green.loadFromFile("sprites/debug/outline_green.png", TEXTURE_PIXEL_FORMAT_RGBA);
	green.setWrapS(GL_CLAMP_TO_EDGE);
	green.setWrapT(GL_CLAMP_TO_EDGE);
	green.setMinFilter(GL_NEAREST);
	green.setMagFilter(GL_NEAREST);

	blue.loadFromFile("sprites/debug/outline_blue.png", TEXTURE_PIXEL_FORMAT_RGBA);
	blue.setWrapS(GL_CLAMP_TO_EDGE);
	blue.setWrapT(GL_CLAMP_TO_EDGE);
	blue.setMinFilter(GL_NEAREST);
	blue.setMagFilter(GL_NEAREST);

	yellow.loadFromFile("sprites/debug/outline_yellow.png", TEXTURE_PIXEL_FORMAT_RGBA);
	yellow.setWrapS(GL_CLAMP_TO_EDGE);
	yellow.setWrapT(GL_CLAMP_TO_EDGE);
	yellow.setMinFilter(GL_NEAREST);
	yellow.setMagFilter(GL_NEAREST);

	vertices = { 0, 0, 0, 0,
				 256, 0, 1, 0,
				 256, 256, 1, 1,
				 0, 0, 0, 0,
				 256, 256, 1, 1,
				 0, 256, 0, 1 };

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));
}

void Physics::printBoxes(bool printBackground)
{
	// Player
	if (player->baseBox->active)
	{
		glm::vec2 scaleFactor = player->hitBox->size / 256.f;
		glm::vec2 posDispl = glm::vec2(player->hitBox->left, player->hitBox->top);

		glm::mat4 modelview = glm::mat4(1.0f);
		modelview = glm::translate(modelview, glm::vec3(posDispl.x, posDispl.y, 0.f));
		modelview = glm::scale(modelview, glm::vec3(scaleFactor.x, scaleFactor.y, 1.f));
		program->setUniformMatrix4f("modelview", modelview);
		program->setUniform2f("texCoordDispl", 0.f, 0.f);

		glEnable(GL_TEXTURE_2D);
		red.use();
		glBindVertexArray(vao);
		glEnableVertexAttribArray(posLocation);
		glEnableVertexAttribArray(texCoordLocation);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisable(GL_TEXTURE_2D);
	}

	if (player->baseBox->active)
	{
		glm::vec2 scaleFactor = player->baseBox->size / 256.f;
		glm::vec2 posDispl = glm::vec2(player->baseBox->left, player->baseBox->top);

		glm::mat4 modelview = glm::mat4(1.0f);
		modelview = glm::translate(modelview, glm::vec3(posDispl.x, posDispl.y, 0.f));
		modelview = glm::scale(modelview, glm::vec3(scaleFactor.x, scaleFactor.y, 1.f));
		program->setUniformMatrix4f("modelview", modelview);
		program->setUniform2f("texCoordDispl", 0.f, 0.f);

		glEnable(GL_TEXTURE_2D);
		yellow.use();
		glBindVertexArray(vao);
		glEnableVertexAttribArray(posLocation);
		glEnableVertexAttribArray(texCoordLocation);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisable(GL_TEXTURE_2D);
	}

	vector<Attack*> attacks = player->getAttacks();
	for (auto a : attacks)
	{
		if (a->box->active)
		{
			glm::vec2 scaleFactor = a->box->size / 256.f;
			glm::vec2 posDispl = glm::vec2(a->box->left, a->box->top);

			glm::mat4 modelview = glm::mat4(1.0f);
			modelview = glm::translate(modelview, glm::vec3(posDispl.x, posDispl.y, 0.f));
			modelview = glm::scale(modelview, glm::vec3(scaleFactor.x, scaleFactor.y, 1.f));
			program->setUniformMatrix4f("modelview", modelview);
			program->setUniform2f("texCoordDispl", 0.f, 0.f);

			glEnable(GL_TEXTURE_2D);
			green.use();
			glBindVertexArray(vao);
			glEnableVertexAttribArray(posLocation);
			glEnableVertexAttribArray(texCoordLocation);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glDisable(GL_TEXTURE_2D);
		}
	}

	// Background
	if (printBackground)
	{
		for (auto b : background->walls)
		{
			if (b->active)
			{
				glm::vec2 scaleFactor = b->size / 256.f;
				glm::vec2 posDispl = glm::vec2(b->left, b->top);

				glm::mat4 modelview = glm::mat4(1.0f);
				modelview = glm::translate(modelview, glm::vec3(posDispl.x, posDispl.y, 0.f));
				modelview = glm::scale(modelview, glm::vec3(scaleFactor.x, scaleFactor.y, 1.f));
				program->setUniformMatrix4f("modelview", modelview);
				program->setUniform2f("texCoordDispl", 0.f, 0.f);

				glEnable(GL_TEXTURE_2D);
				yellow.use();
				glBindVertexArray(vao);
				glEnableVertexAttribArray(posLocation);
				glEnableVertexAttribArray(texCoordLocation);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glDisable(GL_TEXTURE_2D);
			}
		}
	}


	// Enemies
	for (auto e : enemies)
	{
		if (e->hitBox->active)
		{
			glm::vec2 scaleFactor = e->hitBox->size / 256.f;
			glm::vec2 posDispl = glm::vec2(e->hitBox->left, e->hitBox->top);

			glm::mat4 modelview = glm::mat4(1.0f);
			modelview = glm::translate(modelview, glm::vec3(posDispl.x, posDispl.y, 0.f));
			modelview = glm::scale(modelview, glm::vec3(scaleFactor.x, scaleFactor.y, 1.f));
			program->setUniformMatrix4f("modelview", modelview);
			program->setUniform2f("texCoordDispl", 0.f, 0.f);

			glEnable(GL_TEXTURE_2D);
			red.use();
			glBindVertexArray(vao);
			glEnableVertexAttribArray(posLocation);
			glEnableVertexAttribArray(texCoordLocation);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glDisable(GL_TEXTURE_2D);
		}

		if (e->baseBox->active)
		{
			glm::vec2 scaleFactor = e->baseBox->size / 256.f;
			glm::vec2 posDispl = glm::vec2(e->baseBox->left, e->baseBox->top);

			glm::mat4 modelview = glm::mat4(1.0f);
			modelview = glm::translate(modelview, glm::vec3(posDispl.x, posDispl.y, 0.f));
			modelview = glm::scale(modelview, glm::vec3(scaleFactor.x, scaleFactor.y, 1.f));
			program->setUniformMatrix4f("modelview", modelview);
			program->setUniform2f("texCoordDispl", 0.f, 0.f);

			glEnable(GL_TEXTURE_2D);
			yellow.use();
			glBindVertexArray(vao);
			glEnableVertexAttribArray(posLocation);
			glEnableVertexAttribArray(texCoordLocation);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glDisable(GL_TEXTURE_2D);
		}
		attacks = e->getAttacks();
		for (auto a : attacks)
		{
			if (a->box->active)
			{
				glm::vec2 scaleFactor = a->box->size / 256.f;
				glm::vec2 posDispl = glm::vec2(a->box->left, a->box->top);

				glm::mat4 modelview = glm::mat4(1.0f);
				modelview = glm::translate(modelview, glm::vec3(posDispl.x, posDispl.y, 0.f));
				modelview = glm::scale(modelview, glm::vec3(scaleFactor.x, scaleFactor.y, 1.f));
				program->setUniformMatrix4f("modelview", modelview);
				program->setUniform2f("texCoordDispl", 0.f, 0.f);

				glEnable(GL_TEXTURE_2D);
				green.use();
				glBindVertexArray(vao);
				glEnableVertexAttribArray(posLocation);
				glEnableVertexAttribArray(texCoordLocation);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glDisable(GL_TEXTURE_2D);
			}
		}
	}
}

