#pragma once

//#include "../ServerHeader.h"
//#include "../Session/Session.h"
#include "Package.h"

#define MAX_PACKET_THREAD_		SIZE_64

class User {

public:
	float pos_X;
	float pos_Y;
	int userNumber;
	Session* session;
	//CRITICAL_SECTION lock;
	int	direction;
	bool isReady;
	User() {}
	User(Session* session,int id) :session(session) {
		id = userNumber;
		pos_X = 1.0f;
		pos_Y = -1.0f;
		isReady = false;
		direction = 0;
	}

public:
	void SetDirection(int direction) {
		this->direction = direction;
	}
	void SetReady() {
		isReady = true;
	}
	bool IsReady() {
		return isReady;
	}
	void ResetReady() {
		isReady = false;
	}
	void SetUserNumber(int userNumber) {
		this->userNumber = userNumber;
	}
	int GetUserNumber() { return this->userNumber; }
	void SetPosition(float pos_X, float pos_Y) { 
		this->pos_X = pos_X;
		this->pos_Y = pos_Y;
	}
	void GetPositition(float &pos_X, float &pos_Y) {
		pos_X = this->pos_X;
		pos_Y = this->pos_Y;
	}
	Session* GetSession() {
		return session;
	}
};


class ContentsProcess
{
private:
	std::queue<Package *>	packetQueue;
	std::thread	t[5];

	std::recursive_mutex lock__;

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
	
	static int virtualAccountId;
	static void C_REQ_EXIT(Session* session, Packet* packet);
	static void C_REQ_CONNECT(Session* session, Packet* packet);
	static void C_REQ_MOVE(Session* session, Packet* packet);

	void putPackage(Package *package);

	//--------------------------------------------------------------//
	// 기본 패킷 기능 구현
	
};

