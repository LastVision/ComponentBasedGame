#include <stdio.h>

namespace CommonUtilities
{
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	class VectorOnStack
	{
	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);

		~VectorOnStack();

		VectorOnStack & operator=(const VectorOnStack & aVectorOnStack);

		inline const Type& operator[](const CountType & aIndex) const;
		inline Type& operator[](const CountType & aIndex);

		inline void Add(const Type& aObject);
		inline void Insert(CountType aIndex, Type& aObject);
		inline void DeleteCyclic(Type& aObject);
		inline void DeleteCyclicAtIndex(CountType aItemNumber);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(CountType aItemNumber);

		inline void Clear();
		inline void DeleteAll();

		inline CountType Find(const Type &aObject);

		inline Type& GetLast();
		inline const Type& GetLast() const;

		__forceinline CountType Size() const;
		
	private:
		Type myData[SizeT];
		CountType myNumElements;
		bool mySafeMode;
	};


	//----- CONSTRUCTOR -----
	//-----------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::VectorOnStack()
	{
		myNumElements = 0;
		mySafeMode = UseSafeModeFlag;
	}

	//----- DESTRUCTOR ------
	//-----------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::~VectorOnStack()
	{
		myNumElements = 0;
		mySafeMode = true;
	}


	//----- COPY ------
	//-----------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::VectorOnStack(const VectorOnStack& aVectorOnStack)
	{
		*this = aVectorOnStack;
	}


	//----- ASSIGNMENT ------
	//-----------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>& VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::operator=(const VectorOnStack& aVectorOnStack)
	{
		if (mySafeMode == true)
		{
			myNumElements = 0;
			for (CountType i = 0; i < aVectorOnStack.Size(); i++)
			{
				myData[i] = aVectorOnStack[i];
				myNumElements++;
			}
		}
		else
		{
			memcpy(this, &aVectorOnStack, sizeof(aVectorOnStack));
		}

		return *this;
	}


	//----- C_SUBSCRIPT ------
	//------------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline const Type& VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::operator[](const CountType & aIndex) const
	{
		assert(aIndex >= 0 && "Trying to use [] with a index thats below 0");
		assert(aIndex < myNumElements && "Trying to use [] with a index thats greater than the number of elements");

		return myData[aIndex];
	}


	//----- SUBSCRIPT ------
	//----------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline Type& VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::operator[](const CountType & aIndex)
	{
		assert(aIndex >= 0 && "Trying to use [] with a index thats below 0");
		assert(aIndex < myNumElements && "Trying to use [] with a index thats greater than the number of elements");

		return myData[aIndex];
	}


	//----- ADD ------
	//----------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::Add(const Type& aObject)
	{
		assert(myNumElements < SizeT && "Tried to [Add] an element to an allready full vector");

		myData[myNumElements] = aObject;
		myNumElements++;
	}


	//----- INSERT ------
	//-------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::Insert(CountType aIndex, Type& aObject)
	{
		assert(aIndex >= 0 && "Trying to [Insert] to a index thats below 0");
		assert(aIndex <= myNumElements - 1 && "Trying to use [Insert] to a index thats greater than the number of elements");
		assert(myNumElements < SizeT && "Trying to [Insert] into a full vector");

		for (CountType i = myNumElements; i > aIndex; i--)
		{
			myData[i] = myData[i - 1];
		}

		myData[aIndex] = aObject;
		myNumElements++;
	}


	//----- DELETE_CYCLIC ------
	//--------------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::DeleteCyclic(Type& aObject)
	{
		bool deleteSuccesful = false;

		for (CountType i = 0; i < myNumElements; i++)
		{
			if (myData[i] == aObject)
			{
				delete myData[i];
				myData[i] = myData[myNumElements - 1];
				myNumElements--;
				deleteSuccesful = true;
				break;
			}
		}

		assert(deleteSuccesful && "Tried to [DeleteCyclic] an Item that was not found in vector");
	}


	//----- DELETE_CYCLIC_AT_INDEX ------
	//-----------------------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::DeleteCyclicAtIndex(CountType aItemNumber)
	{
		assert(aItemNumber >= 0 && "Trying to [DeleteCyclicAtIndex] at a index thats below 0");
		assert(aItemNumber < myNumElements && "Trying to use [DeleteCyclicAtIndex] at a index thats greater than the number of elements");

		delete myData[aItemNumber];
		myData[aItemNumber] = myData[myNumElements - 1];
		myNumElements--;
	}


	//----- REMOVE_CYCLIC ------
	//--------------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::RemoveCyclic(const Type& aObject)
	{
		bool deleteSuccesful = false;

		for (CountType i = 0; i < myNumElements; i++)
		{
			if (myData[i] == aObject)
			{
				myData[i] = myData[myNumElements - 1];
				myNumElements--;
				deleteSuccesful = true;
				break;
			}
		}

		assert(deleteSuccesful && "Tried to [RemoveCyclic] an Item that was not found in vector");
	}


	//----- REMOVE_CYCLIC_AT_INDEX ------
	//-----------------------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::RemoveCyclicAtIndex(CountType aItemNumber)
	{
		assert(aItemNumber >= 0 && "Trying to [RemoveCyclicAtIndex] at a index thats below 0");
		assert(aItemNumber < myNumElements && "Trying to use [RemoveCyclicAtIndex] at a index thats greater than the number of elements");

		myData[aItemNumber] = myData[myNumElements - 1];
		myNumElements--;
	}


	//----- CLEAR ------
	//------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::Clear()
	{
		myNumElements = 0;
	}


	//----- DELETE_ALL ------
	//-----------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::DeleteAll()
	{
		for (CountType i = 0; i < myNumElements; i++)
		{
			delete myData[i];
			myData[i] = nullptr;
		}

		myNumElements = 0;
	}


	//----- FIND -----
	//----------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	CountType VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::Find(const Type &aObject)
	{
		for (CountType i = 0; i < myNumElements; i++)
		{
			if (myData[i] == aObject)
				return i;
		}

		return FoundNone;
	}


	//----- GET_LAST -----
	//--------------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	Type& VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::GetLast()
	{
		return myData[myNumElements - 1];
	}

	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	const Type&VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::GetLast() const
	{
		return myData[myNumElements - 1];
	}

	//----- SIZE ------
	//-----------------
	template <typename Type, int SizeT, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	__forceinline CountType VectorOnStack<Type, SizeT, CountType, UseSafeModeFlag>::Size() const
	{
		return myNumElements;
	}

	
}

