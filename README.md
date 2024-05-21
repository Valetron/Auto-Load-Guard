# Auto-Load-Guard

## Prerequirements
Conan
```
pip3 install --force-reinstall -v conan==1.64.0
```

GTest
```
conan install -if cmake --build=missing gtest/1.14.0
```

## Build
```
mkdir build ; cd build ; cmake -DCMAKE_BUILD_TYPE=Release .. ; cmake --build .
```
