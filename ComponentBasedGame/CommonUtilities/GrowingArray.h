#pragma once


#define GAHead template <typename Type, typename CountType = unsigned short>
#define GAType GrowingArray<Type, CountType>


#include <memory>
#include <assert.h>



namespace CommonUtilities
{
	GAHead
	class GrowingArray
	{
	public:
		GrowingArray();
		GrowingArray(const CountType aStartSize, bool aUseSafeModeFlag = true);
		GrowingArray(const GrowingArray &aGrowingArray);
		~GrowingArray();

		GrowingArray& operator=(const GrowingArray &aGrowingArray);

		void Init(const CountType aNumElements, bool aUseSafeModeFlag = true);
		void ReInit(const CountType aNumElements, bool aUseSafeModeFlag = true);

		inline const Type& operator[](const CountType &aIndex) const;
		inline Type& operator[](const CountType &aIndex);

		inline void Add(const Type &aObject);
		inline void Insert(CountType aIndex, const Type &aObject);
		inline void DeleteCyclic(Type &aObject);
		inline void DeleteCyclicAtIndex(CountType aIndex);
		inline void RemoveCyclic(const Type &aObject);
		inline void RemoveCyclicAtIndex(CountType aIndex);

		inline CountType Find(const Type &aObject);

		inline Type& GetLast();
		inline const Type& GetLast() const;

		static const CountType FoundNone = static_cast<CountType>(-1);

		inline void RemoveAll();
		inline void DeleteAll();

		void Optimize();
		inline void Reserve(const CountType &aNewSize);
		__forceinline CountType Size() const;

	private:
		inline void Resize();

		Type *myData;
		CountType myNumElements;
		CountType mySize;
		bool mySafeMode;
	};

	//----- CONSTRUCTORS -----
	//------------------------
	GAHead
	GAType::GrowingArray()
	{
		myData = nullptr;

		myNumElements = 0;
		mySize = 0;

		mySafeMode = true;
	}


	GAHead
	GAType::GrowingArray(const CountType aStartSize, bool aUseSafeModeFlag = true)
	{
		Init(aStartSize, aUseSafeModeFlag);
	}


	//----- DESTRUCTOR -----
	//----------------------
	GAHead
	GAType::~GrowingArray()
	{
		delete[] myData;
		myData = nullptr;
	}

	//----- COPY -----
	//----------------
	GAHead
	GAType::GrowingArray(const GrowingArray &aGrowingArray)
	{
		myData = nullptr;
		*this = aGrowingArray;
	}


	//----- ASSIGNEMNT -----
	//----------------------
	GAHead
	GAType& GAType::operator=(const GrowingArray& aGrowingArray) //FunctionHead
	{
		delete[] myData;

		mySafeMode = aGrowingArray.mySafeMode;
		mySize = aGrowingArray.mySize;

		if (mySafeMode == true)
		{
			myNumElements = 0;
			myData = new Type[mySize];

			for (CountType i = 0; i < aGrowingArray.myNumElements; i++)
			{
				Add(aGrowingArray[i]);
			}
		}
		else
		{
			myNumElements = aGrowingArray.myNumElements;;
			myData = new Type[aGrowingArray.mySize];

			memcpy(myData, aGrowingArray.myData, sizeof(Type) * aGrowingArray.myNumElements);
		}

		return *this;
	}


	//----- INIT -----
	//-----------------------
	GAHead
	void GAType::Init(const CountType aMaxSize, bool aUseSafeModeFlag = true)
	{
		assert(aMaxSize > 0 && "Tried to [Init] a GrowingArray to a size below 0");

		myNumElements = 0;
		mySafeMode = aUseSafeModeFlag;

		mySize = aMaxSize;

		myData = new Type[mySize];
	}


	//----- RE_INIT -----
	//-----------------------
	GAHead
	void GAType::ReInit(const CountType aMaxSize, bool aUseSafeModeFlag = true)
	{
		assert(aMaxSize > 0 && "Tried to [ReInit] a GrowingArray to a size below 0");

		delete[] myData;

		Init(aMaxSize, aUseSafeModeFlag);
	}


