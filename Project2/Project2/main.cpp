/*I confirm that the code contained in this 
file (other than that provided or authorised) 
is all my own work and has not been 
submitted elsewhere in fulfilment of this or any 
other award.

Nicholas Athanasopoulos*/


/*controls: q to switch cameras, e to switch to contorller, 
arrow keys to move space bar to fire
Contorller: d pad to move, right trigger to fire, 
left trigger to switch camera*/
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include "GameConstants.h"
#include <windows.h>
#include "windowOGL.h"
#include "cWNDManager.h"
#include "libdrawtext-0.2.1\drawtext.h"
#include "cModelLoader.h"
#include "cModel.h"
#include "cEnemy.h"
#include "cPlayer.h"
#include "cLaser.h"
#include "cSound.h"
//#include "cCamera.h"
#include <vector>
#include <time.h>
#include <Xinput.h>
#include "Controller.h"
#define FONT_SZ	24

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;



    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

    //The example OpenGL code
    windowOGL theOGLWnd;

    //Attach our example to our window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);


    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL()) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	srand(time(NULL)); //seeds the random number generator with the current time

	std::vector<cEnemy*> enemyList;	//Holds all the enemy objects
	std::vector<cEnemy*>::iterator enemyIndex;	//Iterator for the list of enemy objects

	std::vector<cLaser*> enemyLaserList;	//Holds all the enemy laser objects
	std::vector<cLaser*>::iterator enemyLaserIndex;//Iterator for the list of enemy laser objects

	std::vector<cLaser*> laserList;	//holds all the player laser objects
	std::vector<cLaser*>::iterator index;	//iterator

	// Load font
	struct dtx_font *fntmain;

	fntmain = dtx_open_font("Fonts/doctor_who.ttf", 0);	//Gets the wanted font
	dtx_prepare_range(fntmain, FONT_SZ, 0, 256);            

	dtx_use_font(fntmain, FONT_SZ);

	// Load Sound
	cSound themeMusic;
	themeMusic.createContext();
	themeMusic.loadWAVFile("Audio/who10Edit2.wav");
	themeMusic.playAudio(AL_TRUE);	//play the theme song on repeat

	// Load explosion sound
	cSound explosionFX;
	explosionFX.createContext();
	explosionFX.loadWAVFile("Audio/explosion2.wav");

	//Load firing sound
	cSound firingFX;
	firingFX.createContext();
	firingFX.loadWAVFile("Audio/shot007.wav");

	cModelLoader enemyMdl;
	enemyMdl.loadModel("Models/enemy.obj"); // Loads the enemy Model

	cModelLoader playerMdl;
	playerMdl.loadModel("Models/player.obj"); // Loads the Player Model

	cModelLoader pLayerLaser;
	pLayerLaser.loadModel("Models/playerLaser.obj"); //Loads the player laser Model
	
	cModelLoader enemyLaser;
	enemyLaser.loadModel("Models/enemyLaser.obj"); //Loads the player laser Model

	cPlayer thePlayer;	//Creates the player object
	thePlayer.initialise(glm::vec3(-12, 0, 0), glm::vec3(90.0f,90,0), glm::vec3(0.4, 0.4, 0.4), glm::vec3(0, 0, 0), 5.0f, true);	//gives the player its starting position
	thePlayer.setMdlDimensions(playerMdl.getModelDimensions());	//

	int score = 0;	//Players Score value
	Controller* aController = new Controller(0);	//Ceates a new controller object
    //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		if (controller)	//Checks if we want to be using the controller for gameplay instead of the keyboard
		{
			if (aController->isConnected())	//checks if the controller is connected
			{
				if (aController->GetState().Gamepad.bRightTrigger)	//Was the right trigger pressed?
				{
					if (sfire)	//can we fire?
					{
						fire = true;
						sfire = false;	//trigger was pressed so we need to let go before we can fire again
					}
				}
				else //trigger wasnt pressed so we can fire when it is next pressed. Makes it so the player only fires once per trigger press
				{
					sfire = true;
				}
				if (aController->GetState().Gamepad.bLeftTrigger)	//have we pressd the left trigger
				{
					if (cameraSwitch)	//are we able to switch the camera
					{
						cameraSwitch = false; // cant switch camera mode again until we let go of the trgger
						//Switch the camera mode
						if (firstPerson)
						{
							firstPerson = false;
						}
						else
						{
							firstPerson = true;
						}
					}
				}
				else
				{
					cameraSwitch = true; // we let go of the button so we are able to switch cameras on the next trigger press
				}
				if (!firstPerson) // we are not in first person mode so use the top down controls. Button presssed on the dpad is the same as direction on the screen
				{
					if (aController->GetState().Gamepad.wButtons & 0x0004)	//did we press the left dpad button
					{
						pressedLeft = true;
						translationX = -2.0f;
					}
					else
					{
						pressedLeft = false;
						translationX = 0.0f;//no longer pressing the left dpad button
					}
					if (aController->GetState().Gamepad.wButtons & 0x0008) //RIght dpad was pressed
					{
						pressedRight = true;
						translationX = 2.0f;
					}
					else
					{
						pressedRight = false;
						translationX = 0.0f;//right dpad no longer pressed
					}

					if (aController->GetState().Gamepad.wButtons & 0x0001) //If the UP dpad was pressed
					{
						pressedup = true;
						translationY = 2.0f;
					}
					else
					{
						pressedup = false;
						translationY = 0.0f;
					}
					if (aController->GetState().Gamepad.wButtons & 0x0002) //If the Down dpad was pressed
					{
						presseddown = true;
						translationY = -2.0f;
					}
					else
					{
						presseddown = false;
						translationY = 0.0f;
					}
				}
				else // we are in first person mode and so make the up,down buttons move us left to right and right,left buttons move us up, down
				{
					if (aController->GetState().Gamepad.wButtons & 0x0004)	//left dpad
					{

						pressedup = true;
						translationY = 2.0f;
					}
					else
					{
						pressedup = false;
						translationY = 0.0f;
					}
					if (aController->GetState().Gamepad.wButtons & 0x0008)	//right dpad
					{
						presseddown = true;
						translationY = -2.0f;
					}
					else
					{
						presseddown = false;
						translationY = 0.0f;
					}
					if (aController->GetState().Gamepad.wButtons & 0x0001) //up dpad
					{
						pressedRight = true;
						translationX = 2.0f;
					}
					else
					{
						pressedRight = false;
						translationX = 0.0f;
					}
					if (aController->GetState().Gamepad.wButtons & 0x0002) //down dpad
					{

						pressedLeft = true;
						translationX = -2.0f;
					}
					else
					{
						pressedLeft = false;
						translationX = 0.0f;
					}
				}
			}
		}
		pgmWNDMgr->processWNDEvents(); //Process any window events
		
        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		theOGLWnd.initOGL();
		glClearColor(0.8, 0.9, 1, 1); // Set the background colour

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		if (firstPerson)	//Do we want the first person camera or the top down camera
		{
			//sets the camera position at the players position and looks straight forward
			gluLookAt(thePlayer.getPosition().x, thePlayer.getPosition().y, 0, thePlayer.getPosition().x + 100, thePlayer.getPosition().y, 0, 0, 0, 1);
		}
		else
		{
			//looks down at the scene for a top down view
			gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);
		}

		if (enemyList.size() == 0)	// Are there any enemies?
		{
			for (int loop = 0; loop < rand() % 7 + 3; loop++)	// If there are no enemies we create a random number from 3 to 7 new enemies
			{
				cEnemy* aEnemy = new cEnemy();	//Creates a new enemy object
				aEnemy->randomise();	//randomises the enemies start location and movement speed
				aEnemy->setMdlDimensions(enemyMdl.getModelDimensions());
				aEnemy->setRotation(glm::vec3(90, 270, 0));
				aEnemy->setScale(glm::vec3(0.5f, 0.5f, 0.5f));//sets the model
				aEnemy->setMdlRadius(aEnemy->getMdlRadius() / 3);
				enemyList.push_back(aEnemy);	//adds the enemy object to the list
			}
		}

		for (enemyIndex = enemyList.begin(); enemyIndex != enemyList.end(); ++enemyIndex) // Loops through the complete list of enemies
		{
			enemyMdl.renderMdl((*enemyIndex)->getPosition(), (*enemyIndex)->getRotation(), (*enemyIndex)->getScale());	//Renders every enemy
			(*enemyIndex)->update(elapsedTime);	//Updates the enemys position
			if ((*enemyIndex)->SphereSphereCollision(thePlayer.getPosition(), thePlayer.getMdlRadius()/2))	//checks if the enemy collidedwith the player.
			{
				score -= 20;	//Removes some of the player health for colliding with an enemy
				(*enemyIndex)->setIsActive(false);	//sets the enemy to be no longer active
				explosionFX.playAudio(AL_FALSE);	//plays explosion sound(DOESNT WORK)
			}
			if ((*enemyIndex)->getLaser()->isActive() == false)	//checks if the enemy has an active laser
			{
				//makes a new laser if the enemy does not have one
				cLaser* laser = new cLaser();
				//Gets the player position and aims the laser towards the current position of the player
				float x = thePlayer.getPosition().x - (*enemyIndex)->getPosition().x;	//difference in x positon between enemy and player
				float y = thePlayer.getPosition().y - (*enemyIndex)->getPosition().y; //difference in y positon between enemy and player
				float length = sqrt((x*x) + (y*y));	//Length of the vector between enemy and player
				x /= length;	//normalised x value of vector between player and enemy
				y /= length;	//normalised y value of vector between player and enemy
				laser->setDirection(glm::vec3(x,y,0));   //Sets the direction to be towards the players current position
				laser->setRotation(glm::vec3(0, 0, 0));	//sets the lasers rotation
				laser->setScale(glm::vec3(2, 2, 2));	//sets the scale of the lasers model
				laser->setSpeed(15.0f);	//speed of the laser
				laser->setPosition((*enemyIndex)->getPosition() + glm::vec3(-1, 0, 0));    // Spawns the laser to the front of the enemy
				laser->setIsActive(true);	//the laser is now active
				laser->setMdlDimensions(enemyLaser.getModelDimensions());	//sets the laser model
				laser->update(elapsedTime);	//updates the lasers position 
				enemyLaserList.push_back(laser);	//adds the laser to the enemy laser list
				(*enemyIndex)->setLaser(laser);	//sends the laser to the enemy
				firingFX.playAudio(AL_FALSE);	//plays the firing sound
			}
			if ((*enemyIndex)->getPosition().x < -20)	//checks if the enemy has moved off screen
			{
				(*enemyIndex)->setIsActive(false);
			}
		}

		thePlayer.update(elapsedTime);	//updates the player position
		if (!firstPerson)	//checks if we want to render the player model, if we are in firstperson mode, we don't render the player
			playerMdl.renderMdl(thePlayer.getPosition(), thePlayer.getRotation(), thePlayer.getScale());
		
		//are we shooting?
		if (fire)
		{
			cLaser* laser = new cLaser();	//creates a new laser object
			laser->setDirection(glm::vec3(1,0,0));   //sets the laser to move towards the right hand side of the screen
			laser->setRotation(glm::vec3(90, 90, 0));
			//laser->setScale(glm::vec3(20, 20, 20));
			laser->setSpeed(40.0f);	//Laser speed
			laser->setPosition(thePlayer.getPosition() + glm::vec3(1, 0, 0));    //   spawns the laser in front of the player
			laser->setIsActive(true);
			laser->setMdlDimensions(pLayerLaser.getModelDimensions());
			laser->setMdlRadius(laser->getMdlRadius() / 5);//sets the laser model
			laser->update(elapsedTime);		//updates the laser position
          	laserList.push_back(laser);	//adds the laser to the players laser list
			fire = false;	// we only want to shoot once per key press 
			firingFX.playAudio(AL_FALSE);
		}


		for (index = laserList.begin(); index != laserList.end(); ++index)	//loops trough all the players lasers
		{
			if ((*index)->getPosition().x >= 20)	//has the laser left the screen?
			{
				(*index)->setIsActive(false);
			}
			if ((*index)->isActive())
			{
				pLayerLaser.renderMdl((*index)->getPosition(), (*index)->getRotation(), (*index)->getScale() );	//render the laser
				(*index)->update(elapsedTime);	//updates the laser position
				// check for collisions
				for (enemyIndex = enemyList.begin(); enemyIndex != enemyList.end(); ++enemyIndex)	//has the laser hit an enemy
				{
					if ((*index)->SphereSphereCollision((*enemyIndex)->getPosition(), (*enemyIndex)->getMdlRadius()))
					{
						//destroys the enemy and adds to the players score
						(*index)->setIsActive(false);
						(*enemyIndex)->setIsActive(false);
						score += 10;	
						explosionFX.playAudio(AL_FALSE);
						break; // No need to check for other bullets.
						
					}
				}
			}
		}
		for (enemyLaserIndex = enemyLaserList.begin(); enemyLaserIndex != enemyLaserList.end(); ++enemyLaserIndex) // loops through all the enemy lasers
		{
			//has the laser left the screen? the eemy lasers could be moving in any of the directions so we need to check all sides.
			if ((*enemyLaserIndex)->getPosition().x <= -20 || (*enemyLaserIndex)->getPosition().x >= 20 || (*enemyLaserIndex)->getPosition().y >= 20 || (*enemyLaserIndex)->getPosition().y <= -25)
			{
				(*enemyLaserIndex)->setIsActive(false);
			}

			if ((*enemyLaserIndex)->isActive())	
			{
				enemyLaser.renderMdl((*enemyLaserIndex)->getPosition(), (*enemyLaserIndex)->getRotation(), (*enemyLaserIndex)->getScale());	//renders the laser
				(*enemyLaserIndex)->update(elapsedTime);	//updates the laser
				// check for collisions
				if ((*enemyLaserIndex)->SphereSphereCollision(thePlayer.getPosition(), thePlayer.getMdlRadius()/3))
				{
					//the player was hit so destroy the laser and remove some health
					score -= 10;
					(*enemyLaserIndex)->setIsActive(false);
					explosionFX.playAudio(AL_FALSE);
				}
			}
		}
		//Loops through the enemyLaserlist and removes any inactive lasers
		enemyLaserIndex = enemyLaserList.begin();	//start at the beginning of the list
		while (enemyLaserIndex != enemyLaserList.end())	//keep looping until we get to the end of the list
		{
			if ((*enemyLaserIndex)->isActive() == false)	//has the laser been destroyed
			{
				enemyLaserIndex = enemyLaserList.erase(enemyLaserIndex);	//remove it from the list
			}
			else  //laser not destroyed
			{
				++enemyLaserIndex;	//move to the next laser
			}
		}
		//Loops through the player laser list and removes any inactive lasers
		index = laserList.begin();
		while (index != laserList.end())
		{
			if ((*index)->isActive() == false)
			{
 				index = laserList.erase(index);
			}
			else
			{
				++index;
			}

		}
		//Loops through the enemy list and removes any destroyed enemies
		enemyIndex = enemyList.begin();
		while (enemyIndex != enemyList.end())
		{
			if ((*enemyIndex)->isActive() == false)
			{
				enemyIndex = enemyList.erase(enemyIndex);
			}
			else
			{
				++enemyIndex;
			}
		}

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, windowWidth, 0, windowHeight);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glPushAttrib(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);

		glTranslatef(0, 730, 0);//moves the text to the top left hand side of the screen
		if (score < 0)	//if the score is less than 0 mkae it 0
		{
			score = 0;
		}
		string scoreString = " Score: " + to_string(score);	//Makes a String using the players health and score
		const char* ch = scoreString.c_str();	//converts the string to char
		dtx_string(ch);	//displays the char at the origin

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		pgmWNDMgr->swapBuffers();
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
