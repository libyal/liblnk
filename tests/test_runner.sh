#!/bin/bash
# Bash functions to run an executable for testing.
#
# Version: 20160423
#
# When CHECK_WITH_GDB is set to a non-empty value the test executable
# is run with gdb, otherwise it is run without.
#
# When CHECK_WITH_STDERR is set to a non-empty value the test executable
# is run with error output to stderr.
#
# When CHECK_WITH_VALGRIND is set to a non-empty value the test executable
# is run with valgrind, otherwise it is run without.

EXIT_SUCCESS=0;
EXIT_FAILURE=1;
EXIT_IGNORE=77;

# Checks the availability of a binary and exits if not available.
#
# Arguments:
#   a string containing the name of the binary
#
assert_availability_binary()
{
	local BINARY=$1;

	which ${BINARY} > /dev/null 2>&1;
	if test $? -ne ${EXIT_SUCCESS};
	then
		echo "Missing binary: ${BINARY}";
		echo "";

		exit ${EXIT_FAILURE};
	fi
}

# Checks if the input directory is in the ignore list.
#
# Arguments:
#   a string containing the path of the test input directory
#   a string containing space separated ignore list
#
# Returns:
#   an integer containing the exit status to indicate the input directory
#   was found in the ignore list.
#
check_for_directory_in_ignore_list()
{
	local INPUT_DIRECTORY=$1;
	local IGNORE_LIST=$@;

	local INPUT_BASENAME=`basename ${INPUT_DIRECTORY}`;

	for LIST_ELEMENT in `echo "${IGNORE_LIST}" | tr ' ' '\n'`;
	do
		if test "${LIST_ELEMENT}" = "${INPUT_BASENAME}";
		then
			return ${EXIT_SUCCESS};
		fi
	done
	return ${EXIT_FAILURE};
}

# Searches for the binary variant of the executable in case the test executable
# refers to a libtool shell script.
#
# Arguments:
#   a string containing the path of the test executable
#
# Returns:
#   a string containing the path of the binary variant of the test executable
#
find_binary_executable()
{
	local TEST_EXECUTABLE=$1;

	TEST_EXECUTABLE=`readlink -f ${TEST_EXECUTABLE}`;

	# Note that the behavior of `file -bi` is not helpful on Mac OS X.
	local EXECUTABLE_TYPE=`file -b ${TEST_EXECUTABLE}`;

	# Check if the test executable is a libtool shell script.
	# Linux: POSIX shell script, ASCII text executable, with very long lines
	# Mac OS X: POSIX shell script text executable
	echo "${EXECUTABLE_TYPE}" | grep "POSIX shell script" > /dev/null 2>&1;
	RESULT=$?;

	if test ${RESULT} -eq ${EXIT_SUCCESS};
	then
		local TEST_EXECUTABLE_BASENAME=`basename ${TEST_EXECUTABLE}`;
		local TEST_EXECUTABLE_DIRNAME=`dirname ${TEST_EXECUTABLE}`;

		TEST_EXECUTABLE="${TEST_EXECUTABLE_DIRNAME}/.libs/${TEST_EXECUTABLE_BASENAME}";

		if test -x ${TEST_EXECUTABLE};
		then
			# Note that the behavior of `file -bi` is not helpful on Mac OS X.
			EXECUTABLE_TYPE=`file -b ${TEST_EXECUTABLE}`;

			# Linux: ELF 64-bit LSB executable, x86-64, ...
			# Mac OS X: Mach-O 64-bit executable x86_64
			echo "${EXECUTABLE_TYPE}" | grep "executable" > /dev/null 2>&1;
			RESULT=$?;

			if test ${RESULT} -ne ${EXIT_SUCCESS};
			then
				echo "Invalid test executable: ${TEST_EXECUTABLE}";

				exit ${EXIT_FAILURE};
			fi
		fi
	fi
	echo ${TEST_EXECUTABLE};
}

