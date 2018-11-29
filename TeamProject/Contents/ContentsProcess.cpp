#include "/root/WorkSpace/epoll/ContentsProcess.h"

ContentsProcess::ContentsProcess()
{
	this->initialize();
}

ContentsProcess::~ContentsProcess()
{
	delete(weiteQueue);
	delete(readQueue);

	runFuncTable_.clear();
}

void ContentsProcess::initialize()
{
	int processCount = 5;

	weiteQueue = new std::queue<Package *>;
	readQueue = new std::queue<Package *>;
	//쓰레드 풀 필요함.
	std::thread{&ContentsProcess::process , this};
	this->registDefaultPacketFunc();
}

void ContentsProcess::registDefaultPacketFunc()
{

}

void ContentsProcess::putPackage(Package *package)
{
	weiteQueue->push(package);
}

void ContentsProcess::run(Package *package)
{
	PacketType type = package->packet_->type();
	auto itr = runFuncTable_.find(type);
	if (itr == runFuncTable_.end()) {
		package->session_->onClose();
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
	if (readQueue->empty()) {
		return;
	}
	
	package = readQueue->front();
	readQueue->pop();

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
