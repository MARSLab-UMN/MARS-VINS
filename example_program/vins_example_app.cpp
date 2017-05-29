#include <iostream>
#include "core/generic_driver.h"
#include "core/mars-vins-facade.h"

int main(int argc, char** argv) {
  if( argc != 6) {
    std::cout << "Usage: program-name  <config-file-path> <output-path> "
        "<imu-path> <left-image-path> <right-image-path>" << std::endl;
    return -1;
  }

  char* config_path = argv[1];
  char* imu_path = argv[3];
  char* left_image_path = argv[4];
  char* right_image_path = argv[5];
  char* output_path = argv[2];

  std::string img_path(left_image_path);
  size_t image_num = 500;

  // Arguments are IMU path, left image path, and right image path.
  std::unique_ptr<MARS::GenericDriver> driver =
    std::unique_ptr<MARS::GenericDriver>(new MARS::GenericDriver(
      imu_path, left_image_path, right_image_path));

  MARS::MARSVinsFacade mars_vins(std::move(driver), config_path, output_path);

  for (int i = 0; i < image_num; ++i) {
    mars_vins.RunSingleImage();
    MARS::Pose pose;
    mars_vins.GetPose(&pose);
    std::cout << "x: " << pose.global_P_imu[0]
              << "y: " << pose.global_P_imu[1]
              << "z: " << pose.global_P_imu[2] << std::endl;
  }
  return 0;
}
