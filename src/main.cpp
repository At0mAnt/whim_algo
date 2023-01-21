#include "main.h"

/*
Tasks:
*/

int distance_front_left, distance_front_right, distance_side_left, distance_side_right, distance_back, front_sensors;

int rand_no = 0;
int sensor_checker_status;
int counter = 0;

int i=0; //counter
int p=0; //counter 2

// // Setting PWM properties
// const int freq = 30000;
// const int pwmChannel = 0;
// const int resolution = 8;
// int dutyCycle = 100;

int sensor_checker(int wait_time);
void getSensorDistances();
void obsctacleAvoidance();

void setup() {
  Serial.begin(9600);


  /*Inits*/
  Serial.println("INITS");
  initMotors();
  Serial.println("Motors are initialised.");
  initDistance();
  Serial.println("Sensors are initialised.");
  //randomSeed(analogRead(36));
  Serial.println("Random is initialised.");
  
  // // configure LED PWM functionalitites 
  // ledcSetup(pwmChannel, freq, resolution);

  // // attach the channel to the GPIO to be controlled
  // ledcAttachPin(motorLeftPWM, pwmChannel);
  //  // attach the channel to the GPIO to be controlled
  // ledcAttachPin(motorRightPWM, pwmChannel);
  

  #if _DEBUGMODE
    moveMotors(GO_FORWARD);
    delay(1000);
    moveMotors(GO_BACKWARD);
    delay(1000);
    moveMotors(STOP_ALL);
  #endif

  randomSeed(analogRead(36));
}
 
void loop() 
{

  getSensorDistances();
  rand_no=random(0, 100);

  // //change duty cycle 
  // ledcWrite(pwmChannel, dutyCycle);


  //TODO - if back,side,front sensors trigger at the same instance stop 
  
  Serial.println("OB_Avoidance");
  obsctacleAvoidance();
  
  Serial.println("Entered i<1");
  //random spins
  if ((distance_front_right && distance_front_left && distance_side_right && distance_side_left >=60 ) && i<1)
  {
  getSensorDistances();
   rand_no=random(0, 100);

    if (rand_no <=24 ){
    Serial.println(" LEFT FOR i<=1");
    moveMotors(TURN_LEFT);
    delay(2400);
    }else if(rand_no >= 25 && rand_no <= 49){
    moveMotors(TURN_RIGHT);
    delay(2400);
    }else if (rand_no >=50){
      i++;
    }
  }

  i++;
  Serial.println("ADDED i++");
  if (i >= 4){
    Serial.println("i is reset to 0");
    i =0;
  }
  motorMovement(STOP_ALL);
  delay(240);

//------------------------------------------------------------------------------------------------
//  //if inbetween these 51-81cm then move backward
//   else if(distance_front_right >=51 || distance_front_left >= 51 && p<4)
//     {
//       for (p; p>5; p++)
//         {
//           moveMotors(GO_BACKWARD);
//           delay(100);
//         }
   
//     p++;

//     Serial.print("p= ");
//     Serial.println(p);
//     }
    
//   getSensorDistances();
//   
//       delay(140);
//       }
//       //TODO TURN_RIGHT
//       //only be able to turn if the condition that an obstacle is not in the way
//       if(distance_side_right >= 5if(p>=4)
//   {
//     Serial.println("Activated P");
//       getSensorDistances();
//       if((distance_front_right && distance_front_left )<= 90) //&& back is free
//       {
//       moveMotors(GO_BACKWARD);0)
//       {  
//       moveMotors(TURN_RIGHT);F.
//       delay(500);
//       }

//       else if(distance_side_right<= 49)
//       {
//         moveMotors(STOP_ALL);
//         delay(200);
//       }
//       p = 0;
//   }
  
//   while (distance_front_right >=30 && distance_front_right  <=50 ) 
//   {
//     getSensorDistances();
//     //TODO TURN_RIGHT
//     //only be able to turn if the condition that an obstacle is not in the way
//     moveMotors(TURN_LEFT);
//     delay(200);
//   }

//    while (distance_front_left >=30 && distance_front_left<=50) 
//   {
//     getSensorDistances();
//     //TODO TURN_RIGHT
//     //only be able to turn if the condition that an obstacle is not in the way  
//     moveMotors(TURN_RIGHT);
//     delay(200);
//   }

// // limit condition for when it gets stuck on the wall
//    if ((distance_front_left<=30 && i<4 )|| (distance_front_right<=30 && i<4)) 
//   {
//     Serial.println("Special Condition ACTIVATED");
//     for(i ; i>5; i++){
//     getSensorDistances();
//     moveMotors(GO_BACKWARD);
//     delay(200);
//     }
    
//     i++;
//     Serial.print("i= ");
//     Serial.println(i);
   
//     //TODO 
//     //the second 
//   }

//    if (i>=4 /*&& back is clear by 200cm+*/)
//     {
//       moveMotors(GO_BACKWARD);
//       delay(2200);
//       //TODO TURN_RIGHT
//       //only be able to turn if the condition that an obstacle is not in the way
//       moveMotors(TURN_LEFT);
//       delay(4000);
      
//       Serial.println("\n i= ");
//       Serial.print(i);
//       i=0;
//     }

}

void obsctacleAvoidance(){
  
  //TODO - if back,side,front sensors trigger at the same instance stop 

  //side_correction
  if (distance_side_right <= 70 )
  {
    moveMotors(TURN_LEFT);
    delay(240);
   // moveMotors(STOP_ALL);
  }
  else if(distance_side_left <= 70)
  {
    moveMotors(TURN_RIGHT);
    delay(240);
   // moveMotors(STOP_ALL);
  }

  //front correction
  if (distance_front_right >=81 && distance_front_left >= 81)
    { 
      moveMotors(GO_FORWARD);
      delay(240);
    //  moveMotors(STOP_ALL);
    }
    else{  //TODO- if back is free
      
      moveMotors(GO_BACKWARD);
      delay(240);
      // moveMotors(STOP_ALL);
      
      p++;
      Serial.print("p= ");
      Serial.println(p);
    }

    if( p >= 3) //&& back is free
      {
      moveMotors(GO_BACKWARD);
      delay(500);
      
      if(distance_side_right >= 60)
      {
      moveMotors(TURN_RIGHT);
      delay(500);
      }else if(distance_side_left >=60){
      moveMotors(TURN_LEFT);
      delay(500);
      }

      p = 0;
      }
}

void getSensorDistances() {
  distance_front_right = getDistance(sensorFrontRightTrig, sensorFrontRightEcho);
  distance_front_left = getDistance(sensorFrontLeftTrig, sensorFrontLeftEcho);
  distance_side_right = getDistance(sensorSideRightTrig, sensorSideRightEcho);
  distance_side_left = getDistance(sensorSideLeftTrig, sensorSideLeftEcho);

  //distance_back = getDistance(sensorBackTrig, sensorBackEcho); 

  #if _DEBUGMODE
    Serial.print("cm front right: ");
    Serial.print(distance_front_right);
    Serial.print("|   cm front left: ");
    Serial.print(distance_front_left);
    Serial.print("|   cm side right: ");
    Serial.print(distance_side_right);
    Serial.print("|   cm side left: ");
    Serial.print(distance_side_left);
    Serial.print("|   cm back: ");
    Serial.println(distance_back);
  
  #endif

}