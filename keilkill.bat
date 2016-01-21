@echo off
color A
echo.
echo    * by xkwy. 2014-12-27 *
echo.
cd /d %~dp0
DEL /F /S /Q *.bak
DEL /F /S /Q *.ddk
DEL /F /S /Q *.edk
DEL /F /S /Q *.lst
DEL /F /S /Q *.lnp
DEL /F /S /Q *.mpf
DEL /F /S /Q *.mpj
DEL /F /S /Q *.obj
DEL /F /S /Q *.omf
::DEL /F /S /Q *.opt  ::Do not delete JLINK setting
DEL /F /S /Q *.plg
DEL /F /S /Q *.rpt
DEL /F /S /Q *.tmp
DEL /F /S /Q *.__i
DEL /F /S /Q *.crf
DEL /F /S /Q *.o
DEL /F /S /Q *.d
DEL /F /S /Q *.axf
DEL /F /S /Q *.tra
DEL /F /S /Q *.dep           
DEL /F /S /Q JLinkLog.txt
DEL /F /S /Q *.uvguix.xkwy

DEL /F /S /Q *.iex
DEL /F /S /Q *.htm
DEL /F /S /Q *.sct
DEL /F /S /Q *.map

::pause
::exit
