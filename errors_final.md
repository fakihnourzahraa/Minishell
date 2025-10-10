
minishell$ echo $''
$
(should be nothing)

minishell$ echo $_
/usr/bin/valgrind
but
nfakih@c2r2s4:~/Desktop/git/Minishell$ echo $_
echo
idk y

minishell$ echo $123

(empty line)
nfakih@c2r2s4:~/Desktop/git/Minishell$ echo $123
23

minishell$ VAR="a b c"
minishell: VAR=a b c: command not found
nfakih@c2r2s4:~/Desktop/git/Minishell$ VAR="a b c"


minishell$ export VAR=$HOME
minishell$ echo $VAR
/home/nfakih
minishell$ export VAR=$VAR
minishell$ echo $VAR
/home/nfakih


not an error just want to understand y

-> remove spaces from expansion vars
->