#pragma once
#include "DataTable.h"
#include "TileMap.h"

class MapTable : public DataTable
{
	std::unordered_map<std::string, std::string> table;
	TileMap::TileType type;

protected:

public:
	MapTable(Types t);
	~MapTable() override;

	const std::string& Get(const std::string& id);

	bool Load() override;
	bool Load(Languages lang);
	void Release() override;

};

