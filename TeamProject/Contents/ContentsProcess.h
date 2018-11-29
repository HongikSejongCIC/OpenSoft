#pragma once
#include<array>
#include<queue>
//#include<unordered_map>
//#include<hash_map>
#include <map>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

#include"/root/WorkSpace/epoll/Package.h"

// 컨텐츠를 여기서 파생해서 구현합니다.

#define MAX_PACKET_THREAD_		SIZE_64
class ContentsProcess
{
private:
	std::queue<Package *>	*weiteQueue;
	std::queue<Package *>	*readQueue;

protected:
	typedef void(*RunFunc)(Session *session, Packet *rowPacket);
	std::map<PacketType, RunFunc> runFuncTable_;

private:
	void initialize();
	void registDefaultPacketFunc();
	void run(Package *package);
	void execute();

	void process();
public:
	ContentsProcess();
	~ContentsProcess();
	
	void putPackage(Package *package);

	virtual void registSubPacketFunc() = 0;

	//--------------------------------------------------------------//
	// 기본 패킷 기능 구현
	
};

