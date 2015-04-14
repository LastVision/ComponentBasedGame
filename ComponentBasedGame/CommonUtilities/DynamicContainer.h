#pragma once

#include <memory>
#include <assert.h>

#define HEAD template<typename T, int StartSize = 8, bool UseSafeModeFlag = true>
#define TYPE DynamicContainer<T, StartSize, UseSafeModeFlag>

namespace CommonUtilities
{
	HEAD
	class DynamicContainer
	{
	public:
		DynamicContainer();
		DynamicContainer(const DynamicContainer &aDynamicContainer);
		~DynamicContainer();

		DynamicContainer& operator=(const DynamicContainer &aDynamicContainer);

		inline const T& operator[](const int &aIndex) const;
		inline T& operator[](const int &aIndex);

		inline void Add(const T &aObject);
		inline void Insert(int aIndex, const T &aObject);
		inline void DeleteCyclic(T &aObject);
		inline void DeleteCyclicAtIndex(int aIndex);
		inline void RemoveCyclic(const T &aObject);
		inline void RemoveCyclicAtIndex(int aIndex);
		inline void RemoveAll();
		inline void DeleteAll();

		inline int Find(const T &aObject);

		inline T& GetLast();
		inline const T& GetLast() const;

		static const int FoundNone = static_cast<int>(-1);


		void Optimize();
		__forceinline int Size() const;

	private:
		inline void ResizeHeapMemory();
		__forceinline bool IsStackFull();

		void InsertOnStack(const int aIndex, const T &aObject);
		void InsertOnHeap(const int aIndex, const T &aObject);

		T myStackData[StartSize];
		T *myHeapData;
		int myStackNumElements;
		int myStackSize;

		int myHeapNumElements;
		int myHeapSize;
		bool mySafeMode;
		bool myHeapInited;
	};

	HEAD
	TYPE::DynamicContainer()
	{
		myHeapInited = false;
		mySafeMode = UseSafeModeFlag;

		myStackNumElements = 0;
		myStackSize = StartSize;

		myHeapNumElements = 0;
		myHeapSize = 0;

		myHeapData = nullptr;
	}

	HEAD
	TYPE::DynamicContainer(const DynamicContainer &aDynamicContainer)
	{
		myHeapData = nullptr;
		*this = aDynamicContainer;
	}

	HEAD
	TYPE::~DynamicContainer()
	{
		delete[] myHeapData;
		myHeapData = nullptr;
	}

	HEAD
	TYPE& TYPE::operator=(const DynamicContainer &aDynamicContainer)
	{
		delete[] myHeapData;

		mySafeMode = aDynamicContainer.mySafeMode;
		myHeapSize = aDynamicContainer.myHeapSize;
		myHeapInited = aDynamicContainer.myHeapInited;
		myStackSize = aDynamicContainer.myStackSize;

		myHeapNumElements = aDynamicContainer.myHeapNumElements;
		myStackNumElements = aDynamicContainer.myStackNumElements;

		if (mySafeMode == true)
		{
			//Copy stuff from the stack
			for (int i = 0; i < aDynamicContainer.myStackNumElements; ++i)
			{
				myStackData[i] = aDynamicContainer[i];
			}

			//Do we need to copy the heapdata?
			if (myHeapInited == true)
			{
				myHeapData = new T[myHeapSize];
				for (int i = 0; i < aDynamicContainer.myHeapNumElements; ++i)
				{
					myHeapData[i] = aDynamicContainer.myHeapData[i];
				}
			}
		}
		else
		{
			//Copy stuff from the stack
			myStackNumElements = aDynamicContainer.myStackNumElements;
			memcpy(this, &aDynamicContainer.myStackData, sizeof(aDynamicContainer.myStackData));

			if (myHeapInited == true)
			{
				myHeapNumElements = aDynamicContainer.myHeapNumElements;
				myHeapData = new T[myHeapSize];

				memcpy(myHeapData, aDynamicContainer.myHeapData, sizeof(T) * aDynamicContainer.myHeapNumElements);
			}
		}

		return *this;
	}


