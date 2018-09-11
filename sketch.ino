const byte TR = 2;								// Phototransistor pin
const byte LEDS[8] = {10, 9, 8, 7, 6, 5, 4, 3}; //{3, 4, 5, 6, 7, 8, 9, 10}; // LED pins

// Nudes
byte outputArray[100] = {255, 1, 2, 4, 8, 16, 32, 64, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 73, 73, 73, 50, 0, 0, 127, 73, 73, 73, 0, 0, 127, 7, 28, 112, 127, 0, 0, 127, 65, 65, 62, 0, 0, 0, 0, 0, 127, 7, 28, 112, 127, 0, 0, 127, 64, 64, 127, 0, 0, 127, 65, 65, 62, 0, 0, 127, 73, 73, 73, 0, 0, 6, 73, 73, 73, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 64, 32, 16, 8, 4, 2, 1, 255};
// Test
//byte outputArray[100] = {129, 66, 36, 24, 24, 36, 66, 129, 66, 36, 24, 24, 36, 66, 129, 4, 4, 20, 20, 84, 80, 80, 64, 64, 64, 64, 0, 0, 0, 0, 0, 255, 9, 9, 9, 9, 0, 0, 126, 129, 129, 129, 129, 126, 0, 3, 14, 56, 96, 192, 96, 56, 14, 3, 0, 0, 0, 0, 0, 254, 130, 186, 170, 162, 190, 128, 255, 0, 0, 0, 0, 0, 0, 0, 64, 64, 64, 64, 80, 80, 84, 20, 20, 4, 4, 129, 66, 36, 24, 24, 36, 66, 129, 66, 36, 24, 24, 36, 66, 129};

const unsigned long interruptLapBounceMcs = 50000; // prevent fake interrupts; 0,05s = 1200 RPM MAX; Larger bounce -> Lower Speed
const byte extraStepsOffset = 5;				   // offset to display last array element

volatile bool rotateLap = false;
volatile unsigned long outputIndex = 0;
volatile unsigned long timePerStep = 0;
volatile unsigned long nextStepTime = 0;
volatile unsigned long prevLapStartTime = 0;

void lap()
{
	unsigned long itMicros = micros();
	if (itMicros - prevLapStartTime > interruptLapBounceMcs)
	{
		outputIndex = 0;												  // reset output index
		rotateLap = true;												  // trigger rotation
		unsigned long lapTime = itMicros - prevLapStartTime;			  // calculate previous lap time
		timePerStep = lapTime / (sizeof(outputArray) + extraStepsOffset); // one step time = (lap / (128 + delta)
		prevLapStartTime = itMicros;									  // recotd new lap start time
		nextStepTime = itMicros + timePerStep;							  // set next step time
	}
}

void rotate()
{
	byte tmp = outputArray[0];
	for (int i = 0; i < sizeof(outputArray) - 1; i++)
		outputArray[i] = outputArray[i + 1];
	outputArray[sizeof(outputArray) - 1] = tmp;
}

void setup()
{
	pinMode(TR, INPUT);										 // phototransistor init
	attachInterrupt(digitalPinToInterrupt(TR), lap, RISING); // phototransistor (new lap checker) interrupt

	for (int i = 0; i < sizeof(LEDS); i++)
		pinMode(LEDS[i], OUTPUT); // leds init

	//for (int i = 0; i < sizeof(outputArray); i++)
	//outputArray[i] = i + 1;
}

void loop()
{
	unsigned long loopMicros = micros();
	if ((loopMicros >= nextStepTime) && (outputIndex < sizeof(outputArray) - 1))
	{ // current outputArray step update
		nextStepTime = loopMicros + timePerStep;
		outputIndex++;
	}

	if (rotateLap)
	{ // text rotation
		rotate();
		rotateLap = false;
	}

	for (int i = 0; i < sizeof(LEDS); i++) // output cycle
		digitalWrite(LEDS[i], ((1 << i) & outputArray[outputIndex]) != 0);
}
