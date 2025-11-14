#ifndef CONVEYOR_H
#define CONVEYOR_H

#include "stdint.h"

/**
 * 传送带旋转方向
 */
enum class Direction
{
    /**
     * 正转
     */
    Forward,

    /**
     * 反转
     */
    Reverse
};

/**
 * 传送带控制类
 */
class Conveyor
{
public:
    /**
     * 构造函数
     * @param forward_pin 正转控制引脚
     * @param reverse_pin 反转控制引脚
     * @param pwm_pin pwm调速引脚
     */
    Conveyor(int forward_pin, int reverse_pin, int pwm_pin)
        : motor_forward_pin(forward_pin), motor_reverse_pin(reverse_pin), motor_pwm_pin(pwm_pin) {}

    /**
     * 初始化传送带
     */
    void setup();

    /**
     * 运行传送带
     *
     * @param direction 运行方向
     * @param speed_pwm 转速的pwm值
     */
    void run(Direction direction = Direction::Forward, uint16_t speed_pwm = 250);

    /**
     * 停止传送带
     */
    void stop();

private:
    int motor_forward_pin;
    int motor_reverse_pin;
    int motor_pwm_pin;
};

#endif