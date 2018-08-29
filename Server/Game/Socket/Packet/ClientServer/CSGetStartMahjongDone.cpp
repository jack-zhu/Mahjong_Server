﻿#include "PacketHeader.h"
#include "MySQLDataBase.h"
#include "NetServer.h"
#include "CommandHeader.h"
#include "NetClient.h"
#include "CharacterManager.h"
#include "CharacterPlayer.h"
#include "RoomManager.h"
#include "Room.h"
#include "CharacterData.h"
#include "MahjongRobotManager.h"
#include "CharacterMahjongRobot.h"

void CSGetStartMahjongDone::execute()
{
	Character* character = mCharacterManager->getCharacter(mClient->getCharGUID());
	CommandCharacterGetStartDone* cmd = NEW_CMD_INFO(cmd);
	pushCommand(cmd, character);
}
