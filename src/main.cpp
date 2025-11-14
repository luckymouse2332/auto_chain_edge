#include <Arduino.h>
#include <MeArm.h>
#include <Servo.h>

#include "conveyor.h"

Conveyor conveyor(13, 12, 11);
MeArm arm;
Servo pusher;

String status;

void setup()
{
    Serial.begin(9600);

    conveyor.setup();
    arm.begin(3, 5, 6, 9);
    pusher.attach(8);
    delay(1000);
    pusher.write(30);
    delay(1000);
}

void loop()
{
    if (digitalRead(A1))
    {
        return;
    }
    delay(3000);
    arm.snapToXYZ(-80, 0, 0);
    arm.openClaw();
    delay(1000);
    arm.snapToXYZ(-140, 0, -20);
    delay(1000);
    arm.closeClaw();
    delay(1000);

    conveyor.stop();
    arm.snapToXYZ(-80, 0, 20);
    delay(1000);
    arm.snapToXYZ(0, 90, 40);
    delay(500);
    arm.snapToXYZ(0, 120, 40);
    delay(500);
    arm.openClaw();
    delay(1000);
    arm.snapToXYZ(0, 100, 50);
    delay(1000);
    while (analogRead(A4) <= 512)
    {
        delay(5);
    }
    Serial.println("OK");
    if (analogRead(A5) >= 512)
    {
        conveyor.run();
        while (digitalRead(A0))
        {
            delay(5);
        }
        delay(1000);
        conveyor.stop();
        pusher.write(130);
        delay(1000);
        pusher.write(30);
        delay(1000);
        conveyor.run();
    }
    conveyor.run();
    // while (true)
    // {
    //   status = Serial.readStringUntil('\n');
    //   if (status != "") break;
    // }
    // Serial.println("Running");
    // conveyor.run();
    // for (size_t i = 0; i < status.length(); i++)
    // {
    //   if (status[i] == 'b')
    //   {
    //     while (digitalRead(A0))
    //     {
    //       delay(5);
    //     }
    //     delay(1000);
    //     conveyor.stop();
    //     pusher.write(130);
    //     delay(1000);
    //     pusher.write(30);
    //     delay(1000);
    //     conveyor.run();
    //     break;
    //   }
    // }
}
