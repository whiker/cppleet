#! /bin/bash
back_dir=`pwd`
work_dir="fetch_gtest_tmp"

rm -rf $work_dir
mkdir $work_dir
cd $work_dir
git clone $1 -b master
gtest_dir=`ls`
cd $gtest_dir

if [ ! -d 'googletest' ]; then
    echo 'lost dir: googletest'
    exit -1
fi
if [ ! -d 'googletest/include/gtest' ]; then
    echo 'lost dir: include/gtest'
    exit -1
fi

cd googletest
mkdir build
cd build
cmake ..
make
if [ ! -f 'libgtest.a' ]; then
    echo 'make error'
    exit -1
fi

mkdir -p $back_dir/ext/gtest/lib
cp libgtest.a $back_dir/ext/gtest/lib

mkdir -p $back_dir/ext/gtest/include
cd ..
cp -r include/gtest $back_dir/ext/gtest/include

cd $back_dir
rm -rf $work_dir
