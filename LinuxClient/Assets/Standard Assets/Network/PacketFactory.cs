using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace DummyClient
{
    public static class PacketFactory
    {
        public static Packetinterface getPacket(int packetType) 
        {
            switch ((PacketType)packetType)
            {
                case PacketType.E_C_REQ_EXIT: return new PK_C_REQ_EXIT();
                case PacketType.E_S_ANS_EXIT: return new PK_S_ANS_EXIT();
              
                case PacketType.E_C_REQ_CONNECT: return new PK_C_REQ_CONNECT();
                case PacketType.E_S_ANS_CONNECT: return new PK_S_ANS_CONNECT();
             
                case PacketType.E_S_NOTIFY_OTHER_CLIENT: return new PK_S_NOTIFY_OTHER_CLIENT();
               
                case PacketType.E_C_REQ_MOVE: return new PK_C_REQ_MOVE();
                case PacketType.E_S_ANS_MOVE: return new PK_S_ANS_MOVE();
                case PacketType.E_S_NOTIFY_USER_DATA: return new PK_S_NOTIFY_USER_DATA();
             

            }
            return null;
        }
    }
}
