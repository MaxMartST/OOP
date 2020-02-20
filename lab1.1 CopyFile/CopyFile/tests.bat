@echo off
REM чтобы текст команд не выводился в консоль указываем @

REM путь к тестируемой программе передаётся через 1-й аргумент командной строки
SET MyProgram="%~1"

REM затитимся, если test.bat запустили без аргументов
if %MyProgram%=="" (
	echo Please specify path to program 
	exit /B 1
)

REM Copy empty file
%MyProgram% empty.txt "%TEMP%\output.txt" || goto err
REM проверяем результаты копирования, fc сравнивает empty.txt и output.txt
REM чтобы не выводился текст FC подставляем nul
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM Copy nonEmpty file
%MyProgram% nonEmpty.txt "%TEMP%\output.txt" || goto err
REM проверяем результаты копирования, fc сравнивает nonEmpty.txt и output.txt
fc nonEmpty.txt "%TEMP%\output.txt"> nul || goto err
echo Test 2 passed

REM проверка на копирование отсутствуещего файла
%MyProgram% missing.txt "%TEMP%\output.txt" > nul && goto err
echo Test 3 passed

REM проверка на неверное количество аргументов в командной строке
REM запустили с одним аргументом
%MyProgram% missing.txt && goto err
echo Test 4 passed

REM запустили без аргументов
%MyProgram% && goto err
echo Test 5 passed

REM аргументов больше 3
%MyProgram% nonEmpty.txt "%TEMP%\output.txt" empty.txt && goto err
echo Test 6 passed

REM тесты прошли успегно
echo All tests passed successfuly
exit/B 0

REM сюда попадаем в случае ошибки
:err
echo Test failed
exit /B 1