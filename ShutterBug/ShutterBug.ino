  /****************************************************************************************************
  ****************************************************************************************************

  ooooo ooooo ooooo  ooooooo8 ooooo ooooo      ooooooo  oooooooooo  ooooooooo  ooooooooooo oooooooooo  
  888   888   888 o888    88  888   888     o888   888o 888    888  888    88o 888    88   888    888 
  888ooo888   888 888    oooo 888ooo888     888     888 888oooo88   888    888 888ooo8     888oooo88  
  888   888   888 888o    88  888   888     888o   o888 888  88o    888    888 888    oo   888  88o   
  o888o o888o o888o 888ooo888 o888o o888o      88ooo88  o888o  88o8 o888ooo88  o888ooo8888 o888o  88o8 

  ****************************************************************************************************
  ***************************************************************************************************/

  #define POST_DELAY 500
  #define SHUTTER_DELAY 250

  /***************************************************************************************************
  ***************************************************************************************************/

  #define INPUT_PIN D17
  #define OUTPUT_PIN D14
  #define POT_PIN A2

  #include <Bounce2.h>
  Bounce2::Button button = Bounce2::Button();

  void setup() {
    Serial.begin(115200);

    // Configure input button.
    {
      button.attach(INPUT_PIN, INPUT_PULLUP);
      button.interval(5);
      button.setPressedState(LOW);
    }

    // Inputs float by default.
    pinMode(OUTPUT_PIN, OUTPUT);
    digitalWrite(OUTPUT_PIN, HIGH);
    

    // LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
  }

  void loop() {
    int potValue = analogRead(POT_PIN);
    button.update();

    if (button.pressed()) {

      Serial.println("Taking photo!");

      int preDelay = potValue;

      Serial.print("Waiting for PRE_DELAY: ");
      Serial.println(preDelay);

      digitalWrite(LED_BUILTIN, HIGH);
      delay(preDelay);
      digitalWrite(LED_BUILTIN, LOW);

      // Press and hold shutter for 10ms.
      {
        digitalWrite(OUTPUT_PIN, LOW);

        Serial.print("Waiting for SHUTTER_DELAY: ");
        Serial.println(SHUTTER_DELAY);

        delay(SHUTTER_DELAY);

        digitalWrite(OUTPUT_PIN, HIGH);
      }

      Serial.print("Waiting for POST_DELAY: ");
      Serial.println(POST_DELAY);

      // digitalWrite(LED_BUILTIN, HIGH);
      delay(POST_DELAY);
      // digitalWrite(LED_BUILTIN, LOW);

      Serial.println("Photo taken!");
    }
  }
