#pragma once
namespace CommonUtilities
{
	template <typename TYPE>
	class Vector2
	{
	public:
		Vector2(TYPE anX = 0.f, TYPE anY = 0.f);
		~Vector2(void);

		union
		{
			TYPE myX;
			TYPE x;
			TYPE u;
		};

		union
		{
			TYPE myY;
			TYPE y;
			TYPE v;
		};
	private:
	
	};

	template<typename TYPE>
	Vector2<TYPE>::Vector2(TYPE anX = 0.f, TYPE anY = 0.f)
	{
		myX = anX;
		myY = anY;
	}



	template<typename TYPE>
	Vector2<TYPE>::~Vector2()
	{

	}

}