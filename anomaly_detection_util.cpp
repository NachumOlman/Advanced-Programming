/*
 * animaly_detection_util.cpp
 *
 * Author: 316555432 Nachum Olman
 */

#include <math.h>
#include "anomaly_detection_util.h"

float avg(float* x, int size){
	float av = 0;
	for (int i = 0; i < size; i++)
	{
		av += x[i];
	}
	return av / size;
}

// returns the variance of X and Y
float var(float* x, int size){
	float sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += (x[i] * x[i]);
	}
	float first = sum / size;
	float second = avg(x, size);
	return first - (second * second);
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
	float x_av = 0, y_av = 0, xy_av = 0;
	for (int i = 0; i < size; i++)
	{
		x_av += x[i];
		y_av += y[i];
	}
	x_av /= size;
	y_av /= size;
	for (int i = 0; i < size; i++)
	{
		xy_av += x[i] * y[i];
	}
	xy_av /= size;
	return (xy_av - (x_av * y_av));
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
	float cov_xy = cov(x, y, size);
	float var_x = sqrt(var(x, size));
	float var_y = sqrt(var(y, size));
	return (cov_xy / (var_x * var_y));
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){
	float* x = new float[size];
	for (int i = 0; i < size; i++)
	{
		x[i] = points[i]->x;
	};
	float* y = new float[size];
	for (int i = 0; i < size; i++)
	{
		y[i] = points[i]->y;
	};
	float a = (cov(x, y, size) / var(x, size));
	float b = (avg(y, size) - (a * avg(x, size)));
	delete(x);
	delete(y);
	return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
	Line l = linear_reg(points, size);
	float val = (l.f(p.x)) - p.y;
	if (val < 0) val *= -1;
	return val;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	float val = (l.f(p.x)) - p.y;
	if (val < 0) val *= -1;
	return val;
}




