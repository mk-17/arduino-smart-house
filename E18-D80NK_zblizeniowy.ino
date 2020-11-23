/*
URUCHOMIENIE CZUJNIKA ZBLIZENIOWEGO, DO SCHODOW.
SYGNAL 0 POJAWIA SIE TYLKO W MOMENCIE ODBICIA WIAZKI

 Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
 20K-ohm resistor is pulled to 5V. This configuration causes the input to
 read HIGH when the switch is open, and LOW when it is closed.

WARTOSCI WEJ I WYJ DO ZMIANY !

 */

void E18-D80NKSetup() {
  //start serial connection
  //Serial.begin(9600);
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(3, INPUT_PULLUP);
  pinMode(13, OUTPUT);

}

void E18-D80NKLoop() {
  //read the pushbutton value into a variable
  int sensorVal = digitalRead(2);
  //print out the value of the pushbutton
  //Serial.println(sensorVal);

  // Keep in mind the pullup means the pushbutton's
  // logic is inverted. It goes HIGH when it's open,
  // and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (sensorVal == HIGH) {
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
  }
}
