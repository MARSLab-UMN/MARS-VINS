#ifndef _MARS_VINS_FACADE_H_
#define _MARS_VINS_FACADE_H_
#include <memory>

namespace MARS {
struct Pose {
  double imu_q_global[4];
  double global_P_imu[3];
};
class MARSVinsImplementation;
class GenericDriver;

class MARSVinsFacade {
  public:
    explicit MARSVinsFacade(std::unique_ptr<GenericDriver> driver,
                            const char* config_path, const char* output_path);
    ~MARSVinsFacade();
    void RunSingleImage();
    int GetPose(Pose* pose);
  private:
    std::unique_ptr<MARSVinsImplementation> impl_;
};
}
#endif
