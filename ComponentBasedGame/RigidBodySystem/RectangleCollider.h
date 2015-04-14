#pragma once
#include "ICollider.h"

namespace RigidBodySystem
{
	class RectangleCollider : public ICollider
	{
	public:
		RectangleCollider();
		RectangleCollider(const CU::Vector2<float>& aTopLeft, const CU::Vector2<float>& aSize);
		RectangleCollider(const CU::Vector4<float>& aRect);
		~RectangleCollider();

		virtual void UpdatePositions(const CU::Vector2<float>& aPosition);
		virtual void Render();

		virtual bool CheckCollision(const ICollider* aCollider) const;
		virtual bool CheckRigidBodyCollision(const RigidBody* aRigidBody) const;
		virtual bool CheckRectangleCollision(const RectangleCollider* aRectangle) const;
		virtual bool CheckCircleCollision(const CircleCollider* aCircle) const;

		inline const CU::Vector2<float> GetCenterPosition() const override;
		inline const CU::Vector2<float> GetSize() const override;

		inline const float GetTop() const;
		inline const float GetBottom() const;
		inline const float GetLeft() const;
		inline const float GetRight() const;

	private:
		CU::Vector4<float> myRect;
		CU::Vector2<float> myOffset;
	};

	inline const float RectangleCollider::GetTop() const
	{
		return myRect.y;
	}

	inline const float RectangleCollider::GetBottom() const
	{
		return myRect.y + myRect.w;
	}

	inline const float RectangleCollider::GetLeft() const
	{
		return myRect.x;
	}

	inline const float RectangleCollider::GetRight() const
	{
		return myRect.x + myRect.z;
	}

	inline const CU::Vector2<float> RectangleCollider::GetCenterPosition() const
	{
		return{ myRect.x + myRect.z / 2.f, myRect.y + myRect.w / 2.f };
	}

	inline const CU::Vector2<float> RectangleCollider::GetSize() const
	{
		return{ myRect.z, myRect.w };
	}
};

