#include "XMLReader.h"
#include "DL_Debug.h"

XMLReader::XMLReader()
{
	myReadingAllowed = false;
	myHasDocument = false;
	myDoc = nullptr;
}


XMLReader::~XMLReader()
{
}

void XMLReader::OpenDocument(const std::string& aFilePath)
{
	delete myDoc;

	if (myDoc == nullptr)
	{
		myDoc = new tinyxml2::XMLDocument();
	}

	tinyxml2::XMLError error = myDoc->LoadFile(aFilePath.c_str());
	if (error == 0)
	{
		myReadingAllowed = true;
		myHasDocument = true;
		myFilePath = aFilePath;
	}
	else
	{
#pragma region Error-Codes
		switch (error)
		{
		case tinyxml2::XML_NO_ATTRIBUTE:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_NO_ATTRIBUTE", aFilePath.c_str());
			break;
		case tinyxml2::XML_WRONG_ATTRIBUTE_TYPE:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_WRONG_ATTRIBUTE_TYPE", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_FILE_NOT_FOUND:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_FILE_NOT_FOUND", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_FILE_COULD_NOT_BE_OPENED", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_FILE_READ_ERROR:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_FILE_READ_ERROR", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_ELEMENT_MISMATCH:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_ELEMENT_MISMATCH", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_PARSING_ELEMENT:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_PARSING_ELEMENT", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_PARSING_ATTRIBUTE:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_PARSING_ATTRIBUTE", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_IDENTIFYING_TAG:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_IDENTIFYING_TAG", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_PARSING_TEXT:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_PARSING_TEXT", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_PARSING_CDATA:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_PARSING_CDATA", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_PARSING_COMMENT:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_PARSING_COMMENT", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_PARSING_DECLARATION:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_PARSING_DECLARATION", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_PARSING_UNKNOWN:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_PARSING_UNKNOWN", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_EMPTY_DOCUMENT:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_EMPTY_DOCUMENT", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_MISMATCHED_ELEMENT:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_MISMATCHED_ELEMENT", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_PARSING:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_PARSING", aFilePath.c_str());
			break;
		case tinyxml2::XML_CAN_NOT_CONVERT_TEXT:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_CAN_NOT_CONVERT_TEXT", aFilePath.c_str());
			break;
		case tinyxml2::XML_NO_TEXT_NODE:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_NO_TEXT_NODE", aFilePath.c_str());
			break;
		case tinyxml2::XML_ERROR_COUNT:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: XML_ERROR_COUNT", aFilePath.c_str());
			break;
		default:
			DL_DEBUG("Failed to Open XML File. File: %s, Error: Unknown, non of tinyxml's error codes caught it :(", aFilePath.c_str());
			break;
		}
#pragma endregion

		DL_ASSERT("[XMLReader]: Failed to Open XML File. Check Debuglog for error");
	}
}

void XMLReader::OpenForReadingWithoutDocument()
{
	if (myReadingAllowed == true)
	{
		DL_DEBUG("[XMLReader]: Tried to [OpenForReadingWithoutDocument] when the XMLReader had allready opened an document.");
		DL_ASSERT("[XMLReader]: Tried to open an document when one was allready open.");
	}
	myReadingAllowed = true;
	myFilePath = "Unknown FilePath. Used [OpenForReadingWithoutDocument]";
}

void XMLReader::CloseDocument()
{
	if (myHasDocument == true)
	{
		myHasDocument = false;
		myFilePath = "";
		delete myDoc;
		myDoc = nullptr;
	}

	myReadingAllowed = false;
}

std::string XMLReader::GetElementName(XMLElement aElement)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [GetElementName] before reading was allowed.");

	return aElement->Name();
}

/*
	---------------------------
	  Normal Find Operations
	---------------------------
*/

XMLElement XMLReader::FindFirstChild()
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [FindFirstChild] before reading was allowed.");

	if (myHasDocument == false)
		DL_ASSERT("[XMLReader]: Tried to [FindFirstChild] in the document, but there was no document opened.");

	return myDoc->FirstChildElement();
}

