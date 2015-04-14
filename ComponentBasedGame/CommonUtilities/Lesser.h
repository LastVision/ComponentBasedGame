#pragma once

namespace CommonUtilities
{
	template <typename T>
	class Lesser
	{
	public:
		Lesser();
		~Lesser();

		bool operator()(const T& aFirst, const T& aSecond);
	};

	template<typename T>
	Lesser<T>::Lesser()
	{
	}

	template<typename T>
	Lesser<T>::~Lesser()
	{
	}

	template<typename T>
	bool Lesser<T>::operator()(const T& aFirst, const T& aSecond)
	{
		return aFirst < aSecond;
	}
}