	//----- C_SUBSCRIPT -----
	//-----------------------
	GAHead
	inline const Type& //ReturnType
	GAType::operator[](const CountType & aIndex) const //FunctionHead
	{
		assert(mySize > 0 && "Trying to use [] on a unInitialized Array");
		assert(aIndex >= 0 && "Trying to use [] with a index thats below 0");
		assert(aIndex < myNumElements && "Trying to use [] with a index thats greater than the number of elements");

		return myData[aIndex];
	}


	//----- SUBSCRIPT -----
	//---------------------
	GAHead
	inline Type& //ReturnType
	GAType::operator[](const CountType & aIndex) //FunctionHead
	{
		assert(mySize > 0 && "Trying to use [] on a unInitialized Array");
		assert(aIndex >= 0 && "Trying to use [] with a index thats below 0");
		assert(aIndex < myNumElements && "Trying to use [] with a index thats greater than the number of elements");

		return myData[aIndex];
	}


	//----- ADD -----
	//---------------
	GAHead
	inline void GAType::Add(const Type& aObject)
	{
		assert(mySize > 0 && "Trying to [Add] to a unInitialized Array");

		//Do we need to grow?
		if (myNumElements >= mySize)
			Resize();

		myData[myNumElements] = aObject;
		myNumElements++;
	}


	//----- INSERT -----
	//------------------
	GAHead
	inline void GAType::Insert(CountType aIndex, const Type& aObject)
	{
		assert(mySize > 0 && "Trying to [Insert] to a unInitialized Array");
		assert(aIndex >= 0 && "Trying to [Insert] to a index thats below 0");
		assert(aIndex <= myNumElements && "Trying to [Insert] to an index above myNumElements");
		
		//Do we need to grow?
		if (myNumElements >= mySize)
			Resize();

		for (CountType i = myNumElements; i > aIndex; i--)
		{
			myData[i] = myData[i - 1];
		}

		myData[aIndex] = aObject;
		myNumElements++;
	}


