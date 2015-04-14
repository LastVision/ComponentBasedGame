#include <assert.h>


namespace CommonUtilities
{
	template <typename Type, int Size>
	class StaticArray
	{
	public:
		StaticArray();
		StaticArray(const StaticArray& aStaticArray);

		~StaticArray();

		StaticArray& operator=(const StaticArray& aStaticArray);

		inline const Type& operator[](const int& aIndex) const;
		inline Type& operator[](const int& aIndex);


		// Utility functions
		inline void Insert(int aIndex, Type& aObject);
		inline void DeleteAll();

	private:
		Type myData[Size];
	};

	//----- CONSTRUCTOR -----
	//-----------------------
	template <typename Type, int Size>
	StaticArray<Type, Size>::StaticArray()
	{

	}


	//----- DESTRUCTOR -----
	//----------------------
	template <typename Type, int Size>
	StaticArray<Type, Size>::~StaticArray()
	{

	}


	//----- COPY -----
	//----------------
	template <typename Type, int Size>
	StaticArray<Type, Size>::StaticArray(const StaticArray& aStaticArray)
	{
		*this = aStaticArray;
	}


	//----- ASSIGNMENT -----
	//----------------------
	template <typename Type, int Size>
	StaticArray<Type, Size>& StaticArray<Type, Size>::operator=(const StaticArray& aStaticArray)
	{
		for (unsigned int i = 0; i < Size; i++)
		{
			myData[i] = aStaticArray[i];
		}

		return *this;
	}


	//----- C_SUBSCRIPT -----
	//-----------------------
	template <typename Type, int Size>
	inline const Type& StaticArray<Type, Size>::operator[](const int& aIndex) const
	{
		assert(aIndex >= 0 && "Trying to use [] with a index thats below 0");
		assert(aIndex < Size && "Trying to use [] with a index thats greater than Size");

		return myData[aIndex];
	}


	//----- SUBSCRIPT -----
	//---------------------
	template <typename Type, int Size>
	inline Type& StaticArray<Type, Size>::operator[](const int& aIndex)
	{
		assert(aIndex >= 0 && "Trying to use [] with a index thats below 0");
		assert(aIndex < Size && "Trying to use [] with a index thats greater than Size");

		return myData[aIndex];
	}


	//----- INSERT -----
	//------------------
	template <typename Type, int Size>
	inline void StaticArray<Type, Size>::Insert(int aIndex, Type& aObject)
	{
		assert(aIndex >= 0 && "Trying to use Insert with a index thats below 0");
		assert(aIndex < Size && "Trying to use Insert with a index thats greater than Size");


		for (int i = Size - 1; i > aIndex; i--)
		{
			myData[i] = myData[i - 1];
		}

		myData[aIndex] = aObject;
	}


	//----- DELETE_ALL -----
	//----------------------
	template<typename Type, int Size>
	inline void StaticArray<Type, Size>::DeleteAll()
	{
		for (int i = 0; i < Size; i++)
		{
			delete myData[i];
			myData[i] = nullptr;
		}

	}

}