#pragma once

#include <new>
#include <unordered_map>
#include "..\DL_Debug\DL_Debug.h"

namespace CommonUtilities
{
	template<typename Key, short MAX_SIZE = 64>
	class OpaqueDictionary
	{
	public:
		OpaqueDictionary();
		~OpaqueDictionary();

		template<typename Value>
		void SetValue(const Key& aKey, const Value& aValue);

		template<typename Value>
		const Value& GetValue(const Key& aKey) const;

		void Clear();

	private:
		std::unordered_map<Key, void*> myDataPointers;
		char myData[MAX_SIZE];
		int myCurrentIndex;

#ifndef NDEBUG
		std::unordered_map<Key, const std::type_info*> myDataTypes;
#endif
	};


	template<typename Key, short MAX_SIZE>
	OpaqueDictionary<Key, MAX_SIZE>::OpaqueDictionary()
	{
		myCurrentIndex = 0;
	}

	template<typename Key, short MAX_SIZE>
	OpaqueDictionary<Key, MAX_SIZE>::~OpaqueDictionary()
	{

	}


	template<typename Key, short MAX_SIZE>
	template<typename Value>
	void OpaqueDictionary<Key, MAX_SIZE>::SetValue(const Key& aKey, const Value& aValue)
	{
		if (myCurrentIndex + sizeof(Value) >= MAX_SIZE)
		{
			DL_DEBUG("[OpaqueDictionary]: Ran out of memory. Tried to SetValue(Key: %s, ValueType: %s)", aKey, typeid(Value).name());
			DL_ASSERT("[OpaqueDictionary]: Not enough memory allocated!");
		}

		auto it = myDataPointers.find(aKey);

		if (it == myDataPointers.end())
		{
			myDataPointers[aKey] = new (&myData[myCurrentIndex]) Value(aValue);
			myCurrentIndex += sizeof(Value);

#ifndef NDEBUG
			myDataTypes[aKey] = &typeid(Value);
#endif
		}
		else
		{
#ifndef NDEBUG
			if ((typeid(Value) == *myDataTypes[aKey]) == false)
			{
				DL_DEBUG("[OpaqueDictionary]: Trying to set a value to a different type ( %s ) than it was created with ( %s )", typeid(Value).name(), myDataTypes[aKey]->name());
				DL_ASSERT("[OpaqueDictionary]: Trying to set a value to a different type than it was created with!");
			}
#endif
			*(reinterpret_cast<Value*>((*it).second)) = aValue;
		}
	}


	template<typename Key, short MAX_SIZE>
	template<typename Value>
	const Value& OpaqueDictionary<Key, MAX_SIZE>::GetValue(const Key& aKey) const
	{
#ifndef NDEBUG
		auto type = myDataTypes.find(aKey);

		if (type == myDataTypes.end())
		{
			DL_DEBUG("[OpaqueDictionary]: Tried to find Key ( %s ), but was unsucessful.", aKey);
			DL_ASSERT("[OpaqueDictionary]: Key not found!");
		}

		if ((typeid(Value) == *(*type).second) == false)
		{
			DL_DEBUG("[OpaqueDictionary]: Tried to GetValue ( %s ), but the saved value was of type ( %s ).", typeid(Value).name(), *(*type).second->name())
			DL_ASSERT("[OpaqueDictionary]: Incorrect type!");
		}
#endif

		auto it = myDataPointers.find(aKey);
		if (it == myDataPointers.end())
		{
			DL_DEBUG("[OpaqueDictionary]: Tried to find Key ( %s ), but was unsucessful.", aKey);
			DL_ASSERT("[OpaqueDictionary]: Key not found!");
		}

		return *(reinterpret_cast<Value*>((*it).second));
	}


	template<typename Key, short MAX_SIZE>
	void OpaqueDictionary<Key, MAX_SIZE>::Clear()
	{
		myCurrentIndex = 0;
		myDataPointers.clear();

#ifndef NDEBUG
		myDataTypes.clear();
#endif
	}
}
namespace CU = CommonUtilities;