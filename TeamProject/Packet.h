#pragma once
//#include "../ServerHeader.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

#include <thread>
#include <unordered_map>
#include <list>
#include <unordered_set>


#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <thread>

#include<array>
#include<queue>

#include "Util.h"

enum PacketType : int {
	PACKET_TYPE_ERROR = 80,
	E_C_REQ_EXIT = 90,
	E_S_ANS_EXIT = 91,
	E_C_REQ_CONNECT = 105,
	E_S_ANS_CONNECT = 106,
	E_S_NOTIFY_OTHER_CLIENT = 109,
	E_C_REQ_MOVE = 112,
	E_S_ANS_MOVE = 113,
	E_S_NOTIFY_USER_DATA = 115,
};


class Stream {

public:
	int offset;
	char buffer[BUF_SIZE];

	void operator<< (int Value) {
		memcpy(buffer + offset, &Value, sizeof(int));
		offset += sizeof(int);
	};

	void operator<< (float Value) {
		memcpy(buffer + offset, &Value, sizeof(float));
		offset += sizeof(float);
	}

	void operator<< (char Value) {
		memcpy(buffer + offset, &Value, sizeof(char));
		offset += sizeof(char);
	};

	void operator<< (short Value) {
		memcpy(buffer + offset, &Value, sizeof(short));
		offset += sizeof(short);
	};



	void operator<< (bool Value) {
		memcpy(buffer + offset, &Value, sizeof(bool));
		offset += sizeof(bool);
	}

	void operator<< (char* Value) {
		
		int stringSize = int(sizeof(char)*strlen(Value));
		*this << stringSize;

		memcpy(buffer + offset, Value ,stringSize);
		offset += stringSize;
	};

	void operator<< (std::string Value) {

		int stringSize = Value.length();
		*this << stringSize;

		
	

		memcpy(buffer + offset, Value.c_str(), stringSize);
		offset += stringSize;

	};



//-----------------------------------------------------------------------------------------------//
	void operator>> (int& Value) {
		memcpy(&Value, buffer + offset, sizeof(int));
		offset += sizeof(int);
	};


	void operator>> (short& Value) {
		memcpy(&Value, buffer + offset, sizeof(short));
		offset += sizeof(short);
	};


	void operator>> (bool& Value) {
		memcpy(&Value, buffer + offset, sizeof(bool));
		offset += sizeof(bool);
	}

	void operator>> (char* Value) {
		int stringSize;
		*this >> stringSize;
		memcpy(Value, buffer + offset, stringSize);
		offset += sizeof(char) * stringSize;
	};

	void operator>> (char& Value) {

		memcpy(&Value, buffer + offset, sizeof(char));
		offset += sizeof(char);
		
	}

	void operator>> (wchar_t* Value) {
		int stringSize;

		*this >> stringSize;

		memcpy(Value, buffer + offset, sizeof(wchar_t) * stringSize);

		offset += sizeof(wchar_t) * stringSize;

	}



	void operator>> (float& Value) {

		memcpy(&Value, buffer + offset, sizeof(float));
		offset += sizeof(float);
	}

	void operator>> (std::string& Value) {
		int stringSize;

		*this >> stringSize;

		char* str = new char[stringSize];

		memcpy(str, buffer + offset, stringSize);
		offset += stringSize;

		std::string temp(str);
		
		Value += temp;

		delete str;
	}


};  

class Packet
{

public:
	Stream stream;

public:

//	int accountId;

public:
	Packet() {
		memset(this, '\0', sizeof(*this));
	//	accountId = -1;
	}
	~Packet() { };
	virtual PacketType GetType() { return PACKET_TYPE_ERROR; };
	virtual void Encoding() {};
	virtual void Decoding() {};
};

//
//E_C_REQ_EXIT = 90,

class PK_C_REQ_EXIT : public Packet {
public:
	int accountId;
	int roomNumber;
	int userNumber;
public:

	PK_C_REQ_EXIT() {
		accountId = -1;
	}

	PacketType GetType() { return E_C_REQ_EXIT; }

	void Encoding() {

		stream << (int)GetType();
		stream << accountId;
		stream << roomNumber;
		stream << userNumber;
	}


	void Decoding() {
		stream >> accountId;
		stream >> roomNumber;
		stream >> userNumber;
	}


};


class PK_S_ANS_EXIT : public Packet {
public:
	int userNumber;
public:

	PK_S_ANS_EXIT() {
	
	}

	PacketType GetType() { return E_S_ANS_EXIT; }

	void Encoding() {

		stream << (int)GetType();

		stream << userNumber;
	}


	void Decoding() {
	
		stream >> userNumber;
	}
};

class PK_C_REQ_CONNECT : public Packet {
public:

public:

	PK_C_REQ_CONNECT() {
	
	}
	PacketType GetType() { return E_C_REQ_CONNECT; }

	void Encoding() {
		stream << (int)GetType();
	
	}

	void Decoding() {
	
	}
};


//E_S_ANS_CONNECT = 106,
class PK_S_ANS_CONNECT : public Packet {
public:
	int userNumber;

public:
	PacketType GetType() { return E_S_ANS_CONNECT; }

	void Encoding() {
		stream << (int)GetType();
		stream << userNumber;

	}

	void Decoding() {
		stream >> userNumber;

	}
};
//E_S_NOTIFY_OTHER_CLIENT = 109,

class PK_S_NOTIFY_OTHER_CLIENT : public Packet {
public:
	int userNumber;
	float pos_X;
	float pos_Y;
public:
	PK_S_NOTIFY_OTHER_CLIENT() {
	
	}
	PacketType GetType() { return E_S_NOTIFY_OTHER_CLIENT; }

	void Encoding() {
		stream << (int)GetType();
		stream << userNumber;
		stream << pos_X;
		stream << pos_Y;
	}

	void Decoding() {
		stream >> userNumber;
		stream >> pos_X;
		stream >> pos_Y;
	}
};
//E_C_REQ_MOVE = 112,

class PK_C_REQ_MOVE : public Packet {
public:
	int userNumber;
	float steering;
	float accel;
	float footbrake;
	float handbrake;
public:
	PacketType GetType() { return E_C_REQ_MOVE; }

	void Encoding() {
		stream << (int)GetType();
		stream << userNumber;
		stream << steering;
		stream << accel;
		stream << footbrake;
		stream << handbrake;
	}

	void Decoding() {
		stream >> userNumber;
		stream >> steering;
		stream >> accel;
		stream >> footbrake;
		stream >> handbrake;
	}
};
//E_S_ANS_MOVE = 113,


class PK_S_ANS_MOVE : public Packet {
public:
	int userNumber;
	float steering;
	float accel;
	float footbrake;
	float handbrake;
public:
	PacketType GetType() { return E_S_ANS_MOVE; }

	void Encoding() {
		stream << (int)GetType();
		stream << userNumber;
		stream << steering;
		stream << accel;
		stream << footbrake;
		stream << handbrake;
	}

	void Decoding() {
		stream >> userNumber;
		stream >> steering;
		stream >> accel;
		stream >> footbrake;
		stream >> handbrake;
	}

};

class PK_S_NOTIFY_USER_DATA : public Packet {
public:
	int userNumber;
	float pos_X;
	float pos_Y;
public:

	PacketType GetType() { return E_S_NOTIFY_USER_DATA; }


	void Encoding() {
		stream << (int)GetType();
		stream << userNumber;
		stream << pos_X;
		stream << pos_Y;
	}

	void Decoding() {
		stream >> userNumber;
		stream >> pos_X;
		stream >> pos_Y;
	}

};