XMLElement XMLReader::FindFirstChild(const std::string& aChildName)
{
	if (myReadingAllowed == false)
	{
		DL_DEBUG("[XMLReader]: Tried to [FindFirstChild] before reading was allowed. Document: [ None ], Child: [ %s ].", aChildName.c_str());
		DL_ASSERT("[XMLReader]: Tried to [FindFirstChild] before reading was allowed.");
	}

	if (myHasDocument == false)
	{
		DL_DEBUG("[XMLReader]: Tried to [FindFirstChild], but there was no document opened. Document: [ None ], Child: [ %s ].", aChildName.c_str());
		DL_ASSERT("[XMLReader]: Tried to [FindFirstChild], but there was no document opened.");
	}
	
	return myDoc->FirstChildElement(aChildName.c_str());
}

XMLElement XMLReader::FindFirstChild(XMLElement aParent) const
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [FindFirstChild] before reading was allowed.");

	return aParent->FirstChildElement();
}

XMLElement XMLReader::FindFirstChild(XMLElement aParent, const std::string& aChildName) const
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [FindFirstChild] before reading was allowed.");


	return aParent->FirstChildElement(aChildName.c_str());
}

XMLElement XMLReader::FindNextElement(const std::string& aElementName)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [FindNextElement] before reading was allowed.");

	if (myHasDocument == false)
	{
		DL_ASSERT("[XMLReader]: Tried to [FindNextElement], but there was no document opened.");
	}

	return myDoc->NextSiblingElement(aElementName.c_str());
	
}

XMLElement XMLReader::FindNextElement(XMLElement aPrevElement) const
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [FindNextElement] before reading was allowed.");

	return aPrevElement->NextSiblingElement();
}

XMLElement XMLReader::FindNextElement(XMLElement aPrevElement, const std::string& aElementName) const
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [FindNextElement] before reading was allowed.");

	return aPrevElement->NextSiblingElement(aElementName.c_str());
}



/*
	---------------------------
	   Force Find Operations
	---------------------------
*/

XMLElement XMLReader::ForceFindFirstChild(const std::string& aChildName)
{
	if (myHasDocument == false)
		DL_ASSERT("[XMLReader]: Tried to [FindFirstChild] before reading was allowed.");

	if (myHasDocument == false)
	{
		DL_ASSERT("[XMLReader]: Tried to [FindFirstChild], but there was no document opened.");
	}

	DebugFirstChild(aChildName);

	return myDoc->FirstChildElement(aChildName.c_str());
}

XMLElement XMLReader::ForceFindFirstChild(XMLElement aParent) const
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [FindFirstChild] before reading was allowed.");

	DebugFirstChild(aParent);

	return aParent->FirstChildElement();
}

XMLElement XMLReader::ForceFindFirstChild(XMLElement aParent, const std::string& aChildName) const
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [FindFirstChild] before reading was allowed.");


	DebugFirstChild(aParent, aChildName);

	return aParent->FirstChildElement(aChildName.c_str());
}

XMLElement XMLReader::ForceFindNextElement(const std::string& aElementName)
{
	if (myHasDocument == false)
		DL_ASSERT("[XMLReader]: Tried to [FindNextElement] before reading was allowed.");

	if (myHasDocument == false)
	{
		DL_ASSERT("[XMLReader]: Tried to [FindNextElement], but there was no document opened.");
	}

	DebugNextElement(aElementName);

	return myDoc->NextSiblingElement(aElementName.c_str());

}

XMLElement XMLReader::ForceFindNextElement(XMLElement aPrevElement) const
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [FindNextElement] before reading was allowed.");

	DebugNextElement(aPrevElement);

	return aPrevElement->NextSiblingElement();
}

XMLElement XMLReader::ForceFindNextElement(XMLElement aPrevElement, const std::string& aElementName) const
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [FindNextElement] before reading was allowed.");

	DebugNextElement(aPrevElement, aElementName);

	return aPrevElement->NextSiblingElement(aElementName.c_str());
}



/*
	---------------------------
	  Normal Read Operations
	---------------------------
*/

