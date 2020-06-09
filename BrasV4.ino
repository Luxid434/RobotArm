/*

Hello u !

I'm glad to see you here 
but please considere these few points :

-  My robot was controlled by a TV remote 
   so the arm is fully controllable with 
   9 position that you can save and replay 
   whenever you want,

-  I used the "ServoEasing" library to 
   smooth the mouvements (i use little
   motors "Servo motors 9g" and without 
   this library the movements was glitchy af

-  ~\^_^/~

-  I'm a french 15 yo boi so my english is shit

-  Feel free to reddit me or e-mail me your code 
   cuz nobody's code isn't perfect(lucasladreyt@outlook.com)

-  At line 137 you have the "summary" where parts of the code are explained and can be called

Well, enjoy (or pain/suffer idk)


*/


# include <IRremote.h>
# include <IRremoteInt.h>
# include <ServoEasing.h>

IRrecv irrecv (11);
decode_results results;

ServoEasing servX;
ServoEasing servY;
ServoEasing servZ;
ServoEasing servW;
ServoEasing servC;

int x;
int y;
int z;
int w;
int c;
int vit = 15;

boolean on = true;
boolean off = false;

boolean aOui = false;
boolean aNon = true;

boolean finish = true;

unsigned long previousMillis = 0;
unsigned long currentMillis = millis();

int p = 1;

