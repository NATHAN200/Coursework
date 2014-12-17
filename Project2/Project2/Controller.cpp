#include "Controller.h"

Controller::Controller(int number)
{
	_controllerNum = number;
}
Controller::~Controller()
{

}
bool Controller::isConnected()
{
	//Invoke the memset(); function to zero the XBOX_CONTROLLER_State. 
	ZeroMemory(&_controllerState, 0, sizeof(XINPUT_STATE));

	//We store the XInputGetState value inside result, note that result is a DWORD which is a typedef unsigned long. 
	DWORD result = XInputGetState(_controllerNum, &_controllerState);

	return result == ERROR_DEVICE_NOT_CONNECTED ? false : true;
}
XINPUT_STATE Controller::GetState()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD result = XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}
