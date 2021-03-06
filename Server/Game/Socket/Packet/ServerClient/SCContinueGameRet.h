﻿#ifndef _SC_CONTINUE_GAME_RET_H_
#define _SC_CONTINUE_GAME_RET_H_

#include "Packet.h"

class SCContinueGameRet : public Packet
{
public:
	SCContinueGameRet(PACKET_TYPE type)
		:Packet(type) {}
	virtual void fillParams()
	{
		pushParam(mBanker);
	}
public:
	bool mBanker;
};

#endif