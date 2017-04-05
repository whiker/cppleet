#! /bin/bash
run_app='CppleetExample'
if [ $# -gt 0 ]; then
    run_app=$1
fi

if [ ! -d 'include' ]; then
    mkdir include
fi
rm -rf include/run_app.h
echo '#ifndef CPPLEET_RUN_APP_H' > include/run_app.h
echo '#define CPPLEET_RUN_APP_H' >> include/run_app.h
echo "#define RUN_APP $run_app" >> include/run_app.h
echo "#endif" >> include/run_app.h
