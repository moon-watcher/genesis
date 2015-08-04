pskill gens_djcc
del out\goplanes.bin

SET GDK=c:/dropbox/segagenesisdevelopment/sgdk100
SET GDK_WIN=C:\Dropbox\SegaGenesisDevelopment\sgdk100
SET PATH=C:\Dropbox\SegaGenesisDevelopment\sgdk100\bin;%PATH%

copy *.rc /B+ ,,/Y
%GDK_WIN%\bin\make -f %GDK_WIN%\makefile.gen


@if exist out\rom.bin (
    rename out\rom.bin goplanes.bin
) else (
    @ECHO ********************* ERROR BUILDING %~1.bin *********************
)