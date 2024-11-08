#include <Arduino.h>

class PID
{
  public:
    PID(float, float, float);
    float compute(const float &);
    void begin();
    void end();
    void reset(float, float, float);
  private:
    float __Kp = 0, __Ki = 0, __Kd = 0;
    long __prevT  = 0;
    float __eintegral = 0;
    float __eprev = 0;
};

PID::PID(float Kp, float Kd, float Ki)
{
  this->__Kp = Kp;
  this->__Ki = Ki;
  this->__Kd = Kd;
}

float PID::compute(const float &e)
{
  // Delta T
  long currT = micros();
  float deltaT = ((float)(currT - this->__prevT)) / (1.0e6);
  this->__prevT = currT;

  // Dedt
  float dedt = (e - this->__eprev) / (deltaT);
  this->__eprev = e;

  // Intergral e
  this->__eintegral += e * deltaT;

  return this->__Kp * e + this->__Kd * dedt + this->__Ki * this->__eintegral;
}

void PID::begin()
{
  this->__prevT = micros();
  this->__eintegral = 0;
  this->__eprev = 0;
}

void PID::end()
{
  this->__eintegral = 0;
  this->__eprev = 0;
}

void PID::reset(float Kp, float Kd, float Ki)
{
  this->__prevT = micros();
  this->__eintegral = 0;
  this->__eprev = 0;
  this->__Kp = Kp;
  this->__Ki = Ki;
  this->__Kd = Kd;
}