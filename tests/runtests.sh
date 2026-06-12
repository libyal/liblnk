#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/liblnk/.libs/liblnk.1.dylib && test -f ./pylnk/.libs/pylnk.so
then
	install_name_tool -change /usr/local/lib/liblnk.1.dylib ${PWD}/liblnk/.libs/liblnk.1.dylib ./pylnk/.libs/pylnk.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

