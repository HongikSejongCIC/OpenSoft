#include "Session.h"

Session :: Session(int sock)
{
	socket_ = sock;
}
bool Session :: recvMessage(int getByte)
{
	
	memcpy(&buff[total_bytes],recvBuff,getByte);
	total_bytes += getByte;

	while(1)
	{
		int packetSize;
		PacketType packetType;
		int currentOffset = 0;
		
		if(total_bytes < sizeof(int))//total_bytes가 처음recv를 받았다면고대로 total_bytes에 받은 바이트만큼 넣어줌
			break;
 		
		memcpy(&packetSize, buff, sizeof(int));
		currentOffset += sizeof(int);
		printf("size: %d",packetSize);

		if(total_bytes < packetSize)
			break;

		memcpy(&packetType, &buff[currentOffset], sizeof(int));
		currentOffset += sizeof(int);

		Packet* packet = getPacket(packetType);



		memcpy(packet->stream.buffer,&buff[currentOffset], packetSize- currentOffset);


		packet->Encoding();

		pushPacket(packet);

		memcpy(buff,&buff[packetSize],total_bytes-packetSize);
		total_bytes -= packetSize;
	}
	return true;
}

Packet* Session :: getPacket(PacketType packetType){

	switch(packetType){
	case E_C_REQ_EXIT: return new PK_C_REQ_EXIT();

	}
	return nullptr;
}

void Session :: pushPacket(Packet* pack)
{
	p.push(pack);
}

void Session :: popPacket(Packet* pack)
{
	if(p.empty()){
		pack = nullptr;
	}
	pack = p.front();
	p.pop();
}

void Session :: SendtoOther(Packet* pack )
{
	/*
	char buff[MAX_BUFF_SIZE] = {NULL,};
	int total_Send_bytes = 0;
	while(!p.empty())
	{
		packet_* tmppack = NULL; 
		pack_dequeue(tmppack);
		int len = sizeof(tmppack->data_) + sizeof(tmppack->type_);	
		sscanf(buff, "%d", len);//길이를 버퍼에 넣어줌
		sscanf(buff + sizeof(int), "%d", tmppack->type_);//int형태의 타입을 버퍼에 넣어줌
		memcpy(buff + sizeof(int)*2, tmppack->data_, sizeof(tmppack->data_));
		
		s_bytes = send(socket_,buff,MAX_BUFF_SIZE,0);
		printf("pack_len: %d, pack_type: %d, pack_data: %s\n", len, tmppack->type_, tmppack->data_);
	}
	*/
}
