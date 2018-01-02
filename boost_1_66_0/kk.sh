set -ix

    # "/home/richard/lively/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-g++"   -O3 -finline-functions -Wno-inline -Wall -fPIC  -DBOOST_ALL_NO_LIB=1 -DBOOST_ATOMIC_DYN_LINK=1 -DBOOST_ATOMIC_SOURCE -DNDEBUG  -I"." -I"../../external/stlport/stlport" -c -o "bin.v2/libs/atomic/build/gcc-gnu-4.7/release/threadapi-pthread/threading-multi/lockpool.o" "libs/atomic/src/lockpool.cpp"

/home/richard/lively/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-g++   -I/home/richard/lively/bionic/libstdc++/include -O3 -finline-functions -Wno-inline -Wall -fPIC  -DBOOST_ALL_NO_LIB=1 -DBOOST_ATOMIC_DYN_LINK=1 -DBOOST_ATOMIC_SOURCE -DNDEBUG -D_STLP_USE_DYNAMIC_LIB=1  -I. -I/home/richard/lively/external/stlport/stlport -c -o bin.v2/libs/atomic/build/gcc-gnu-4.7/release/stdlib-stlport-5.0/target-os-android/threadapi-pthread/threading-multi/lockpool.o  libs/atomic/src/lockpool.cpp