bool XMLReader::ReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, std::string& aTargetVariable)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(string)] before reading was allowed.");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->FindAttribute(aAttributeToRead.c_str()) != 0)
	{
		aTargetVariable = aElementToReadFrom->Attribute(aAttributeToRead.c_str());
		return true;
	}

	return false;
}

bool XMLReader::ReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, int* aTargetVariable)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(int)] before reading was allowed.");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->QueryIntAttribute(aAttributeToRead.c_str(), aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	return false;
}

bool XMLReader::ReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, float* aTargetVariable)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(float)] before reading was allowed.");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->QueryFloatAttribute(aAttributeToRead.c_str(), aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	return false;
}

bool XMLReader::ReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, double* aTargetVariable)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(double)] before reading was allowed.");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->QueryDoubleAttribute(aAttributeToRead.c_str(), aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	return false;
}

bool XMLReader::ReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, bool* aTargetVariable)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(bool)] before reading was allowed.");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->QueryBoolAttribute(aAttributeToRead.c_str(), aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	return false;
}

bool XMLReader::ReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, char* aTargetVariable)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(char)] before reading was allowed.");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->FindAttribute(aAttributeToRead.c_str()) != 0)
	{
		*aTargetVariable = *aElementToReadFrom->Attribute(aAttributeToRead.c_str());
		return true;
	}

	return false;
}

/*
	---------------------------
	   Force Read Operations
	---------------------------
*/

bool XMLReader::ForceReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, std::string& aTargetVariable)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [ForceReadAttribute(string)] before reading was allowed.");

	if (aElementToReadFrom->FindAttribute(aAttributeToRead.c_str()) != 0)
	{
		aTargetVariable = aElementToReadFrom->Attribute(aAttributeToRead.c_str());
		return true;
	}

	DL_DEBUG("Failed to read Attribute: [ %s ], from Element: [ %s ], in Document: [ %s ]", aAttributeToRead.c_str(), aElementToReadFrom->Name(), myFilePath.c_str());
	DL_ASSERT("Failed to [ForceReadAttribute(string)], check DebugLog for more info");
	return false;
}

