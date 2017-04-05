#! /bin/bash
clear

if [ ! -d 'ext/gtest' ]; then
    /bin/bash ./bin/fetch_gtest.sh 'https://github.com/google/googletest'
fi

/bin/bash ./bin/run_app.sh $@

if [ ! -d 'build' ]; then
    mkdir build
    cd build
    cmake ..
else
    cd build
fi
make
clear
./cppleet