	//----- CONST_SUBSCRIPT ------
	//----------------------------
	HEAD
	const T& TYPE::operator[](const int &aIndex) const
	{
		assert(aIndex < Size() && "[DynamicArray]: Tried to use [Subscript-operator] with an index greater than the number of elements.");
		assert(aIndex >= 0 && "[DynamicArray]: Tried to use [Subscript-operator] with an index smaller than zero.");

		if (aIndex >= myStackSize && myHeapInited == true)
			return myHeapData[aIndex - myStackSize];
		else
			return myStackData[aIndex];
	}

	//----- SUBSCRIPT ------
	//----------------------
	HEAD
	T& TYPE::operator[](const int &aIndex)
	{
		assert(aIndex < Size() && "[DynamicArray]: Tried to use [Subscript-operator] with an index greater than the number of elements.");
		assert(aIndex >= 0 && "[DynamicArray]: Tried to use [Subscript-operator] with an index smaller than zero.");


		if (aIndex >= myStackSize && myHeapInited == true)
			return myHeapData[aIndex - myStackSize];
		else
			return myStackData[aIndex];
	}



	//----- ADD ------
	//----------------
	HEAD
	void TYPE::Add(const T &aObject)
	{
		if (IsStackFull())
		{
			if (myHeapInited == false)
			{
				myHeapSize = myStackSize * 2;
				myHeapData = new T[myHeapSize];
				myHeapInited = true;
			}

			if (myHeapNumElements >= myHeapSize)
			{
				ResizeHeapMemory();
			}

			myHeapData[myHeapNumElements] = aObject;
			++myHeapNumElements;
		}
		else
		{
			myStackData[myStackNumElements] = aObject;
			++myStackNumElements;
		}
	}


	//----- INSERT ------
	//-------------------
	HEAD
	void TYPE::Insert(int aIndex, const T &aObject)
	{
		assert(aIndex < Size() && "[DynamicArray]: Tried to [Insert] at an index greater than the size.");
		assert(aIndex >= 0 && "[DynamicArray]: Tried to [Insert] at an index smaller than zero.");

		if (IsStackFull())
		{
			//Init the heap if it isnt inited...
			if (myHeapInited == false)
			{
				myHeapSize = myStackSize * 2;
				myHeapData = new T[myHeapSize];
				myHeapInited = true;
			}

			//Are we trying to insert onto the stackmemory? Then we need to do some extra work
			if (aIndex < myStackSize)
			{
				//Copy the last object from stackmemory
				T lastStackObj = myStackData[myStackNumElements-1];
				--myStackNumElements;

				//Insert the new object on the stack at the requested index
				InsertOnStack(aIndex, aObject);

				//Does the heap have room for more stuff?
				if (myHeapNumElements >= myHeapSize)
				{
					ResizeHeapMemory();
				}

				//Insert the element that was last in stackmemory first in heapmemory
				InsertOnHeap(0, lastStackObj);
			}
			//If not then just insert onto heapmemory
			else
			{
				InsertOnHeap(aIndex - myStackSize, aObject);
			}
		}
		else
		{
			InsertOnStack(aIndex, aObject);
		}
	}




	//----- DELETE_CYCLIC ------
	//--------------------------
	HEAD
	void TYPE::DeleteCyclic(T &aObject)
	{
		bool deleteSuccesful = false;

		for (int i = 0; i < myStackNumElements; ++i)
		{
			if (myStackData[i] == aObject)
			{
				delete myStackData[i];
				myStackData[i] = myStackData[myStackNumElements - 1];
				--myStackNumElements;
				deleteSuccesful = true;
				break;
			}
		}

		//Do we have heap memory and did we not find the object on the stack?
		if (myHeapInited == true && deleteSuccesful == false)
		{
			for (int i = 0; i < myHeapNumElements; ++i)
			{
				if (myHeapData[i] == aObject)
				{
					delete myHeapData[i];
					myHeapData[i] = myHeapData[myHeapNumElements - 1];
					--myHeapNumElements;
					deleteSuccesful = true;
					break;
				}
			}
		}

		assert(deleteSuccesful && "[DynamicContainer]: Tried to [DeleteCyclic] an item that wasnt found in the container.");
	}