bool XMLReader::ForceReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, int* aTargetVariable)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [ForceReadAttribute(int)] before reading was allowed.");

	if (aElementToReadFrom->QueryIntAttribute(aAttributeToRead.c_str(), aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	DL_DEBUG("Failed to read Attribute: [ %s ], from Element: [ %s ], in Document: [ %s ]", aAttributeToRead.c_str(), aElementToReadFrom->Name(), myFilePath.c_str());
	DL_ASSERT("Failed to [ForceReadAttribute(int)], check DebugLog for more info");
	return false;
}

bool XMLReader::ForceReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, float* aTargetVariable)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(float)] before reading was allowed.");

	if (aElementToReadFrom->QueryFloatAttribute(aAttributeToRead.c_str(), aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	DL_DEBUG("Failed to read Attribute: [ %s ], from Element: [ %s ], in Document: [ %s ]", aAttributeToRead.c_str(), aElementToReadFrom->Name(), myFilePath.c_str());
	DL_ASSERT("Failed to [ForceReadAttribute(float)], check DebugLog for more info");
	return false;
}

bool XMLReader::ForceReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, double* aTargetVariable)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(double)] before reading was allowed.");

	if (aElementToReadFrom->QueryDoubleAttribute(aAttributeToRead.c_str(), aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	DL_DEBUG("Failed to read Attribute: [ %s ], from Element: [ %s ], in Document: [ %s ]", aAttributeToRead.c_str(), aElementToReadFrom->Name(), myFilePath.c_str());
	DL_ASSERT("Failed to [ForceReadAttribute(double)], check DebugLog for more info");
	return false;
}

bool XMLReader::ForceReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, bool* aTargetVariable)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(bool)] before reading was allowed.");

	if (aElementToReadFrom->QueryBoolAttribute(aAttributeToRead.c_str(), aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	DL_DEBUG("Failed to read Attribute: [ %s ], from Element: [ %s ], in Document: [ %s ]", aAttributeToRead.c_str(), aElementToReadFrom->Name(), myFilePath.c_str());
	DL_ASSERT("Failed to [ForceReadAttribute(bool)], check DebugLog for more info");
	return false;
}

bool XMLReader::ForceReadAttribute(const XMLElement aElementToReadFrom, const std::string& aAttributeToRead, char* aTargetVariable)
{
	if (myReadingAllowed == false)
		DL_ASSERT("[XMLReader]: Tried to [ForceReadAttribute(char)] before reading was allowed.");

	if (aElementToReadFrom->FindAttribute(aAttributeToRead.c_str()) != 0)
	{
		*aTargetVariable = *aElementToReadFrom->Attribute(aAttributeToRead.c_str());
		return true;
	}

	DL_DEBUG("Failed to read Attribute: [ %s ], from Element: [ %s ], in Document: [ %s ]", aAttributeToRead.c_str(), aElementToReadFrom->Name(), myFilePath.c_str());
	DL_ASSERT("Failed to [ForceReadAttribute(char)], check DebugLog for more info");
	return false;
}


/*
	---------------------------
	     Debug Operations
	---------------------------
*/
void XMLReader::DebugFirstChild()
{
	if (myDoc->FirstChildElement() == nullptr)
	{
		DL_DEBUG("Failed to [ForceFindFirstChild]. Parent: [ Document ], Child: [ None (Tried to find first in document) ], File: [ %s ]", myFilePath.c_str());
		DL_ASSERT("Failed to [ForceFindFirstChild], check DebugLog for more info");
	}
}

void XMLReader::DebugFirstChild(const std::string& aChildName)
{
	if (myDoc->FirstChildElement(aChildName.c_str()) == nullptr)
	{
		DL_DEBUG("Failed to [ForceFindFirstChild]. Parent: [ Document ], Child: [ %s ], File: [ %s ]", aChildName.c_str(), myFilePath.c_str());
		DL_ASSERT("Failed to [ForceFindFirstChild], check DebugLog for more info");
	}
}

void XMLReader::DebugFirstChild(XMLElement aParent) const
{
	if (aParent->FirstChildElement() == nullptr)
	{
		DL_DEBUG("Failed to [ForceFindFirstChild]. Parent: [ %s ], Child: [ First ], File:  [ %s ]", aParent->Name(), myFilePath.c_str());
		DL_ASSERT("Failed to [ForceFindFirstChild], check DebugLog for more info");
	}
}

void XMLReader::DebugFirstChild(XMLElement aParent, const std::string& aChildName) const
{
	if (aParent->FirstChildElement(aChildName.c_str()) == nullptr)
	{
		DL_DEBUG("Failed to [ForceFindFirstChild]. Parent: [ %s ], Child: [ %s ], File: [ %s ]", aParent->Name(), aChildName.c_str(), myFilePath.c_str());
		DL_ASSERT("Failed to [ForceFindFirstChild], check DebugLog for more info");
	}
}
	
void XMLReader::DebugNextElement(const std::string& aChildName)
{
	if (myDoc->NextSiblingElement(aChildName.c_str()) == nullptr)
	{
		DL_DEBUG("Failed to [ForceFindNextElement]. Parent: [ Document ], Child: [ %s ], File: [ %s ]", aChildName.c_str(), myFilePath.c_str());
		DL_ASSERT("Failed to [ForceFindNextElement], check DebugLog for more info");
	}
}

void XMLReader::DebugNextElement(XMLElement aParent) const
{
	if (aParent->NextSiblingElement() == nullptr)
	{
		DL_DEBUG("Failed to [ForceFindNextElement]. Parent: [ %s ], Child: [ First ], File: [ %s ]", aParent->Name(), myFilePath.c_str());
		DL_ASSERT("Failed to [ForceFindNextElement], check DebugLog for more info");
	}
}

void XMLReader::DebugNextElement(XMLElement aParent, const std::string& aChildName) const
{
	if (aParent->NextSiblingElement(aChildName.c_str()) == nullptr)
	{
		DL_DEBUG("Failed to [ForceFindNextElement]. Parent: [ %s ], Child: [ %s ], File: [ %s ]", aParent->Name(), aChildName.c_str(), myFilePath.c_str());
		DL_ASSERT("Failed to [ForceFindNextElement], check DebugLog for more info");
	}
}