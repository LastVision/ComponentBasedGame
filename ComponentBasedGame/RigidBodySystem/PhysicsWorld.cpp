#include "PhysicsWorld.h"
#include "..\ComponentSystem\RigidBodyComponent.h"
#include "RectangleCollider.h"
#include "CircleCollider.h"

namespace RigidBodySystem
{
	PhysicsWorld::PhysicsWorld()
	{
		myRigidBodies.Init(128);
		myDeadBodies.Init(8);
	}


	PhysicsWorld::~PhysicsWorld()
	{
		for (int i = 0; i < myRigidBodies.Size(); ++i)
		{
			myRigidBodies.DeleteCyclicAtIndex(i);
		}
	}	

	void PhysicsWorld::SetCollisionTags(const std::string& aTagsFile)
	{
		myXMLReader.OpenDocument(aTagsFile);


		XMLElement collisionGroup = myXMLReader.FindFirstChild();

		int collisionID = 1;
		while (collisionGroup != nullptr)
		{
			std::string collisionName = myXMLReader.GetElementName(collisionGroup);
			myCollisionGroups[collisionName] = collisionID;


			collisionID += collisionID;
			collisionGroup = myXMLReader.FindNextElement(collisionGroup);
		}

		myXMLReader.CloseDocument();
	}

	RigidBody* PhysicsWorld::CreateRigidBody(const CollisionGroup aCollisionGroup, const CollisionGroup aTargetCollisionGroup)
	{
		RigidBody* newBody = new RigidBody(this, aCollisionGroup, aTargetCollisionGroup);
		myRigidBodies.Add(newBody);
		return newBody;
	}

	RigidBody* PhysicsWorld::CopyRigidBody(const RigidBody* aRigidBody)
	{
		RigidBody* newBody = new RigidBody(*aRigidBody);
		myRigidBodies.Add(newBody);
		return newBody;
	}

	//***********************
	//  Collider Builders
	//***********************
	void PhysicsWorld::BuildRectangleCollider(RigidBody* aOwner, XMLElement aColliderElement)
	{
		myXMLReader.OpenForReadingWithoutDocument();

		CU::Vector2<float> position;
		CU::Vector2<float> size;

		XMLElement positionElement = myXMLReader.ForceFindFirstChild(aColliderElement, "Position");
		XMLElement sizeElement = myXMLReader.ForceFindFirstChild(aColliderElement, "Size");

		myXMLReader.ForceReadAttribute(positionElement, "X", &position.x);
		myXMLReader.ForceReadAttribute(positionElement, "Y", &position.y);

		myXMLReader.ForceReadAttribute(sizeElement, "Width", &size.x);
		myXMLReader.ForceReadAttribute(sizeElement, "Height", &size.y);

		aOwner->AddCollider(new RectangleCollider(position, size), eColliderType::RECTANGLE);

		myXMLReader.CloseDocument();
	}

	void PhysicsWorld::BuildCircleCollider(RigidBody* aOwner, XMLElement aColliderElement)
	{
		myXMLReader.OpenForReadingWithoutDocument();

		CU::Vector2<float> position;
		float radius;

		XMLElement positionElement = myXMLReader.ForceFindFirstChild(aColliderElement, "Position");
		XMLElement sizeElement = myXMLReader.ForceFindFirstChild(aColliderElement, "Size");

		myXMLReader.ForceReadAttribute(positionElement, "X", &position.x);
		myXMLReader.ForceReadAttribute(positionElement, "Y", &position.y);

		myXMLReader.ForceReadAttribute(sizeElement, "Radius", &radius);

		aOwner->AddCollider(new CircleCollider(position, radius), eColliderType::CIRCLE);

		myXMLReader.CloseDocument();
	}

	int PhysicsWorld::GetCollisionGroupValue(const std::string& aCollisionGroup)
	{
		auto it = myCollisionGroups.find(aCollisionGroup);
		if (it == myCollisionGroups.end())
			return 0;

		return it->second;
	}

	void PhysicsWorld::DoCollisionChecks()
	{
		for (int i = 0; i < myRigidBodies.Size(); ++i)
		{
			if (myRigidBodies[i]->myIsActive == false) continue;

			if (myRigidBodies[i]->GetOwner() == nullptr)
			{
				myDeadBodies.Add(i);
				continue;
			}

			for (int j = i + 1; j < myRigidBodies.Size(); ++j)
			{
				if (myRigidBodies[j]->myIsActive == false) continue;

				if (myRigidBodies[j]->GetOwner() == nullptr)
				{
					myDeadBodies.Add(j);
					continue;

				}

				if (myRigidBodies[i]->CheckRigidBodyCollision(myRigidBodies[j]) == true)
				{
					myRigidBodies[i]->GetOwner()->HandleCollision(myRigidBodies[j]);
				}

				if (myRigidBodies[j]->CheckRigidBodyCollision(myRigidBodies[i]) == true)
				{
					myRigidBodies[j]->GetOwner()->HandleCollision(myRigidBodies[i]);
				}
			}
		}

		for (int i = myDeadBodies.Size() - 1; i >= 0; --i)
		{
			myRigidBodies.DeleteCyclicAtIndex(i);
		}

		myDeadBodies.RemoveAll();
	}

	RigidBody* PhysicsWorld::CheckForCollisions(RigidBody* aRigidBody)
	{
		for (int i = 0; i < myRigidBodies.Size(); ++i)
		{
			if (myRigidBodies[i]->myIsActive == false) continue;
			if (myRigidBodies[i] == aRigidBody) continue;
			if (aRigidBody->myIsActive == false) continue;

			//TODO: Skapa en circle runt varje RigidBody som kan användas här som en billig check för
			//att kolla om de två RigidBodiesn ens är tillräckligt nära för att kunna kollidera.
			//Detta för att slippa loopa igenom alla Colliders för alla RigidBodes även om de
			//är väldigt långt ifrån varandra

			if (aRigidBody->CheckRigidBodyCollision(myRigidBodies[i]) == true)
				return myRigidBodies[i];
		}

		return nullptr;
	}

	void PhysicsWorld::RenderColliders()
	{
		for (int i = 0; i < myRigidBodies.Size(); ++i)
		{
			if (myRigidBodies[i]->myIsActive == true)
				myRigidBodies[i]->Render();
		}
	}
};
