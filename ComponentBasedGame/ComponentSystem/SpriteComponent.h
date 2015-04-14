#pragma once
#include "IComponent.h"
#include "..\HGE_BasicProject\Rendering\Sprite.h"
#include "..\HGE\include\hgecolor.h"

namespace ComponentSystem
{
	class SpriteComponent : public IComponent
	{
	public:
		SpriteComponent(GameObject& aOwner, const std::string& aSpritePath, const int aRenderPriority = 100);
		~SpriteComponent();

		void Update(const float aDeltaTime) override;

		inline void StartColorBlinking(const hgeColor& aColor, const float aDuration, const float aTimePerBlink);

		inline const std::shared_ptr<Sprite> GetSprite() const;
		inline const std::string& GetSpritePath() const;
		inline const bool IsBlinking() const;
		inline const int GetRenderPriority() const;

	private:
		std::shared_ptr<Sprite> mySprite;
		std::string mySpritePath;
		int myRenderPriority;

		bool myIsBlinking;
		bool myIsUsingBlinkColor;
		hgeColor myBlinkColor;
		float myTimePerBlink;
		float myBlinkDuration;
		float myCurrentBlinkTime;
	};

	inline const std::shared_ptr<Sprite> SpriteComponent::GetSprite() const
	{
		return mySprite;
	}

	inline const std::string& SpriteComponent::GetSpritePath() const
	{
		return mySpritePath;
	}

	inline void SpriteComponent::StartColorBlinking(const hgeColor& aColor, const float aDuration, const float aTimePerBlink)
	{
		myIsBlinking = true;
		myBlinkColor = aColor;
		myTimePerBlink = aTimePerBlink;
		myBlinkDuration = aDuration;
	}

	inline const bool SpriteComponent::IsBlinking() const
	{
		return myIsBlinking;
	}

	inline const int SpriteComponent::GetRenderPriority() const
	{
		return myRenderPriority;
	}
}
