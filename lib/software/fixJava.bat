color 0A
TITLE Tyler's java fixer

FOR /d %%u in (C:\Users\*) do (
        IF NOT EXIST %%u\Appdata\LocalLow\Sun\Java\Deployment\security (
        mkdir %%u\Appdata\LocalLow\Sun\Java\Deployment\security
        )
        copy "lib\software\deployment.properties" "%%u\Appdata\LocalLow\Sun\Java\Deployment\deployment.properties"
        copy "lib\software\exception.sites" "%%u\Appdata\LocalLow\Sun\Java\Deployment\security\exception.sites"
)

@echo off
pause
exit
