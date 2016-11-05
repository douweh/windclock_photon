int setWindDir(String direction);
int setWindSpeed(String speed);
int setCircleDelay(String delay);
int setViewDelay(String delay);

#define SIXTEEN_MINUTE_MILLIS (16 * 60 * 1000)
unsigned long lastSync = millis();

int N = D7;
int NW = D6;
int W = D5;
int SW = D4;
int S = D3;
int SE = D2;
int E = D1;
int NE = D0;

String windDir      = "N";
String windSpeed    = "1";
int circleDelay     = 100;
int viewDelay       = 5000;

void setup() {
    Particle.function("windDir", setWindDir);
    Particle.function("windSpeed", setWindSpeed);
    Particle.function("circleDelay", setCircleDelay);
    Particle.function("viewDelay", setViewDelay);
    pinMode(N, OUTPUT);
    pinMode(NE, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(SE, OUTPUT);
    pinMode(S, OUTPUT);
    pinMode(SW, OUTPUT);
    pinMode(W, OUTPUT);
    pinMode(NW, OUTPUT);
}

int setWindDir(String direction) {
    windDir = direction;
    lastSync = millis();
    return 1;
}

int setWindSpeed(String speed) {
    windSpeed = speed;
    lastSync = millis();
    return 1;
}

int setCircleDelay(String delay) {
    circleDelay = delay.toInt();
    return 1;
}

int setViewDelay(String delay) {
    viewDelay = delay.toInt();
    return 1;
}

void ledsOff(){
    digitalWrite(N, LOW);
    digitalWrite(NE, LOW);
    digitalWrite(E, LOW);
    digitalWrite(SE, LOW);
    digitalWrite(S, LOW);
    digitalWrite(SW, LOW);
    digitalWrite(W, LOW);
    digitalWrite(NW, LOW);
}

void ledsOn(){
    digitalWrite(N, HIGH);
    digitalWrite(NE, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(SE, HIGH);
    digitalWrite(S, HIGH);
    digitalWrite(SW, HIGH);
    digitalWrite(W, HIGH);
    digitalWrite(NW, HIGH);
}

void showWindDir() {
    String direction = windDir;
    ledsOff();

    if (direction == "N") {
        digitalWrite(N, HIGH);
    } else if (direction == "NNE") {
        digitalWrite(N, HIGH);
        digitalWrite(NE, HIGH);
    } else if (direction == "NE") {
        digitalWrite(NE, HIGH);
    } else if (direction == "ENE") {
        digitalWrite(NE, HIGH);
        digitalWrite(E, HIGH);
    } else if (direction == "E") {
        digitalWrite(E, HIGH);
    } else if (direction == "ESE") {
        digitalWrite(E, HIGH);
        digitalWrite(SE, HIGH);
    } else if (direction == "SE") {
        digitalWrite(SE, HIGH);
    } else if (direction == "SSE") {
        digitalWrite(SE, HIGH);
        digitalWrite(S, HIGH);
    } else if (direction == "S") {
        digitalWrite(S, HIGH);
    } else if (direction == "SSW") {
        digitalWrite(S, HIGH);
        digitalWrite(SW, HIGH);
    } else if (direction == "SW") {
        digitalWrite(SW, HIGH);
    } else if (direction == "WSW") {
        digitalWrite(W, HIGH);
        digitalWrite(SW, HIGH);
    } else if (direction == "W") {
        digitalWrite(W, HIGH);
    } else if (direction == "WNW") {
        digitalWrite(W, HIGH);
        digitalWrite(NW, HIGH);
    } else if (direction == "NW") {
        digitalWrite(NW, HIGH);
    } else if (direction == "NNW") {
        digitalWrite(N, HIGH);
        digitalWrite(NW, HIGH);
    }
}

void showWindSpeed() {
    String speed = windSpeed;
    ledsOff();

    if (speed == "1") {
        digitalWrite(N, HIGH);
    } else if (speed == "2") {
        digitalWrite(N, HIGH);
        digitalWrite(NE, HIGH);
    } else if (speed == "3") {
        digitalWrite(N, HIGH);
        digitalWrite(NE, HIGH);
        digitalWrite(E, HIGH);
    } else if (speed == "4") {
        digitalWrite(N, HIGH);
        digitalWrite(NE, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(SE, HIGH);
    } else if (speed == "5") {
        digitalWrite(N, HIGH);
        digitalWrite(NE, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(SE, HIGH);
        digitalWrite(S, HIGH);
    } else if (speed == "6") {
        digitalWrite(N, HIGH);
        digitalWrite(NE, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(SE, HIGH);
        digitalWrite(S, HIGH);
        digitalWrite(SW, HIGH);
    } else if (speed == "7") {
        digitalWrite(N, HIGH);
        digitalWrite(NE, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(SE, HIGH);
        digitalWrite(S, HIGH);
        digitalWrite(SW, HIGH);
        digitalWrite(W, HIGH);
    }
     else if (speed == "8") {
        digitalWrite(N, HIGH);
        digitalWrite(NE, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(SE, HIGH);
        digitalWrite(S, HIGH);
        digitalWrite(SW, HIGH);
        digitalWrite(W, HIGH);
        digitalWrite(NW, HIGH);
    }
}

void showCircle(int speed){
    ledsOff();
    // loop
    digitalWrite(N, HIGH);
    delay(speed);
    digitalWrite(N, LOW);
    digitalWrite(NE, HIGH);
    delay(speed);
    digitalWrite(NE, LOW);
    digitalWrite(E, HIGH);
    delay(speed);
    digitalWrite(E, LOW);
    digitalWrite(SE, HIGH);
    delay(speed);
    digitalWrite(SE, LOW);
    digitalWrite(S, HIGH);
    delay(speed);
    digitalWrite(S, LOW);
    digitalWrite(SW, HIGH);
    delay(speed);
    digitalWrite(SW, LOW);
    digitalWrite(W, HIGH);
    delay(speed);
    digitalWrite(W, LOW);
    digitalWrite(NW, HIGH);
    delay(speed);
    digitalWrite(NW, LOW);
    digitalWrite(N, HIGH);
    delay(speed);
    digitalWrite(N, LOW);
}

void nowifi(){
    ledsOff();
    delay(100);
    ledsOn();
    delay(400);
    ledsOff();
    delay(100);
    ledsOn();
    delay(400);
    ledsOff();
    delay(100);
    ledsOn();
    delay(400);
    ledsOff();
    delay(1000);
}

void nodata(){
    ledsOff();
    delay(2000);
    ledsOn();
    delay(500);
    ledsOff();
    delay(500);
    ledsOn();
    delay(500);
}

void loop() {
    if (!WiFi.ready()) {
        nowifi();
    } else if (millis() - lastSync > SIXTEEN_MINUTE_MILLIS) {
        nodata();
    } else {
        showCircle(circleDelay);
        showWindDir();
        delay(viewDelay);
        showCircle(circleDelay);
        showWindSpeed();
        delay(viewDelay);
    }
}
