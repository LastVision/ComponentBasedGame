#pragma once

#include <vector>
#include "line.h"

template <typename T>
class LineVolume
{
public:
	LineVolume();
	LineVolume(std::vector<Line<T>> aLineList);
	~LineVolume();

	void AddLine(Line<T> aLine);
	void RemoveLine(Line<T> aLine);

	bool Inside(CU::Vector2<T> aPosition);

private:
	std::vector<Line<T>> myLines;
};

template <typename T>
LineVolume<T>::LineVolume()
{

}

template <typename T>
LineVolume<T>::LineVolume(std::vector<Line<T>> aLineList)
{
	myLines = aLineList;
}

template <typename T>
LineVolume<T>::~LineVolume()
{
	
}


template <typename T>
void LineVolume<T>::AddLine(Line<T> aLine)
{
	myLines.push_back(aLine);
}

template <typename T>
void LineVolume<T>::RemoveLine(Line<T> aLine)
{
	for (unsigned int i = 0; i < myLines.size(); i++)
	{
		if (myLines[i].GetPoint() == aLine.GetPoint() && myLines[i].GetNormal() == aLine.GetNormal())
		{
			myLines.erase(myLines.begin() + i);
			return;
		}
	}
}


template <typename T>
bool LineVolume<T>::Inside(CU::Vector2<T> aPosition)
{
	for (unsigned int i = 0; i < myLines.size(); i++)
	{
		if (myLines[i].Inside(aPosition) == false)
			return false;
	}

	return true;
}