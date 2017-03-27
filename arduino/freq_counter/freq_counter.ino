// Below: pin number for FOUT
#define PIN_NUMBER 4
// Below: number of samples for averaging
#define AVERAGE 4
// Below: define to use serial output with python script
#define PYTHON_OUTPUT
unsigned int doppler_div = 44;
unsigned int samples[AVERAGE];
unsigned int x;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_NUMBER, INPUT);
}

void loop() {
  noInterrupts();
  pulseIn(PIN_NUMBER, HIGH);
  unsigned int pulse_length = 0;
  for (x = 0; x < AVERAGE; x++)
  {
    pulse_length = pulseIn(PIN_NUMBER, HIGH); 
    pulse_length += pulseIn(PIN_NUMBER, LOW);    
    samples[x] =  pulse_length;
  }
  interrupts();

  // Check for consistency
  bool samples_ok = true;
  unsigned int nbPulsesTime = samples[0];
  for (x = 1; x < AVERAGE; x++)
  {
    nbPulsesTime += samples[x];
    if ((samples[x] > samples[0] * 2) || (samples[x] < samples[0] / 2))
    {
      samples_ok = false;
    }
  }

  if (samples_ok)
  {
    unsigned int Ttime = nbPulsesTime / AVERAGE;
    unsigned int Freq = 1000000 / Ttime;

    #ifdef PYTHON_OUTPUT
      Serial.write(Freq/doppler_div);
    #else
      //Serial.print(Ttime);
      Serial.print("\r\n");
      Serial.print(Freq);
      Serial.print("Hz : ");
      Serial.print(Freq/doppler_div);
      Serial.print("km/h\r\n");
    #endif
  }
  else
  {
    #ifndef PYTHON_OUTPUT
      Serial.print(".");
    #endif
  }
}
