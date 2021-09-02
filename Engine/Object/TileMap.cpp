#include "TileMap.h"
#include"Engine.h"
namespace henry
{
	void TileMap::Create()
	{
		for (int i = 0; i < tile.size(); i++)
		{
			int index = tile[i];
			if (index == 0) continue;

			auto actor = ObjectFactory::Instance().Create<Actor>(tileName[index]);
			if (actor)
			{
				int x = i % numTileX;
				int y = i / numTileX;
				
				actor->transform.position = start + (henry::Vector2{ x, y } * size);
				scene->AddActor(std::move(actor));
			}
		}
	}

	bool TileMap::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool TileMap::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, numTileX);
		JSON_READ(value, numTileY);
		JSON_READ(value, start);
		JSON_READ(value, size);
		JSON_READ(value, tileName);
		JSON_READ(value, tile);


		return true;
	}
}