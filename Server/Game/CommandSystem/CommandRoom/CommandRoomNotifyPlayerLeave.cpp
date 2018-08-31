﻿#include "CommandHeader.h"
#include "Room.h"
#include "RoomManager.h"
#include "CharacterPlayer.h"
#include "CharacterManager.h"

void CommandRoomNotifyPlayerLeave::execute()
{
	Room* room = static_cast<Room*>(mReceiver);
	// 将玩家从房间中移除
	if (room != NULL)
	{
		room->leaveRoom(mPlayer);
	}
	// 房间中存在玩家时才不为空
	bool isEmpty = true;
	auto& playerList = room->getPlayerList();
	if (playerList.size() > 0)
	{
		auto iter = playerList.begin();
		auto iterEnd = playerList.end();
		FOR(playerList, ; iter != iterEnd; ++iter)
		{
			if (iter->second->getClientGUID() != INVALID_ID)
			{
				isEmpty = false;
				break;
			}
		}
		END(playerList);
	}
	if (!isEmpty)
	{
		// 如果需要通知其他玩家
		if (mNotifyOtherPlayer)
		{
			auto& playerList = room->getPlayerList();
			auto iterPlayer = playerList.begin();
			auto iterPlayerEnd = playerList.end();
			FOR(playerList, ; iterPlayer != iterPlayerEnd; ++iterPlayer)
			{
				CommandCharacterNotifyOtherPlayerLeaveRoom* cmdLeave = NEW_CMD_INFO(cmdLeave);
				cmdLeave->mLeavePlayerID = mPlayer->getGUID();
				pushCommand(cmdLeave, iterPlayer->second);
			}
			END(playerList);
		}
	}
	// 房间已经没人,或者玩家离开后只剩机器人
	else 
	{
		// 真实玩家退出时才会判断是否将全部的机器人退出去,然后销毁房间
		if (mPlayer->getType() == CT_PLAYER)
		{
			// 使全部机器人退出房间
			// 复制一份列表,避免迭代器失效
			auto tempList = playerList;
			auto iter = tempList.begin();
			auto iterEnd = tempList.end();
			FOR(tempList, ; iter != iterEnd; ++iter)
			{
				CommandCharacterLeaveRoom* leave = NEW_CMD_INFO(leave);
				pushCommand(leave, iter->second);
			}
			END(tempList);
			// 销毁房间
			CommandRoomManagerDestroyRoom* cmdDestroyRoom = NEW_CMD_INFO(cmdDestroyRoom);
			cmdDestroyRoom->mRoomID = room->getID();
			pushCommand(cmdDestroyRoom, mRoomManager);
		}
	}
}

std::string CommandRoomNotifyPlayerLeave::showDebugInfo()
{
	COMMAND_DEBUG(DEBUG_EMPTY);
}
