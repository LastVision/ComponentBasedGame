#include "TargetingComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"

namespace ComponentSystem
{
	TargetingComponent::TargetingComponent(GameObject &aOwner, CU::GrowingArray<GameObject*, int> &aGameObjects, const float aRange, const int aTargetingTags) 
		: IComponent(aOwner), myTargets(aGameObjects), myRange(aRange), myTargetingTags(aTargetingTags)
	{
		myCurrentTarget = nullptr;
	}


	TargetingComponent::~TargetingComponent()
	{
	}

	void TargetingComponent::Update(const float )
	{
		PositionComponent* ownerPosComp = static_cast<PositionComponent*>(myOwner->GetComponent(eComponentType::POSITION_COMPONENT));
		myCurrentTarget = nullptr;

		DL_ASSERT_EX(ownerPosComp != nullptr, "[SingleTargetingComponent]: The GameObject that does the aiming does not have an PositionComponent. For the Targeting to work the GameObject need an PositionComponent.");
		PositionComponent* targetPosComp = nullptr;


		CU::Vector2<float> ownerSize;
		CU::Vector2<float> targetSize;
		
		SpriteComponent* ownerSpriteComp = static_cast<SpriteComponent*>(myOwner->GetComponent(eComponentType::SPRITE_COMPONENT));
		if (ownerSpriteComp != nullptr)
		{
			ownerSize.x = ownerSpriteComp->GetSprite()->GetWidth()/2.f;
			ownerSize.y = ownerSpriteComp->GetSprite()->GetHeight()/2.f;
		}
		SpriteComponent* targetSpriteComp;


		float closestDist = 10000.f;
		for (int i = 0; i < myTargets.Size(); ++i)
		{
			if ((myTargetingTags & myTargets[i]->GetTags()) == 0) continue;

			targetSize.x = 0;
			targetSize.y = 0;

			targetPosComp = static_cast<PositionComponent*>(myTargets[i]->GetComponent(eComponentType::POSITION_COMPONENT));
			if (targetPosComp == nullptr) continue;

			
			targetSpriteComp = static_cast<SpriteComponent*>(myTargets[i]->GetComponent(eComponentType::SPRITE_COMPONENT));
			if (ownerSpriteComp != nullptr)
			{
				targetSize.x = ownerSpriteComp->GetSprite()->GetWidth()/2.f;
				targetSize.y = ownerSpriteComp->GetSprite()->GetHeight()/2.f;
			}

			float dist = CU::Length((targetPosComp->GetPosition() + targetSize) - (ownerPosComp->GetPosition() + ownerSize));
			if (dist <= myRange && dist <= closestDist)
			{
				myCurrentTarget = myTargets[i];
				closestDist = dist;
				//break;
			}
		}

		if (myCurrentTarget != nullptr)
		{
			Renderer::GetInstance()->RenderLine((targetPosComp->GetPosition() + targetSize), (ownerPosComp->GetPosition() + ownerSize));
		}
		
	}
};