# Searches for the path to the binary variant of the library.
#
# Arguments:
#   a string containing the path of the test executable
#
# Returns:
#   a string containing the path of the binary variant of the library.
#
find_binary_library_path()
{
	local TEST_EXECUTABLE=$1;
	local LIBRARY_NAME="${TEST_EXECUTABLE}";

	echo ${LIBRARY_NAME} | grep 'tools' > /dev/null 2>&1;

	if test $? -eq ${EXIT_SUCCESS};
	then
		LIBRARY_NAME=`dirname ${LIBRARY_NAME}`;
		LIBRARY_NAME=`dirname ${LIBRARY_NAME}`;
		LIBRARY_NAME=`basename ${LIBRARY_NAME} | sed 's/\(.*\)tools$/lib\1/'`;
	else
		LIBRARY_NAME=`basename ${LIBRARY_NAME} | sed 's/^py//' | sed 's/^\([^_]*\)_test_.*$/lib\1/'`;
	fi
	TEST_EXECUTABLE=`dirname ${TEST_EXECUTABLE}`;
	TEST_EXECUTABLE=`dirname ${TEST_EXECUTABLE}`;
	TEST_EXECUTABLE=`dirname ${TEST_EXECUTABLE}`;

	local LIBRARY_PATH="${TEST_EXECUTABLE}/${LIBRARY_NAME}/.libs";

	if ! test -d "${LIBRARY_PATH}";
	then
		LIBRARY_PATH="../${LIBRARY_NAME}/.libs";
	fi
	echo "${LIBRARY_PATH}";
}

# Searches for the path to the binary variant of the Python module
#
# Globals:
#   PYTHON_VERSION
#
# Arguments:
#   a string containing the path of the test executable
#
# Returns:
#   a string containing the path of the binary variant of the Python module
#
find_binary_python_module_path()
{
	local TEST_EXECUTABLE=$1;

	local PYTHON_MODULE_NAME=`basename ${TEST_EXECUTABLE} | sed 's/^py\(.*\)_test_.*$/py\1/'`;

	TEST_EXECUTABLE=`dirname ${TEST_EXECUTABLE}`;
	TEST_EXECUTABLE=`dirname ${TEST_EXECUTABLE}`;
	TEST_EXECUTABLE=`dirname ${TEST_EXECUTABLE}`;

	PYTHON_VERSION=`echo ${PYTHON_VERSION} | cut -c1`;

	local PYTHON_MODULE_PATH="${TEST_EXECUTABLE}/${PYTHON_MODULE_NAME}-python${PYTHON_VERSION}/.libs";

	if ! test -d "${PYTHON_MODULE_PATH}";
	then
		PYTHON_MODULE_PATH="../${PYTHON_MODULE_NAME}-python${PYTHON_VERSION}/.libs";
	fi
	if ! test -d "${PYTHON_MODULE_PATH}";
	then
		PYTHON_MODULE_PATH="${TEST_EXECUTABLE}/${PYTHON_MODULE_NAME}/.libs";
	fi
	if ! test -d "${PYTHON_MODULE_PATH}";
	then
		PYTHON_MODULE_PATH="../${PYTHON_MODULE_NAME}/.libs";
	fi
	echo "${PYTHON_MODULE_PATH}";
}

# Determines the test option file.
#
# Arguments:
#   a string containing the path of the test set directory
#   a string containing the path of the test input file
#   a string containing the name of the option set
#
# Returns:
#   a string containing the test input files
#
get_testion_option_file()
{
	local TEST_SET_DIRECTORY=$1;
	local INPUT_FILE=$2;
	local OPTION_SET=$3;

	local INPUT_NAME=`basename "${INPUT_FILE}"`;
	local OPTION_FILE="${TEST_SET_DIRECTORY}/${INPUT_NAME}.${OPTION_SET}";

	echo "${OPTION_FILE}";
}

# Determines the test profile directory.
# The directory is created if it does not exist.
#
# Arguments:
#   a string containing the path of the test input directory
#   a string containing the name of the test profile
#
# Returns:
#   a string containing the path of the test profile directory
#
get_test_profile_directory()
{
	local TEST_INPUT_DIRECTORY=$1;
	local TEST_PROFILE=$2;

	local TEST_PROFILE_DIRECTORY="${TEST_INPUT_DIRECTORY}/.${TEST_PROFILE}";

	if ! test -d "${TEST_PROFILE_DIRECTORY}";
	then
		mkdir "${TEST_PROFILE_DIRECTORY}";
	fi
	echo "${TEST_PROFILE_DIRECTORY}";
}

# Determines the test set directory.
# The directory is created if it does not exist.
#
# Arguments:
#   a string containing the path of the test profile directory
#   a string containing the path of the test set input directory
#
# Returns:
#   a string containing the path of the test set directory
#
get_test_set_directory()
{
	local TEST_PROFILE_DIRECTORY=$1;
	local TEST_SET_INPUT_DIRECTORY=$2;

	local TEST_SET=`basename ${TEST_SET_INPUT_DIRECTORY}`;
	local TEST_SET_DIRECTORY="${TEST_PROFILE_DIRECTORY}/${TEST_SET}";

	if ! test -d "${TEST_SET_DIRECTORY}";
	then
		mkdir "${TEST_SET_DIRECTORY}";
	fi
	echo "${TEST_SET_DIRECTORY}";
}

