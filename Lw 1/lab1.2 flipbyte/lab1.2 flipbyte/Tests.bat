@echo off
REM ����� ����� ������ �� ��������� � ������� ��������� @

SET MyProgram="%~1"

REM ������ �� ������� ������� ������ 
if %MyProgram%=="" (
	echo Please specify path to program 
	exit /B 1
)

REM �������� ����������� ��������� � ��������� �� 0 �� 255
%MyProgram% "6" > nul || goto err
echo Test 1 passed

REM �������� ���������������� ��������� 
%MyProgram% "6abc" > nul || goto err
echo Test 2 passed

REM �������� ���������������� ��������� 
%MyProgram% "    6 abc" > nul || goto err
echo Test 3 passed

REM ���������� ����� 
%MyProgram% "not a number" > nul && goto err
echo Test 4 passed

REM �������� �� ��������� ���� min
%MyProgram% "-10 abc" > nul && goto err
echo Test 5 passed

REM �������� �� ��������� ���� max
%MyProgram% "900abc" > nul && goto err
echo Test 6 passed

REM ��������� � ������� �����������
%MyProgram% "20" "45"> nul && goto err
echo Test 7 passed

REM ��������� ��� ����������
%MyProgram% > nul && goto err
echo Test 8 passed

REM ����� ������ �������
echo All tests passed successfuly
exit/B 0

:err
echo Test failed
exit /B 1