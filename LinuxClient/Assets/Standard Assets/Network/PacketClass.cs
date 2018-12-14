using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace DummyClient
{
    public class PK_C_REQ_EXIT : Packet, Packetinterface
    {

        public int accountId;
        public int roomNumber;
        public int userNumber;
        
        public PK_C_REQ_EXIT()
        {
            type = (int)PacketType.E_C_REQ_EXIT;

        }

        int Packetinterface.getType(){
            return type;
        }

        void Packetinterface.encode()
        {
            PacketUtil.encodeHeader(stream, type);
            PacketUtil.encode(stream, accountId);
            PacketUtil.encode(stream, roomNumber);
            PacketUtil.encode(stream, userNumber);
        }
        void Packetinterface.decode(byte[] packet, ref int offset)
        {
            accountId = PacketUtil.decodeInt32(packet, ref offset);
            roomNumber = PacketUtil.decodeInt32(packet, ref offset);
            userNumber = PacketUtil.decodeInt32(packet, ref offset);
        }
        MemoryStream Packetinterface.getStream()
        {
            return stream;
        }
    }

    public class PK_S_ANS_EXIT : Packet, Packetinterface
    {

    
        public int userNumber;

        public PK_S_ANS_EXIT()
        {
            type = (int)PacketType.E_S_ANS_EXIT;

        }

        int Packetinterface.getType()
        {
            return type;
        }

        void Packetinterface.encode()
        {
            PacketUtil.encodeHeader(stream, type);
      
            PacketUtil.encode(stream, userNumber);
        }
        void Packetinterface.decode(byte[] packet, ref int offset)
        {
            userNumber = PacketUtil.decodeInt32(packet, ref offset);
        }
        MemoryStream Packetinterface.getStream()
        {
            return stream;
        }
    }

  

    //E_C_REQ_CONNECT = 105,

    public class PK_C_REQ_CONNECT : Packet, Packetinterface
    {

     
        public PK_C_REQ_CONNECT()
        {
            type = (int)PacketType.E_C_REQ_CONNECT;
        }


        void Packetinterface.encode()
        {
            PacketUtil.encodeHeader(stream, type);
     
        }
        void Packetinterface.decode(byte[] packet, ref int offset)
        {

        }

        MemoryStream Packetinterface.getStream()
        {
            return stream;
        }


        int Packetinterface.getType()
        {
            return type;
        }
    };


    //E_S_ANS_CONNECT = 106,
    public class PK_S_ANS_CONNECT : Packet, Packetinterface
    {
        public int userNumber;
      
        public PK_S_ANS_CONNECT()
        {
            type = (int)PacketType.E_S_ANS_CONNECT;
        }


        void Packetinterface.encode()
        {
            PacketUtil.encodeHeader(stream, type);
            PacketUtil.encode(stream, userNumber);

        }
        void Packetinterface.decode(byte[] packet, ref int offset)
        {
            userNumber = PacketUtil.decodeInt32(packet, ref offset);

        }

        MemoryStream Packetinterface.getStream()
        {
            return stream;
        }


        int Packetinterface.getType()
        {
            return type;
        }
    };
    //E_C_REQ_CONNECT_ROOM = 107,
   
    //E_S_NOTIFY_OTHER_CLIENT = 109,

    public class PK_S_NOTIFY_OTHER_CLIENT : Packet, Packetinterface
    {
    	public int userNumber;
        public float pos_X;
        public float pos_Y;

	    public PK_S_NOTIFY_OTHER_CLIENT()
        {
            type = (int)PacketType.E_S_NOTIFY_OTHER_CLIENT;
        }

        void Packetinterface.encode()
        {
            PacketUtil.encodeHeader(stream, type);
            PacketUtil.encode(stream, userNumber);
            PacketUtil.encode(stream, pos_X);
            PacketUtil.encode(stream, pos_Y);
        }
        void Packetinterface.decode(byte[] packet, ref int offset)
        {
            userNumber = PacketUtil.decodeInt32(packet, ref offset);
            pos_X = PacketUtil.decodefloat(packet, ref offset);
            pos_Y = PacketUtil.decodefloat(packet, ref offset);
        }

        MemoryStream Packetinterface.getStream()
        {
            return stream;
        }


        int Packetinterface.getType()
        {
            return type;
        }
    };
    //E_C_REQ_MOVE = 112,

    public class PK_C_REQ_MOVE : Packet, Packetinterface
    {
        public int userNumber;
        public float steering;
        public float accel;
        public float footbrake;
        public float handbrake;

        public PK_C_REQ_MOVE()
        {
            type = (int)PacketType.E_C_REQ_MOVE;
        }

        void Packetinterface.encode()
        {
            PacketUtil.encodeHeader(stream, type);
            PacketUtil.encode(stream, userNumber);
            PacketUtil.encode(stream, steering);
            PacketUtil.encode(stream, accel);
            PacketUtil.encode(stream, footbrake);

            PacketUtil.encode(stream, handbrake);
        }
        void Packetinterface.decode(byte[] packet, ref int offset)
        {
            userNumber = PacketUtil.decodeInt32(packet, ref offset);
            steering = PacketUtil.decodefloat(packet, ref offset);
            accel = PacketUtil.decodefloat(packet, ref offset);
            footbrake = PacketUtil.decodefloat(packet, ref offset);
            handbrake = PacketUtil.decodefloat(packet, ref offset);


        }


        MemoryStream Packetinterface.getStream()
        {
            return stream;
        }


        int Packetinterface.getType()
        {
            return type;
        }
    };
    //E_S_ANS_MOVE = 113,


    public class PK_S_ANS_MOVE : Packet, Packetinterface
    {

        public int userNumber;
        public float steering;
        public float accel;
        public float footbrake;
        public float handbrake;

        public PK_S_ANS_MOVE()
        {
            type = (int)PacketType.E_S_ANS_MOVE;
        }
            
        void Packetinterface.encode()
        {
            PacketUtil.encodeHeader(stream, type);
            PacketUtil.encode(stream, userNumber);
            PacketUtil.encode(stream, steering);
            PacketUtil.encode(stream, accel);
            PacketUtil.encode(stream, footbrake);

            PacketUtil.encode(stream, handbrake);
        }
        void Packetinterface.decode(byte[] packet, ref int offset)
        {
            userNumber = PacketUtil.decodeInt32(packet, ref offset);
            steering = PacketUtil.decodefloat(packet, ref offset);
            accel = PacketUtil.decodefloat(packet, ref offset);
            footbrake = PacketUtil.decodefloat(packet, ref offset);
            handbrake = PacketUtil.decodefloat(packet, ref offset);


        }
        MemoryStream Packetinterface.getStream()
        {
            return stream;
        }


        int Packetinterface.getType()
        {
            return type;
        }
    };

   

    public class PK_S_NOTIFY_USER_DATA : Packet, Packetinterface
    {

        public int userNumber;
        public float pos_X;
        public float pos_Y;

        public PK_S_NOTIFY_USER_DATA()
        {
            type = (int)PacketType.E_S_NOTIFY_USER_DATA;
        }

        void Packetinterface.encode()
        {
            PacketUtil.encodeHeader(stream, type);
            PacketUtil.encode(stream, userNumber);
            PacketUtil.encode(stream, pos_X);
            PacketUtil.encode(stream, pos_Y);
        }

        void Packetinterface.decode(byte[] packet, ref int offset)
        {
            userNumber = PacketUtil.decodeInt32(packet, ref offset);
            pos_X = PacketUtil.decodefloat(packet, ref offset);
            pos_Y = PacketUtil.decodefloat(packet, ref offset);

        }
        MemoryStream Packetinterface.getStream()
        {
            return stream;
        }


        int Packetinterface.getType()
        {
            return type;
        }
    }


 
}
