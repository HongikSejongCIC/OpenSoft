#pragma once
#include "ServerHeader.h"


using namespace std;

#define MAX_BUFF_SIZE 1024


class Session{
private:
	int socket_;
	int r_bytes;
	int total_bytes;
	int s_bytes;
	queue<Packet*> p;
	char buff[MAX_BUFF_SIZE];
public:
	char recvBuff[MAX_BUFF_SIZE];  
	Session(int sock);
	bool recvMessage(int getByte);
	void pushPacket(Packet* pack);
	void popPacket(Packet* pack);
	void SendtoOther(Packet* pack);
	Packet* getPacket(PacketType packetType);
};
