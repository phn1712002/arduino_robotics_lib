// Based on code by Juan Miguel Jimeno. This is his license:
//         Copyright (c) 2021 Juan Miguel Jimeno
//
//         Licensed under the Apache License, Version 2.0 (the "License");
//         you may not use this file except in compliance with the License.
//         You may obtain a copy of the License at
//
//             http://www.apache.org/licenses/LICENSE-2.0
//
//         Unless required by applicable law or agreed to in writing, software
//         distributed under the License is distributed on an "AS IS" BASIS,
//         WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//         See the License for the specific language governing permissions and
//         limitations under the License.

// Read : https://github.com/avivhu/botabotabot/blob/main/src/kinematics.hpp

#include "Arduino.h"

class Kinematics
{
public:
    Kinematics(float platform_wheel_offset_meters, float wheel_radius_meters, float max_motor_rpm);
    
    struct rpm
    {
        float motorRpm[3];
    };

    rpm get_rpm(float linear_x, float linear_y, float angular_z);
    rpm get_rpm_use_joystick(float joystick_linearX, float joystick_linearY, float joystick_angularZ);

private:
    float _max_motor_rpm;
    float _platform_wheel_offset_meters;
    float _wheel_radius_meters;
    float _max_wheel_rotation_velocity_radiansPerSec;
    float _max_translation_velocity_metersPerSec;
    float _max_platform_rotation_velocity_radiansPerSec;
    float _max_platform_rotation_velocity_degreesPerSec;
};

// Receive desired platform velocity and compute the required RPM for each motor to achieve this velocity
// linear_x, linear_y - In meters/sec
// angular_z - In degrees/sec
// => The platform's positive rotation is Counter Clock-Wise as seen from the top looking down.
// => The wheels' positive rotation is Clock-Wise as seen from inside the platform looking out.

Kinematics::Kinematics(float platform_wheel_offset_meters, float wheel_radius_meters, float max_motor_rpm)
{
    this->_wheel_radius_meters = wheel_radius_meters;
    this->_platform_wheel_offset_meters = platform_wheel_offset_meters;
    this->_max_motor_rpm = max_motor_rpm;

    this->_max_wheel_rotation_velocity_radiansPerSec = this->_max_motor_rpm * (2 * M_PI) / 60;
    this->_max_translation_velocity_metersPerSec = this->_wheel_radius_meters * this->_max_wheel_rotation_velocity_radiansPerSec;
    this->_max_platform_rotation_velocity_radiansPerSec = this->_max_translation_velocity_metersPerSec / this->_platform_wheel_offset_meters;
    this->_max_platform_rotation_velocity_degreesPerSec = this->_max_platform_rotation_velocity_radiansPerSec * 180 / M_PI;
}

Kinematics::rpm Kinematics::get_rpm(float linearX, float linearY, float angularZ)
{
    const auto sin_60 = 0.8660254037844386f;
    const auto angularZRadians = float(M_PI) * angularZ / 180;

    // Compute angular speed of each wheel in radians / sec
    auto u1 = (-this->_platform_wheel_offset_meters * angularZRadians + 1.0f * linearX) / this->_wheel_radius_meters;
    auto u2 = (-this->_platform_wheel_offset_meters * angularZRadians - 0.5f * linearX + -sin_60 * linearY) / this->_wheel_radius_meters;
    auto u3 = (-this->_platform_wheel_offset_meters * angularZRadians - 0.5f * linearX + +sin_60 * linearY) / this->_wheel_radius_meters;

    // Convert to rad/sec to RPM (revs per minute)
    u1 *= 60.0 / (2 * M_PI);
    u2 *= 60.0 / (2 * M_PI);
    u3 *= 60.0 / (2 * M_PI);

    return {{u1, u2, u3}};
};

Kinematics::rpm Kinematics::get_rpm_use_joystick(float joystick_linearX, float joystick_linearY, float joystick_angularZ)
{
    /*
    joystick_linearX, joystick_linearX, joystick_linearX = [-1, 1] is value of joystick
    */
    auto dx = joystick_linearX * this->_max_translation_velocity_metersPerSec;
    auto dy = joystick_linearY * this->_max_translation_velocity_metersPerSec;
    auto dRot = joystick_angularZ * this->_max_platform_rotation_velocity_degreesPerSec;
    Kinematics::rpm all_rpm = this->get_rpm(dx, dy, dRot);

    return all_rpm;
}