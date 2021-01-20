#pragma once
#ifndef __SPACE_SHIP__
#define __SPACE_SHIP__
#include "DisplayObject.h"
#include "TextureManager.h"

class SpaceShip final : public DisplayObject
{
public:
	// constructor(s)
	SpaceShip();

	// destructor
	~SpaceShip();
	
	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	// Getters & Setters
	void setDestination(glm::vec2 destination);
	void setMaxSpeed(float speed);
	void setOrientation(glm::vec2 orientation);
	void setRotation(float x1, float x2, float y1, float y2);
	float getRotation() const;
	glm::vec2 getDestination() const;


private:

	glm::vec2 m_destination;		// Where I'm going
	glm::vec2 m_targetDirection;	// Normalized values
	glm::vec2 m_orientation;		// Spaceship orientation
	float m_rotationAngle;			// Spaceship rotation
	float m_maxSpeed;

	void m_Move();
};

#endif /* defined (__SPACE_SHIP__) */
