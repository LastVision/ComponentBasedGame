#pragma once
#include "IComponent.h"
#include "InputWrapper.h"

namespace ComponentSystem
{
	class InputComponent : public IComponent
	{
	public:
		InputComponent(GameObject& aOwner, InputWrapper* aInput, const char aUpKey, const char aDownKey, const char aLeftKey, const char aRightKey);
		~InputComponent();

		void Update(const float aDelta) override;


		inline const char GetUpKey() const;
		inline const char GetDownKey() const;
		inline const char GetLeftKey() const;
		inline const char GetRightKey() const;

	private:
		InputWrapper* myInput;
		char myUpKey;
		char myDownKey;
		char myLeftKey;
		char myRightKey;
	};

	inline const char InputComponent::GetUpKey() const
	{
		return myUpKey;
	}

	inline const char InputComponent::GetDownKey() const
	{
		return myDownKey;
	}

	inline const char InputComponent::GetLeftKey() const
	{
		return myLeftKey;
	}

	inline const char InputComponent::GetRightKey() const
	{
		return myRightKey;
	}
}
