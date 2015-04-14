#include "InputWrapper.h"
#include <sstream>


InputWrapper::InputWrapper()
{

}


InputWrapper::~InputWrapper()
{
	Shutdown();
}

bool InputWrapper::Init(HWND aHWND)
{
	DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&myDirectInputObject, nullptr);


	myDirectInputObject->CreateDevice(GUID_SysKeyboard, &myKeyboardDevice, nullptr);

	if (myKeyboardDevice != NULL)
	{
		myKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
		myKeyboardDevice->SetCooperativeLevel(GetActiveWindow(), DISCL_BACKGROUND | DISCL_EXCLUSIVE);
		myKeyboardDevice->Acquire();
	}
	else
	{
		OutputDebugStringA("COULD NOT CREATE KEYBOARD");
		return false;
	}

	myDirectInputObject->CreateDevice(GUID_SysMouse, &myMouseDevice, NULL);
	if (myMouseDevice)
	{
		myMouseDevice->SetDataFormat(&c_dfDIMouse);
		myMouseDevice->SetCooperativeLevel(GetActiveWindow(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
		myMouseDevice->SetProperty(DIPROP_AXISMODE, DIPROPAXISMODE_ABS);
		myMouseDevice->Acquire();
	}
	else
	{
		OutputDebugStringA("COULD NOT CREATE MOUSE");
		return false;
	}

	myMousePosition.myX = 0;
	myMousePosition.myY = 0;
	myMouseWheelPosition = 0;


	myWindowHandle = aHWND;

	return true;
}

void InputWrapper::Shutdown()
{
	if (myMouseDevice)
	{
		myMouseDevice->Unacquire();
		myMouseDevice->Release();
		myMouseDevice = 0;
	}

	if (myKeyboardDevice)
	{
		myKeyboardDevice->Unacquire();
		myKeyboardDevice->Release();
		myKeyboardDevice = 0;
	}

	if (myDirectInputObject)
	{
		myDirectInputObject->Release();
		myDirectInputObject = 0;
	}
}

void InputWrapper::Update()
{
	//Copy the previous frames keyboardState into prevState before we grab the new states
	memcpy_s(myPrevKeyboardState, sizeof(myPrevKeyboardState), myCurrKeyboardState, sizeof(myCurrKeyboardState));
	myKeyboardDevice->GetDeviceState(sizeof(myCurrKeyboardState), (LPVOID)&myCurrKeyboardState);

	//Same for mouseState
	myPrevMouseState = myCurrMouseState;
	myMouseDevice->GetDeviceState(sizeof(_DIMOUSESTATE), &myCurrMouseState);

	tagPOINT cursorXandY;
	GetCursorPos(&cursorXandY);
	ScreenToClient(myWindowHandle, &cursorXandY);

	//Add the positionchanges (position-delta) that we read form the mouse
	myMousePosition.myX = static_cast<float>(cursorXandY.x);
	myMousePosition.myY = static_cast<float>(cursorXandY.y);
	//The "Z" value of the mouse is the mousewheel
	myMouseWheelPosition += myCurrMouseState.lZ;
}

char InputWrapper::ConvertCharToKey(const char aChar) const
{
	switch (aChar)
	{
		//Upper Case Char
	case 'A':
		return DIK_A;
		break;
	case 'B':
		return DIK_B;
		break;
	case 'C':
		return DIK_C;
		break;
	case 'D':
		return DIK_D;
		break;
	case 'E':
		return DIK_E;
		break;
	case 'F':
		return DIK_F;
		break;
	case 'G':
		return DIK_G;
		break;
	case 'H':
		return DIK_H;
		break;
	case 'I':
		return DIK_I;
		break;
	case 'J':
		return DIK_J;
		break;
	case 'K':
		return DIK_K;
		break;
	case 'L':
		return DIK_L;
		break;
	case 'M':
		return DIK_M;
		break;
	case 'N':
		return DIK_N;
		break;
	case 'O':
		return DIK_O;
		break;
	case 'P':
		return DIK_P;
		break;
	case 'Q':
		return DIK_Q;
		break;
	case 'R':
		return DIK_R;
		break;
	case 'S':
		return DIK_S;
		break;
	case 'T':
		return DIK_T;
		break;
	case 'U':
		return DIK_U;
		break;
	case 'V':
		return DIK_V;
		break;
	case 'W':
		return DIK_W;
		break;
	case 'X':
		return DIK_X;
		break;
	case 'Y':
		return DIK_Y;
		break;
	case 'Z':
		return DIK_Z;
		break;

		//Lower Case Char
	case 'a':
		return DIK_A;
		break;
	case 'b':
		return DIK_B;
		break;
	case 'c':
		return DIK_C;
		break;
	case 'd':
		return DIK_D;
		break;
	case 'e':
		return DIK_E;
		break;
	case 'f':
		return DIK_F;
		break;
	case 'g':
		return DIK_G;
		break;
	case 'h':
		return DIK_H;
		break;
	case 'i':
		return DIK_I;
		break;
	case 'j':
		return DIK_J;
		break;
	case 'k':
		return DIK_K;
		break;
	case 'l':
		return DIK_L;
		break;
	case 'm':
		return DIK_M;
		break;
	case 'n':
		return DIK_N;
		break;
	case 'o':
		return DIK_O;
		break;
	case 'p':
		return DIK_P;
		break;
	case 'q':
		return DIK_Q;
		break;
	case 'r':
		return DIK_R;
		break;
	case 's':
		return DIK_S;
		break;
	case 't':
		return DIK_T;
		break;
	case 'u':
		return DIK_U;
		break;
	case 'v':
		return DIK_V;
		break;
	case 'w':
		return DIK_W;
		break;
	case 'x':
		return DIK_X;
		break;
	case 'y':
		return DIK_Y;
		break;
	case 'z':
		return DIK_Z;
		break;

	default:
		break;
	}

	return aChar;
}


