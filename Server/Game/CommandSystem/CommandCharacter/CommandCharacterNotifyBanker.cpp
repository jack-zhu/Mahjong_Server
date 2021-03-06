﻿#include "CommandHeader.h"
#include "CharacterPlayer.h"
#include "CharacterData.h"
#include "CharacterManager.h"
#include "PacketHeader.h"
#include "NetServer.h"

void CommandCharacterNotifyBanker::execute()
{
	CharacterPlayer* player = static_cast<CharacterPlayer*>(mReceiver);
	SCNotifyBanker* notifyBanker = NEW_PACKET(notifyBanker, PT_SC_NOTIFY_BANKER);
	notifyBanker->mGUID = mBankerID;
	sendMessage(notifyBanker, player);
}

std::string CommandCharacterNotifyBanker::showDebugInfo()
{
	COMMAND_DEBUG("banker id : %d", (int)mBankerID);
}