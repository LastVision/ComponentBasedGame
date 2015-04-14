#include <stdarg.h>
#include <sstream>
#include "DL_Assert.h"
#include "DL_Debug.h"


namespace DL_Debug
{
	Debug* Debug::ourInstance = nullptr;

	Debug::Debug(std::string aFile)
	{
		myLogFile.open(aFile.c_str(), std::ios::trunc);
	}


	Debug::~Debug()
	{
	}

	bool Debug::Create(std::string aFile)
	{
		assert(ourInstance == nullptr && "DebugObject already created");

		ourInstance = new Debug(aFile);
		if (ourInstance == nullptr)
			return false;

		return true;
	}
	bool Debug::Destroy()
	{
		ourInstance->myLogFile.close();

		delete ourInstance;
		ourInstance = nullptr;

		return true;
	}
	Debug* Debug::GetInstance()
	{
		return ourInstance;
	}

	void Debug::AssertMessage(const char *aFileName, int aLine, const char *aFunctionName, const char *aString)
	{

		std::stringstream sstream;

		sstream << "\nAssert at:\nFile: " << aFileName << "\nLine: " << aLine <<
			"\nFunction: " << aFunctionName << "\nMsg: " << aString;

		myLogFile << "\nAssert at:\nFile: " << aFileName << "\nLine: " << aLine <<
			"\nFunction: " << aFunctionName << "\nMsg: " << aString;

		myLogFile << "\nCallStack:\n";

		DL_Debug::StackWalker ss;
		ss.ShowCallstack();

		myLogFile.flush();


		size_t size = strlen(sstream.str().c_str()) + 1;
		wchar_t* wa = new wchar_t[size];
		size_t tempSize;
		mbstowcs_s(&tempSize, wa, size, sstream.str().c_str(), size);


		_wassert(wa, _CRT_WIDE(__FILE__), __LINE__);
	}

	void Debug::AssertMessage(bool aExpression, const char *aFileName, int aLine, const char *aFunctionName, const char *aString)
	{
		if (aExpression == true)
			return;

		myLogFile << "\nAssert at:\nFile: " << aFileName << "\nLine: " << aLine <<
			"\nFunction: " << aFunctionName << "\nMsg: " << aString;

		myLogFile << "\nCallStack:\n";

		DL_Debug::StackWalker ss;
		ss.ShowCallstack();

		myLogFile.flush();

		std::stringstream sstream;

		sstream << "\nAssert at:\nFile: " << aFileName << "\nLine: " << aLine <<
			"\nFunction: " << aFunctionName << "\nMsg: " << aString << std::endl;

		size_t size = strlen(sstream.str().c_str()) + 1;
		wchar_t* wa = new wchar_t[size];
		size_t tempSize;
		mbstowcs_s(&tempSize, wa, size, sstream.str().c_str(), size);


		_wassert(wa, _CRT_WIDE(__FILE__), __LINE__);
	}

	void Debug::PrintMessage(const char *aString)
	{
		myLogFile << aString;
		myLogFile.flush();
	}

	void Debug::DebugMessage(const int aLine, const char *aFileName, const char *aFormattedString, ...)
	{
		myLogFile << "\nLine: " << aLine << "\nFile: " << aFileName << "\n";

		char buffer[256];
		va_list args;
		va_start(args, aFormattedString);

		vsprintf_s(buffer, aFormattedString, args);

		va_end(args);

		myLogFile << "Msg: " << buffer << "\n";

		myLogFile.flush();
	}
};