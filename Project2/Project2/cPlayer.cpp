#include "cPlayer.h"

cPlayer::cPlayer() : cModel()
{

}

void cPlayer::update(float elapsedTime)
{
	if (pressedup && m_mdlPosition.y < 15.0f)	//check if we want to move up and if there is enough room on the screen to move up
	{
		m_mdlDirection.y += 200 * elapsedTime;	//distance to move in the y direction
	}
	if (presseddown &&  m_mdlDirection.y > -15.0f)	//check if we want to move down and if there is enough room on the screen to move down
	{
		m_mdlDirection.y -= 200 * elapsedTime;
	}
	if (m_mdlPosition.y > 15.0f)	//if we have moved off screen move back
	{
		m_mdlDirection.y = 0;
		m_mdlPosition.y = 15.0f;
	}
	if (m_mdlPosition.y < -15.0f)
	{
		m_mdlDirection.y = 0;
		m_mdlPosition.y = -15.0f;
	}
	if (pressedRight && m_mdlPosition.x < 17.0f)//can we move right
	{
		m_mdlDirection.x += 200 * elapsedTime;	
	}
	if (pressedLeft && m_mdlPosition.x > -17.0f)//move left
	{
		m_mdlDirection.x -= 200 * elapsedTime;
	}
	if (m_mdlPosition.x > 17.0f)
	{
		m_mdlPosition.x = 17.0f;
		m_mdlDirection.x = 0;
	}
	if (m_mdlPosition.x < -17.0f)
	{
		m_mdlPosition.x = -17.0f;
		m_mdlDirection.x = 0;
	}

	cModel::m_mdlPosition += cModel::m_mdlDirection * cModel::m_mdlSpeed *elapsedTime;	//final movement calculation
	cModel::m_mdlDirection *= 0.6f;

	translationY = 0;	//reset whether we are moving
	translationX = 0;
}

cPlayer::~cPlayer()
{

}