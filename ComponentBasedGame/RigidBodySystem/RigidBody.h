#pragma once

#include "ICollider.h"
#include "ColliderFactory.h"
#include "GrowingArray.h"
#include <unordered_map>

namespace ComponentSystem
{
	class RigidBodyComponent;
}
namespace CS = ComponentSystem;

namespace RigidBodySystem
{
	enum class eColliderType
	{
		RECTANGLE,
		CIRCLE,
		RIGIDBODY
	};

	typedef int CollisionGroup;

	class PhysicsWorld;
	class RigidBody : public ICollider
	{
	public:

		friend class PhysicsWorld;

		RigidBody(PhysicsWorld* aPhysicsWorld, const CollisionGroup aCollisionGroup, const CollisionGroup aTargetCollisionGroup);
		RigidBody(const RigidBody& aRigidBody);
		~RigidBody();

		inline void AddCollider(ICollider* aCollider, eColliderType aColliderType);
		inline void RemoveCollider(ICollider* aCollider, eColliderType aColliderType);


		virtual void UpdatePositions(const CU::Vector2<float>& aPosition);
		virtual void Render();

		virtual RigidBody* CheckCollisionVSWorld();
		virtual bool CheckCollision(const ICollider* aCollider) const;
		virtual bool CheckRigidBodyCollision(const RigidBody* aRigidBody) const;
		virtual bool CheckRectangleCollision(const RectangleCollider* aRectangle) const;
		virtual bool CheckCircleCollision(const CircleCollider* aCircle) const;


		inline const CU::GrowingArray<ICollider*, int>& GetColliders() const;
		inline const CU::Vector2<float>& GetPosition() const;
		inline const CU::Vector2<float> GetCenterPosition() const override;
		inline const CU::Vector2<float> GetSize() const override;
		inline const CollisionGroup GetCollisionGroup() const;
		inline const CollisionGroup GetTargetCollisionGroup() const;

		inline void SetOwner(CS::RigidBodyComponent* aOwner);
		inline CS::RigidBodyComponent* GetOwner();

		inline void SetActiveStatus(const bool aStatus);

	private:
		CU::GrowingArray<ICollider*, int> myColliders;
		CU::Vector2<float> myPosition;
		CU::Vector2<float> myCenter;
		CU::Vector2<float> mySize;
		CS::RigidBodyComponent* myOwner;
		std::unordered_map<eColliderType, CU::GrowingArray<ICollider*, int>> myColliderMap;

		PhysicsWorld* myWorld;
		CollisionGroup myCollisionGroup;
		CollisionGroup myTargetCollisionGroup;
		bool myIsActive;
	};

	inline void RigidBody::AddCollider(ICollider* aCollider, eColliderType aColliderType)
	{
		auto it = myColliderMap.find(aColliderType);
		if (it == myColliderMap.end())
			myColliderMap[aColliderType].Init(4);


		myColliderMap[aColliderType].Add(aCollider);

		myColliders.Add(aCollider);

		float minX = 0.f;
		float minY = 0.f;
		float maxX = 0.f;
		float maxY = 0.f;

		for (int i = 0; i < myColliders.Size(); ++i)
		{
			ICollider* currCollider = myColliders[i];

			float currMinX = currCollider->GetCenterPosition().x - currCollider->GetSize().x / 2.f;
			float currMinY = currCollider->GetCenterPosition().y - currCollider->GetSize().y / 2.f;

			float currMaxX = currCollider->GetCenterPosition().x + currCollider->GetSize().x / 2.f;
			float currMaxY = currCollider->GetCenterPosition().y + currCollider->GetSize().y / 2.f;

			if (currMinX < minX)
				minX = currMinX;

			if (currMinY < minY)
				minY = currMinY;

			if (currMaxX > maxX)
				maxX = currMaxX;

			if (currMaxY > maxY)
				maxY = currMaxY;
		}

		mySize.x = maxX - minX;
		mySize.y = maxY - minY;

		myCenter.x = maxX - mySize.x / 2.f;
		myCenter.y = maxY - mySize.y / 2.f;
	}

	inline void RigidBody::RemoveCollider(ICollider* aCollider, eColliderType aColliderType)
	{
		auto it = myColliderMap.find(aColliderType);
		if (it != myColliderMap.end())
			myColliderMap[aColliderType].RemoveCyclic(aCollider);

		myColliders.RemoveCyclic(aCollider);
	}

	inline const CU::GrowingArray<ICollider*, int>& RigidBody::GetColliders() const
	{
		return myColliders;
	}

	inline const CU::Vector2<float>& RigidBody::GetPosition() const
	{
		return myPosition;
	}

	inline const CU::Vector2<float> RigidBody::GetCenterPosition() const
	{
		return myCenter;
	}

	inline const CU::Vector2<float> RigidBody::GetSize() const
	{
		return mySize;
	}

	inline const CollisionGroup RigidBody::GetCollisionGroup() const
	{
		return myCollisionGroup;
	}

	inline const CollisionGroup RigidBody::GetTargetCollisionGroup() const
	{
		return myTargetCollisionGroup;
	}

	inline void RigidBody::SetOwner(CS::RigidBodyComponent* aOwner)
	{
		myOwner = aOwner;
	}

	inline CS::RigidBodyComponent* RigidBody::GetOwner()
	{
		return myOwner;
	}

	inline void RigidBody::SetActiveStatus(const bool aStatus)
	{
		myIsActive = aStatus;
	}
};
namespace RBS = RigidBodySystem;
