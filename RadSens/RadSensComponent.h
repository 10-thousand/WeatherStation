#include "esphome.h"

#include "CG_RadSens.h"

#ifdef RS_DEFAULT_I2C_ADDRESS 
#undef RS_DEFAULT_I2C_ADDRESS
#define RS_DEFAULT_I2C_ADDRESS 0x66
#endif 

using namespace esphome;


class RadSensComponent: public Component  {
  public: 
  Sensor * IntensityDynamic_Sensor = new Sensor();
  Sensor * IntensityStatic_Sensor = new Sensor();

  uint32_t timer_cnt; 
  CG_RadSens libRadSens {
    RS_DEFAULT_I2C_ADDRESS
  };
  
  RadSensComponent(): Component () {}

  void setup() override {
    timer_cnt = 0;
    libRadSens.init();
    libRadSens.setLedState(true);
    libRadSens.setSensitivity(105);
  }

  void loop() override {
      if (millis() - timer_cnt > 120000) { 
        timer_cnt = millis();
        float IntensityDynamic = libRadSens.getRadIntensyDynamic();
        float IntensityStatic = libRadSens.getRadIntensyStatic();

        if (IntensityDynamic != 0) {
          IntensityDynamic_Sensor -> publish_state(IntensityDynamic);
        }
        if (IntensityStatic != 0) {
          IntensityStatic_Sensor -> publish_state(IntensityStatic);
        }
     }
  }
};
