/*
 * generic_driver.h
 *
 *  Created on: May 19, 2017
 *      Author: mrinalkanti
 */

#ifndef GENERIC_DRIVER_H_
#define GENERIC_DRIVER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace MARS {

struct Generic_Image {
  unsigned char * data;
  int height;
  int width;
  int stride;
  double timestamp;
};

struct Generic_IMU {
  double accelX;
  double accelY;
  double accelZ;

  double gyroX;
  double gyroY;
  double gyroZ;

  double timestamp;
};

class GenericDriver {
public:
  GenericDriver(char* imu_path, char* left_image_path, char* right_image_path);
  ~GenericDriver();

  void startCamera(int cam_id);
  void getImage(struct Generic_Image* img, int cam_id);

  void startIMU();
  void getIMU(Generic_IMU* imu);

private:
  bool LoadPGMFile(struct Generic_Image* img, const std::string& file_name);

  char* l_img_path_;
  char* r_img_path_;
  char* imu_path_;

  std::ifstream imu_file_;
  std::ifstream l_img_timestamp_file_;
  std::ifstream r_img_timestamp_file_;

  int l_index_, r_index_;
}; // End of class: GenericDriver
} // End of namespace: MARS

#endif /* GENERIC_DRIVER_H_ */
