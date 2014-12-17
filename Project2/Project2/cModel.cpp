#include "cModel.h"

cModel::cModel()
{
	m_mdlPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_mdlRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_mdlDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	m_mdlSpeed = 0.0f;
	m_IsActive = false;
	m_mdlScale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_Dimensions.s_mdldepth = 0.0f;
	m_Dimensions.s_mdlheight = 0.0f;
	m_Dimensions.s_mdlWidth = 0.0f;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// Setters
// +++++++++++++++++++++++++++++++++++++++++++++

void cModel::setPosition(glm::vec3 mdlPosition)
{
	m_mdlPosition = mdlPosition;
}

void cModel::setRotation(glm::vec3 mdlRotation)
{
	m_mdlRotation = mdlRotation;
}

void cModel::setDirection(glm::vec3 mdlDirection)
{
	m_mdlDirection = mdlDirection;
}

void cModel::setSpeed(float mdlSpeed)
{
	m_mdlSpeed = mdlSpeed;
}

void cModel::setIsActive(bool mdlIsActive)
{
	m_IsActive = mdlIsActive;
}

void cModel::setMdlDimensions(mdlDimensions mdlDims)
{
	m_Dimensions = mdlDims;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
}

void cModel::setMdlRadius(float mdlRadius)
{
	m_mdlRadius = mdlRadius;
}

void cModel::setScale(glm::vec3 mdlScale)
{
	m_mdlScale = mdlScale;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// Getters
// +++++++++++++++++++++++++++++++++++++++++++++

glm::vec3 cModel::getPosition()
{
	return m_mdlPosition;
}

glm::vec3 cModel::getRotation()
{
	return m_mdlRotation;
}

glm::vec3 cModel::getDirection()
{
	return m_mdlDirection;
}

float cModel::getSpeed()
{
	return m_mdlSpeed;
}

bool cModel::isActive()
{
	return m_IsActive;
}

mdlDimensions cModel::getMdlDimensions()
{
	return m_Dimensions;
}

float cModel::getMdlRadius()
{
	return m_mdlRadius;
}

glm::vec3 cModel::getScale()
{
	return m_mdlScale;
}

void cModel::initialise(glm::vec3 mdlPosition, glm::vec3 mdlRotation, glm::vec3 mdlScale, glm::vec3 mdlDirection, float mdlSpeed, bool mdlIsActive)
{
	//gives defualt values to the models properties
	setPosition(mdlPosition);
	setRotation(mdlRotation);
	setScale(mdlScale);
	setDirection(mdlDirection);
	setSpeed(mdlSpeed);
	setIsActive(mdlIsActive);
	m_Dimensions.s_mdldepth = 0.0f;
	m_Dimensions.s_mdlheight = 0.0f;
	m_Dimensions.s_mdlWidth = 0.0f;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
	glRotatef(mdlRotation.x, 1, 0, 0);
	glRotatef(mdlRotation.y, 0, 1, 0);
	glRotatef(mdlRotation.z, 0, 0, 1);
	glTranslatef(mdlPosition.x, mdlPosition.y, mdlPosition.z);
}

bool cModel::SphereSphereCollision(glm::vec3 mdlPosition, float mdlRadius)
{
	const float distSq = lengthSQRD(m_mdlPosition - mdlPosition); //distance between centres

	const float sumRadius = (m_mdlRadius + mdlRadius);	//minimum distance between the two objects

	if (distSq < sumRadius * sumRadius)	//if the distanc eis samller than the minimum there was a collision
	{
		return true; // Collision
	}
	return false; // No Collision
}

float cModel::lengthSQRD(glm::vec3 mdlLength)
{
	return (mdlLength.x * mdlLength.x) + (mdlLength.y * mdlLength.y) + (mdlLength.z * mdlLength.z);
}

cModel::~cModel()
{

}