
# minishell$ echo $''
# $
# (should be nothing)

minishell$ echo $_
/usr/bin/valgrind
but
nfakih@c2r2s4:~/Desktop/git/Minishell$ echo $_
echo
idk y

# minishell$ echo $123

# (empty line)
# nfakih@c2r2s4:~/Desktop/git/Minishell$ echo $123
# 23

# minishell$ VAR="a b c"
# minishell: VAR=a b c: command not found
# nfakih@c2r2s4:~/Desktop/git/Minishell$ VAR="a b c"


# minishell$ export VAR=$HOME
# minishell$ echo $VAR
# /home/nfakih
# minishell$ export VAR=$VAR
# minishell$ echo $VAR
# /home/nfakih


not an error just want to understand y


h
nfakih@c1r7s3:~/Desktop/git/Minishell$ export V="              h        '$HOME'   "
nfakih@c1r7s3:~/Desktop/git/Minishell$ echo $V
h '/home/nfakih'
nfakih@c1r7s3:~/Desktop/git/Minishell$ export V="              h        "$HOME"   "
nfakih@c1r7s3:~/Desktop/git/Minishell$ echo $V
h /home/nfakih
nfakih@c1r7s3:~/Desktop/git/Minishell$ 


# minishell$ echo $123
# z1�

minishell: syntax error unclosed quote '
minishell$ echo $?
127
should be 1


minishell$ echo $?
127
minishell$ 
shoould be 126

minishell: syntax error near unexpected token `>'
minishell$ echo $?
127
should be 2

ls > a << b > c << d < e > f | cat << a << b > c > d >t>f<<p|cat Makefile>jnde1<jnde2>jnde3|ls>jnde4>jnde5<jnde6>jnde7|ls ls ls > jnde | << a << v | easy | exit

minishell$ echo "$"'HOME'
HOME
nour@nfakih:~/Desktop/myFiles/42/git/Minishell$ echo "$"'HOME'
$HOME


minishell$ echo "'$'HOME"
''HOME
nour@nfakih:~/Desktop/myFiles/42/git/Minishell$ echo "'$'HOME"
'$'HOME


minishell$ << $HOME
> $HOME
> /home/nour
should exit at $HOME

-> remove spaces from expansion vars
->