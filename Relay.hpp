#include "Arduino.h"

class Relay
{
  public:
    Relay(uint8_t pin);
    void ON();
    void OFF();
    void on_off_timeout();
  private:
    uint8_t __pin;
};

Relay::Relay(uint8_t pin)
{
  pinMode(pin, OUTPUT);
  this->__pin = pin;  
}

void Relay::ON()
{
  digitalWrite(this->__pin, HIGH);
}

void Relay::OFF()
{
  digitalWrite(this->__pin, LOW);
}

void Relay::on_off_timeout(long timeout)
{
  digitalWrite(this->__pin, HIGH);
  delay(timeout);
  digitalWrite(this->__pin, LOW);
}