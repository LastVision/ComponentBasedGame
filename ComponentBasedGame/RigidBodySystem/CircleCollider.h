#pragma once
#include "ICollider.h"

namespace RigidBodySystem
{
	class CircleCollider :
		public ICollider
	{
	public:
		CircleCollider();
		CircleCollider(const CU::Vector3<float>& aCircle);
		CircleCollider(const CU::Vector2<float>& aCenter, float aRadius);
		~CircleCollider();

		virtual void UpdatePositions(const CU::Vector2<float>& aPosition);
		virtual void Render();

		virtual bool CheckCollision(const ICollider* aCollider) const;
		virtual bool CheckRigidBodyCollision(const RigidBody* aRigidBody) const;
		virtual bool CheckRectangleCollision(const RectangleCollider* aRectangle) const;
		virtual bool CheckCircleCollision(const CircleCollider* aCircle) const;

		inline const CU::Vector2<float> GetCenterPosition() const override;
		inline const CU::Vector2<float> GetSize() const override;
		inline const float GetRadius() const;

	private:
		CU::Vector3<float> myCircle;
		CU::Vector2<float> myOffset;
	};

	inline const CU::Vector2<float> CircleCollider::GetCenterPosition() const
	{
		return {myCircle.x, myCircle.y };
	}

	inline const CU::Vector2<float> CircleCollider::GetSize() const
	{
		return{ myCircle.z, myCircle.z };
	}

	inline const float CircleCollider::GetRadius() const
	{
		return myCircle.z;
	}
};

