Get-Location
Set-Location -Path C:\
$webclient = New-Object System.Net.WebClient
$url = "http://10.1.0.83/hdtb/software/javawin.exe"
$file = "$pwd\java8u45.exe"
$webclient.DownloadFile($url,$file)

CMD /c $file /s