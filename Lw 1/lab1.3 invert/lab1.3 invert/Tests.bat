rem "$(ProjectDir)Tests.bat" "$(TargetPath)"

@echo off

SET MyProgram="%~1"
SET OUT="%TEMP%\out_matrix_3x3.txt"

if %MyProgram%=="" (
	echo Please specify path to program 
	exit /B 1
)

rem check the output of the inverted matrix 3x3. det != 0
%MyProgram% matrix_3x3.txt > %OUT% || goto err
fc test_out_matrix_3x3.txt %OUT% || goto err
del %OUT%
echo Test: inverted matrix output - passed

rem empty file
%MyProgram% empty.txt > nul && goto err
echo Test: empty file - passed

rem no arguments
%MyProgram% && goto err
echo Test: no arguments - passed

rem extra argument
%MyProgram% matrix_3x3.txt newMatrix_3x3.txt && goto err
echo Test: extra argument - passed

rem nonexistent file
%MyProgram% lost_matrix_3x3.txt && goto err
echo Test: nonexistent file - passed

rem determinant is zero
%MyProgram% bad_matrix.txt &&  goto err
echo Test: determinant is zero - passed

rem extra column in the matrix 3x4
%MyProgram% matrix_3x4.txt > nul &&  goto err
echo Test: extra column in the matrix 3x4 - passed

rem lack of rows in the matrix
%MyProgram% matrix_2x3.txt > nul &&  goto err
echo Test: lack of rows in the matrix - passed

rem тесты прошли успегно
echo All tests passed successfuly
exit/B 0

rem тесты не прошли
:err
echo Test failed
exit /B 1