	//----- DELETE_CYCLIC_AT_INDEX ------
	//-----------------------------------
	HEAD
	void TYPE::DeleteCyclicAtIndex(int aIndex)
	{
		assert(aIndex >= 0 && "[DynamicContainer]: Tried to [DeleteCyclicAtIndex] at an index thats less than 0.");
		assert(aIndex < Size() && "[DynamicContainer]: Tried to [DeleteCyclicAtIndex] at an index greater than the number of elements.");

		if (aIndex < myStackNumElements)
		{
			delete myStackData[aIndex];

			if (myHeapInited == true)
			{
				myStackData[aIndex] = myHeapData[myHeapNumElements - 1];
				--myHeapNumElements;

				if (myHeapNumElements <= 0)
				{
					myHeapInited = false;
					delete[] myHeapData;
					myHeapData = nullptr;
				}
			}
			else
			{
				myStackData[aIndex] = myStackData[myStackNumElements - 1];
				--myStackNumElements;
			}
			
		}
		else if (myHeapInited == true)
		{
			delete myHeapData[aIndex];
			myHeapData[aIndex] = myHeapData[myHeapNumElements - 1];
			--myHeapNumElements;

			if (myHeapNumElements <= 0)
			{
				myHeapInited = false;
				delete[] myHeapData;
				myHeapData = nullptr;
			}
		}
	}




	//----- REMOVE_CYCLIC ------
	//--------------------------
	HEAD
	void TYPE::RemoveCyclic(const T &aObject)
	{
		bool removalSuccesful = false;

		for (int i = 0; i < myStackNumElements; ++i)
		{
			if (myStackData[i] == aObject)
			{
				myStackData[i] = myStackData[myStackNumElements - 1];
				--myStackNumElements;
				removalSuccesful = true;
				break;
			}
		}

		//Do we have heap memory and did we not find the object on the stack?
		if (myHeapInited == true && removalSuccesful == false)
		{
			for (int i = 0; i < myHeapNumElements; ++i)
			{
				if (myHeapData[i] == aObject)
				{
					myHeapData[i] = myHeapData[myHeapNumElements - 1];
					--myHeapNumElements;
					removalSuccesful = true;
					break;
				}
			}
		}

		assert(removalSuccesful && "[DynamicContainer]: Tried to [RemoveCyclic] an item that wasnt found in the container.");
	}

	//----- REMOVE_CYCLIC_AT_INDEX ------
	//-----------------------------------
	HEAD
	void TYPE::RemoveCyclicAtIndex(int aIndex)
	{
		assert(aIndex >= 0 && "[DynamicContainer]: Tried to [RemoveCyclicAtIndex] at an index thats less than 0.");
		assert(aIndex < Size() && "[DynamicContainer]: Tried to [RemoveCyclicAtIndex] at an index greater than the number of elements.");

		if (aIndex < myStackNumElements)
		{
			if (myHeapInited == true)
			{
				myStackData[aIndex] = myHeapData[myHeapNumElements - 1];
				--myHeapNumElements;

				if (myHeapNumElements <= 0)
				{
					myHeapInited = false;
					delete[] myHeapData;
					myHeapData = nullptr;
				}
			}
			else
			{
				myStackData[aIndex] = myStackData[myStackNumElements - 1];
				--myStackNumElements;
			}
		}
		else
		{
			myHeapData[aIndex] = myHeapData[myHeapNumElements - 1];
			--myHeapNumElements;

			if (myHeapNumElements <= 0)
			{
				myHeapInited = false;
				delete[] myHeapData;
				myHeapData = nullptr;
			}
		}
	}



	//----- REMOVE_ALL ------
	//-----------------------
	HEAD
	void TYPE::RemoveAll()
	{
		myHeapNumElements = 0;
		myStackNumElements = 0;
	}

	//----- DELETE_ALL ------
	//-----------------------
	HEAD
	void TYPE::DeleteAll()
	{
		//Do we have any heapmemory that we need to delete?
		if (myHeapInited == true)
		{
			for (int i = 0; i < myHeapNumElements; ++i)
			{
				if (myHeapData[i] != nullptr)
				{
					delete myHeapData[i];
					myHeapData[i] = nullptr;
				}
			}

			myHeapNumElements = 0;
			if (myHeapData != nullptr)
			{
				delete myHeapData;
				myHeapData = nullptr;
			}

			myHeapInited = false;
		}

		for (int i = 0; i < myStackNumElements; ++i)
		{
			if (myStackData[i] != nullptr)
			{
				delete myStackData[i];
				myStackData[i] = nullptr;
			}
		}

		myStackNumElements = 0;
	}



