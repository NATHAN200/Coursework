#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

#define GLM_FORCE_RADIANS

#include <stdlib.h>
#include <Windows.h>
#include <GL\glut.h>
#include <OpenAL\al.h>
#include <OpenAL\alc.h>
#include <OpenAL\alut.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\geometric.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\quaternion.hpp>
#include "glm-0.3.2\glm\glm.h"
#include <vector>


//Define the string to appear in the top left corner of the window
#define WINDOW_TITLE "OpenGl Models, Lighting and Text"

struct mdlDimensions{
	float s_mdlWidth, s_mdlheight, s_mdldepth;
};

const float PLAYFIELDX  = 100.0f;
const float PLAYFIELDZ = 300.0f;
extern bool pressedRight;	//Are we pressing right
extern bool pressedLeft;	//Are we pressing left
extern bool pressedup;		//are we pressing up
extern bool presseddown;	//are we pressing down
extern int drawMode;
extern float translationX;	//Are we moving in the x axis
extern float translationY;	//Are we moving in the y axis
extern bool fire;			//are we firing
extern bool sfire;			//can we fire
extern bool firstPerson;	//what camera mode(first person or top down) do we want
extern bool controller;		//do we want to use the controller
extern bool cameraSwitch;	//can we switch camera views?


#endif