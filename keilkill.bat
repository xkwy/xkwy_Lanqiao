@echo off
color A
echo.
echo    * by xkwy. 2016-1-22 *
echo.
cd /d %~dp0
DEL /F /S /Q Listings\.
DEL /F /S /Q *.bak 2>nul
DEL /F /S /Q *.ddk 2>nul
DEL /F /S /Q *.edk 2>nul
DEL /F /S /Q *.lst 2>nul
DEL /F /S /Q *.lnp 2>nul
DEL /F /S /Q *.mpf 2>nul
DEL /F /S /Q *.mpj 2>nul
DEL /F /S /Q *.obj 2>nul
DEL /F /S /Q *.omf 2>nul
DEL /F /S /Q *.plg 2>nul
DEL /F /S /Q *.rpt 2>nul
DEL /F /S /Q *.tmp 2>nul
DEL /F /S /Q *.__i 2>nul
DEL /F /S /Q *.crf 2>nul
DEL /F /S /Q *.o 2>nul
DEL /F /S /Q *.d 2>nul
DEL /F /S /Q *.axf 2>nul
DEL /F /S /Q *.tra 2>nul
DEL /F /S /Q *.dep 2>nul
DEL /F /S /Q JLinkLog.txt 2>nul
DEL /F /S /Q *.uvguix.xkwy 2>nul

DEL /F /S /Q *.iex 2>nul
DEL /F /S /Q *.htm 2>nul
DEL /F /S /Q *.sct 2>nul
DEL /F /S /Q *.map 2>nul

echo.
echo    # Complete! (xkwy)   #
echo.

rem pause
rem exit
