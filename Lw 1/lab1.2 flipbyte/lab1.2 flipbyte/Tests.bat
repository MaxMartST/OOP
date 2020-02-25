@echo off
REM чтобы текст команд не выводился в консоль указываем @

SET MyProgram="%~1"

REM защита от русного запуска тестов 
if %MyProgram%=="" (
	echo Please specify path to program 
	exit /B 1
)

REM проверка корректного аргумента в диапазоне от 0 до 255
%MyProgram% "6" > nul || goto err
echo Test 1 passed

REM проверка комбинированного аргумента 
%MyProgram% "6abc" > nul || goto err
echo Test 2 passed

REM проверка комбинированного аргумента 
%MyProgram% "    6 abc" > nul || goto err
echo Test 3 passed

REM отсутствие числа 
%MyProgram% "not a number" > nul && goto err
echo Test 4 passed

REM проверка со значением ниже min
%MyProgram% "-10 abc" > nul && goto err
echo Test 5 passed

REM проверка со значением выше max
%MyProgram% "900abc" > nul && goto err
echo Test 6 passed

REM запустили с лищними аргументами
%MyProgram% "20" "45"> nul && goto err
echo Test 7 passed

REM запустили без аргументов
%MyProgram% > nul && goto err
echo Test 8 passed

REM тесты прошли успегно
echo All tests passed successfuly
exit/B 0

:err
echo Test failed
exit /B 1