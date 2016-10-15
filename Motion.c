double accelerometerOffsetX = 0.0;
double accelerometerOffsetY = 0.0;
double accelerometerOffsetZ = 0.0;

double acceleration[3][2] = {{0,0}, {0,0}, {0,0}};
double velocity[3][2] = {{0,0}, {0,0}, {0,0}};
double position[3][2] = {{0,0}, {0,0}, {0,0}};

// setup - Arduino Setup Funciton

void setup()
{
  Serial.begin(9600);
  initAccelerometer(5, 1);
}

//============================================================================
// loop
//============================================================================

void loop()
{
  acceleration[0][1] =    readAccelerometer(ACCEL_X) - accelerometerOffsetX;         // x-axis
  acceleration[1][1] =    readAccelerometer(ACCEL_Y) - accelerometerOffsetY;         // y-axis
  acceleration[2][1] = -( readAccelerometer(ACCEL_Z) - accelerometerOffsetZ) + 1.0;  // z-axis inverse, 1 g for earth gravity.

  analyzeAccelerometer();

  Serial.print("X: ");
    Serial.print(acceleration[0][1]);

  Serial.print(" Y: ");
    Serial.print(acceleration[1][1]);

  Serial.print(" Z: ");
    Serial.print(acceleration[2][1]);

  Serial.print(position[0][1]);

  Serial.println();

  // delay 50 milliseconds
  delay(50);
}

// initAccelerometer - Initializes everything for the accelerometer

//============================================================================
// analyzeAccelerometer - performs double integration on x, y, and z axes
//============================================================================

void analyzeAccelerometer()
{
  // acceleration[i][j]

  // acceleration[0][j] is x
  // acceleration[1][j] is y
  // acceleration[2][j] is z

  // let j = 0 be initial/previous, j = 1 be current

  // outer loop that handles: x, y, z;

  for (int j = 0; j < 3; j++)
  {
    // get the velocity
    velocity[j][1] = velocity[j][0] + acceleration[j][0] + ((acceleration[j][1] - acceleration[j][0]) / 2);

    // get the distance
    position[j][1] = position[j][0] + velocity[j][0] + ((velocity[j][1] - velocity[j][0]) / 2);

    // get ready for the next set of readings
    acceleration[j][0] = acceleration[j][1];
    velocity[j][0] = velocity[j][1];
    position[j][0] = position[j][1];
  }
}
