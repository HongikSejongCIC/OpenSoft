#include "Server.h"

//g++ -std=gnu++11 -pthread Server.cpp

Server::Server(ContentsProcess* contentsProcess){
	this->contentsProcess = contentsProcess;
	port = 9000;
	Initialize();
}


void Server::Initialize(){
	CreateEpoll();	
	Listen();
	RegistEpollEvent(lstnfd,listen_event, EPOLLIN);

	Create_Thread();

}

void Server::Listen(){
	
	struct sockaddr_in addr_in;
	
	lstnfd = socket(PF_INET,SOCK_STREAM, 0);
	
	if(lstnfd < 0){
		printf("Make Listen socket Failed");
		return;
	}

	memset(&addr_in, 0, sizeof(sockaddr_in));

	addr_in.sin_family = AF_INET;
	addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_in.sin_port = htons(port);
	
	if(bind(lstnfd, (struct sockaddr*)&addr_in, sizeof(sockaddr_in))<0){
		printf("bind error");
		return;
	}

	if(listen(lstnfd, 5) < 0){
		printf("listen Failed ");
		return;
	}
	

}

void Server::SetNonBlocking(int fd){
	int flag = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flag|O_NONBLOCK);

}

void Server::CreateEpoll(){
	if((epfd = epoll_create(INCREASE_COUNT * 10)) < 0){
		printf("epoll_create Failed\n");
		return;
	}		
}

void Server::RegistEpollEvent(int fd, epoll_event& event, unsigned int flag){

memset(&event, 0, sizeof(epoll_event));

event.events = flag;
event.data.fd = fd;
epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);

}
/*
void Server::CreateSession(){
	
}
*/
void Server::Run(){

	epoll_event event;
	int client;	
	char buf[BUF_SIZE] = { 0,};
	while(true){
	try{
		int ret = epoll_wait(epfd,&event, 1 , -1);
		if( ret < 0 ){
			printf("epoll_wait Error\n ");
			return; 
		}


		if(event.data.fd == lstnfd){
			
			sockaddr_in client_addr;
			socklen_t addrlen = sizeof(sockaddr_in);
		
			client = accept(lstnfd, (sockaddr*)&client_addr,&addrlen);
			if(client < 0 ){
				printf("Accept Error\n");
				return;
			}			
			SetNonBlocking(client);
			epoll_event clientEpollEvent;
			RegistEpollEvent(client,clientEpollEvent,EPOLLIN | EPOLLET);
			
			Session* session = new Session(client);
			
			Session_Map.insert(std::make_pair(client, session));

		}

		else{
			client = event.data.fd;
			
			Session* session = Session_Map.find(client)->second;

			int recvBytes = read(client, session->recvBuff , BUF_SIZE);
			
			printf("Recv Bytes => %d\n" , recvBytes);
			buf[recvBytes] = '\0';	
			printf("buf : %s\n " , buf);
			
			
			session->recvMessage(recvBytes);
			
			while(true){
			Packet* packet = nullptr;
			session->popPacket(packet);
			if(packet == nullptr)
				break;

			Package* package = Packaging(session,packet);	
			contentsProcess->putPackage(package);						
			
			
			
			}
			/*
				TODO : Get Session From Session_Map
				TODO : Request Data Analyzer to Session
				TODO : Push Package to Contents
			*/

		}
		}catch(int fd){
			int client = event.data.fd;
			RegistEpollEvent(client,event,EPOLL_CTL_DEL);
			printf("Error Client Out\n");
		
		}
	}
	

}

Package* Server::Packaging(Session* session, Packet* packet){

	Package* package = new Package();
	package->session_ = session;
	package->packet_ = packet;
	return package;
}

Server::~Server(){
	for(int i = 0; i < THREAD_COUNT ; i++)
		epoll_Thread[i].join();

}


void Server::test(){

	printf("test");
}


void Server::Create_Thread(){
	for(int i = 0 ; i < THREAD_COUNT; i++){
		epoll_Thread[i] = std::thread {&Server::Run, this};
	}

	//	epoll_Thread[i] = std::thread {&Server::Run, this};

}

int main(){
	
	ContentsProcess* contentsProcess = new ContentsProcess();
	Server* server = new Server(contentsProcess);
	server->Run();

	while(true){

	}		
	return 0;

}
