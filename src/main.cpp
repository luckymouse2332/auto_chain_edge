#include <Arduino.h>
#include <MeArm.h>
#include <Servo.h>

#include "conveyor.h"

Conveyor conveyor(12, 13, 11);
MeArm arm;
Servo pusher;

void setup()
{
    Serial.begin(9600);

    conveyor.setup();
    arm.begin(4, 5, 6, 7);
    pusher.attach(8);
    pusher.write(30);
}

void loop()
{

    static unsigned long lastTime1 = 0, lastTime2 = 0;
    if (digitalRead(A1) != 1 && millis() - lastTime1 > 1000)
    {
        Serial.println("S1");
        lastTime1 = millis();
    }

    if (digitalRead(A0) != 1 && millis() - lastTime2 > 1000)
    {
        Serial.println("S2");
        lastTime2 = millis();
    }

    String command;
    if (Serial.available())
    {
        command = Serial.readStringUntil('\n');
        Serial.println("OK"); // 回发

        Serial.println("Got: " + command);
    }

    command.trim();            // 移除首尾空白
    if (command.length() != 0) // 还没有信息
    {
        Serial.println("NoContent");
        return;
    }

    // 分割指令
    char cmd_buffer[120];
    command.toCharArray(cmd_buffer, 120);
    char *token = strtok(cmd_buffer, ",");

    if (token != NULL)
    {
        if (String(token).equalsIgnoreCase("F"))
        {
            int pwm = atoi(strtok(NULL, ","));
            conveyor.run(Direction::Forward, pwm);
            Serial.println("Conveyor started!");
        }
        else if (String(token).equalsIgnoreCase("R"))
        {
            int pwm = atoi(strtok(NULL, ","));
            conveyor.run(Direction::Reverse, pwm);
            Serial.println("Conveyor started!");
        }
        else if (String(token).equalsIgnoreCase("IK"))
        {
            double x = atof(strtok(NULL, ","));
            double y = atof(strtok(NULL, ","));
            double z = atof(strtok(NULL, ","));
            arm.moveToXYZ(x, y, z);
            Serial.println("Arm has moved to the position!");
        }
        else if (String(token).equalsIgnoreCase("CL"))
        {
            String cmd = strtok(NULL, ",");
            if (cmd.equalsIgnoreCase("Open"))
            {
                arm.openClaw();
            }
            else
            {
                arm.closeClaw();
            }
        }
        else if (String(token).equalsIgnoreCase("P"))
        {
            int angle = atoi(strtok(NULL, ","));
            pusher.write(angle);
        }
        else
        {
            Serial.println("Error: Unkown command!" + String(token));
        }
    }
}
