@echo off
color 0A
TITLE Standard cleanup

del /f /q /s "%userprofile%\Cookies\*.*"
del /f /q /s "%userprofile%\AppData\Local\Microsoft\Windows\Temporary Internet Files\*.*""

FOR /D %%p IN ("C:\Temp\*.*") DO rmdir "%%p" /s /q
FOR /D %%p IN ("%userprofile%\Downloads\*.*") DO rmdir "%%p" /s /q
FOR /f %%p IN ("%userprofile%\Downloads\*.*") DO del "%%p" /s /q

exit