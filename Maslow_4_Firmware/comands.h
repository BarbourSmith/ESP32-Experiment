float setPoint = 0;

ESP32MotorControl MotorControl = ESP32MotorControl();

void parseCommand(String command, String value){
    Serial.println("Parsing Command:");
    Serial.println(command);
    
    if(command == "setpoint"){
        Serial.println("Error: ");
        Serial.println(setPoint - value.toFloat());
        setPoint = value.toFloat();
    }
}

// void setupMotor(){
    // const int freq = 1000;
    // const int ledChannel = 0;
    // const int resolution = 8;
    
    // ledcSetup(ledChannel, freq, resolution);
    
    // attach the channel to the GPIO to be controlled
    // ledcAttachPin(MotorIn1, ledChannel);
    // ledcAttachPin(MotorIn2, ledChannel);
// }

void motorStop(){
    MotorControl.motorsStop();
}

// void motorForwards(){
    // digitalWrite(MotorIn1, LOW);
    // digitalWrite(MotorIn2, HIGH);
// }

// void motorReverse(){
    // digitalWrite(MotorIn1, HIGH);
    // digitalWrite(MotorIn2, LOW);
// }

void motorSpeed(int speed){
    //Serial.println(speed);
    if(speed < 0){
        // Serial.println("Less than zero");
        speed = constrain(abs(speed), 0, 255);
        MotorControl.motorReverse(0, speed);
    }
    else{
        // Serial.println("More than zero");
        speed = constrain(abs(speed), 0, 255);
        MotorControl.motorForward(0, speed);
    }
}

