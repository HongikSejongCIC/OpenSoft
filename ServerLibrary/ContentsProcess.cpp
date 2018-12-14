#include "ContentsProcess.h"

int ContentsProcess::virtualAccountId = 0;
static User user[2];
static std::recursive_mutex lock_;


ContentsProcess::ContentsProcess()
{
	this->initialize();
}

ContentsProcess::~ContentsProcess()
{

	for(int i = 0 ; i< 5; i++){
		t[i].join();
	}	

	runFuncTable_.clear();
}

void ContentsProcess::initialize()
{
	int processCount = 5;

	//쓰레드 풀 필요함.
	for(int i = 0 ; i < processCount ; i ++){
		t[i] = std::thread{&ContentsProcess::process , this};
	}
	this->registDefaultPacketFunc();
}

void ContentsProcess::registDefaultPacketFunc()
{

//#define INSERT_PACKET_PROCESS(type) runFuncTable_.insert(std::make_pair(E_##type,&ContentsProcess::##type))

//		INSERT_PACKET_PROCESS(C_REQ_EXIT);
//		INSERT_PACKET_PROCESS(C_REQ_CONNECT);
//		INSERT_PACKET_PROCESS(C_REQ_MOVE);
		runFuncTable_.insert(std::make_pair(E_C_REQ_EXIT,ContentsProcess::C_REQ_EXIT));
		runFuncTable_.insert(std::make_pair(E_C_REQ_CONNECT,ContentsProcess::C_REQ_CONNECT));
		runFuncTable_.insert(std::make_pair(E_C_REQ_MOVE,ContentsProcess::C_REQ_MOVE));

}

void ContentsProcess::putPackage(Package *package)
{
	lock__.lock();
	printf("put Package! \n");
	packetQueue.push(package);
	lock__.unlock();
}

void ContentsProcess::run(Package *package)
{
	PacketType type = package->packet_->GetType();
	printf("package's packet Type is %d \n", type);
	auto itr = runFuncTable_.find((int)type);
	if (itr == runFuncTable_.end()) {
//		package->session_->onClose();
		printf("is Not Exist Func in table \n");		
		return;
	}
	RunFunc runFunction = itr->second;
#ifdef _DEBUG
	
#endif //_DEBUG
	runFunction(package->session_, package->packet_);
}

void ContentsProcess::execute()
{
	Package *package = nullptr;
	if (packetQueue.empty()) {	
		return;
	}
	
	lock__.lock();
	if(packetQueue.empty()){
		lock__.unlock();
		return;
	}
	package = packetQueue.front();
	packetQueue.pop();
	lock__.unlock();

	this->run(package);
	
	delete(package);
}

void ContentsProcess::process()
{
	while (true) {
		this->execute();
	}
}




//--------------------------------------------------------------//
// 기본 패킷 기능 구현



void ContentsProcess::C_REQ_EXIT(Session* session, Packet* rowPacket) {

	PK_C_REQ_EXIT* packet = (PK_C_REQ_EXIT*)rowPacket;
	printf("C_REQ_EXIT Packet\n");


	delete packet;
	/*
	TODO : Find User , Delete Session;
	*/

	
}


void ContentsProcess::C_REQ_CONNECT(Session* session, Packet* rowPacket) {

	printf("Entet CONNECT\n");

	PK_C_REQ_CONNECT* packet = (PK_C_REQ_CONNECT*)rowPacket;
	//User* user = new User(session,packet->accountId, packet->name);
	PK_S_ANS_CONNECT ansPacket;
//	EnterCriticalSection(&lock);
	lock_.lock();
	user[virtualAccountId].session = session;
	ansPacket.userNumber = virtualAccountId;
	user[virtualAccountId].userNumber = virtualAccountId++;
//	LeaveCriticalSection(&lock);
	lock_.unlock();
	
	//session->SendPacket(&ansPacket);

	session->SendtoOther(&ansPacket);

	delete packet;
}



/*
	서버
*/

void ContentsProcess::C_REQ_MOVE(Session* session, Packet* rowPacket) {

	printf("Enter MOVE\n");
	
	PK_C_REQ_MOVE* packet = (PK_C_REQ_MOVE*)rowPacket;


	
	PK_S_ANS_MOVE ansPacket;
	ansPacket.userNumber = packet->userNumber;
	ansPacket.steering = packet->steering;
	ansPacket.accel = packet->accel;
	ansPacket.footbrake = packet->footbrake;
	ansPacket.handbrake = packet->handbrake;
	
	if (packet->userNumber == 0) {
		user[1].session->SendtoOther(&ansPacket);
	}
	else {
		user[0].session->SendtoOther(&ansPacket);
	}

	
	//TODO :
	// 맵에대한 접근을 SRW로 한다면 어떨까? 

	printf("userNumber : %d, steering : %f, accel : %f, footbrak : %f, handbrake : %f\n", packet->userNumber, packet->steering, packet->accel, packet->footbrake, packet->handbrake);
	
	
	delete packet;
}

