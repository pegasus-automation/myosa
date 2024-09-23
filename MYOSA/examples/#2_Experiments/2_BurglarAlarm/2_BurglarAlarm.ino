/*
  This code is developed under the MYOSA (LearnTheEasyWay) initiative of MakeSense EduTech and Pegasus Automation.
  Code has been derived from internet sources and component datasheets.
  Existing readily-available libraries would have been used "AS IS" and modified for ease of learning purpose.
  
  Burglar Alarm
  Connection: Connect "Light, Proximity, and Gesture" and "Actuator" boards from the MYOSA kit with the "Controller" board and power them up inside your locker along with your valuables.
  Working: Now in normal scenario, locker lights will be OFF and there will be complete dark but in case of unwanted theft, there would be light in the locker and hence on the module too. Controller will detect the light from the Light sensor and will turn the Buzzer On alerting the user of unwanted theft.

  Synopsis of MYOSA platform
  MYOSA Platform consists of a centralized motherboard a.k.a Controller board, 5 different sensor modules, an OLED display and an actuator board in the kit.
  Controller board is designed on ESP32 module. It is a low-power system on a chip microcontrollers with integrated Wi-Fi and Bluetooth.
  5 Sensors are as below,
  1 --> Accelerometer and Gyroscope (6-axis motion sensor)
  2 --> Temperature and Humidity Sensor
  3 --> Barometric Pressure Sensor
  4 --> Light, Proximity and Gesture Sensor
  5 --> Air Quality Sensor
  Actuator board contains a Buzzer and an AC switching circuit to turn on/off an electrical appliance.
  There is also an OLED display in the MYOSA kit.

  You can design N number of such utility examples as a part of your learning from this kit.
  
  Detailed Information about MYOSA platform and usage is provided in the link below.
  Detailed Guide: https://drive.google.com/file/d/1On6kzIq3ejcu9aMGr2ZB690NnFrXG2yO/view

  NOTE
  All information, including URL references, is subject to change without prior notice.
  Please always use the latest versions of software-release for best performance.
  Unless required by applicable law or agreed to in writing, this software is distributed on an 
  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied

  Modifications
  1 December, 2021 by Pegasus Automation
  (as a part of MYOSA Initiative)
  
  Contact Team MakeSense EduTech for any kind of feedback/issues pertaining to performance or any update request.
  Email: dev.myosa@gmail.com
*/

/* Library Inclusion */
#include <LightProximityAndGesture.h>
#include <Actuator.h>

/* Creating Object of LightProximityAndGesture and Actuator class */
Actuator gpioExpander;
LightProximityAndGesture Lpg;
uint16_t *rgbProportion;

/* Setup Function */
void setup() {

  /* Setting up communication */
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(100000);

  /* Initializing Actuator Board */
  for(;;)
  {
    if(gpioExpander.ping())
    {
      Serial.println("4bit IO Expander Actautor (PCA9536) is connected");
      break;
    }
    Serial.println("4bit IO Expander Actuator (PCA9536) is disconnected");
    delay(500u);
  }
  
  /* Set buzzer IO as output */
  gpioExpander.setMode(BUZZER_IO, IO_OUTPUT);
  gpioExpander.setState(BUZZER_IO, IO_LOW);
  delay(3000);
  
  /* Initializing Light, Proximity, Gesture Sensor */
  for(;;)
  {
    if(Lpg.begin())
    {
      Serial.println("Proximity, Ambient Light, RGB & Gesture sensor is connected...");
      break;
    }
    Serial.println("Proximity, Ambient Light, RGB & Gesture sensor is disconnected...");
    delay(500u);
  }
  Serial.println("APDS9960 initialization completed");

  /* Start running the APDS9960 Ambient light sensor (no interrupts) */
  if( Lpg.enableAmbientLightSensor(DISABLE) )
  {
    Serial.println("Light sensor is now running");
  }
  else
  {
    Serial.println("Something went wrong during light sensor init!");
  }

  /* Wait for initialization and calibration to finish */
  delay(500u);
}

/* Loop Function */
void loop() {

  /* Loop Function constantly checks the Ambient Light levels and if that rises up (meaning there is a light source in the locker), Buzzer will Turn On */
  if(Lpg.ping())
  {
    /* Read the light levels (ambient, red, green, blue) */
    int ambLight = Lpg.getAmbientLight();
    if(ambLight>10)
    {
      gpioExpander.setState(BUZZER_IO, IO_HIGH);
      Serial.println("Alert! Alert! Alert! Burglar Detected...");
    }
    else
    {
      gpioExpander.setState(BUZZER_IO, IO_LOW);
    }
  }
  delay(150u);
}