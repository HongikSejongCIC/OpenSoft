#pragma once
#include "../ServerHeader.h"


class Server{


public:
	std::thread epoll_Thread[THREAD_COUNT];	
	int ip;
	int port;
	
	int epfd;
	int lstnfd;

	int eventCount;

	struct epoll_event listen_event;

	//std::unordered_map<int,Session*> Session_Map; 
	
public:
	Server();
	~Server();
	void SetNonBlocking(int fd);
	void Initialize();
	void Listen();
	
	void CreateEpoll();
	void RegistEpollEvent(int fd, epoll_event& event, unsigned int flag);

	//void CreateSession();
	void Run();
	void Create_Thread();
	void test();	
};
