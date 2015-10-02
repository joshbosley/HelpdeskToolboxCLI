@echo off
color 09
TITLE Data scrubber

FOR /d %%p IN ("C:\Users\*") DO (

	if NOT "%userprofile%" == "%%p" (
		rmdir "%%p" /S /q

		FOR /f %%u IN ("%%p") DO (
			del "%%u" /s /q
		)
	)
)

:: Delete any temp data
FOR /D %%p IN ("C:\Temp\*.*") DO rmdir "%%p" /s /q

exit