#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <windows.h>
#include <Xinput.h>


class Controller
{
public:
	Controller(int playerNumber);
	bool isConnected();
	XINPUT_STATE GetState();
	~Controller();

private:
	XINPUT_STATE _controllerState;
	int _controllerNum;
};
#endif