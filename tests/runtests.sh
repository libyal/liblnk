#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/liblnk/.libs/liblnk.1.dylib" ] && [ -f ./pylnk/.libs/pylnk.so ]
then
    install_name_tool -change /usr/local/lib/liblnk.1.dylib "${PWD}/liblnk/.libs/liblnk.1.dylib" ./pylnk/.libs/pylnk.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

