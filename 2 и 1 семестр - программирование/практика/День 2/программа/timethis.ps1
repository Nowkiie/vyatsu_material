param([string]$command)
$x = Invoke-Expression -Command $command
measure-command {$x | write-host}

