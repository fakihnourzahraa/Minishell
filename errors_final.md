
MIRA: 

nfakih@c1r7s3:~/Desktop/git/Minishell$ export V="              h        '$HOME'   "
nfakih@c1r7s3:~/Desktop/git/Minishell$ echo $V
h '/home/nfakih'
nfakih@c1r7s3:~/Desktop/git/Minishell$ export V="              h        "$HOME"   "
nfakih@c1r7s3:~/Desktop/git/Minishell$ echo $V
h /home/nfakih
nfakih@c1r7s3:~/Desktop/git/Minishell$ 

cat: f.txt: Permission denied
minishell$ echo $?
1
(should be 126)

ls > a << b > c << d < e > f | cat << a << b > c > d >t>f<<p|cat Makefile>jnde1<jnde2>jnde3|ls>jnde4>jnde5<jnde6>jnde7|ls ls ls > jnde | << a << v | easy | exit

minishell$ ./test.sh
minishell: ./test.sh: command not found
minishell$ echo $?
127
(remove permission from sh file, should be permission denied not command not found + exit code 126)

NOUR:

minishell$ echo $123
(empty line)
nfakih@c2r2s4:~/Desktop/git/Minishell$ echo $123
23

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

nour@nfakih:~$ a <<< b
a: command not found
nour@nfakih:~$ echo $?
127

echo $$


BOTH:
The program should not accept unexpected arguments when launching, such as ./minishell 123
OLDPWD (keep checking)
makefile: wildcards and libft

DONE!!!!:
# minishell$ echo $''
# $
# (should be nothing)

# minishell$ VAR="a b c"
# minishell: VAR=a b c: command not found
# nfakih@c2r2s4:~/Desktop/git/Minishell$ VAR="a b c"

# minishell$ < |
# minishell: syntax error near unexpected token `|'
# minishell$ echo $?
# 0
# should be 2

# minishell$ export VAR=$HOME
# minishell$ echo $VAR
# /home/nfakih
# minishell$ export VAR=$VAR
# minishell$ echo $VAR
# /home/nfakih

# minishell: syntax error near unexpected token `>'
# minishell$ echo $?
# 127
# should be 2

minishell$ echo $_
/usr/bin/valgrind
but
nfakih@c2r2s4:~/Desktop/git/Minishell$ echo $_
echo
not an error just want to understand y

# Great job, ctrl+c in a cat block is returning 2 (syntax error) instead of 130.

minishell$ a <<< b
minishell: syntax error near unexpected token `<'
minishell$ echo $?
2
minishell$ is supposed to be 2!!!!!!