#pragma once

//#include "../ServerHeader.h"
//#include "../Session/Session.h"
#include "Package.h"

#define MAX_PACKET_THREAD_		SIZE_64

//class Package;
class ContentsProcess
{
private:
	std::queue<Package *>	*weiteQueue;
	std::queue<Package *>	*readQueue;

protected:
	typedef void(*RunFunc)(Session *session, Packet *rowPacket);
	std::unordered_map<int, RunFunc> runFuncTable_;

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

//	virtual void registSubPacketFunc(){};

	//--------------------------------------------------------------//
	// 기본 패킷 기능 구현
	
};

