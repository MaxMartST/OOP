@echo off
REM ����� ����� ������ �� ��������� � ������� ��������� @

REM ���� � ����������� ��������� ��������� ����� 1-� �������� ��������� ������
SET MyProgram="%~1"

REM ���������, ���� test.bat ��������� ��� ����������
if %MyProgram%=="" (
	echo Please specify path to program 
	exit /B 1
)

REM Copy empty file
%MyProgram% empty.txt "%TEMP%\output.txt" || goto err
REM ��������� ���������� �����������, fc ���������� empty.txt � output.txt
REM ����� �� ��������� ����� FC ����������� nul
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM Copy nonEmpty file
%MyProgram% nonEmpty.txt "%TEMP%\output.txt" || goto err
REM ��������� ���������� �����������, fc ���������� nonEmpty.txt � output.txt
fc nonEmpty.txt "%TEMP%\output.txt"> nul || goto err
echo Test 2 passed

REM �������� �� ����������� �������������� �����
%MyProgram% missing.txt "%TEMP%\output.txt" > nul && goto err
echo Test 3 passed

REM �������� �� �������� ���������� ���������� � ��������� ������
REM ��������� � ����� ����������
%MyProgram% missing.txt && goto err
echo Test 4 passed

REM ��������� ��� ����������
%MyProgram% && goto err
echo Test 5 passed

REM ���������� ������ 3
%MyProgram% nonEmpty.txt "%TEMP%\output.txt" empty.txt && goto err
echo Test 6 passed

REM ����� ������ �������
echo All tests passed successfuly
exit/B 0

REM ���� �������� � ������ ������
:err
echo Test failed
exit /B 1