#pragma once

#include <string>
#include <fstream>
#include "DL_StackWalker.h"

#define DL_ASSERT(string) DL_Debug::Debug::GetInstance()->AssertMessage(__FILE__,__LINE__,__FUNCTION__,string);
#define DL_ASSERT_EX(expression, string) DL_Debug::Debug::GetInstance()->AssertMessage((expression), __FILE__,__LINE__,__FUNCTION__,string);
#define DL_PRINT(string)  DL_Debug::Debug::GetInstance()->PrintMessage(string);
#define DL_DEBUG( ... )  DL_Debug::Debug::GetInstance()->DebugMessage(__LINE__,__FUNCTION__,__VA_ARGS__);


namespace DL_Debug
{
	class Debug
	{
	public:
		static bool Create(std::string aFile = "DebugLogger.txt");
		static bool Destroy();
		static Debug* GetInstance();

		void AssertMessage(const char *aFileName, int aLine, const char *aFunctionName, const char *aString);
		void AssertMessage(bool aExpression, const char *aFileName, int aLine, const char *aFunctionName, const char *aString);
		void PrintMessage(const char *aString);
		void DebugMessage(const int aLine, const char *aFileName, const char *aFormattedString, ...);

	private:
		Debug(std::string aFile);
		~Debug();
		static Debug* ourInstance;

		std::ofstream myLogFile;
	};
};



