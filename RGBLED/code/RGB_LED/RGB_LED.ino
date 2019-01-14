//RGB LED

// Go from red to yellow to green

// Starting at red, increase green until yellow is reached
// When yellow is reached, start decreasing red until green is reached

/******************************************************/
// Structs

struct Color
{
    int r;
    int g;
    int b;
};

/******************************************************/
// Initialization

// Colors
const struct Color RED = {255, 100, 100};
const struct Color YELLOW = {255, 255, 100};
const struct Color GREEN = {100, 255, 100};
const struct Color AQUA = {100, 255, 255};
const struct Color BLUE = {100, 100, 255};
const struct Color VIOLET = {255, 100, 255};

// R petal on RGB LED module connected to digital pin 11
const int RED_PIN = 2;

// G petal on RGB LED module connected to digital pin 10
const int GREEN_PIN = 3;

// B petal on RGB LED module connected to digital pin 9
const int BLUE_PIN = 4;

// Color variables
const int targetColorsLength = 6;

const struct Color targetColors[targetColorsLength] = {
  RED,
  YELLOW, 
  GREEN,
  AQUA, 
  BLUE,
  VIOLET};
  
int targetColorsIndex = 1;
struct Color color = targetColors[0];

/******************************************************/
// Helper Functions

struct Color compareColors(struct Color colorA, struct Color colorB)
{
    const struct Color compare = {
        colorB.r - colorA.r,
        colorB.g - colorA.g,
        colorB.b - colorA.b};

    return compare;
}

// if compare is greater than 0, add 1; if less, subtract one; else do nothing
int stepValue(int initialValue, int compare, int stepAmount)
{
    const int finalValue = initialValue + (compare > 0 ? stepAmount : (compare < 0 ? -1 * stepAmount : 0));
    return finalValue;
}

// the color generating function
void sendColor(struct Color color)
{
    analogWrite(RED_PIN, color.r);
    analogWrite(GREEN_PIN, color.g);
    analogWrite(BLUE_PIN, color.b);
}

/**************************************************************************/

void setup()
{
    Serial.begin(115200);
    pinMode(RED_PIN, OUTPUT);   // sets the RED_PIN to be an output
    pinMode(GREEN_PIN, OUTPUT); // sets the GREEN_PIN to be an output
    pinMode(BLUE_PIN, OUTPUT);  // sets the BLUE_PIN to be an output
}

/***************************************************************************/

// run over and over again
void loop()
{
    sendColor(color);
    
    const struct Color compare = compareColors(
      color,
      targetColors[targetColorsIndex]
     );

    // if target color has been reached, move to the next
    // cycling through
    if (compare.r == 0 and compare.g == 0 and compare.b == 0) {
      targetColorsIndex++;
      targetColorsIndex %= targetColorsLength;
    }

    color = {
        stepValue(color.r, compare.r, 1),
        stepValue(color.g, compare.g, 1),
        stepValue(color.b, compare.b, 1),
    };

    delay(10);
}
