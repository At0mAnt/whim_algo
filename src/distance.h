#ifndef distance
#define distance

/*Pin Defines*/
#define sensorFrontLeftEcho 23
#define sensorFrontLeftTrig 22
#define sensorFrontRightEcho 33
#define sensorFrontRightTrig 25

#define sensorSideLeftEcho 26
#define sensorSideLeftTrig 27
#define sensorSideRightEcho 14
#define sensorSideRightTrig 12

#define sensorBackEcho 19
#define sensorBackTrig 18

#define CRICITAL_DISTANCE 10

void initDistance();
int getDistance(int distanceSensorTrig, int distanceSensorEcho);

#endif