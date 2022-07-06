#include "pch.h"
#include "PlayerManager.h"
#include "Job.h"

void PlayerManager::AddPlayer(PlayerRef player)
{
	WRITE_LOCK;
	_players->insert(make_pair(player->GetAccountId(), player));
	return;
}
void PlayerManager::Update() {
	Vector<PlayerRef> copiedPlayers;
	{
		WRITE_LOCK;
		for (auto const& [accountId, player] : *_players) {
			copiedPlayers.push_back(player);
		}
	}

	for (auto& player : copiedPlayers) {
		player->Update();
	}
}

PlayerManager::PlayerManager() {
	auto job = MakeShared<Job>([this]() {
		this->Update();
	});
	Scheduler::SetInterval(job);
}