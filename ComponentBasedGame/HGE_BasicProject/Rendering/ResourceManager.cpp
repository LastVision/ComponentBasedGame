#include "ResourceManager.h"
#include "DL_Debug.h"

namespace CommonUtilities
{
	//****** STATIC ******

	void ResourceManager::Create(HGE *aHGEHandle)
	{
		DL_ASSERT_EX(ourInstance == nullptr, "Tried to [Create] a [ResourceManager] after we allready created one");

		ourInstance = new ResourceManager();
		ourInstance->myHGEHandle = aHGEHandle;
	}

	ResourceManager* ResourceManager::GetInstance()
	{
		return ourInstance;
	}
	bool ResourceManager::Destroy()
	{
		delete ourInstance;
		ourInstance = nullptr;

		return true;
	}


	//****** PUBLIC ******
	bool ResourceManager::LoadFont(const std::string &aKey, const std::string &aFontPath)
	{
		myFonts[aKey] = std::shared_ptr<hgeFont>(new hgeFont(aFontPath.c_str()));
		return true;
	}

	const std::shared_ptr<hgeFont>& ResourceManager::GetFont(const std::string &aKey)
	{
		if (myFonts.find(aKey) == myFonts.end())
		{
			DL_DEBUG("[ResourceManager]: Tried to [GetFont] an unloaded font. [Key]: %s", aKey.c_str());
			DL_ASSERT("Failed to [GetFont]");
		}

		return myFonts[aKey];
	}


	std::shared_ptr<Sprite> ResourceManager::GetSprite(const std::string &aKey, const std::string &aSpritePath, const CU::Vector2<float>& aPositionInTexture, const CU::Vector2<float>& aSize, eHotSpot aHotspot)
	{
		if (mySprites.find(aKey) == mySprites.end())
		{
			HTEXTURE tex = myHGEHandle->Texture_Load(aSpritePath.c_str());

			hgeSprite* sprite = new hgeSprite(tex, aPositionInTexture.x, aPositionInTexture.y, aSize.x, aSize.y);

			mySprites[aKey] = std::shared_ptr<Sprite>(new Sprite());
			mySprites[aKey]->SetHGESprite(sprite);
			if (aHotspot == CU::eHotSpot::CENTER)
			{
				mySprites[aKey]->SetHotspot(CU::Vector2<float>(aSize.myX / 2, aSize.myY / 2));
			}
		}

		return mySprites[aKey];
	}

	std::shared_ptr<Sprite> ResourceManager::GetSprite(const std::string &aKey, const std::string &aSpritePath, eHotSpot aHotspot)
	{
		if (mySprites.find(aKey) == mySprites.end())
		{

			HTEXTURE tex = myHGEHandle->Texture_Load(aSpritePath.c_str());
			float width = static_cast<float>(myHGEHandle->Texture_GetWidth(tex));
			float height = static_cast<float>(myHGEHandle->Texture_GetHeight(tex));


			hgeSprite* sprite = new hgeSprite(tex, 0.f, 0.f, width, height);

			mySprites[aKey] = std::shared_ptr<Sprite>(new Sprite());
			mySprites[aKey]->SetHGESprite(sprite);
			if (aHotspot == CU::eHotSpot::CENTER)
			{
				mySprites[aKey]->SetHotspot(CU::Vector2<float>(width / 2, height / 2));
			}
		}

		return mySprites[aKey];
	}

	//****** PRIVATE ******

	ResourceManager* ResourceManager::ourInstance = nullptr;

	ResourceManager::ResourceManager()
	{
	}


	ResourceManager::~ResourceManager()
	{
	}
};