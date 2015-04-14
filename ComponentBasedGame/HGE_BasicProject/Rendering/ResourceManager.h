#pragma once

#include <map>
#include "..\..\HGE\include\hgesprite.h"
#include "..\..\HGE\include\hgefont.h"
#include <memory>
#include "..\..\HGE\include\hge.h"
#include <string>
#include <Vector.h>

#include "Sprite.h"

namespace CommonUtilities
{

	enum class eHotSpot
	{
		TOP_LEFT,
		TOP,
		TOP_RIGHT,
		CENTER_LEFT,
		CENTER,
		CENTER_RIGHT,
		BOTTOM_LEFT,
		BOTTOM,
		BOTTOM_RIGHT
	};

	class ResourceManager
	{
	public:
		static void Create(HGE *aHGEHandle);
		static bool Destroy();
		static ResourceManager* GetInstance();

		bool LoadFont(const std::string &aFont, const std::string &aFontPath);
		const std::shared_ptr<hgeFont>& GetFont(const std::string &aKey);


		std::shared_ptr<Sprite> GetSprite(const std::string &aKey, const std::string &aSpritePath, const CU::Vector2<float>& aPositionInTexture, const CU::Vector2<float>& aSize, eHotSpot aHotSpot = eHotSpot::TOP_LEFT);
		std::shared_ptr<Sprite> GetSprite(const std::string &aKey, const std::string &aSpritePath, eHotSpot aHotSpot = eHotSpot::TOP_LEFT);

	private:
		ResourceManager();
		~ResourceManager();

		static ResourceManager* ourInstance;

		HGE *myHGEHandle;
		std::map<std::string, std::shared_ptr<Sprite>> mySprites;
		std::map<std::string, std::shared_ptr<hgeFont>> myFonts;
	};

} namespace CU = CommonUtilities;