	//----- DELETE_CYCLIC -----
	//-------------------------
	GAHead
	inline void GAType::DeleteCyclic(Type& aObject)
	{
		assert(mySize > 0 && "Trying to use [DeleteCyclic] on a unInitialized Array");

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


	//----- DELETE_CYCLIC_AT_INDEX -----
	//----------------------------------
	GAHead
	inline void GAType::DeleteCyclicAtIndex(CountType aIndex)
	{
		assert(mySize > 0 && "Trying to use [DeleteCyclicAtIndex] on a unInitialized Array");
		assert(aIndex >= 0 && "Trying to [DeleteCyclicAtIndex] at a index thats below 0");
		assert(aIndex < myNumElements && "Trying to use [DeleteCyclicAtIndex] at a index thats greater than the number of elements");

		delete myData[aIndex];
		myData[aIndex] = myData[myNumElements - 1];
		myNumElements--;
	}


	//----- REMOVE_CYCLIC -----
	//-------------------------
	GAHead
	inline void GAType::RemoveCyclic(const Type& aObject)
	{
		assert(mySize > 0 && "Trying to use [RemoveCyclic] on a unInitialized Array");

		bool removalSuccesful = false;

		for (CountType i = 0; i < myNumElements; i++)
		{
			if (myData[i] == aObject)
			{
				myData[i] = myData[myNumElements - 1];
				myNumElements--;
				removalSuccesful = true;
				break;
			}
		}

		assert(removalSuccesful && "Tried to [RemoveCyclic] an Item that was not found in vector");
	}


	//----- REMOVE_CYCLIC_AT_INDEX -----
	//---------------------------------
	GAHead
	inline void GAType::RemoveCyclicAtIndex(CountType aIndex)
	{
		assert(mySize > 0 && "Trying to use [RemoveCyclicAtIndex] on a unInitialized Array");
		assert(aIndex >= 0 && "Trying to [RemoveCyclicAtIndex] at a index thats below 0");
		assert(aIndex < myNumElements && "Trying to use [RemoveCyclicAtIndex] at a index thats greater than the number of elements");

		myData[aIndex] = myData[myNumElements - 1];
		myNumElements--;
	}



	//----- FIND -----
	//----------------
	GAHead
	inline CountType GAType::Find(const Type &aObject)
	{
		assert(mySize > 0 && "Trying to use [FIND] on a unInitialized Array");

		for (CountType i = 0; i < myNumElements; i++)
		{
			if (myData[i] == aObject)
				return i;
		}

		return FoundNone;
	}


	//----- GET_LAST -----
	//--------------------
	GAHead
	inline Type& GAType::GetLast()
	{
		assert(mySize > 0 && "Trying to use [FIND] on a unInitialized Array");
		return myData[myNumElements - 1];
	}

	GAHead
	inline const Type& GAType::GetLast() const
	{
		assert(mySize > 0 && "Trying to use [FIND] on a unInitialized Array");
		return myData[myNumElements - 1];
	}


	//----- CLEAR -----
	//-----------------
	GAHead
	inline void GAType::RemoveAll()
	{
		myNumElements = 0;
	}


	//----- DELETE_ALL -----
	//----------------------
	GAHead
	inline void GAType::DeleteAll()
	{
		assert(mySize > 0 && "Trying to use [DELET_ALL] on a unInitialized Array");

		for (CountType i = 0; i < myNumElements; i++)
		{
			if (myData[i] != nullptr)
			{
				delete myData[i];
				myData[i] = nullptr;
			}
			
		}

		myNumElements = 0;
	}

	//----- OPTIMIZE -----
	//--------------------
	GAHead
	void GAType::Optimize()
	{
		if (myNumElements < mySize)
		{
			myNumElements -= 1;
			mySize = myNumElements;
			Type *newMem = new Type[mySize];

			//Copy all of our data into the new memory
			if (mySafeMode == true)
			{
				for (CountType i = 0; i < mySize; i++)
				{
					newMem[i] = myData[i];
				}
			}
			else
			{
				memcpy(newMem, myData, sizeof(Type) * mySize);
			}

			delete[] myData;

			myData = newMem;
		}
	}



	//----- RESERVE -----
	//------------------
	GAHead
	inline void GAType::Reserve(const CountType &aNewSize)
	{
		//assert(mySize > 0 && "Trying to use [Reserve] on a unInitialized Array");
		//There has to be a better way to do this, it looks kinda iffy to me
		//Perhaps we should check if aNewSize is less than our current MaxSize.
		//If that is the case we only need set mySize = aNewSize 
		//and myNumElements to aNewSize (IF myNumElements is greater than aNewSize)

		if (aNewSize < myNumElements)
		{
			myNumElements = aNewSize;
			return;
		}

		//Change our maxSize
		mySize = aNewSize;

		//Alocate new memory
		Type *newMem = new Type[aNewSize];

		//Copy all of our data into the new memory
		if (mySafeMode == true)
		{
			for (CountType i = 0; i < myNumElements; i++)
			{
				newMem[i] = myData[i];
			}
		}
		else
		{
			memcpy(newMem, myData, sizeof(Type) * myNumElements);
		}

		

		//If we had saved anything before we tried to reserv, then we need to delete that old data
		//(The data got copied into our new memory above, so we are not losing any data, just
		//getting rid of the old "version" of the data, that no longer will be used)
		if (myNumElements > 0)
			delete myData;

		//Move our elementHead to the last spot in our new memory
		//This allows the user to use the subscript-operator to acces all the objects in our array
		//just like we want
		myNumElements = aNewSize;

		//Make our DataPointer point to the new data/memory
		myData = newMem;
	}


	//----- SIZE -----
	//----------------
	GAHead
	__forceinline CountType GAType::Size() const
	{
		assert(mySize > 0 && "Trying to use [Size] on a unInitialized Array");
		return myNumElements;
	}


	//----- RESIZE -----
	//-------------------------
	GAHead
	inline void GAType::Resize()
	{
		//Increase our maxSize
		mySize *= 2;

		//Allocate new memory
		Type *newMem = new Type[mySize];

		//Copy all of our data into the new memory
		if (mySafeMode == true)
		{
			for (CountType i = 0; i < myNumElements; i++)
			{
				newMem[i] = myData[i];
			}
		}
		else
		{
			memcpy(newMem, myData, sizeof(Type) * myNumElements);
		}
		
		//Delete old data
		delete[] myData;

		//Then point to new data
		myData = newMem;

	}
}
namespace CU = CommonUtilities;


