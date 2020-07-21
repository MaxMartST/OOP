@echo off

SET MyProgram="%~1"

rem защита запуска без аргумента
if %MyProgram%=="" (
	echo Please specify path to program 
	exit /B 1
)

%MyProgram% "pack" test_input.txt "%TEMP%\out_encode.txt" || goto err
fc test_example_encode.txt "%TEMP%\out_encode.txt" || goto err
echo Test: command pack - passed
echo Test: comparing the result with an example - passed

%MyProgram% "unpack" test_example_encode.txt "%TEMP%\out_decode.txt" || goto err
fc test_input.txt "%TEMP%\out_decode.txt" || goto err
echo Test: command unpack - passed
echo Test: comparing the decoding result with an example - passed

%MyProgram% "pack" empty.txt "%TEMP%\out_encode.txt" || goto err
fc empty.txt "%TEMP%\out_encode.txt" || goto err
echo Test: command pack - passed
echo Test: encode empty file - passed

%MyProgram% "unpack" empty.txt "%TEMP%\out_decode.txt" || goto err
fc empty.txt "%TEMP%\out_decode.txt" || goto err
echo Test: command pack - passed
echo Test: decode empty file - passed

%MyProgram% "pack" coding_repetition_overflow.txt "%TEMP%\out_encode.txt" || goto err
fc coding_repetition_example.txt "%TEMP%\out_encode.txt" || goto err
echo Test: command unpack - passed
echo Test: compare encoding results on character counter overflow (256 byte) - passed

%MyProgram% "unpack" coding_repetition_example.txt "%TEMP%\out_decode.txt" || goto err
fc coding_repetition_overflow.txt "%TEMP%\out_decode.txt" || goto err
echo Test: command unpack - passed
echo Test: compare decoding results on character counter overflow (256 byte) - passed

%MyProgram% "pAcK" test_input.txt "%TEMP%\out_encode.txt" || goto err
echo Test: command mix register - passed

%MyProgram% "copy" test_input.txt "%TEMP%\out_encode.txt" && goto err
echo Test: invalid command - passed

rem без аргументов
%MyProgram% && goto err
echo Test: no arguments - passed

rem несуществующий файл
%MyProgram% lost_file.txt && goto err
echo Test: nonexistent file - passed

rem тесты прошли успегно
echo All tests passed successfuly
exit/B 0

rem тесты не прошли
:err
echo Test failed
exit /B 1