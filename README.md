# L-Bike

[![Ubuntu build](https://github.com/Alpha2Mao/L-Bike/actions/workflows/cmake.yml/badge.svg)](https://github.com/Alpha2Mao/L-Bike/actions/workflows/cmake.yml)
![GitHub](https://img.shields.io/github/license/Alpha2Mao/L-Bike)
![coverity](https://scan.coverity.com/projects/24516/badge.svg)

## Introduction
This application is used upload vehicle data to TSP platform based on Raspberry Pi 4B, the transport protocols is mqtt.

## Get Started
- ###Build
```shell
cmake -Bbuild -Hiceoryx_meta -DCMAKE_PREFIX_PATH=$(PWD)/build/dependencies/ -DBUILD_TEST=ON -DINTROSPECTION=OFF -DBINDING_C=ON -DEXAMPLES=ON
```
- ### Cross build for raspberry
```shell
sudo apt install crossbuild-essential-arm64
cmake -B build_aarch64 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./cmake/raspberrypi-toolchain.cmake
cd build_aarch64
make
make package # L_Bike-0.0.1-Linux.deb deb格式安装包打包
# 或使用如下命令打包
cpack -G DEB
# rpm格式包打包
cpack -G RPM
```
- ### Supported Platforms
| Operating System |              supports              |
|------------------|:----------------------------------:|
| Linux            |                yes                 |
| MacOS            |                yes                 |
| Raspberry Pi     |                yes                 |
| Windows 10       |   no, planned for implementation   |
| QNX              | no, not planned for implementation |



## Process
- [x] Project init
- [x] Add program cross build
- [ ] add mqtt
- [ ] implement thread pool

## References
- [Raspberry Pi Documentation](https://www.raspberrypi.com/documentation/computers/linux_kernel.html#building-the-kernel-locally)

## Dependency
- https://github.com/eclipse/paho.mqtt.cpp
- 

## Study Notes
- [CMakePackageConfigHelpers](https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html?highlight=configure_package_config_file#command:configure_package_config_file)
- [cmake-packages](https://cmake.org/cmake/help/v3.0/manual/cmake-packages.7.html?highlight=write_basic_package_version_file#package-configuration-file)
