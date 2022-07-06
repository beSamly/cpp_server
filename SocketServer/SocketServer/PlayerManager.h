#pragma once

#include "Player.h"
#include "Scheduler.h"

class PlayerManager : public Scheduler
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

