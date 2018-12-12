#pragma once
//#include "../ServerHeader.h"

#include "Session.h"
class Package
{
public:
	Session *session_;
	Packet *packet_;
	Package(){

	}
	Package(Session *session, Packet *packet)
	{
		session_ = session;
		packet_ = packet;
	}

	~Package()
	{
		session_ = nullptr;
		delete(packet_);
	}
};
