#include "Session.h"

Session :: Session(int sock)
{
	socket_ = sock;


	r_bytes = 0;
	total_bytes = 0;
	s_bytes = 0;
	memset(buff, 0 , BUF_SIZE);

}
bool Session :: recvMessage(int getByte)
{
	memcpy(&buff[total_bytes],recvBuff,getByte);
	total_bytes += getByte;
	printf("receive bytes %d, total Bytes : %d \n", getByte, total_bytes);

	while(1)
	{
		int packetSize;
		PacketType packetType;
		int currentOffset = 0;
			
		if(total_bytes < sizeof(int)){
			printf("total_bytes is not enough to parsing \n");
			break;
		}
 		
		memcpy(&packetSize, buff, sizeof(int));
		currentOffset += sizeof(int);
		printf("size: %d",packetSize);

		if(total_bytes < packetSize)
			break;

		memcpy(&packetType, &buff[currentOffset], sizeof(int));
		currentOffset += sizeof(int);

		Packet* packet = getPacket(packetType);

		memcpy(packet->stream.buffer,&buff[currentOffset], packetSize- currentOffset);

		packet->Decoding();
		
		printf("Stream Parse! Packet Type : %d \n", packet->GetType());	
		pushPacket(packet);

		memcpy(buff,&buff[packetSize],total_bytes-packetSize);
		total_bytes -= packetSize;
	}
	return true;
}

Packet* Session :: getPacket(PacketType packetType){

	switch (packetType) {
	case E_C_REQ_EXIT: return new PK_C_REQ_EXIT();
	case E_S_ANS_EXIT: return new PK_S_ANS_EXIT();

	case E_C_REQ_CONNECT: return new PK_C_REQ_CONNECT();
	case E_S_ANS_CONNECT: return new PK_S_ANS_CONNECT();
	
	case E_S_NOTIFY_OTHER_CLIENT: return new PK_S_NOTIFY_OTHER_CLIENT();

	case E_C_REQ_MOVE: return new PK_C_REQ_MOVE();
	case E_S_ANS_MOVE: return new PK_S_ANS_MOVE();

	case E_S_NOTIFY_USER_DATA: return new PK_S_NOTIFY_USER_DATA();

	}
	return nullptr;
}

void Session :: pushPacket(Packet* pack)
{
	lock_.lock();
	p.push(pack);
	lock_.unlock();
}

Packet* Session :: popPacket()
{

	Packet* temp = nullptr;
	lock_.lock();
	if(p.empty()){
		printf("Sesion Queue Empty\n");
	
	}else{
		printf("popPacket");
	
		temp = p.front();
		p.pop();
	}

	lock_.unlock();

	return temp;
}

void Session :: SendtoOther(Packet* pack )
{	

	pack->stream.offset = 0;
		

	pack->Encoding();

	int buflen = pack->stream.offset + sizeof(int);
	char buf[100] = {0,};
	memcpy(buf,&buflen,sizeof(int));
	memcpy(&buf[sizeof(int)],pack->stream.buffer,pack->stream.offset);

//	memcpy(&pack->stream.buffer[sizeof(int)],pack->stream.buffer,pack->stream.offset);
//	memcpy(pack->stream.buffer,&buflen,sizeof(int));

	s_bytes = send(socket_,buf,buflen,0);
	printf("pack_len: %d, pack_type: %d, \n", buflen , pack->GetType());
	
	
}
