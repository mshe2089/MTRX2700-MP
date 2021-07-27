#include "accelerometer.h"
#include <math.h>

void convertUnits(AccelRaw *raw_data, AccelScaled *scaled_data){
    scaled_data->x = (float)(raw_data->x)/250;
    scaled_data->y = (float)(raw_data->y)/250;
    scaled_data->z = (float)(raw_data->z)/250;
}

void calc_xy_angles(float x_val, float y_val, float z_val, float* accel_angle_x, float* accel_angle_y){
   // Using x y and z from accelerometer, calculate x and y angles
   float result;
   double x2, y2, z2;  
   
   

   // Work out the squares
   x2 = (double)(x_val*x_val);
   y2 = (double)(y_val*y_val);
   z2 = (double)(z_val*z_val);

   //X Axis
   result=sqrt(y2+z2);
   result=x_val/result;
   *accel_angle_x = atan(result);

   //Y Axis
   result=sqrt(x2+z2);
   result=y_val/result;
   *accel_angle_y = atan(result);
}