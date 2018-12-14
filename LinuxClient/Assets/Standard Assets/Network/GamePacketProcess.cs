using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace DummyClient
{


    public class GamePacketProcess
    {
        
        public  void S_ANS_EXIT(Packetinterface rowPacket)
        {
            PK_S_ANS_EXIT packet = (PK_S_ANS_EXIT)rowPacket;

            GameManager.getInstance.DeleteCharacter(packet.userNumber);
            
        }

        public void S_ANS_CONNECT(Packetinterface rowPacket)
        {
              PK_S_ANS_CONNECT packet = (PK_S_ANS_CONNECT)rowPacket;

            if (packet.userNumber == 0)
            {
                GameManager.getInstance.userCar = 0;
                GameManager.getInstance.enemyCar = 1;
            }
            else
            {
                GameManager.getInstance.userCar = 1;
                GameManager.getInstance.enemyCar = 0;

            }




            GameManager.getInstance.CreateMainCharacter();
            GameManager.getInstance.CreateEnemyCharacter();

        }

        public void S_NOTIFY_CLIENT_DATA(Packetinterface rowPacket)
        {
            PK_S_NOTIFY_OTHER_CLIENT packet = (PK_S_NOTIFY_OTHER_CLIENT)rowPacket;

            Debug.Log("Recive S_NOTIFY_OTHER_CLIENT EnemyNumber : " + packet.userNumber.ToString());
            
           
            GameManager.getInstance.SetCharacterPostition(packet.userNumber, packet.pos_X, packet.pos_Y);
        }

        public void S_NOTIFY_USER_DATA(Packetinterface rowPacket)
        {
            PK_S_NOTIFY_USER_DATA packet = (PK_S_NOTIFY_USER_DATA)rowPacket;
            Debug.Log("Recive S_NOTIFY_USER_DATA");
            packet.userNumber = GameManager.getInstance.userCar;

         

            GameManager.getInstance.SetCharacterPostition(packet.userNumber, packet.pos_X, packet.pos_Y);


        }
       

        public void S_ANS_MOVE(Packetinterface rowPacket)
        {

            PK_S_ANS_MOVE packet = (PK_S_ANS_MOVE)rowPacket;

            //GameManager.getInstance.MoveCharacter(packet.steering, packet.accel, packet.footbrake, packet.handbrake);

            GameManager.getInstance.MoveEnemy(packet.steering, packet.accel, packet.footbrake, packet.handbrake);
        }



    }
}
