#include "RigidBody.h"
#include "RectangleCollider.h"
#include "CircleCollider.h"
#include "PhysicsWorld.h"

namespace RigidBodySystem
{
	RigidBody::RigidBody(PhysicsWorld* aPhysicsWorld, const CollisionGroup aCollisionGroup, const CollisionGroup aTargetCollisionGroup) : myWorld(aPhysicsWorld), myCollisionGroup(aCollisionGroup), myTargetCollisionGroup(aTargetCollisionGroup)
	{
		myColliders.Init(8);
		myOwner = nullptr;
		myIsActive = true;
	}

	RigidBody::RigidBody(const RigidBody& aRigidBody)
	{
		myColliders.Init(8);
		myCollisionGroup = aRigidBody.myCollisionGroup;
		myTargetCollisionGroup = aRigidBody.myTargetCollisionGroup;
		myOwner = nullptr;
		myPosition = aRigidBody.myPosition;
		myIsActive = aRigidBody.myIsActive;
		myWorld = aRigidBody.myWorld;


		auto it = aRigidBody.myColliderMap.begin();
		while (it != aRigidBody.myColliderMap.end())
		{
			if (it->first == eColliderType::RECTANGLE)
			{
				for (int i = 0; i < it->second.Size(); ++i)
				{
					AddCollider(new RectangleCollider(*static_cast<RectangleCollider*>(it->second[i])), eColliderType::RECTANGLE);
				}
			}
			else if (it->first == eColliderType::CIRCLE)
			{
				for (int i = 0; i < it->second.Size(); ++i)
				{
					AddCollider(new CircleCollider(*static_cast<CircleCollider*>(it->second[i])), eColliderType::CIRCLE);
				}
			}

			it++;
		}
	}


	RigidBody::~RigidBody()
	{
	}

	void RigidBody::UpdatePositions(const CU::Vector2<float>& aPosition)
	{
		myPosition = aPosition;
		myCenter = { aPosition.x + mySize.x / 2.f, aPosition.y + mySize.y / 2.f };

		for (int i = 0; i < myColliders.Size(); ++i)
		{
			myColliders[i]->UpdatePositions(aPosition);
		}
	}

	void RigidBody::Render()
	{
		for (int i = 0; i < myColliders.Size(); ++i)
		{
			myColliders[i]->Render();
		}
	}

	RigidBody* RigidBody::CheckCollisionVSWorld()
	{
		return myWorld->CheckForCollisions(this);
	}

	bool RigidBody::CheckCollision(const ICollider* aCollider) const
	{
		for (int i = 0; i < myColliders.Size(); ++i)
		{
			if (myColliders[i]->CheckCollision(aCollider) == true)
				return true;
		}

		return false;
	}

	bool RigidBody::CheckRigidBodyCollision(const RigidBody* aRigidBody) const
	{
		if (myIsActive == false || aRigidBody->myIsActive == false) return false;
		if ((myCollisionGroup & aRigidBody->myTargetCollisionGroup) == 0) return false;

		for (int i = 0; i < myColliders.Size(); ++i)
		{
			if (myColliders[i]->CheckRigidBodyCollision(aRigidBody) == true)
				return true;
		}

		return false;
	}

	bool RigidBody::CheckRectangleCollision(const RectangleCollider* aRectangle) const
	{
		for (int i = 0; i < myColliders.Size(); ++i)
		{
			if (myColliders[i]->CheckRectangleCollision(aRectangle) == true)
				return true;
		}

		return false;
	}

	bool RigidBody::CheckCircleCollision(const CircleCollider* aCircle) const
	{
		for (int i = 0; i < myColliders.Size(); ++i)
		{
			if (myColliders[i]->CheckCircleCollision(aCircle) == true)
				return true;
		}

		return false;
	}
};
