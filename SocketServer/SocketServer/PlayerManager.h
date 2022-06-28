#pragma once

#include "Player.h"
#include "RunInterval.h"

class PlayerManager : public RunInterval
{
public:
	PlayerManager();
private :
	USE_LOCK;
	MapRef<int32, PlayerRef> _players = MakeShared<Map<int32, PlayerRef>>();

public:
	void AddPlayer(PlayerRef player);
	void Update();
};

