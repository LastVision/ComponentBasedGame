#pragma once
#include "GrowingArray.h"

namespace CommonUtilities
{
	template <typename T, typename Comparer>
	class Heap
	{
	public:
		Heap();
		Heap(const CU::GrowingArray<T>& aGrowingArray);
		~Heap();

		void Enqueue(const T& someData);
		T Dequeue();
		bool IsEmpty() const;

	private:
		Comparer myComparer;
		CU::GrowingArray<T, int> myData;
		void Swap(const int aFirstId, const int aSecondId);
		void RecurseDownTreeUntilNotTrue(int aIndex);
	};

	template <typename T, typename Comparer>
	Heap<T, Comparer>::Heap()
	{
		myData.Init(32);
	}

	template <typename T, typename Comparer>
	Heap<T, Comparer>::Heap(const CU::GrowingArray<T>& aGrowingArray)
	{
		myData.Init(32);
		myData = aGrowingArray;

		int indexOfLastNonLeafNode = (myData.Size() - 1) / 2;
		for (short i = indexOfLastNonLeafNode; i >= 0; --i)
		{
			int pos = i;
			RecurseDownTreeUntilNotTrue(pos);
		}
	}

	template <typename T, typename Comparer>
	void Heap<T, Comparer>::RecurseDownTreeUntilNotTrue(int aIndex)
	{
		int leftChild = aIndex * 2 + 1;
		int rightChild = aIndex * 2 + 2;

		if (rightChild < myData.Size())
		{
			if (myComparer(myData[leftChild], myData[rightChild]) && myComparer(myData[leftChild], myData[aIndex]))
			{
				Swap(aIndex, leftChild);
				RecurseDownTreeUntilNotTrue(leftChild);
			}
			else if (myComparer(myData[rightChild], myData[aIndex]))
			{
				Swap(aIndex, rightChild);
				RecurseDownTreeUntilNotTrue(rightChild);
			}
		}
		else if (leftChild < myData.Size())
		{
			if (myComparer(myData[leftChild], myData[aIndex]))
			{
				Swap(aIndex, leftChild);
				RecurseDownTreeUntilNotTrue(leftChild);
			}
		}
	}

	template <typename T, typename Comparer>
	Heap<T, Comparer>::~Heap()
	{
	}

	template <typename T, typename Comparer>
	void Heap<T, Comparer>::Enqueue(const T& someData)
	{
		myData.Add(someData);

		int pos = myData.Size() - 1;
		while ((pos > 0) && myComparer(myData[pos], myData[(pos - 1) / 2]))
		{
			Swap((pos - 1) / 2, pos);
			pos = (pos - 1) / 2;
		}
	}

	template <typename T, typename Comparer>
	void Heap<T, Comparer>::Swap(const int aFirstId, const int aSecondId)
	{
		T valueHolder = myData[aFirstId];
		myData[aFirstId] = myData[aSecondId];
		myData[aSecondId] = valueHolder;
	}

	template <typename T, typename Comparer>
	T Heap<T, Comparer>::Dequeue()
	{
		assert(myData.Size() > 0 && "Heap-array is empty.");
		if (myData.Size() == 3)
		{
			int apa = 0;
		}
		T originalRoot = myData[0];
		myData[0] = myData[myData.Size() - 1];
		myData.RemoveCyclicAtIndex(myData.Size() - 1);


		int leafLevel = (myData.Size() - 1) / 2;
		int pos = 0;
		int leftChild = pos * 2 + 1;
		int rightChild = pos * 2 + 2;

		while ((pos <= leafLevel) && (leftChild < myData.Size() || rightChild < myData.Size()))
		{
			if (rightChild < myData.Size() && (myComparer(myData[leftChild], myData[pos]) || myComparer(myData[rightChild], myData[pos])))
			{
				if (myComparer(myData[leftChild], myData[rightChild]) && myComparer(myData[leftChild], myData[pos]))
				{
					Swap(pos, leftChild);
					pos = leftChild;
					leftChild = pos * 2 + 1;
					rightChild = pos * 2 + 2;
				}
				else if (myComparer(myData[rightChild], myData[pos]))
				{
					Swap(pos, rightChild);
					pos = rightChild;
					rightChild = pos * 2 + 2;
					leftChild = pos * 2 + 1;
				}
				else
				{
					break;
				}
			}
			else if (leftChild < myData.Size())
			{
				if (myComparer(myData[leftChild], myData[pos]))
				{
					Swap(pos, leftChild);
					pos = leftChild;
					leftChild = pos * 2 + 1;
					rightChild = pos * 2 + 2;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}

		return originalRoot;
	}

	template <typename T, typename Comparer>
	bool Heap<T, Comparer>::IsEmpty() const
	{
		return myData.Size() == 0;
	}
}

namespace CU = CommonUtilities;