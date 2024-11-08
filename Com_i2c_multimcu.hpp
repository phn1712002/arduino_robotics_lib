#include <Wire.h>
#include <Arduino.h>

/////////////////////////////////////
#define SPEED_STANDARD_MODE_I2C 100000
#define SPEED_FAST_MODE_I2C 400000 
#define TIME_OUT_I2C_DEF 25000U
/////////////////////////////////////

/////////////////////////////////////
template <typename T> unsigned int I2C_writeAnything (const T& value)
{
  Wire.write((byte *) &value, sizeof (value));
  return sizeof (value);
}  // end of I2C_writeAnything

template <typename T> unsigned int I2C_readAnything(T& value)
{
  byte * p = (byte*) &value;
  unsigned int i;
  for (i = 0; i < sizeof value; i++)
        *p++ = Wire.read();
  return i;
}  // end of I2C_readAnything
/////////////////////////////////////


/////////////////////////////////////
/*
Function default of communicate i2c multi MCU
*/
void function_none_sla(int Howmany)
{
  /*
  If board sub use send msg to board main then function will use in onReceive
  Else board sub use read msg from board main then function will overwrite
  */
}

void function_check_board_sla()
{
  /*
  Function default of communicate i2c multi MCU
  */
  bool check = true;
  I2C_writeAnything(check);
}
/////////////////////////////////////


/////////////////////////////////////
/*
Device_I2C use in board main
*/
class Device_I2C
{
  public: 
    Device_I2C(int);
    template <typename T> unsigned int write(const T&);
    template <typename T> byte read(T&);
    bool check_board();

  private:
    int __id_i2c;

};

Device_I2C::Device_I2C(int id)
{
  this->__id_i2c = id;
};

bool Device_I2C::check_board()
{
  bool check = false;
  this->read(check);
  return check;
}

template <typename T> unsigned int Device_I2C::write(const T& value)
{
   Wire.beginTransmission(this->__id_i2c);
   unsigned int status = I2C_writeAnything(value);
   Wire.endTransmission();
   return status;
};

template <typename T> byte Device_I2C::read(T& value)
{
  byte status = Wire.requestFrom(this->__id_i2c, sizeof(value));
  if (status != 0 && status == sizeof(value)) I2C_readAnything(value);
  else status = 0;
  return status;
};
/////////////////////////////////////


/////////////////////////////////////
/*
COM_I2C use in board main or board sub to begin I2C.
*/
class COM_I2C
{
  public:
    COM_I2C();
    void begin(int, uint32_t, uint32_t, bool);
    void set_function(void (*function_Ser)(void), void (*function_Sla)(int));
  private:
    int __id_i2c; 
};

COM_I2C::COM_I2C()
{
  
}

void COM_I2C::begin(int id = 0, uint32_t clock = 100000, uint32_t timeout = 25000U, bool reset_with_timeout = true)
{
  /*
  Input:
    id - This is id of board in I2C, Attention: board main -> 0
    clock - Set speed of I2C
    timeout - Set timeout when error in I2C
    reset_with_timeout - Set reset when error I2C
  */
  if (id == 0) Wire.begin();
  else Wire.begin(id);
  Wire.setClock(clock);
  Wire.setWireTimeout(timeout, reset_with_timeout);

  this->__id_i2c = id;
};

void COM_I2C::set_function(void (*function_Ser)(void) = function_check_board_sla, void (*function_Sla)(int) = function_none_sla)
{
   /*
    Attention:
    Sub -> Main : Input(function_Ser = function_overwrite, function_Sla = function_none_sla)

    Main -> Sub: Input(function_Ser = function_check_board_sla, function_Sla = function_overwrite)
  */
  Wire.onRequest(function_Ser);
  Wire.onReceive(function_Sla);
};
/////////////////////////////////////