# Reads the test profile ignore file if it exists.
#
# Arguments:
#   a string containing the path of the test profile directory
#
# Returns:
#   a string containing a space separated ignore list
#
read_ignore_list()
{
	local TEST_PROFILE_DIRECTORY=$1;
	local IGNORE_FILE="${TEST_PROFILE_DIRECTORY}/ignore";
	local IGNORE_LIST="";

	if test -f "${IGNORE_FILE}";
	then
		IGNORE_LIST=`cat ${IGNORE_FILE} | sed '/^#/d'`;
	fi
	echo ${IGNORE_LIST};
}

# Reads the test set option file.
#
# Arguments:
#   a string containing the path of the test set directory
#   a string containing the path of the test input file
#   a string containing the name of the option set
#
# Returns:
#   a string containing the ignore list
#
read_option_file()
{
	local TEST_SET_DIRECTORY=$1;
	local INPUT_FILE=$2;
	local OPTION_SET=$3;

	local OPTION_FILE=$(get_testion_option_file "${TEST_SET_DIRECTORY}" "${INPUT_FILE}" "${OPTION_SET}");

	local OPTIONS=()
	local OPTIONS_STRING=`cat "${OPTION_FILE}" | head -n 1 | sed 's/[\r\n]*$//'`;

	echo "${OPTIONS_STRING}";
}

