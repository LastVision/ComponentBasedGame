#pragma once

#include <vector>
#include <assert.h>

template <typename T> 
class TemplateQueue
{
public:
	TemplateQueue();
	~TemplateQueue();

	void Enqueue(T aObject);
	void Dequeue();
	int Count() const;
	void Reset();

	T& Peek();

	const std::vector<T>& GetFullQueue();

private:
	std::vector<T> myVector;
};

template <typename T>
TemplateQueue<T>::TemplateQueue()
{
	myVector.reserve(100);
}

template <typename T>
TemplateQueue<T>::~TemplateQueue()
{
}

template <typename T>
void TemplateQueue<T>::Enqueue(T aVector)
{
	myVector.push_back(aVector);
}

template <typename T>
void TemplateQueue<T>::Dequeue()
{
	assert(myVector.size() > 0 && "Tried to dequeue an empty queue");
	myVector.erase(myVector.begin());
}

template <typename T>
int TemplateQueue<T>::Count() const
{
	return myVector.size();
}

template <typename T>
T& TemplateQueue<T>::Peek()
{
	assert(myVector.size() > 0 && "Tried to peek into an empty queue");
	return myVector[0];
}

template <typename T>
const std::vector<T>& TemplateQueue<T>::GetFullQueue()
{
	return myVector;
}

template <typename T>
void TemplateQueue<T>::Reset()
{
	myVector.clear();
}
