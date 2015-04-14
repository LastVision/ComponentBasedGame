#pragma once

#include "GrowingArray.h"
#include "RigidBody.h"
#include <unordered_map>
#include "..\HGE_BasicProject\XMLReader.h"

namespace RigidBodySystem
{
	//Would be cool to be able to define all of this in XML somehow. Like an PhysicsSettings.xml or something, where the user can create any collisiongroups he wants to
	enum eCollisionGroups : int
	{
		NONE = 0,
		TILES = 1,
		PLAYER = 2,
		ENEMY = 4
	};

	class RigidBody;

	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld();

		void SetCollisionTags(const std::string& aTagsFile);

		RigidBody* CreateRigidBody(const CollisionGroup aCollisionGroup, const CollisionGroup aTargetCollisionGroup);
		RigidBody* CopyRigidBody(const RigidBody* aRigidBody);
		void BuildRectangleCollider(RigidBody* aOwner, XMLElement aColliderElement);
		void BuildCircleCollider(RigidBody* aOwner, XMLElement aColliderElement);
		int GetCollisionGroupValue(const std::string& aCollisionGroup);


		void DoCollisionChecks();
		RigidBody* CheckForCollisions(RigidBody* aRigidBody);
		void RenderColliders();

	private:
		CU::GrowingArray<RigidBody*, int> myRigidBodies;
		CU::GrowingArray<int, int> myDeadBodies;
		std::unordered_map<std::string, int> myCollisionGroups;
		XMLReader myXMLReader;

		
	};
}
namespace RBS = RigidBodySystem;
