# L-Bike

[![Ubuntu build](https://github.com/Alpha2Mao/L-Bike/actions/workflows/cmake.yml/badge.svg)](https://github.com/Alpha2Mao/L-Bike/actions/workflows/cmake.yml)
![GitHub](https://img.shields.io/github/license/Alpha2Mao/L-Bike)
![coverity](https://scan.coverity.com/projects/24516/badge.svg)

bicycle GPS position upload

## Introduction
## Get Started
### Build
```shell
cmake -Bbuild -Hiceoryx_meta -DCMAKE_PREFIX_PATH=$(PWD)/build/dependencies/ -DBUILD_TEST=ON -DINTROSPECTION=OFF -DBINDING_C=ON -DEXAMPLES=ON
```

