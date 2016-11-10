# Library API type testing script
#
# Version: 20161110

$ExitSuccess = 0
$ExitFailure = 1
$ExitIgnore = 77

$TestPrefix = Split-Path -path ${Pwd}.Path -parent
$TestPrefix = Split-Path -path ${TestPrefix} -leaf
$TestPrefix = ${TestPrefix}.Substring(3)

$TestTypes = "data_block data_string distributed_link_tracker_properties file_information io_handle known_folder_location link_target_identifier location_information special_folder_location"
$TestTypesWithInput = "file"

$TestToolDirectory = "..\msvscpp\Release"

Function TestAPIType
{
	param( [string]$TestType )

	$TestDescription = "Testing API type: ${TestType}"
	$TestExecutable = "${TestToolDirectory}\${TestPrefix}_test_${TestType}.exe"

	$Output = Invoke-Expression ${TestExecutable}
	$Result = ${LastExitCode}

	If (${Result} -ne ${ExitSuccess})
	{
		Write-Host ${Output} -foreground Red
	}
	Write-Host "${TestDescription} " -nonewline

	If (${Result} -ne ${ExitSuccess})
	{
		Write-Host " (FAIL)"
	}
	Else
	{
		Write-Host " (PASS)"
	}
	Return ${Result}
}

If (-Not (Test-Path ${TestToolDirectory}))
{
	$TestToolDirectory = "..\vs2010\Release"
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	Write-Host "Missing test tool directory." -foreground Red

	Exit ${ExitFailure}
}

$Result = ${ExitIgnore}

Foreach (${TestType} in ${TestTypes} -split " ")
{
	$Result = TestAPIType ${TestType}

	If (${Result} -ne ${ExitSuccess})
	{
		Break
	}
}

Foreach (${TestType} in ${TestTypesWithInput} -split " ")
{
	$Result = TestAPIType ${TestType}

	If (${Result} -ne ${ExitSuccess})
	{
		Break
	}
}

Exit ${Result}