# Runs the test with optional arguments.
#
# Globals:
#   CHECK_WITH_GDB
#   CHECK_WITH_STDERR
#   CHECK_WITH_VALGRIND
#   PYTHON_VERSION
#
# Arguments:
#   a string containing the path of the test executable
#   an array containing the arguments for the test executable
#
# Returns:
#   an integer containg the exit status of the test executable
#
run_test_with_arguments()
{
	local TEST_EXECUTABLE=$1;
	shift 1;
	local ARGUMENTS=$@;

	if ! test -f ${TEST_EXECUTABLE};
	then
		echo "Missing test executable: ${TEST_EXECUTABLE}";
		echo "";

		return ${EXIT_FAILURE};
	fi
	local PLATFORM=`uname -s`;

	# Note that the behavior of `file -bi` is not helpful on Mac OS X.
	local EXECUTABLE_TYPE=`file -b ${TEST_EXECUTABLE}`;

	# Check if the test executable is a Python script.
	# Linux: Python script, ASCII text executable
	# Mac OS X: a python script text executable
	echo "${EXECUTABLE_TYPE}" | grep -i "python script" > /dev/null 2>&1;
	local IS_PYTHON_SCRIPT=$?;

	if test ${IS_PYTHON_SCRIPT} -eq 0;
	then
		local PYTHON=`which python${PYTHON_VERSION} 2> /dev/null`;

		if ! test -x ${PYTHON};
		then
			echo "Missing executable: ${PYTHON}";

			exit ${EXIT_FAILURE};
		fi
	fi
	local RESULT=0;

	if ! test -z ${CHECK_WITH_GDB};
	then
		local TEST_EXECUTABLE=$( find_binary_executable ${TEST_EXECUTABLE} );
		local LIBRARY_PATH=$( find_binary_library_path ${TEST_EXECUTABLE} );
		local PYTHON_MODULE_PATH=$( find_binary_python_module_path ${TEST_EXECUTABLE} );

		if test "${PLATFORM}" = "Darwin";
		then
			if test ${IS_PYTHON_SCRIPT} -eq 0;
			then
				DYLD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" gdb -ex "set non-stop on" -ex "run" -ex "quit" --args "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]};
				RESULT=$?;
			else
				DYLD_LIBRARY_PATH="${LIBRARY_PATH}" gdb -ex "set non-stop on" -ex "run" -ex "quit" --args "${TEST_EXECUTABLE}" ${ARGUMENTS[@]};
				RESULT=$?;
			fi
		else
			if test ${IS_PYTHON_SCRIPT} -eq 0;
			then
				LD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" gdb -ex "set non-stop on" -ex "run" -ex "quit" --args "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]};
				RESULT=$?;
			else
				LD_LIBRARY_PATH="${LIBRARY_PATH}" gdb -ex "set non-stop on" -ex "run" -ex "quit" --args "${TEST_EXECUTABLE}" ${ARGUMENTS[@]};
				RESULT=$?;
			fi
		fi

	elif ! test -z ${CHECK_WITH_VALGRIND};
	then
		local TEST_EXECUTABLE=$( find_binary_executable ${TEST_EXECUTABLE} );
		local LIBRARY_PATH=$( find_binary_library_path ${TEST_EXECUTABLE} );
		local PYTHON_MODULE_PATH=$( find_binary_python_module_path ${TEST_EXECUTABLE} );

		local VALGRIND_LOG="valgrind.log-$$";
		local VALGRIND_OPTIONS=("--tool=memcheck" "--leak-check=full" "--show-leak-kinds=definite,indirect,possible" "--track-origins=yes" "--log-file=${VALGRIND_LOG}");

		if test "${PLATFORM}" = "Darwin";
		then
			if test ${IS_PYTHON_SCRIPT} -eq 0;
			then
				DYLD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" valgrind ${VALGRIND_OPTIONS[@]} "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]};
				RESULT=$?;
			else
				DYLD_LIBRARY_PATH="${LIBRARY_PATH}" valgrind ${VALGRIND_OPTIONS[@]} "${TEST_EXECUTABLE}" ${ARGUMENTS[@]};
				RESULT=$?;
			fi
		else
			if test ${IS_PYTHON_SCRIPT} -eq 0;
			then
				LD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" valgrind ${VALGRIND_OPTIONS[@]} "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]};
				RESULT=$?;
			else
				LD_LIBRARY_PATH="${LIBRARY_PATH}" valgrind ${VALGRIND_OPTIONS[@]} "${TEST_EXECUTABLE}" ${ARGUMENTS[@]};
				RESULT=$?;
			fi
		fi
		if test ${RESULT} -eq ${EXIT_SUCCESS};
		then
			grep "All heap blocks were freed -- no leaks are possible" ${VALGRIND_LOG} > /dev/null 2>&1;

			if test $? -ne ${EXIT_SUCCESS};
			then
				# Ignore "still reachable"
				# Also see: http://valgrind.org/docs/manual/faq.html#faq.deflost

				grep "definitely lost: 0 bytes in 0 blocks" ${VALGRIND_LOG} > /dev/null 2>&1;
				RESULT_DIRECTLY_LOST=$?;

				grep "indirectly lost: 0 bytes in 0 blocks" ${VALGRIND_LOG} > /dev/null 2>&1;
				RESULT_INDIRECTLY_LOST=$?;

				grep "possibly lost: 0 bytes in 0 blocks" ${VALGRIND_LOG} > /dev/null 2>&1;
				RESULT_POSSIBLY_LOST=$?;

				grep "suppressed: 0 bytes in 0 blocks" ${VALGRIND_LOG} > /dev/null 2>&1;
				RESULT_SUPPRESSED=$?;

				if test ${RESULT_DIRECTLY_LOST} -ne ${EXIT_SUCCESS} || test ${RESULT_INDIRECTLY_LOST} -ne ${EXIT_SUCCESS} || test ${RESULT_POSSIBLY_LOST} -ne ${EXIT_SUCCESS} || test ${RESULT_SUPPRESSED} -ne ${EXIT_SUCCESS};
				then
					echo "Memory leakage detected.";
					cat ${VALGRIND_LOG};

					RESULT=${EXIT_FAILURE};
				fi
			fi
		fi
		rm -f ${VALGRIND_LOG};

	elif test ${IS_PYTHON_SCRIPT} -eq 0;
	then
		if ! test -f "${TEST_EXECUTABLE}";
		then
			echo "Invalid test Python script: ${TEST_EXECUTABLE}";
			echo "";

			return ${EXIT_FAILURE};
		fi
		local LIBRARY_PATH=$( find_binary_library_path ${TEST_EXECUTABLE} );
		local PYTHON_MODULE_PATH=$( find_binary_python_module_path ${TEST_EXECUTABLE} );

		if test "${PLATFORM}" = "Darwin";
		then
			if ! test -z ${CHECK_WITH_STDERR};
			then
				DYLD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]};
				RESULT=$?;
			else
				DYLD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} 2> /dev/null;
				RESULT=$?;
			fi
		else
			if ! test -z ${CHECK_WITH_STDERR};
			then
				LD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]};
				RESULT=$?;
			else
				LD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} 2> /dev/null;
				RESULT=$?;
			fi
		fi
	else
		if ! test -x "${TEST_EXECUTABLE}";
		then
			echo "Invalid test executable: ${TEST_EXECUTABLE}";
			echo "";

			return ${EXIT_FAILURE};
		fi

		if ! test -z ${CHECK_WITH_STDERR};
		then
			${TEST_EXECUTABLE} ${ARGUMENTS[@]};
			RESULT=$?;
		else
			${TEST_EXECUTABLE} ${ARGUMENTS[@]} 2> /dev/null;
			RESULT=$?;
		fi
	fi
	return ${RESULT};
}

