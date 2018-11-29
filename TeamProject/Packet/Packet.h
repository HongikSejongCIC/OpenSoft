#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "/root/WorkSpace/epoll/PacketHeader.h"

class Packet
{
public:
    virtual PacketType type() = 0;
};

class PK_TEST : public Packet
{
public:	
	PacketType type() {return E_TEST;}
};
