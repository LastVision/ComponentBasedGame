#pragma once

#include "tinyxml2.h"
#include <string>

#define XMLElement tinyxml2::XMLElement*

class XMLReader
{
public:
	XMLReader();
	~XMLReader();

	void OpenDocument(const std::string& aFilePath);
	void OpenForReadingWithoutDocument();
	void CloseDocument();

	std::string GetElementName(XMLElement aElement);




	/*
	---------------------------
	  Normal Find Operations
	---------------------------

	These will try to find the requested element, if the element is not found
	a nullptr will be returned
	*/

	XMLElement FindFirstChild();
	XMLElement FindFirstChild(const std::string& aChildName);
	XMLElement FindFirstChild(XMLElement aParent) const;
	XMLElement FindFirstChild(XMLElement aParent, const std::string& aChildName) const;
	XMLElement FindNextElement(const std::string& aElementName);
	XMLElement FindNextElement(XMLElement aPrevElement) const;
	XMLElement FindNextElement(XMLElement aPrevElement, const std::string& aElementName) const;





	/*
	---------------------------
	Force Find Operations
	---------------------------

	These will try to find the requested element, however it will
	not return a nullptr if the element isnt found.
	Instead it will crash and print an errormessage into
	the DebugLogger about the involved Parent, Child, Element and Document
	*/

	XMLElement ForceFindFirstChild(const std::string& aChildName);
	XMLElement ForceFindFirstChild(XMLElement aParent) const;
	XMLElement ForceFindFirstChild(XMLElement aParent, const std::string& aChildName) const;
	XMLElement ForceFindNextElement(const std::string& aElementName);
	XMLElement ForceFindNextElement(XMLElement aPrevElement) const;
	XMLElement ForceFindNextElement(XMLElement aPrevElement, const std::string& aElementName) const;

	

	

	/*
	---------------------------
	   Normal Read Operations
	---------------------------

	These will try to read the attribute from the element and store the value
	into the targetvariable.
	If the attribute is not found, the targetvariable simply wont be changed,
	the program wont crash or even produce an error.
	*/

	bool ReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, std::string& aTargetVariable);
	bool ReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, int* aTargetVariable);
	bool ReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, float* aTargetVariable);
	bool ReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, double* aTargetVariable);
	bool ReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, bool* aTargetVariable);
	bool ReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, char* aTargetVariable);



	/*
	---------------------------
	   Force Read Operations
	---------------------------

	These will try to read the attribute from the element and store the value
	into the targetvariable.
	If the attribute is not found, the program will crash and print an
	error message to the DebugLogger about the involved Element, Attribute and Document.
	*/

	bool ForceReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, std::string& aTargetVariable);
	bool ForceReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, int* aTargetVariable);
	bool ForceReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, float* aTargetVariable);
	bool ForceReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, double* aTargetVariable);
	bool ForceReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, bool* aTargetVariable);
	bool ForceReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, char* aTargetVariable);
	
private:

	/*
	---------------------------
	     Debug Operations
	---------------------------

	These are used to verify that the FindFirstChild and FindNextSiblingElement
	functions return valid pointers, that is, pointers that isnt nullptr.

	The ForceFind-functions all use these debugfunctions to verify that 
	the requested Child/Element was found and crashes otherwise.
	*/

	void DebugFirstChild();
	void DebugFirstChild(const std::string& aChildName);
	void DebugFirstChild(XMLElement aParent) const;
	void DebugFirstChild(XMLElement aParent, const std::string& aChildName) const;

	void DebugNextElement(const std::string& aChildName);
	void DebugNextElement(XMLElement aParent) const;
	void DebugNextElement(XMLElement aParent, const std::string& aChildName) const;

	

	tinyxml2::XMLDocument* myDoc;
	std::string myFilePath;
	bool myReadingAllowed;
	bool myHasDocument;
};

