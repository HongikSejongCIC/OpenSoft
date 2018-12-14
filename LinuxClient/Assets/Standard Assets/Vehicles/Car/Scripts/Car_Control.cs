using System;
using UnityEngine;
using UnityStandardAssets.CrossPlatformInput;
using DummyClient;

namespace UnityStandardAssets.Vehicles.Car
{
    [RequireComponent(typeof(CarController))]
    public class Car_Control : MonoBehaviour
    {
        private CarController m_Car; // the car controller we want to use

        float beforeSteering;
        float beforeAccel;
        float beforeFootbrake;
        float beforeHandbrake;


        public float h;
        public float v;
        public float handbreake;

        private void Awake()
        {
            // get the car controller
            m_Car = GetComponent<CarController>();
        }


        private void Start()
        {
            h = 0;
            v = 0;
            handbreake = 0;
        }

        private void FixedUpdate()
        {
            // pass the input to the car!
            m_Car.Move(h, v, v, handbreake);

        }
    }

}