# Runs the test with an input file and optional arguments.
#
# Globals:
#   CHECK_WITH_GDB
#   CHECK_WITH_STDERR
#   CHECK_WITH_VALGRIND
#   PYTHON_VERSION
#
# Arguments:
#   a string containing the path of the test executable
#   a string containing the path of the test input file
#   an array containing the arguments for the test executable
#
# Returns:
#   an integer containg the exit status of the test executable
#
run_test_with_input_and_arguments()
{
	local TEST_EXECUTABLE=$1;
	local INPUT_FILE=$2;
	shift 2;
	local ARGUMENTS=$@;

	if ! test -f ${TEST_EXECUTABLE};
	then
		echo "Missing test executable: ${TEST_EXECUTABLE}";
		echo "";

		return ${EXIT_FAILURE};
	fi
	local PLATFORM=`uname -s`;

	# Note that the behavior of `file -bi` is not helpful on Mac OS X.
	local EXECUTABLE_TYPE=`file -b ${TEST_EXECUTABLE}`;

	# Check if the test executable is a Python script.
	# Linux: Python script, ASCII text executable
	# Mac OS X: a python script text executable
	echo "${EXECUTABLE_TYPE}" | grep -i "python script" > /dev/null 2>&1;
	local IS_PYTHON_SCRIPT=$?;

	if test ${IS_PYTHON_SCRIPT} -eq 0;
	then
		local PYTHON=`which python${PYTHON_VERSION} 2> /dev/null`;

		if ! test -x ${PYTHON};
		then
			echo "Missing executable: ${PYTHON}";

			exit ${EXIT_FAILURE};
		fi
	fi
	local RESULT=0;

	if ! test -z ${CHECK_WITH_GDB};
	then
		local TEST_EXECUTABLE=$( find_binary_executable ${TEST_EXECUTABLE} );
		local LIBRARY_PATH=$( find_binary_library_path ${TEST_EXECUTABLE} );
		local PYTHON_MODULE_PATH=$( find_binary_python_module_path ${TEST_EXECUTABLE} );

		if test "${PLATFORM}" = "Darwin";
		then
			if test ${IS_PYTHON_SCRIPT} -eq 0;
			then
				DYLD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" gdb -ex "set non-stop on" -ex "run" -ex "quit" --args "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} "${INPUT_FILE}";
				RESULT=$?;
			else
				DYLD_LIBRARY_PATH="${LIBRARY_PATH}" gdb -ex "set non-stop on" -ex "run" -ex "quit" --args "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} "${INPUT_FILE}";
				RESULT=$?;
			fi
		else
			if test ${IS_PYTHON_SCRIPT} -eq 0;
			then
				LD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" gdb -ex "set non-stop on" -ex "run" -ex "quit" --args "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} "${INPUT_FILE}";
				RESULT=$?;
			else
				LD_LIBRARY_PATH="${LIBRARY_PATH}" gdb -ex "set non-stop on" -ex "run" -ex "quit" --args "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} "${INPUT_FILE}";
				RESULT=$?;
			fi
		fi

	elif ! test -z ${CHECK_WITH_VALGRIND};
	then
		local TEST_EXECUTABLE=$( find_binary_executable ${TEST_EXECUTABLE} );
		local LIBRARY_PATH=$( find_binary_library_path ${TEST_EXECUTABLE} );
		local PYTHON_MODULE_PATH=$( find_binary_python_module_path ${TEST_EXECUTABLE} );

		local VALGRIND_LOG="valgrind.log-$$";
		local VALGRIND_OPTIONS=("--tool=memcheck" "--leak-check=full" "--show-leak-kinds=definite,indirect,possible" "--track-origins=yes" "--log-file=${VALGRIND_LOG}");

		if test "${PLATFORM}" = "Darwin";
		then
			if test ${IS_PYTHON_SCRIPT} -eq 0;
			then
				DYLD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" valgrind ${VALGRIND_OPTIONS[@]} "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} "${INPUT_FILE}";
				RESULT=$?;
			else
				DYLD_LIBRARY_PATH="${LIBRARY_PATH}" valgrind ${VALGRIND_OPTIONS[@]} "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} "${INPUT_FILE}";
				RESULT=$?;
			fi
		else
			if test ${IS_PYTHON_SCRIPT} -eq 0;
			then
				LD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" valgrind ${VALGRIND_OPTIONS[@]} "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} "${INPUT_FILE}";
				RESULT=$?;
			else
				LD_LIBRARY_PATH="${LIBRARY_PATH}" valgrind ${VALGRIND_OPTIONS[@]} "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} "${INPUT_FILE}";
				RESULT=$?;
			fi
		fi
		if test ${RESULT} -eq ${EXIT_SUCCESS};
		then
			grep "All heap blocks were freed -- no leaks are possible" ${VALGRIND_LOG} > /dev/null 2>&1;

			if test $? -ne ${EXIT_SUCCESS};
			then
				# Ignore "still reachable"
				# Also see: http://valgrind.org/docs/manual/faq.html#faq.deflost

				grep "definitely lost: 0 bytes in 0 blocks" ${VALGRIND_LOG} > /dev/null 2>&1;
				RESULT_DIRECTLY_LOST=$?;

				grep "indirectly lost: 0 bytes in 0 blocks" ${VALGRIND_LOG} > /dev/null 2>&1;
				RESULT_INDIRECTLY_LOST=$?;

				grep "possibly lost: 0 bytes in 0 blocks" ${VALGRIND_LOG} > /dev/null 2>&1;
				RESULT_POSSIBLY_LOST=$?;

				grep "suppressed: 0 bytes in 0 blocks" ${VALGRIND_LOG} > /dev/null 2>&1;
				RESULT_SUPPRESSED=$?;

				if test ${RESULT_DIRECTLY_LOST} -ne ${EXIT_SUCCESS} || test ${RESULT_INDIRECTLY_LOST} -ne ${EXIT_SUCCESS} || test ${RESULT_POSSIBLY_LOST} -ne ${EXIT_SUCCESS} || test ${RESULT_SUPPRESSED} -ne ${EXIT_SUCCESS};
				then
					echo "Memory leakage detected.";
					cat ${VALGRIND_LOG};

					RESULT=${EXIT_FAILURE};
				fi
			fi
		fi
		rm -f ${VALGRIND_LOG};

	elif test ${IS_PYTHON_SCRIPT} -eq 0;
	then
		if ! test -f "${TEST_EXECUTABLE}";
		then
			echo "Invalid test Python script: ${TEST_EXECUTABLE}";
			echo "";

			return ${EXIT_FAILURE};
		fi
		local LIBRARY_PATH=$( find_binary_library_path ${TEST_EXECUTABLE} );
		local PYTHON_MODULE_PATH=$( find_binary_python_module_path ${TEST_EXECUTABLE} );

		if test "${PLATFORM}" = "Darwin";
		then
			if ! test -z ${CHECK_WITH_STDERR};
			then
				DYLD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} "${INPUT_FILE}";
				RESULT=$?;
			else
				DYLD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} "${INPUT_FILE}" 2> /dev/null;
				RESULT=$?;
			fi
		else
			if ! test -z ${CHECK_WITH_STDERR};
			then
				LD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} "${INPUT_FILE}";
				RESULT=$?;
			else
				LD_LIBRARY_PATH="${LIBRARY_PATH}" PYTHONPATH="${PYTHON_MODULE_PATH}" "${PYTHON}" "${TEST_EXECUTABLE}" ${ARGUMENTS[@]} "${INPUT_FILE}" 2> /dev/null;
				RESULT=$?;
			fi
		fi
	else
		if ! test -x "${TEST_EXECUTABLE}";
		then
			echo "Invalid test executable: ${TEST_EXECUTABLE}";
			echo "";

			return ${EXIT_FAILURE};
		fi

		if ! test -z ${CHECK_WITH_STDERR};
		then
			${TEST_EXECUTABLE} ${ARGUMENTS[@]} "${INPUT_FILE}";
			RESULT=$?;
		else
			${TEST_EXECUTABLE} ${ARGUMENTS[@]} "${INPUT_FILE}" 2> /dev/null;
			RESULT=$?;
		fi
	fi
	return ${RESULT};
}

