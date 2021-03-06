﻿#include "CommandHeader.h"
#include "CharacterPlayer.h"
#include "PacketHeader.h"
#include "NetServer.h"
#include "CharacterData.h"

void CommandCharacterNotifyOtherPlayerDrop::execute()
{
	CharacterPlayer* player = static_cast<CharacterPlayer*>(mReceiver);
	SCOtherPlayerDrop* otherPlayerDrop = NEW_PACKET(otherPlayerDrop, PT_SC_OTHER_PLAYER_DROP);
	otherPlayerDrop->mPlayerGUID = mPlayerGUID;
	otherPlayerDrop->mMahjong = mMahjong;
	otherPlayerDrop->mIndex = mIndex;
	sendMessage(otherPlayerDrop, player);

	// 打出一张牌后需要重新排列
	CommandCharacterNotifyOtherPlayerReorderMahjong* cmdReorder = NEW_CMD_INFO(cmdReorder);
	cmdReorder->mPlayerGUID = mPlayerGUID;
	pushCommand(cmdReorder, player);
}

std::string CommandCharacterNotifyOtherPlayerDrop::showDebugInfo()
{
	COMMAND_DEBUG("player guid : %d, mahjong : %s", (int)mPlayerGUID, MAHJONG_NAME[(int)mMahjong].c_str());
}