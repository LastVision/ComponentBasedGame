#pragma once

#include <dinput.h>
#include <Windows.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

struct Position
{
	float myX;
	float myY;
};

enum eMouseButtons
{
	LEFT = 0,
	RIGHT,
	MOUSE_WHEEL
};

class InputWrapper
{
public:
	InputWrapper();
	~InputWrapper();
	bool Init(HWND aHWND);
	void Shutdown();
	void Update();

	inline bool IsKeyDown(const char aChar) const;
	inline bool IsKeyClicked(const char aChar) const;
	inline bool IsKeyUp(const char aChar) const;
	inline bool IsMouseDown(const eMouseButtons aButton) const;
	inline bool IsMouseClicked(const eMouseButtons aButton) const;
	inline bool IsMouseUp(const eMouseButtons aButton) const;
	inline Position MousePos() const;
	inline float GetMouseWheelPos() const;

	char ConvertCharToKey(const char aChar) const;

private:
	LPDIRECTINPUT8 myDirectInputObject;

	LPDIRECTINPUTDEVICE8 myKeyboardDevice;
	char myCurrKeyboardState[256];
	char myPrevKeyboardState[256];

	Position myMousePosition;
	float myMouseWheelPosition;

	LPDIRECTINPUTDEVICE8 myMouseDevice;
	_DIMOUSESTATE myCurrMouseState;
	_DIMOUSESTATE myPrevMouseState;

	HWND myWindowHandle;
};

inline bool InputWrapper::IsKeyDown(const char aChar) const
{
	return (myCurrKeyboardState[aChar] & 0x80) != 0;
}

inline bool InputWrapper::IsKeyUp(const char aChar) const
{
	return (myCurrKeyboardState[aChar] & 0x80) == 0 && (myPrevKeyboardState[aChar] & 0x80) != 0;
}

inline bool InputWrapper::IsKeyClicked(const char aChar) const
{
	return ((myCurrKeyboardState[aChar] & 0x80) != 0 && (myPrevKeyboardState[aChar] & 0x80) == 0);
}

inline bool InputWrapper::IsMouseDown(const eMouseButtons aButton) const
{
	return (myCurrMouseState.rgbButtons[aButton] & 0x80) != 0;
}

inline bool InputWrapper::IsMouseUp(const eMouseButtons aButton) const
{
	return (myCurrMouseState.rgbButtons[aButton] & 0x80) == 0 && (myPrevMouseState.rgbButtons[aButton] & 0x80) != 0;
}

inline bool InputWrapper::IsMouseClicked(const eMouseButtons aButton) const
{
	return ((myCurrMouseState.rgbButtons[aButton] & 0x80) != 0 && (myPrevMouseState.rgbButtons[aButton] & 0x80) == 0);
}

inline Position InputWrapper::MousePos() const
{
	return myMousePosition;
}

inline float InputWrapper::GetMouseWheelPos() const
{
	return myMouseWheelPosition;
}