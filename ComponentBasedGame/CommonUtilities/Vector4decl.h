#pragma once

namespace CommonUtilities
{
	template <typename TYPE>
	class Vector4
	{
	public:
		Vector4(TYPE anX = 0.f, TYPE anY = 0.f, TYPE anZ = 0.f, TYPE anW = 0.f);
		~Vector4(void);

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

		union
		{
			TYPE myW;
			TYPE w;
			TYPE myA;
			TYPE a;
		};
	private:

	};

	template<typename TYPE>
	Vector4<TYPE>::Vector4(TYPE anX = 0.f, TYPE anY = 0.f, TYPE anZ = 0.f, TYPE anW = 0.f)
	{
		myX = anX;
		myY = anY;
		myZ = anZ;
		myW = anW;
	}

	template<typename TYPE>
	Vector4<TYPE>::~Vector4()
	{

	}
}