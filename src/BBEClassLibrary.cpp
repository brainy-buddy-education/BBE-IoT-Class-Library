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

#include "BBEClassLibrary.h"

/****************** Ultra Sonic Sensor Class *******************/

UltraSonicSensor::UltraSonicSensor(int TrigrPin, int EchoPin) {
    _echoPin = EchoPin;
    _trigPin = TrigrPin;
    pinMode(_trigPin, OUTPUT); //for UNO, trigger pin is an output
    pinMode(_echoPin, INPUT); //for UNO, trigger pin is an input
    _avgDistance = _distance = 999.0;
	_delay_inbetween = DEFAULT_DELAY;
}

bool UltraSonicSensor::MeasureDistance(float *pDist)
{
	bool success;
    float d = 0.0;
    _duration = 0;
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(12);
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    _duration = pulseIn(_echoPin, HIGH, PULSE_TIMEOUT);
	d = ((float)_duration * 100.0) / 5882.0;
    delay(10);
	if(d<3.0 || d>70.0)success = false;
	else
	{
		*pDist = d;
		success = true;
	}
    return success;
}

float UltraSonicSensor::AvgDistance(int count)
{
	int ii, jj;
	float min, max, avg, d;
	min = 999.0;
	max = 0.0;
	avg = d = 0.0;

	if (count < 3)count = 3;

	ii = 0;
	jj = 0;
	while(ii < count + 2 && jj <20)
	{
		if(MeasureDistance(&d))
		{
			if (d < min)min = d;
			if (d > max)max = d;
			avg += d;
			ii++;
		}
		delay(_delay_inbetween);// delay for <wait> ms
		jj++;
	}

	avg -= (max + min);
	avg /= count;
	if(ii < count + 2) return 999.0;
	else return avg;
}

float UltraSonicSensor::ReadDistanceOnce()
{
	if(MeasureDistance(&_distance))
	{
		return _distance;
	}
	else
	{
		return 0;
	}
}

/****************** Motor Fan Class *******************/

MotorFan::MotorFan(int Pin_in1, int Pin_in2, int Pin_pwm) {

	_Pin_Motor_PWM = Pin_pwm;
    _Pin_IN1 = Pin_in1;
    _Pin_IN2 = Pin_in2;
	pinMode(_Pin_Motor_PWM,OUTPUT);
	pinMode(_Pin_IN1,OUTPUT);
	pinMode(_Pin_IN2,OUTPUT);
	_MotorCommand = LOW;
	digitalWrite(_Pin_Motor_PWM,_MotorCommand);
	_MotorDirection = 1;
	digitalWrite(_Pin_IN1,LOW);
	digitalWrite(_Pin_IN2,HIGH);

}

void MotorFan::TurnOff()
{
  _MotorCommand = LOW;
  digitalWrite(_Pin_Motor_PWM,_MotorCommand);
}

void MotorFan::RunClockWise()
{
  _MotorCommand = HIGH;
  digitalWrite(_Pin_Motor_PWM,_MotorCommand);
  _MotorDirection = 1;
  digitalWrite(_Pin_IN1,LOW);
  digitalWrite(_Pin_IN2,HIGH);
}

void MotorFan::RunCounterClockWise()
{
  _MotorCommand = HIGH;
  digitalWrite(_Pin_Motor_PWM,_MotorCommand);
  _MotorDirection = -1;
  digitalWrite(_Pin_IN1,HIGH);
  digitalWrite(_Pin_IN2,LOW);
}

/****************** RaspCar Class *******************/
RaspCar::RaspCar(int IN1, int IN2, int IN3,  int IN4,  int ENA,  int ENB,  int MotorSpeed)
{
	_IN1 = IN1;
	_IN2 = IN2;
	_IN3 = IN3;
	_IN4 = IN4;
	_ENA = ENA;
	_ENB = ENB;
	_MotorSppeed = MotorSpeed;

	pinMode(_IN1,OUTPUT);
	pinMode(_IN2,OUTPUT);
	pinMode(_IN3,OUTPUT);
	pinMode(_IN4,OUTPUT);
	pinMode(_ENA,OUTPUT);
	pinMode(_ENB,OUTPUT);
	digitalWrite(_IN1,LOW);
	digitalWrite(_IN2,LOW);
	digitalWrite(_IN3,LOW);
	digitalWrite(_IN4,LOW);
	analogWrite(_ENA,_MotorSppeed);//left motor speed:0-255
	analogWrite(_ENB,_MotorSppeed);//right motor speed:0-255
}

void RaspCar::Forward(int Sec)
{
  digitalWrite(_IN1,HIGH);
  digitalWrite(_IN2,LOW);         // left wheel goes forward
  digitalWrite(_IN3,HIGH);      
  digitalWrite(_IN4,LOW);         // right wheel goes forward
  delay(1000*Sec);
  digitalWrite(_IN1,LOW);
  digitalWrite(_IN2,LOW);
  digitalWrite(_IN3,LOW);
  digitalWrite(_IN4,LOW);
  return;
}

void RaspCar::Backward(int Sec)
{
  digitalWrite(_IN1,LOW);
  digitalWrite(_IN2,HIGH);        //left wheel is back up
  digitalWrite(_IN3,LOW);      
  digitalWrite(_IN4,HIGH);        // right wheel is back up
  delay(1000*Sec);
  digitalWrite(_IN1,LOW);
  digitalWrite(_IN2,LOW);
  digitalWrite(_IN3,LOW);
  digitalWrite(_IN4,LOW);
  return;
}

void RaspCar::TurnLeft(int Sec)
{
  digitalWrite(_IN1,HIGH);
  digitalWrite(_IN2,LOW);         // left wheel goes forward
  digitalWrite(_IN3,LOW);      
  digitalWrite(_IN4,HIGH);         // right wheel goes forward
  delay(1000*Sec);
  digitalWrite(_IN1,LOW);
  digitalWrite(_IN2,LOW);
  digitalWrite(_IN3,LOW);
  digitalWrite(_IN4,LOW);
  return;
}

void RaspCar::TurnRight(int Sec)
{
  digitalWrite(_IN1,LOW);
  digitalWrite(_IN2,HIGH);         // left wheel goes forward
  digitalWrite(_IN3,HIGH);      
  digitalWrite(_IN4,LOW);         // right wheel goes forward
  delay(1000*Sec);
  digitalWrite(_IN1,LOW);
  digitalWrite(_IN2,LOW);
  digitalWrite(_IN3,LOW);
  digitalWrite(_IN4,LOW);
  return;
}


/*********** Serial Port Class ***********************************/
USBPort::USBPort(int baudrate)
{
	_baudRate = baudrate;
}

void USBPort::Initialize()
{
	Serial.begin(_baudRate);
	delay(500);
}

boolean USBPort::Read()
{
	boolean newcontents = false;
	if (Serial.available())
	{
		_string = "";
		newcontents = true;
	}
	while (Serial.available() > 0)
	{
		_inChar = Serial.read(); // Read a character
		_string += _inChar; // Add it
	}
	_string.toCharArray(_commandBuf, BUFFSIZE);
	if (newcontents)
	{
		_nameBuf[0] = _commandBuf[0];
		_nameBuf[1] = _commandBuf[1];
		_nameBuf[2] = 0;
		CommandID = _nameBuf;
		_string = _commandBuf + 2;
		CommandValue = _string.toInt();
	}
	return newcontents;

}