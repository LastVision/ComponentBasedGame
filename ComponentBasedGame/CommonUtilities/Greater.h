#pragma once

namespace CommonUtilities
{
	template <typename T>
	class Greater
	{
	public:
		Greater();
		~Greater();

		bool operator()(const T& aFirst, const T& aSecond);
	};

	template<typename T>
	Greater<T>::Greater()
	{
	}

	template<typename T>
	Greater<T>::~Greater()
	{
	}

	template<typename T>
	bool Greater<T>::operator()(const T& aFirst, const T& aSecond)
	{
		return aFirst > aSecond;
	}
}

