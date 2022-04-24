# L-Bike

[![Ubuntu build](https://github.com/Alpha2Mao/L-Bike/actions/workflows/cmake.yml/badge.svg)](https://github.com/Alpha2Mao/L-Bike/actions/workflows/cmake.yml)
![GitHub](https://img.shields.io/github/license/Alpha2Mao/L-Bike)
![coverity](https://scan.coverity.com/projects/24516/badge.svg)

bicycle GPS position upload

## Introduction
## Get Started
- ###Build
```shell
cmake -Bbuild -Hiceoryx_meta -DCMAKE_PREFIX_PATH=$(PWD)/build/dependencies/ -DBUILD_TEST=ON -DINTROSPECTION=OFF -DBINDING_C=ON -DEXAMPLES=ON
```
- ### Cross build for raspberry
```shell
sudo apt install crossbuild-essential-arm64
```


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
