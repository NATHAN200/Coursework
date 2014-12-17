#ifndef _CENEMIES_H
#define _CENEMIES_H

#include "GameConstants.h"
#include "cModel.h"
#include "cLaser.h"
class cEnemy : public cModel
{
public:
	cEnemy();
	cLaser* getLaser();	
	void setLaser(cLaser* laser);
	bool getHasfired();
	void setHasFired(bool fired);
	void randomise();
	virtual void update(float elapsedTime);

	~cEnemy();

private:
	cLaser* laser; //The currect laser that the enemy has fired
	const float m_EnemyMinSpeed = 3.0f;
	const float m_EnemyMaxSpeed = 10.0f;
	const float m_EnemySpeedAdjustment = 2.5f;
	bool hasFired;

};
#endif