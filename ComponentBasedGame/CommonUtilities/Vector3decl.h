#pragma once

namespace CommonUtilities
{
	template <typename TYPE>
	class Vector3
	{
	public:
		Vector3(TYPE anX = 0.f, TYPE anY = 0.f, TYPE anZ = 0.f);
		~Vector3(void);

		union
		{
			TYPE myX;
			TYPE x;
			TYPE myR;
			TYPE r;
		};

		union
		{
			TYPE myY;
			TYPE y;
			TYPE myG;
			TYPE g;
		};

		union
		{
			TYPE myZ;
			TYPE z;
			TYPE myB;
			TYPE b;
		};
	private:

	};

	template<typename TYPE>
	Vector3<TYPE>::Vector3(TYPE anX = 0.f, TYPE anY = 0.f, TYPE anZ = 0.f)
	{
		myX = anX;
		myY = anY;
		myZ = anZ;
	}



	template<typename TYPE>
	Vector3<TYPE>::~Vector3()
	{

	}
}
