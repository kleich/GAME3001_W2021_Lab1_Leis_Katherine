#include "SpaceShip.h"
#include <cmath>
#include "Util.h"

SpaceShip::SpaceShip() : m_rotationAngle(0.0f), m_maxSpeed(5.0f)
{
	TextureManager::Instance()->load("../Assets/textures/spaceship.png", "spaceship");

	auto size = TextureManager::Instance()->getTextureSize("spaceship");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SPACE_SHIP);
	setOrientation(glm::vec2(0.0f, -1.0f)); 
}

SpaceShip::~SpaceShip()
= default;

void SpaceShip::draw()
{
	TextureManager::Instance()->draw("spaceship", getTransform()->position.x, getTransform()->position.y, getRotation(), 255, true); // file, x, y, ANGLE
	
	Util::DrawLine(getTransform()->position, getDestination()); // Draw a line from the 'top' of the ship
}

void SpaceShip::update()
{
	m_Move();
}

void SpaceShip::clean()
{
}

void SpaceShip::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}


void SpaceShip::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

void SpaceShip::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

// Face the target = angle rotation calculation
// = we know the distance from ship to target  (1 side), distance from top to target (hypo), distance from center of ship to top of ship
// x1-x2 y1-y2
// angle rotation would be the angle
// 
// I'm not sure if below is correct but I'm able to get the results I wanted. Curious to see better ways to do it

void SpaceShip::setRotation(float x1, float x2, float y1, float y2)
{
	m_rotationAngle = atan2(x1 - x2, y1 - y2) * Util::Rad2Deg;
}

float SpaceShip::getRotation() const
{
	return m_rotationAngle;
}

glm::vec2 SpaceShip::getDestination() const
{
	return m_destination;
}


void SpaceShip::m_Move()
{
	// Direction with magnitude
	m_targetDirection = m_destination - getTransform()->position; // The difference between where I'm going and where I am.

	
	// Normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	// Calculate velocity
	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	// Add the velocity to the position every frame
	getTransform()->position += getRigidBody()->velocity;
}
