#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/liblnk/.libs/liblnk.1.dylib && test -f ./pylnk/.libs/pylnk.so;
then
	install_name_tool -change /usr/local/lib/liblnk.1.dylib ${PWD}/liblnk/.libs/liblnk.1.dylib ./pylnk/.libs/pylnk.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