# Runs the test on the input file.
#
# Note that this function is not intended to be directly invoked
# from outside the test runner script.
#
# Arguments:
#   a string containing the path of the test set directory
#   a string containing the description of the test
#   a string containing the test mode
#   a string containing the name of the option set
#   a string containing the path of the test executable
#   a string containing the path of the test input file
#   an array containing the arguments for the test executable
#
# Returns:
#   an integer containg the exit status of the test executable
#
run_test_on_input_file()
{
	local TEST_SET_DIRECTORY=$1;
	local TEST_DESCRIPTION=$2;
	local TEST_MODE=$3;
	local OPTION_SET=$4;
	local TEST_EXECUTABLE=$5;
	local INPUT_FILE=$6;
	shift 6;
	local ARGUMENTS=$@;

	local INPUT_NAME=`basename "${INPUT_FILE}"`;
	local OPTIONS=();
	local TEST_OUTPUT="${INPUT_NAME}";

	if ! test -z "${OPTION_SET}";
	then
		OPTIONS_STRING=$(read_option_file "${TEST_SET_DIRECTORY}" "${INPUT_FILE}" "${OPTION_SET}");
		IFS=" " read -a OPTIONS <<< "${OPTIONS_STRING}";

		TEST_OUTPUT="${INPUT_NAME}-${OPTION_SET}";
	fi

	local TMPDIR="tmp$$";
	local RESULT=0;

	rm -rf ${TMPDIR};
	mkdir ${TMPDIR};

	if test "${TEST_MODE}" = "with_callback";
	then
		test_callback "${TMPDIR}" "${TEST_SET_DIRECTORY}" "${TEST_OUTPUT}" "${TEST_EXECUTABLE}" "${TEST_INPUT}" ${ARGUMENTS[@]} ${OPTIONS[@]};
		RESULT=$?;

	elif test "${TEST_MODE}" = "with_stdout_reference";
	then
		TEST_EXECUTABLE=`readlink -f ${TEST_EXECUTABLE}`;

		if ! test -x ${TEST_EXECUTABLE};
		then
			echo "Invalid test executable: ${TEST_EXECUTABLE}";
			echo "";

			return ${EXIT_FAILURE};
		fi
		local INPUT_FILE_FULL_PATH=`readlink -f "${INPUT_FILE}"`;
		local TEST_LOG="${TEST_OUTPUT}.log";

		(cd ${TMPDIR} && run_test_with_input_and_arguments "${TEST_EXECUTABLE}" "${INPUT_FILE_FULL_PATH}" ${ARGUMENTS[@]} ${OPTIONS[@]} | sed '1,2d' > "${TEST_LOG}");
		RESULT=$?;

		local TEST_RESULTS="${TMPDIR}/${TEST_LOG}";
		local STORED_TEST_RESULTS="${TEST_SET_DIRECTORY}/${TEST_LOG}.gz";

		if test -f "${STORED_TEST_RESULTS}";
		then
			# Using zcat here since zdiff has issues on Mac OS X.
			# Note that zcat on Mac OS X requires the input from stdin.
			zcat < "${STORED_TEST_RESULTS}" | diff "${TEST_RESULTS}" -;
			RESULT=$?;
		else
			gzip "${TEST_RESULTS}";

			mv "${TEST_RESULTS}.gz" ${TEST_SET_DIRECTORY};
		fi

	else
		run_test_with_input_and_arguments "${TEST_EXECUTABLE}" "${INPUT_FILE}" ${ARGUMENTS[@]} ${OPTIONS[@]};
		RESULT=$?;
	fi

	rm -rf ${TMPDIR};

	if test -z "${OPTION_SET}";
	then
		echo -n "Testing ${TEST_DESCRIPTION} with input: ${INPUT_FILE}";
	else
		echo -n "Testing ${TEST_DESCRIPTION} with option: ${OPTION_SET} and input: ${INPUT_FILE}";
	fi

	if test ${RESULT} -ne ${EXIT_SUCCESS};
	then
		echo " (FAIL)";
	else
		echo " (PASS)";
	fi
	return ${RESULT};
}

