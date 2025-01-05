// Stepper motor controller for Lego Sun/Moon/Earth model
// Tennessee Carmel-Veilleux, December 2024
//
// Needs AccelStepper library
// Board: Teensy LC
// Tutorial consulted: https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/
//
// Pinout:
// - STEPPERn pins are connected to SBT0811 ULN2003A-based driver board
//   with pinout for 28BYJ-48 5V
// 
// - STEPPER1: Pin 21 
// - STEPPER2: Pin 17
// - STEPPER3: Pin 16
// - STEPPER4: Pin 5
// 
// Pot has 3 pins all connected to GPIOs to reduce wiring:
// - Low side (GND): Pin 13
// - Wiper: Pin 14
// - High side (3.3V): Pin 15

#include <AccelStepper.h>

namespace {

constexpr int STEPPER1_PIN = 21;
constexpr int STEPPER2_PIN = 17;
constexpr int STEPPER3_PIN = 16;
constexpr int STEPPER4_PIN = 5;
constexpr int POT_GND_PIN = 13;
constexpr int POT_VREF_PIN = 15;
constexpr int POT_WIPER_PIN = 14;

constexpr int kMotorInterfaceType = 4; // 4-phase unipolar stepper.
constexpr unsigned long kAdcReadIntervalMillis = 100u;
constexpr long kMaxSpeedStepsPerSec = 300;

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper gStepper(kMotorInterfaceType, STEPPER1_PIN, STEPPER3_PIN, STEPPER2_PIN, STEPPER4_PIN);
unsigned long gLastAdcReadMillis = 0;

} // namespace

void setup() {
  // put your setup code here, to run once:
  pinMode(STEPPER1_PIN, OUTPUT);
  pinMode(STEPPER2_PIN, OUTPUT);
  pinMode(STEPPER3_PIN, OUTPUT);
  pinMode(STEPPER4_PIN, OUTPUT);

  pinMode(STEPPER4_PIN, OUTPUT);
  pinMode(STEPPER4_PIN, OUTPUT);

  pinMode(POT_WIPER_PIN, INPUT);
  
  pinMode(POT_GND_PIN, OUTPUT);
  digitalWrite(POT_GND_PIN, LOW);

  pinMode(POT_VREF_PIN, OUTPUT);
  digitalWrite(POT_VREF_PIN, HIGH);

  gStepper.setAcceleration(50);
  gStepper.setMaxSpeed(kMaxSpeedStepsPerSec);
  gStepper.setSpeed(60);

  Serial.begin(115200);
}


void loop() {
  // Run the stepper scheduler event loop
  gStepper.runSpeed();

  // Every once in a while, read the pot and change speed.
  unsigned long nowMillis = millis();
  if ((nowMillis - gLastAdcReadMillis) >= kAdcReadIntervalMillis)
  {
    gLastAdcReadMillis = nowMillis;

    // Average ADC readout to reduce noise.
    constexpr long int kAveragedSamples = 4;
    long adcAverage = 0;
    for (int i = 0; i < kAveragedSamples; ++i)
    {
      adcAverage += analogRead(POT_WIPER_PIN);
    }
    adcAverage /= kAveragedSamples;

    // Remap speed from linear pot range to linear pulse range.
    long speed = map(adcAverage, 0, 1023, -kMaxSpeedStepsPerSec, kMaxSpeedStepsPerSec);

    gStepper.setSpeed(speed);

#if 0
    // Debugging of the code.
    Serial.print(adcAverage);
    Serial.print(',');
    Serial.println(speed);
#endif
  }
}