int posX[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int posY[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int posZ[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int posW[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int posC[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void setup () {
  Serial.begin(9600);

  irrecv.enableIRIn ();

  servX.attach(3);
  servY.attach(2);
  servZ.attach(4);
  servW.attach(5);
  servC.attach(6);

  servX.setSpeed(100);
  servY.setSpeed(100);
  servZ.setSpeed(100);
  servW.setSpeed(100);
  servC.setSpeed(100);

  delay(1000);

  forceHomeReturn();
}

void loop () {
  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis >= 1000) && (aOui == true)) {
    previousMillis = currentMillis;
    p++;
    servX.setSpeed(vit * 10);
    servY.setSpeed(vit * 10);
    servZ.setSpeed(vit * 10);
    servW.setSpeed(vit * 10);
    servC.setSpeed(vit * 10);

    if (p > 9) p = 1;

    if ((posX[p]) == 1) {
      posX[p] = posX[p - 1];
    }
    if ((posY[p]) == 1) {
      posY[p] = posY[p - 1];
    }
    if ((posZ[p]) == 1) {
      posZ[p] = posZ[p - 1];
    }
    if ((posW[p]) == 1) {
      posW[p] = posW[p - 1];
    }
    if ((posC[p]) == 1) {
      posC[p] = posC[p - 1];
    }

    delay(250);
    servC.easeTo(posC[p]);
    delay(250);
    servW.easeTo(posW[p]);
    delay(250);
    servZ.easeTo(posZ[p]);
    delay(250);
    servX.easeTo(posX[p]);
    delay(250);
    servY.easeTo(posY[p]);
    Serial.println("effectué :)");
  }

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    fleches();   //this part is where you can freely move the robot

    vitesse();  // this part control the speed of the arm

    homeReturn();  // this part is used to return at the default position when your ass is tired

    pos(); // this part is used to save positions

    onOff();  // this is the on/off part lul

    automatique(); // this is the automaticly part

    irrecv.resume();
  }
}













void fleches() {
  if (results.value == 0x810) {  //haut
    if ((x <= 0)) x = 5;
    if ((x >= 180)) x = 175;
    else {
      x += vit;
      servX.write(x);
    }
  }

  if (results.value == 0xE10) {  // bas
    if ((x <= 0)) x = 5;
    if ((x >= 180)) x = 175;
    else {
      x -= vit;
      servX.write(x);
    }
  }

  if (results.value == 0xA10) {  //droite
    if ((y <= 0)) y = 5;
    if ((y >= 180)) y = 175;
    else {
      y += vit;
      servY.write(y);
    }
  }

  if (results.value == 0xC10) {  //gauche
    if ((y <= 0)) y = 5;
    if ((y >= 180)) y = 175;
    else {
      y -= vit;
      servY.write(y);
    }
  }

  if (results.value == 0x10) {  //volume+
    if ((z <= 0)) z = 5;
    if ((z >= 180)) z = 175;
    else {
      z += vit;
      servZ.write(z);
    }
  }

  if (results.value == 0x610) {  //volume-
    if ((z <= 0)) z = 5;
    if ((z >= 180)) z = 175;
    else {
      z -= vit;
      servZ.write(z);
    }
  }

  if (results.value == 0x410) {  //prog+
    if ((w <= 0)) w = 5;
    if ((w >= 180)) w = 175;
    else {
      w += vit;
      servW.write(w);
    }
  }

  if (results.value == 0x110) {  //prog-
    if ((w <= 0)) w = 5;
    if ((w >= 180)) w = 175;
    else {
      w -= vit;
      servW.write(w);
    }
  }
  servX.write(x);
  servY.write(y);
  servZ.write(z);
  servW.write(w);
  servC.write(c);
}

void homeReturn() {
  if (results.value == 0xC05C83) {  //return
    Serial.println("Retour à la position de départ...");
    c = 90;
    servC.easeTo(c);
    w = 90;
    servW.easeTo(w);
    z = 90;
    servZ.easeTo(z);
    x = 90;
    servX.easeTo(x);
    y = 90;
    servY.easeTo(y);
  }
}

void forceHomeReturn() {
  c = 90;
  servC.easeTo(c);
  w = 90;
  servW.easeTo(w);
  z = 90;
  servZ.easeTo(z);
  x = 90;
  servX.easeTo(x);
  y = 90;
  servY.easeTo(y);
}

void vitesse() {
  if (results.value == 0xC05C6D) {  //rouge
    vit = 5;
    Serial.print("La vitesse est égale à ");
    Serial.println(vit);
  }

  if (results.value == 0xC05C6E) {  //vert
    vit = 10;
    Serial.print("La vitesse est égale à ");
    Serial.println(vit);
  }

  if (results.value == 0xC05C6F) {  //jaune
    vit = 15;
    Serial.print("La vitesse est égale à ");
    Serial.println(vit);
  }

  if (results.value == 0xC05C70) {  //bleu
    vit = 20;
    Serial.print("La vitesse est égale à ");
    Serial.println(vit);
  }
}

void pos() {
  if (results.value == 0xC05C01) {  // 1
    int i = 1;
    posX[i] = servX.read();
    posY[i] = servY.read();
    posZ[i] = servZ.read();
    posW[i] = servW.read();
    posC[i] = servC.read();
    Serial.print("Position ");
    Serial.print(i);
    Serial.println(" sauvegardée");
  }
  if (results.value == 0xC05C02) {  // 2
    int i = 2;
    posX[i] = servX.read();
    posY[i] = servY.read();
    posZ[i] = servZ.read();
    posW[i] = servW.read();
    posC[i] = servC.read();
    Serial.print("Position ");
    Serial.print(i);
    Serial.println(" sauvegardée");
  }
  if (results.value == 0xC05C03) {  // 3
    int i = 3;
    posX[i] = servX.read();
    posY[i] = servY.read();
    posZ[i] = servZ.read();
    posW[i] = servW.read();
    posC[i] = servC.read();
    Serial.print("Position ");
    Serial.print(i);
    Serial.println(" sauvegardée");
  }
  if (results.value == 0xC05C04) {  // 4
    int i = 4;
    posX[i] = servX.read();
    posY[i] = servY.read();
    posZ[i] = servZ.read();
    posW[i] = servW.read();
    posC[i] = servC.read();
    Serial.print("Position ");
    Serial.print(i);
    Serial.println(" sauvegardée");
  }
  if (results.value == 0xC05C05) {  // 5
    int i = 5;
    posX[i] = servX.read();
    posY[i] = servY.read();
    posZ[i] = servZ.read();
    posW[i] = servW.read();
    posC[i] = servC.read();
    Serial.print("Position ");
    Serial.print(i);
    Serial.println(" sauvegardée");
  }
  if (results.value == 0xC05C06) {  // 6
    int i = 6;
    posX[i] = servX.read();
    posY[i] = servY.read();
    posZ[i] = servZ.read();
    posW[i] = servW.read();
    posC[i] = servC.read();
    Serial.print("Position ");
    Serial.print(i);
    Serial.println(" sauvegardée");
  }
  if (results.value == 0xC05C07) {  // 7
    int i = 7;
    posX[i] = servX.read();
    posY[i] = servY.read();
    posZ[i] = servZ.read();
    posW[i] = servW.read();
    posC[i] = servC.read();
    Serial.print("Position ");
    Serial.print(i);
    Serial.println(" sauvegardée");
  }
  if (results.value == 0xC05C08) {  // 8
    int i = 8;
    posX[i] = servX.read();
    posY[i] = servY.read();
    posZ[i] = servZ.read();
    posW[i] = servW.read();
    posC[i] = servC.read();
    Serial.print("Position ");
    Serial.print(i);
    Serial.println(" sauvegardée");
  }
  if (results.value == 0xC05C09) {  // 9
    int i = 9;
    posX[i] = servX.read();
    posY[i] = servY.read();
    posZ[i] = servZ.read();
    posW[i] = servW.read();
    posC[i] = servC.read();
    Serial.print("Position ");
    Serial.print(i);
    Serial.println(" sauvegardée");
  }
}

void onOff() {
  if ((results.value == 0xC05C0D) || (results.value == 0xC05C0C)) { // on/off
    if (on == true) {
      forceHomeReturn();
      servX.detach();
      servY.detach();
      servZ.detach();
      servW.detach();
      servC.detach();
      off = true;
      on = false;
    }
    else if (off == true) {
      servX.attach(3);
      servY.attach(2);
      servZ.attach(4);
      servW.attach(5);
      servC.attach(6);
      forceHomeReturn();
      on = true;
      off = false;
    }
  }
}

void automatique() {
  if (results.value == 0x2CE9) {   //play
    aOui = true;
    Serial.println("aOui == true");
  }
  if (results.value == 0x4CE9) {   //pause
    aOui = false;
    Serial.println("aOui == false");
  }
}
