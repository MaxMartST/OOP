rem "$(ProjectDir)tests.bat" "$(TargetPath)"

@echo off

SET MyProgram="%~1"
SET OUT="%TEMP%\out_matrix_3x3.txt"

if %MyProgram%=="" (
	echo Please specify path to program 
	exit /B 1
)

%MyProgram% "pack" input_file.txt output_file.txt > nul || goto err
echo Test: command pack - passed

%MyProgram% "unpack" input_file.txt output_file.txt > nul || goto err
echo Test: command unpack - passed

rem %MyProgram% "copy" input_file.txt output_file.txt && goto err
rem echo Test: invalid command - passed

rem no arguments
%MyProgram% && goto err
echo Test: no arguments - passed

rem nonexistent file
%MyProgram% lost_matrix_3x3.txt && goto err
echo Test: nonexistent file - passed

rem тесты прошли успегно
echo All tests passed successfuly
exit/B 0

rem тесты не прошли
:err
echo Test failed
exit /B 1