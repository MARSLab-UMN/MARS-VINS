/*
 * generic_driver.cpp
 *
 *  Created on: May 19, 2017
 *      Author: mrinalkanti
 */

#include "core/generic_driver.h"

namespace MARS {

GenericDriver::GenericDriver(char* imu_path,
    char* left_image_path, char* right_image_path) {
  imu_path_ = imu_path;
  l_img_path_ = left_image_path;
  r_img_path_ = right_image_path;

  l_index_ = 0;
  r_index_ = 0;
}

GenericDriver::~GenericDriver() {
  if(imu_file_.is_open()) {
    imu_file_.close();
  }
  if(l_img_timestamp_file_.is_open()) {
    l_img_timestamp_file_.close();
  }
  if(r_img_timestamp_file_.is_open()) {
    r_img_timestamp_file_.close();
  }
}

void GenericDriver::startCamera(int cam_id) {
  if (cam_id == 0) {
    std::string timestamps_file(l_img_path_);
    timestamps_file = timestamps_file + "/timestamps.txt";
    l_img_timestamp_file_.open(timestamps_file.c_str());
  } else if (cam_id == 1) {
    if (r_img_path_ == nullptr) {
      std::cout<< "Right camera not initialized." << std::endl;
      return;
    }
    std::string timestamps_file(r_img_path_);
    timestamps_file = timestamps_file + "/timestamps.txt";
    r_img_timestamp_file_.open(timestamps_file.c_str());
  } else {
    std::cout<< "Wrong camera id." << std::endl;
  }
}

bool GenericDriver::LoadPGMFile(struct Generic_Image* img,
    const std::string& file_name) {
  char junk[100];
  std::ifstream pgm_file;
  pgm_file.open(file_name.c_str(), std::ios::binary);
  if(pgm_file.is_open() == false)
    return false;
  std::string p5_string;
  pgm_file >> p5_string;
  int width = 0;
  int height = 0;
  pgm_file >> width >> height;  // Width, Height
  int max_pixel_value;
  pgm_file >> max_pixel_value;
  pgm_file.getline(junk, 100);

  img->height = height;
  img->width = width;
  img->stride = width;
  img->data = (unsigned char*) malloc(width * height * sizeof(unsigned char));
  pgm_file.read(reinterpret_cast<char*>(img->data), height * width);

  if(pgm_file) {
      pgm_file.close();
      return true;
  } else {
      pgm_file.close();
      return false;
  }
}

void GenericDriver::getImage(struct Generic_Image* img, int cam_id) {
  double image_time;
  std::ostringstream s;
  std::string image_title;
  img->data = nullptr;

  if (cam_id == 0) {
    std::string location(l_img_path_);
    s << location << "m" << std::setfill('0') << std::setw(7)
      << l_index_ << ".pgm";
    l_img_timestamp_file_ >> image_title;
    l_img_timestamp_file_ >> image_time;
    ++l_index_;
  } else if (cam_id == 1) {
    if (r_img_path_ == nullptr) {
      std::cout<< "Right camera not initialized." << std::endl;
      return;
    }

    std::string location(r_img_path_);
    s << location << "m" << std::setfill('0') << std::setw(7)
      << r_index_ << ".pgm";
    r_img_timestamp_file_ >> image_title;
    r_img_timestamp_file_ >> image_time;
    ++r_index_;
  } else {
    std::cout<< "Wrong camera id." << std::endl;
    return;
  }

  std::string image_location(s.str());
  const bool success = LoadPGMFile(img, image_location);
  if (!success) {
    std::cout<< "Image read failed."<<std::endl;
    return;
  }
  img->timestamp = image_time;
}

void GenericDriver::startIMU() {
  imu_file_.open(imu_path_);std::cout<<imu_path_<<std::endl;
}

void GenericDriver::getIMU(Generic_IMU* imu) {
  imu_file_ >> imu->timestamp;

  imu_file_ >> imu->gyroX;
  imu_file_ >> imu->gyroY;
  imu_file_ >> imu->gyroZ;

  imu_file_ >> imu->accelX;
  imu_file_ >> imu->accelY;
  imu_file_ >> imu->accelZ;
}

} // End of namespace: MARS


