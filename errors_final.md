 cc  expansion_main.c tokenization/token.c tokenization/token_helpers.c tokenization/parsing.c tokenization/redir.c tokenization/data_structure.c tokenization/edge.c  cleanup.c tokenization/splits.c tokenization/chars.c env/envir.utils.c expansion/expansion.c env/envir.c expansion/expand_var.c expansion/replace_var.c expansion/trim.c libft/libft.a -o test_tokenization 
MIRA: 

cat: f.txt: Permission denied
minishell$ echo $?
1
(should be 126)  done

ls > a << b > c << d < e > f | cat << a << b > c > d >t>f<<p|cat Makefile>jnde1<jnde2>jnde3|ls>jnde4>jnde5<jnde6>jnde7|ls ls ls > jnde | << a << v | easy | exit
(ok lmshkle fiye he <<a <<v | yane lmshkl ben heredoc wl pipe 3am t3tbr awal wehd huwe delm lama ma tshuf pipe ) 
+test cat <<eof>file (3am t3l2) done

minishell$ ./test.sh
minishell: ./test.sh: command not found
minishell$ echo $?
127 
(remove permission from sh file, should be permission denied not command not found + exit code 126) done

minishell$ $NONEXISTENT
minishell: : Permission denied

NOUR:
NOUR:
minishell$ cat << $HOME
> /home/nfakih

minishell$ << $HOME
> $HOME
> /home/nour
should exit at $HOME

nour@nfakih:~$ a <<< b
a: command not found
nour@nfakih:~$ echo $?
127

BOTH:
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

# nfakih@c1r7s3:~/Desktop/git/Minishell$ export V="              h        '$HOME'   "
# nfakih@c1r7s3:~/Desktop/git/Minishell$ echo $V
# h '/home/nfakih'
# nfakih@c1r7s3:~/Desktop/git/Minishell$ export V="              h        "$HOME"   "
# nfakih@c1r7s3:~/Desktop/git/Minishell$ echo $V
# h /home/nfakih
# nfakih@c1r7s3:~/Desktop/git/Minishell$ 


# The program should not accept unexpected arguments when launching, such as ./minishell 123

minishell$ echo $_
/usr/bin/valgrind
but
nfakih@c2r2s4:~/Desktop/git/Minishell$ echo $_
echo
not an error just want to understand y

# Great job, ctrl+c in a cat block is returning 2 (syntax error) instead of 130.


# minishell$ echo $123
# (empty line)
# nfakih@c2r2s4:~/Desktop/git/Minishell$ echo $123
# 23

# minishell$ echo "'$'HOME"
# ''HOME
# nour@nfakih:~/Desktop/myFiles/42/git/Minishell$ echo "'$'HOME"
# '$'HOME

minishell$ echo "$"'HOME'
HOME
nour@nfakih:~/Desktop/myFiles/42/git/Minishell$ echo "$"'HOME'
$HOME

# Mixed expansion
cat << EOF
Hello $USER, your home is $HOME
The path is: $PATH
EOF

# Expansion with quotes inside heredoc
cat << EOF
He said "$USER is here"
'Single quotes' should not prevent expansion
EOF

# Non-existent variables
cat << EOF
This $NONEXISTENT variable is empty
EOF

# Special parameters (if you implement them)
cat << EOF
Exit status: $?
PID: $$
EOF

# Nested quotes in expansion
cat << EOF
"$USER"'s home is '$HOME'
EOF

# Single quotes - no expansion
cat << 'EOF'
$USER $HOME $PATH
EOF

# Double quotes - no expansion
cat << "EOF"
$USER $HOME $PATH
EOF



< in.txt cat << EOF > out.txt 2> err.txt
heredoc
EOF

cat << EOF
Current date: $(date)
Files: $(ls)
EOF

# Nested command substitution
cat << EOF
User $(whoami) in directory $(pwd)
EOF