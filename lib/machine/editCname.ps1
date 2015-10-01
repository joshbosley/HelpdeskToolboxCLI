$cname=$args[0]

$(gwmi win32_computersystem).Rename($cname)