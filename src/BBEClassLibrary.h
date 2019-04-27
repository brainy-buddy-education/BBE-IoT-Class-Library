/*****************************
 * Brainy Buddy Education, LLC, CONFIDENTIAL
 *  [2019] Brainy Buddy Education, LLC
 *  All Rights Reserved.
 * 
 * NOTICE:  All information contained herein is, and remains
 * the property of Brainy Buddy Education, LLC,.
 * The intellectual and technical concepts contained
 * herein are proprietary to Brainy Buddy Education, LLC
 * and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Brainy Buddy Education, LLC.  
******************************/

#ifndef BBE_CLASS_LIBRARY_H
#define BBE_CLASS_LIBRARY_H

#include "Arduino.h"
#include <inttypes.h>

#define PULSE_TIMEOUT 150000L	// 100ms
#define DEFAULT_DELAY 10
#define DEFAULT_PINGS 5
#define BUFFSIZE 20

class UltraSonicSensor
{
public:
	
	/**
	* Constructor
	* Ultrasonic sensor SR04, four connections pins: 	1-VCC, 2-ECHO, 3-TRIGGER, 4-GND
	* \param TrigPin if 10us high a trigger signal is generated from SR04
	* \param EchoPin digital INPUT-Pin for measuring distance
	*
	* \return void
	*/
	UltraSonicSensor(int TrigPin, int EchoPin);


	/**
	* Do count measurents and calculate the average. 
	* To avoid defilement from ow/high peaks, min/max values
	* are substracted from the average
	*
	* \param wait delay between measurements, default = DEFAULT_DELAY/ms
	* \param count number of measurements, default DEFAULT_PINGS
	* \return long distance in centimeter
	**/
	float AvgDistance(int count=DEFAULT_PINGS);

	/**
	* read distance for once and update the private member variable.
	* \return Distance in centi meter
	*/
	float ReadDistanceOnce();


private:
	/**
	* Do the measurement calculation and return result in centimeter
	* SR04 measure echo time to obstacle and return way. 
	* Sound travels with 340m/sec
	* Example: Obstace 100cm away from SR04. Measure time is 100cm to
	* obstacle and 100cm return = 200cm
	* 1sec = 1000ms = 1.000.000uS
	* 1.000.000 / 340 = Distance in microseconds for 100cm
	* 2941uS fuer 100cm = 5882 uS fuer 200cm
	*
	* duration / 5882 * 100 = distance in cm
	*/	

	/**
	* Do a measurment for this sensor. Return distance as long
	* in centimenter
	* \return long distance in centimeter
	*/
	bool MeasureDistance(float *pDist);

	int _echoPin, _trigPin;
	int _delay_inbetween;
	long _duration; //in ms
	float _distance, _avgDistance;

};

class MotorFan
{
public:
	
	/**
	* Constructor
	* MotorFan three connections pins to Arduino: 	1-Motor_PWM, 2-IN1, 3-motor+, 4-motor-, 5,6-GND, 7-IN2, 8-V++
	* \param Pin_in1
	* \param Pin_in2
	* \param Motor_PWM
	*
	* \return void
	*/
	MotorFan(int Pin_in1, int Pin_in2, int Pin_pwm);


	/**
	* remove the drive force to the fan. 
	**/
	void TurnOff();

	/**
	* rotate the fan clockwise. 
	**/
	void RunClockWise();

	/**
	* rotate the fan counter-clockwise. 
	**/
	void RunCounterClockWise();


private:

	int _Pin_IN1, _Pin_IN2, _Pin_Motor_PWM;
	int _MotorCommand;
	int _MotorDirection;

};


class RaspCar
{
public:
	
	/**
	* Constructor
	* RaspCar seven parameters int IN1, int IN2, int IN3,  int IN4,  int ENA,  int ENB,  int MotorSpeed
	*
	* \return void
	*/
	RaspCar(int IN1, int IN2, int IN3,  int IN4,  int ENA,  int ENB,  int MotorSpeed);

	/**
	* Car Movement Control functions
	*
	* \return void
	*/
	void Forward(int Sec);
	void Backward(int Sec);
	void TurnLeft(int Sec);
	void TurnRight(int Sec);


private:

	int _IN1, _IN2, _IN3, _IN4, _ENA, _ENB;
	int _MotorSppeed;
	
};

class USBPort
{
public:
	/**
	* Constructor
	* USBPort, 
	*
	* \return void
	*/
	USBPort(int baudrate);
	void Initialize();
	
	/**
	reading the serial port
	* return
	*/
	boolean Read();

	String CommandID = "";
	int CommandValue;

private:
	int _baudRate;
	String _string = "";
	char _commandBuf[BUFFSIZE];
	char _nameBuf[3];
	char _inChar = -1; // Where to store the character read
};


#endif



