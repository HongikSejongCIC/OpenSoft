#pragma once

#include "../ServerHeader.h"
class Session;
class Package
{
public:
	Session *session_;
	Packet *packet_;

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
