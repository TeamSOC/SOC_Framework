#include "TextureManager.h"
#include <string>

using namespace std;

namespace Rendering
{
	namespace Texture
	{

		TextureManager::TextureManager()
		{
			resourceDirLen = strlen(RESOURCE_DIR);
		}

		TextureManager::~TextureManager()
		{
			DeleteAll();
		}

		Texture* TextureManager::AddTexture(std::string path, bool inResourceFolder)
		{
			if(inResourceFolder)
				path.erase(0, resourceDirLen);

			SOCHashMap<std::string, Texture*>::iterator iter = hash.find(path);

			if(iter != hash.end())
				return iter->second;

			Texture *tex = NULL;
			bool success;

			tex = new Texture();
			success = tex->Create(path.c_str());

			if(success == false)
				return NULL;

			hash.insert(SOCHashMap<string, Texture*>::value_type(path, tex));

			return tex;
		}

		Texture* TextureManager::FindTexture(std::string path, bool inResourceFolder)
		{
			if(inResourceFolder)
				path.erase(0, resourceDirLen);
			return hash.find(path)->second;
		}

		void TextureManager::Delete(std::string path, bool inResourceFolder/* = true*/)
		{
			if(inResourceFolder)
				path.erase(0, resourceDirLen);

			SOCHashMap<string, Texture*>::iterator iter = hash.find(path);

			if( iter == hash.end() )
				return;

			Utility::SAFE_DELETE(iter->second);

			hash.erase(iter);
		}

		void TextureManager::Delete(Texture* texture, bool remove)
		{
			SOCHashMap<string, Texture*>::iterator iter;
			for(iter = hash.begin(); iter != hash.end(); ++iter)
			{
				if( (*iter).second == texture )
				{
					if(remove)
						delete texture;

					hash.erase(iter);
					return;
				}
			}
		}

		void TextureManager::DeleteAll()
		{
			for(SOCHashMap<string, Texture*>::iterator iter = hash.begin();iter != hash.end(); ++iter)
				Utility::SAFE_DELETE(iter->second);

			hash.clear();
		}
	}
}