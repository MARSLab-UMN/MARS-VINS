cmake_minimum_required(VERSION 2.8)
include_directories(core/include)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(example_app example_program/generic_driver.cpp example_program/vins_example_app.cpp)
if (ANDROID)
set (core_lib_dir ${CMAKE_CURRENT_SOURCE_DIR}/core/lib_android64/)
set (third_party_dir ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib_android64/)
elseif(${PLATFORM} STREQUAL "ARM64")
set (core_lib_dir ${CMAKE_CURRENT_SOURCE_DIR}/core/lib_arm64/)
set (third_party_dir ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib_arm64/)
elseif (${PLATFORM} STREQUAL "x86")
set (core_lib_dir ${CMAKE_CURRENT_SOURCE_DIR}/core/lib_x86/)
set (third_party_dir ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib_x86/)
endif()
set (core_lib_dir ${core_lib_dir}/${CAMERA_MODEL})
message(${core_lib_dir})
set (LIBS -L${core_lib_dir}
	  -L${third_party_dir}
	  -lmars_core
	  #           liblibpng.a
	  #           liblibwebp.a
	  #           libzlib.a
           -lopencv_contrib
           -lopencv_nonfree
           -lopencv_videostab
           -lopencv_photo
           -lopencv_objdetect
           -lopencv_video
           -lopencv_ml
           -lopencv_calib3d
           -lopencv_features2d
           -lopencv_highgui
           -lopencv_imgproc
           -lopencv_core)


target_link_libraries(example_app ${LIBS})


set (INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
INSTALL(DIRECTORY ${core_lib_dir}/ DESTINATION   ${INSTALL_DIR})
INSTALL(DIRECTORY ${third_party_dir} DESTINATION ${INSTALL_DIR})
