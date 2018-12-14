using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DummyClient;
using System;

using UnityStandardAssets.Vehicles.Car;
public class GameManager : MonoBehaviour {
    static protected GameManager gameManager;
    static public GameManager getInstance { get { return gameManager; } }
    public GameObject MainUnit;
    public GameObject EnemyUnit;
    private GameObject mainCharacter;




    public GameObject[] UserList = new GameObject[2];

    public Int32 userCar;
    public Int32 enemyCar;
    



    //public UserList userList;
    // Use this for initialization



    public float BoundaryTop;
    public float BoundaryBottom;
    public float BoundaryLeft;
    public float BoundaryRight;



    public enum Direction
    {
        N,
        T,
        TR,
        R,
        RB,
        B,
        BL,
        L,
        LT,
    }


    private void Awake()
    {
        gameManager = this;
    }
    void Start () {
     
        DontDestroyOnLoad(this);

    }
	
	// Update is called once per frame
	void Update () {
		
	}
    
   
    public void DeleteCharacter(Int32 Number)
    {

     
        GameObject unit = UserList[(int)Number];

        Destroy(unit);
    }

    public void CreateEnemyCharacter()
    {
        Debug.Log("Create  Enemy Number : " + enemyCar.ToString());

   


        GameObject unit = Instantiate(EnemyUnit);
        UserList[(int)enemyCar] = unit;
       // unit.GetComponent<EnemyScript>().number = Number;

    }
    public void CreateMainCharacter()
    {
        Debug.Log("Create user Number : " + userCar.ToString());

        //  GameObject userList = GameObject.Find("UserList");
        GameObject unit = Instantiate(MainUnit);
        UserList[(int)userCar] = unit;
        
        print("instance");


      //  pointingCharacter.RegistCharacter(unit.transform);
    }
    
    public void MoveCharacter(float steering, float accel, float footbrake, float handbrake)
    {
        UserList[(int)enemyCar].GetComponent<CarController>().Move(steering, accel, footbrake, handbrake);

        Debug.Log("streeing : " + steering.ToString() + "accel : " + accel.ToString() + "footbrake : " + footbrake.ToString() + " handbrake : " + handbrake.ToString());
    }
    
    public void MoveEnemy(float steering, float accel, float footbrake, float handbrake)
    {
        UserList[(int)enemyCar].GetComponent<Car_Control>().h = steering;
        UserList[(int)enemyCar].GetComponent<Car_Control>().v = accel;
        UserList[(int)enemyCar].GetComponent<Car_Control>().handbreake = handbrake;

    }


    public void SetCharacterPostition(Int32 Number, float pos_X, float pos_Y)
    {


     
        if (UserList[Number] == null)
            return;

        UserList[Number].transform.position = new Vector3(pos_X, pos_Y, -10.0f);
       
        print("SetPostition");
    }
}