	//----- FIND ------
	//-----------------
	HEAD
	int TYPE::Find(const T &aObject)
	{
		for (int i = 0; i < myStackNumElements; ++i)
		{
			if (myStackData[i] == aObject)
				return i;
		}

		if (myHeapInited == true)
		{
			for (int i = 0; i < myHeapNumElements; ++i)
			{
				if (myHeapData[i] == aObject)
					return i;
			}
		}

		return FoundNone;
	}



	//----- GET_LAST ------
	//--------------------
	HEAD
	inline T& TYPE::GetLast()
	{
		if (myHeapInited == true)
		{
			return myHeapData[myHeapNumElements-1];
		}

		return myStackData[myStackNumElements-1];
	}

	//----- CONST_GET_LAST ------
	//---------------------------
	HEAD
	inline const T& TYPE::GetLast() const
	{
		if (myHeapInited == true)
		{
			return myHeapData[myHeapNumElements-1];
		}

		return myStackData[myStackNumElements-1];
	}




	//----- SIZE ------
	//-----------------
	HEAD
	__forceinline int TYPE::Size() const
	{
		return myStackNumElements + myHeapNumElements;
	}


	//----- OPTIMIZE ------
	//-----------------
	HEAD
	void TYPE::Optimize()
	{
		assert(myHeapInited == true && "[DynamicContainer]: Tried to [Optimize] before we started using the heap.");

		if (myHeapNumElements < myHeapSize)
		{
			myHeapSize = myHeapNumElements;
			T *newMem = new T[myHeapSize];

			//Copy all of our data into the new memory
			if (mySafeMode == true)
			{
				for (int i = 0; i < myHeapSize; i++)
				{
					newMem[i] = myHeapData[i];
				}
			}
			else
			{
				memcpy(newMem, myHeapData, sizeof(T) * myHeapSize);
			}

			delete[] myHeapData;

			myHeapData = newMem;
		}
	}


	//----- RESIZE_HEAP_MEMORY ------
	//-------------------------------
	HEAD
	inline void TYPE::ResizeHeapMemory()
	{
		//Increase heapsize
		myHeapSize *= 2;

		//Allocate new memory
		T *newMem = new T[myHeapSize];

		//Copy all our data to the new memory
		if (mySafeMode == true)
		{
			for (int i = 0; i < myHeapNumElements; ++i)
			{
				newMem[i] = myHeapData[i];
			}
		}
		else
		{
			memcpy(newMem, myHeapData, sizeof(T) * myHeapNumElements);
		}

		//Delete our old data
		delete[] myHeapData;

		//Make our old datapointer point to the new data
		myHeapData = newMem;
	}

	
	//----- IS_STACK_FULL ------
	//--------------------------
	HEAD
	__forceinline bool TYPE::IsStackFull()
	{
		return myStackNumElements >= myStackSize;
	}



	//----- INSERT_ON_STACK ------
	//--------------------------
	HEAD
	void TYPE::InsertOnStack(const int aIndex, const T &aObject)
	{
		assert(aIndex >= 0 && "[DynamicArray]: Trying to [InsertOnStack] to a index thats below 0");
		assert(aIndex <= myStackNumElements && "[DynamicArray]: Trying to [InsertOnStack] to a index thats greater than the number of elements");

		for (int i = myStackNumElements; i > aIndex; i--)
		{
			myStackData[i] = myStackData[i - 1];
		}

		myStackData[aIndex] = aObject;
		myStackNumElements++;
	}

	//----- INSERT_ON_HEAP ------
	//--------------------------
	HEAD
	void TYPE::InsertOnHeap(const int aIndex, const T &aObject)
	{
		assert(myHeapInited && "[DynamicArray]: Trying to [InsertOnHeap] to a unInitialized Array");
		assert(aIndex >= 0 && "[DynamicArray]: Trying to [InsertOnHeap] to a index thats below 0");
		assert(aIndex <= myHeapNumElements && "[DynamicArray]: Trying to [InsertOnHeap] to an index above myHeapNumElements");

		//Do we need to grow?
		if (myHeapNumElements >= myHeapSize)
			ResizeHeapMemory();

		for (int i = myHeapNumElements; i > aIndex; i--)
		{
			myHeapData[i] = myHeapData[i - 1];
		}

		myHeapData[aIndex] = aObject;
		myHeapNumElements++;
	}
}
namespace CU = CommonUtilities;