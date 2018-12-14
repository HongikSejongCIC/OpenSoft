#pragma once
#include "ServerHeader.h"


using namespace std;



class Session{
private:
	int socket_;
	int r_bytes;
	int s_bytes;
	queue<Packet*> p;
	char buff[BUF_SIZE];

	recursive_mutex lock_;

public:

	int total_bytes;

	char recvBuff[BUF_SIZE];  
	Session(int sock);
	bool recvMessage(int getByte);
	void pushPacket(Packet* pack);
	Packet* popPacket();
	void SendtoOther(Packet* pack);
	Packet* getPacket(PacketType packetType);
};
