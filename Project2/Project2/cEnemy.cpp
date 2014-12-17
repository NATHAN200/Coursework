#include "cEnemy.h"

cEnemy::cEnemy() : cModel()
{
	hasFired = false;
	laser = new cLaser();
	laser->setIsActive(false);	//gives a defualt laser object that is set to false so that the enemy will create a new one on its first update

}
bool cEnemy::getHasfired()
{
	return hasFired;
}

void cEnemy::setHasFired(bool fired)
{
	hasFired = fired;
}
cLaser* cEnemy::getLaser()
{
	return laser;
}

void cEnemy::setLaser(cLaser* lsr)
{
	laser = lsr;
}
void cEnemy::randomise()
{	
	cModel::m_mdlPosition.y = (rand() % 30 - 15);
	cModel::m_mdlPosition.x = 23.0f;
	cModel::m_mdlDirection.x = -1;
	cModel::m_mdlSpeed = m_EnemyMinSpeed + rand() / (float)RAND_MAX * m_EnemyMaxSpeed;
	cModel::m_IsActive = true;
}

void cEnemy::update(float elapsedTime)
{
	cModel::m_mdlPosition += cModel::m_mdlDirection * cModel::m_mdlSpeed * elapsedTime;
}

cEnemy::~cEnemy()
{

}

