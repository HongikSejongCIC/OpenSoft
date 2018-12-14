using System;
using UnityEngine;
using UnityStandardAssets.CrossPlatformInput;
using DummyClient;

namespace UnityStandardAssets.Vehicles.Car
{
    [RequireComponent(typeof (CarController))]
    public class CarUserControl : MonoBehaviour
    {
        private CarController m_Car; // the car controller we want to use

        float beforeSteering;
        float beforeAccel;
        float beforeFootbrake;
        float beforeHandbrake;
        private void Awake()
        {
            // get the car controller
            m_Car = GetComponent<CarController>();
        }
        

        private void Start()
        {
            beforeSteering = 0.0f; ;
            beforeAccel = 0.0f;
            beforeFootbrake = 0.0f;
            beforeHandbrake = 0.0f;
        }

        int count = 0;

        private void FixedUpdate()
        {
            // pass the input to the car!
            float h = CrossPlatformInputManager.GetAxis("Horizontal");
            float v = CrossPlatformInputManager.GetAxis("Vertical");
#if !MOBILE_INPUT
            float handbrake = CrossPlatformInputManager.GetAxis("Jump");
            m_Car.Move(h, v, v, handbrake);

            //Debug.Log("InputKey h:" + h + " v:" + v + " hb:" + handbrake);

            //if (beforeSteering != h || beforeAccel != v || beforeFootbrake != v || beforeHandbrake != handbrake)
            //{

            if ((v == 0 && beforeAccel != 0.0f))
            {
                beforeSteering = h;
                beforeAccel = v;
                beforeFootbrake = v;
                beforeHandbrake = handbrake;

                PK_C_REQ_MOVE packet = new PK_C_REQ_MOVE();
                packet.userNumber = GameManager.getInstance.userCar;
                packet.steering = h;
                packet.accel = v;
                packet.footbrake = v;
                packet.handbrake = handbrake;

                //Debug.Log("count : " + count.ToString() + "userNumber : " + packet.userNumber.ToString() + "sterring : " + packet.steering.ToString() + " accel : " + packet.accel.ToString());


                GameNetWork.getInstance.sendPacket(packet);

            }


            if (h != 0.0f || v != 0.0f || handbrake != 0.0f)
                {
                beforeSteering = h;
                beforeAccel = v;
                beforeFootbrake = v;
                beforeHandbrake = handbrake;

                PK_C_REQ_MOVE packet = new PK_C_REQ_MOVE();
                packet.userNumber = GameManager.getInstance.userCar;
                packet.steering = h;
                packet.accel = v;
                packet.footbrake = v;
                packet.handbrake = handbrake;

                //Debug.Log("count : " + count.ToString() + "userNumber : " + packet.userNumber.ToString() + "sterring : " + packet.steering.ToString() + " accel : " + packet.accel.ToString());


                GameNetWork.getInstance.sendPacket(packet);

                 }
#else
            m_Car.Move(h, v, v, 0f);
#endif
        }
    }
}
