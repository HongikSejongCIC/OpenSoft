Server.exe : Server.o ContentsProcess.o Session.o
	g++ -std=c++11 -pthread -o Server.exe Server.o ContentsProcess.o Session.o

Server.o : Server.cpp
	g++ -std=c++11 -pthread -c Server.cpp

ContentsProcess.o : ContentsProcess.cpp
	g++ -std=c++11 -pthread -c ContentsProcess.cpp

Session.o : Session.cpp
	g++ -std=c++11 -c Session.cpp


