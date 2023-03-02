# cmake -G Ninja \
#     -DCMAKE_BUILD_TYPE=RELEASE \
#     -DCMAKE_C_FLAGS_RELEASE=-O3 -DCMAKE_CXX_FLAGS_RELEASE=-O3 \
#     -DCMAKE_TOOLCHAIN_FILE=$TPU_SDK_PATH/cmake/toolchain-linux-uclibc.cmake \
#     -DTPU_SDK_PATH=$TPU_SDK_PATH \
#     -DOPENCV_PATH=$TPU_SDK_PATH/opencv \
#     ..
/host-tools/gcc/arm-cvitek-linux-uclibcgnueabihf/bin/arm-cvitek-linux-uclibcgnueabihf-g++ \
    -march=armv7-a -mfpu=neon -mfloat-abi=hard -marm -O3 \
    app_plate_det.cpp \
    -o demo \
    -L${TPU_SDK_PATH}/lib -L${TPU_SDK_PATH}/opencv/lib \
    -L`pwd`/build \
    -I${TPU_SDK_PATH}/include \
    -I${TPU_SDK_PATH}/opencv/include \
    -Wl,-rpath,${TPU_SDK_PATH}/lib:${TPU_SDK_PATH}/opencv/lib \
    -lcviruntime  -lcvikernel  -lopencv_core  -lopencv_imgcodecs -lclpr