# Runs the test on the input directory.
#
# Globals:
#   CHECK_WITH_GDB
#   CHECK_WITH_VALGRIND
#
# Arguments:
#   a string containing the name of the test profile
#   a string containing the description of the test
#   a string containing the test mode, supported tests modes are:
#     default: the test executable should be be run without any test
#              conditions.
#     with_callback: the test executable should be run and the callback
#                    function should be called afterwards. The name of the
#                    callback function is "test_callback".
#     with_stdout_reference: the test executable should be run and its output
#                            to stdout, except for the first 2 lines, should
#                            be compared to a reference file, if available.
#     Note the globals override the test mode.
#   a string containing the name of the option set
#   a string containing the path of the test executable
#   a string containing the path of the test input directory
#   a string containing the input glob
#   an array containing the arguments for the test executable
#
# Returns:
#   an integer containg the exit status of the test executable
#
run_test_on_input_directory()
{
	local TEST_PROFILE=$1;
	local TEST_DESCRIPTION=$2;
	local TEST_MODE=$3;
	local OPTION_SETS=$4;
	local TEST_EXECUTABLE=$5;
	local TEST_INPUT_DIRECTORY=$6;
	local INPUT_GLOB=$7;
	shift 7;
	local ARGUMENTS=$@;

	assert_availability_binary cat;
	assert_availability_binary cut;
	assert_availability_binary diff;
	assert_availability_binary file;
	assert_availability_binary gzip;
	assert_availability_binary ls;
	assert_availability_binary readlink;
	assert_availability_binary sed;
	assert_availability_binary tr;
	assert_availability_binary uname;
	assert_availability_binary wc;
	assert_availability_binary zcat;

	if ! test -z ${CHECK_WITH_GDB};
	then
		assert_availability_binary gdb;

	elif ! test -z ${CHECK_WITH_VALGRIND};
	then
		assert_availability_binary valgrind;
	fi

	if ! test "${TEST_MODE}" = "default" && test "${TEST_MODE}" != "with_callback" && ! test "${TEST_MODE}" = "with_stdout_reference";
	then
		echo "Unsupported test mode: ${TEST_MODE}";
		echo "";

		return ${EXIT_FAILURE};
	fi

	if ! test -f ${TEST_EXECUTABLE};
	then
		echo "Missing test executable: ${TEST_EXECUTABLE}";
		echo "";

		return ${EXIT_FAILURE};
	fi

	if ! test -d "${TEST_INPUT_DIRECTORY}";
	then
		echo "Test input directory: ${TEST_INPUT_DIRECTORY} not found.";

		return ${EXIT_IGNORE};
	fi
	local RESULT=`ls ${TEST_INPUT_DIRECTORY}/* | tr ' ' '\n' | wc -l`;

	if test ${RESULT} -eq ${EXIT_SUCCESS};
	then
		echo "No files or directories found in the test input directory: ${TEST_INPUT_DIRECTORY}";

		return ${EXIT_IGNORE};
	fi

	local TEST_PROFILE_DIRECTORY=$(get_test_profile_directory "${TEST_INPUT_DIRECTORY}" "${TEST_PROFILE}");

	local IGNORE_LIST=$(read_ignore_list "${TEST_PROFILE_DIRECTORY}");

	RESULT=${EXIT_SUCCESS};

	for TEST_SET_INPUT_DIRECTORY in ${TEST_INPUT_DIRECTORY}/*;
	do
		if ! test -d "${TEST_SET_INPUT_DIRECTORY}";
		then
			continue;
		fi
		if check_for_directory_in_ignore_list "${TEST_SET_INPUT_DIRECTORY}" "${IGNORE_LIST}";
		then
			continue;
		fi

		local TEST_SET_DIRECTORY=$(get_test_set_directory "${TEST_PROFILE_DIRECTORY}" "${TEST_SET_INPUT_DIRECTORY}");

		local INPUT_FILES="";
		if test -f "${TEST_SET_DIRECTORY}/files";
		then
			INPUT_FILES=`cat ${TEST_SET_DIRECTORY}/files | sed "s?^?${TEST_SET_INPUT_DIRECTORY}/?"`;
		else
			INPUT_FILES="${TEST_SET_INPUT_DIRECTORY}/${INPUT_GLOB}";
		fi

		while read -r INPUT_FILE;
		do
			local TESTED_WITH_OPTIONS=0;

			for OPTION_SET in `echo ${OPTION_SETS} | tr ' ' '\n'`;
			do
				local OPTION_FILE=$(get_testion_option_file "${TEST_SET_DIRECTORY}" "${INPUT_FILE}" "${OPTION_SET}");

				if ! test -f ${OPTION_FILE};
				then
					continue
				fi

				run_test_on_input_file "${TEST_SET_DIRECTORY}" "${TEST_DESCRIPTION}" "${TEST_MODE}" "${OPTION_SET}" "${TEST_EXECUTABLE}" "${INPUT_FILE}" ${ARGUMENTS[@]};
				RESULT=$?;

				if test ${RESULT} -ne ${EXIT_SUCCESS};
				then
					return ${RESULT};
				fi
				TESTED_WITH_OPTIONS=1;
			done

			if test ${RESULT} -eq ${EXIT_SUCCESS} && test ${TESTED_WITH_OPTIONS} -eq 0;
			then
				run_test_on_input_file "${TEST_SET_DIRECTORY}" "${TEST_DESCRIPTION}" "${TEST_MODE}" "" "${TEST_EXECUTABLE}" "${INPUT_FILE}" ${ARGUMENTS[@]};
				RESULT=$?;

				if test ${RESULT} -ne ${EXIT_SUCCESS};
				then
					return ${RESULT};
				fi
			fi
		done < <(ls -1 ${INPUT_FILES});
	done

	return ${RESULT};
}

