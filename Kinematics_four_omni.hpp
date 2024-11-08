#include "Arduino.h"

class Kinematics
{
public:
    Kinematics(float bodyWheelOffsetMeters, float wheelRadiusMeters) : 
        _bodyWheelOffsetMeters(bodyWheelOffsetMeters),
        _wheelRadiusMeters(wheelRadiusMeters)
    {
    }

    struct rpm
    {
        float motorRpm[4];
    };

    struct velocities
    {
        float linear_x;
        float linear_y;
        float angular_z;
    };

    rpm get_rpm(float linear_x, float linear_y, float angular_z);

    float _bodyWheelOffsetMeters;
    float _wheelRadiusMeters;
};

// Receive desired platform velocity and compute the required RPM for each motor to achieve this velocity
// linear_x, linear_y - In meters/sec
// angular_z - In degrees/sec
// => The platform's positive rotation is Counter Clock-Wise as seen from the top looking down.
// => The wheels' positive rotation is Clock-Wise as seen from inside the platform looking out.

Kinematics::rpm Kinematics::get_rpm(float linearX, float linearY, float angularZ)
{
    const auto angularZRadians = float(M_PI) * angularZ / 180;

    auto u1 = (-cos(_bodyWheelOffsetMeters * M_PI / 180) * linearX + sin(_bodyWheelOffsetMeters * M_PI / 180) * linearY + L * angularZRadians) / _wheelRadiusMeters;
    auto u2 = (-cos(_bodyWheelOffsetMeters * M_PI / 180) * linearX - sin(_bodyWheelOffsetMeters * M_PI / 180) * linearY + L * angularZRadians) / _wheelRadiusMeters;
    auto u3 = (cos(_bodyWheelOffsetMeters * M_PI / 180) * linearX - sin(_bodyWheelOffsetMeters * M_PI / 180) * linearY + L * angularZRadians) / _wheelRadiusMeters;
    auto u4 = (cos(_bodyWheelOffsetMeters * M_PI / 180) * linearX + sin(_bodyWheelOffsetMeters * M_PI / 180) * linearY + L * angularZRadians) / _wheelRadiusMeters;

    return {{u1, u2, u3, u4}};
};