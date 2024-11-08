/*
    Attention:
    PSS_X  = [0, 255]
    PSS_Y  = [0, 255]
    
    const float max_motor_rpm = 291;
    const auto platform_wheel_offset_meters = 0.104f;
    const auto wheel_radius_meters = 100.0f / 1000 / 2;

    const auto max_wheel_rotation_velocity_radiansPerSec = max_motor_rpm * (2 * M_PI) / 60;
    const auto max_translation_velocity_metersPerSec = wheel_radius_meters * max_wheel_rotation_velocity_radiansPerSec;
    const auto max_platform_rotation_velocity_radiansPerSec = max_translation_velocity_metersPerSec / platform_wheel_offset_meters;
    const auto max_platform_rotation_velocity_degreesPerSec = max_platform_rotation_velocity_radiansPerSec * 180 / M_PI;

    dx = convert_joystick_neg1to1(ps2x.Analog(PSS_X)) * max_translation_velocity_metersPerSec;
    dy = convert_joystick_neg1to1(ps2x.Analog(PSS_Y)) * max_translation_velocity_metersPerSec;
    dRot = -convert_joystick_neg1to1(ps2x.Analog(PSS_X)) * max_platform_rotation_velocity_degreesPerSec;
    
    all_rpm_current = kinematics.get_rpm(dx, dy, dRot);
    or
    all_rpm_current = kinematics.get_rpm_use_joystick(convert_joystick_neg1to1(ps2x.Analog(PSS_X)), convert_joystick_neg1to1(ps2x.Analog(PSS_Y)), -convert_joystick_neg1to1(ps2x.Analog(PSS_X)))
*/

#include "Arduino.h"

float convert_joystick_neg1to1(const float &value, const uint16_t &joystickMax = 255)
{
    float res = float(value / joystickMax); // Convert to -0.5, 0.5 range (nearly, because of the trim)
    
    return 2 * res - 1;
}
