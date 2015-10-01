$domain=$args[0]
$username=$args[1]
$pass=$args[2]
$cred = $domain + "\" + $username
$password = ConvertTo-SecureString $pass -AsPlainText -Force 
$DomainCred = New-Object System.Management.Automation.PSCredential $cred, $password
Add-Computer -Credential $DomainCred -DomainName  $domain