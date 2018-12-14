using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace DummyClient
{

    enum PacketType
    {
        E_C_REQ_EXIT = 90,
        E_S_ANS_EXIT = 91,
        PACKET_TYPE_ERROR = 99,
       
       
        E_C_REQ_CONNECT = 105,
        E_S_ANS_CONNECT = 106,
       
        E_S_NOTIFY_OTHER_CLIENT = 109,
      
        E_C_REQ_MOVE = 112,
        E_S_ANS_MOVE = 113,


        E_S_NOTIFY_USER_DATA = 115,
     
    }
};
