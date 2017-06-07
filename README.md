# MARS-VINS
## Copyright, Patent & License Notice
The MARS VINS software is copyrighted by the Regents of the University of
Minnesota. Use of the software may be covered by at least US patents and
applications 9,243,916, 9,658,07, 14/733,468 and 15/601,261 assigned to Regents
of the University of Minnesota. The software can be freely used for educational
and research purposes by non-profit institutions and US government agencies
only. Other organizations are allowed to use the MARS VINS software only for
evaluation purposes, and any further uses will require prior approval from
http://z.umn.edu/marsvins. The software may not be sold or redistributed
without prior approval. One may make copies of the software for their use
provided that the copies, are not sold or distributed, are used under the same
terms and conditions.

As unestablished research software, this code is provided on an "as is" basis
without warranty of any kind, either expressed or implied. The downloading, or
executing any part of this software constitutes an implicit agreement to these
terms. These terms and conditions are subject to change at any time without
prior notice.

============================================================================
If you want to use this library in your research, please cite:

1. M. K. Paul, K. Wu, J. Hesch, E. Nerurkar, and S. I. Roumeliotis, 
“A Comparative Analysis of Tightly-coupled Monocular, Binocular, and Stereo 
VINS”, International Conference on Robotics and Automation (ICRA), 
Singapore, May 29-Jun. 3, 2017.
============================================================================

## Quick Install Instructions
Follow these steps to build an example program on linux (built for ubuntu 14.04)
This program will run stereo vins on a given dataset (see https://drive.google.com/drive/folders/0B599VDE8UJvURjZOazBpak10bFk for some example datasets and config file).
```
cd MARS-VINS
mkdir build
cd build
cmake ..
make example_app -DPLATFORM=x86 -DCAMERA_MODEL=equidistant
make install
./example_app <config file> <output file> <imu data file> <left image directory> <right image directory>
```
## Custom install
The following options for MARS-VINS are currently available:
Platforms:

Linux (x86)

Linux (arm64)

Android (arm64)

In addition to these platforms, 3 camera models:

equidistant

fov 

radial_tangential

example_app can be compiled for any of the above combinations in the following
fashion.

For linux builds:
```
cd MARS-VINS
cd build
cmake -DPLATFORM=<x86 or arm64> -DCAMERA_MODEL=<equidistant or fov or  or radial_tangential> ..
make example_app
make install
./example_app <config file> <output file> <imu data file> <left image directory> <right image directory>
```

For android builds (adb required to interface with android, android device should be rooted):
```
cd MARS-VINS
cd build_android
## edit cmake_android.sh to select your camera model
sh cmake_android.sh
make example_app
make install
adb push ./example_app <directory on android device>
adb shell
cd <directory on android device>
./example_app <config file> <output file> <imu data file> <left image directory> <right image directory>
```
