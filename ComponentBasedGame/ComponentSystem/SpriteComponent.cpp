#include <ResourceManager.h>
#include "DL_Debug.h"

#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "GameObject.h"

namespace ComponentSystem
{
	SpriteComponent::SpriteComponent(GameObject& aOwner, const std::string& aSpritePath, const int aRenderPriority) : IComponent(aOwner)
	{
		mySprite = CU::ResourceManager::GetInstance()->GetSprite(aSpritePath, aSpritePath);
		mySpritePath = aSpritePath;
		myPriority = 100;
		myRenderPriority = aRenderPriority;
		mySprite->SetRenderPriority(myRenderPriority);

		myIsBlinking = false;
		myIsUsingBlinkColor = false;
		myBlinkColor = hgeColor(1.f, 1.f, 1.f, 1.f);
		myTimePerBlink = 0.f;
		myBlinkDuration = 0.f;
	}


	SpriteComponent::~SpriteComponent()
	{
	}

	void SpriteComponent::Update(const float aDelta)
	{
		PositionComponent* ownerPosComp = static_cast<PositionComponent*>(myOwner->GetComponent(eComponentType::POSITION_COMPONENT));

		DL_ASSERT_EX(ownerPosComp != nullptr, "[SpriteComponent]: Owner did not have an Position_Component. The GameObject has to have an Position to use a SpriteComponent.");

		if (myIsBlinking == true)
		{
			myCurrentBlinkTime += aDelta;
			if (myCurrentBlinkTime >= myTimePerBlink)
			{
				myIsUsingBlinkColor = !myIsUsingBlinkColor;
				myBlinkDuration -= myCurrentBlinkTime;
				myCurrentBlinkTime = 0.f;

				if (myBlinkDuration <= 0.f)
				{
					myIsBlinking = false;
					myIsUsingBlinkColor = false;
				}
			}
		}


		if (myIsUsingBlinkColor == true)
		{
			mySprite->SetColor(myBlinkColor.GetHWColor());
		}
		else
		{
			mySprite->SetColor();
		}

		mySprite->Render(ownerPosComp->GetPosition());
	}
}
