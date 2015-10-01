color 0A
TITLE Tyler's java fixer

FOR /d %%u in (C:\Users\*) do (

	copy "lib\machine\deployment.properties" "%%u\Appdata\LocalLow\Sun\Java\Deployment\deployment.properties"
)

@echo off
pause
exit