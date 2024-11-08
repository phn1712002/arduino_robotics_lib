/*
Version: 1.0.0
(c) 2014 Korneliusz Jarzebski
www.jarzebski.pl

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Arduino.h"

class KalmanFilter
{
    public:

	KalmanFilter(double angle = 0.001, double bias = 0.003, double measure = 0.03);
	double update(double newValue, double newRate);

    private:

	double Q_angle, Q_bias, R_measure;
	double K_angle, K_bias, K_rate;
	double P[2][2], K[2];
	double S, y;
	double dt, kt;
};

KalmanFilter::KalmanFilter(double angle, double bias, double measure)
{
    Q_angle = angle;
    Q_bias = bias;
    R_measure = measure;

    K_angle = 0;
    K_bias = 0;

    P[0][0] = 0;
    P[0][1] = 0;
    P[1][0] = 0;
    P[1][1] = 0;

    kt = (double)micros();
}

double KalmanFilter::update(double newValue, double newRate)
{
    dt = (double)(micros() - kt) / 1000000;

    K_rate = newRate - K_bias;
    K_angle += dt * K_rate;

    P[0][0] += dt * (P[1][1] + P[0][1]) + Q_angle * dt;
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_bias * dt;

    S = P[0][0] + R_measure;

    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;

    y = newValue - K_angle;

    K_angle += K[0] * y;
    K_bias += K[1] * y;

    P[0][0] -= K[0] * P[0][0];
    P[0][1] -= K[0] * P[0][1];
    P[1][0] -= K[1] * P[0][0];
    P[1][1] -= K[1] * P[0][1];

    kt = (double)micros();

    return K_angle;
};
