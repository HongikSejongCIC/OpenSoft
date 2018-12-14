using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;

namespace DummyClient
{

    public class GameNetWork : MonoBehaviour
    {
        static protected GameNetWork gameNetWork;
        static public GameNetWork getInstance { get { return gameNetWork; } }

        public Network network;

        public string name_;


        //public GameContentsProcess gameContentsProcess;
        private void Awake()
        {
            gameNetWork = this;
            network = new Network();
        }


        string gameServerIp = "52.79.226.149";
        int gameServerPort = 9200;


        private void Start()
        {
            // gameContentsProcess = new GameContentsProcess();

            Open(gameServerIp, gameServerPort);

            DontDestroyOnLoad(this);
     
        }



        public void sendPacket(Packetinterface packet)
        {
            network.sendPacket(packet);
        }

        private void OnDestroy()
        {
            disconnect();
        }
        
        public bool ConnectToServer(string ip, int port)
        {
            return network.Connect(ip, port);
        }
        
        public void Open(string ip, int port)
        {
            if (!ConnectToServer(ip, port))
            {
                Debug.Log("Game Server Connect Failed");
            }
            network.receiveStart();
            // network.ReceiveStart();
            // gameContentsProcess.JobStart();

            //StartCoroutine(Recv());

            PK_C_REQ_CONNECT packet = new PK_C_REQ_CONNECT();
            gameNetWork.sendPacket(packet);

        }

        public NET_STATE GetState()
        {
            return network.State();
        }

        public void disconnect()
        {
            PK_C_REQ_EXIT exitPacket = new PK_C_REQ_EXIT();

            network.sendPacket(exitPacket);

            network.close();
        }

     
        IEnumerator Recv()
        {
            while (true)
            {
               // network.receive();
                yield return null;
            }
        }



    }
}
