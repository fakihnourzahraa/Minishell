 cc  expansion_main.c tokenization/token.c tokenization/token_helpers.c tokenization/parsing.c tokenization/redir.c tokenization/data_structure.c tokenization/edge.c  cleanup.c tokenization/splits.c tokenization/chars.c env/envir.utils.c expansion/expansion.c env/envir.c expansion/expand_var.c expansion/replace_var.c expansion/trim.c libft/libft.a -o test_tokenization 

MIRA:
nfakih@c1r7s4 ~/Desktop/git/Minishell
 % valgrind --leak-check=full -q ./minishell
minishell$ ls > a << b > c << d < e > f | cat << a << b > c > d >t>f<<p|cat Makefile>jnde1<jnde2>jnde3|ls>jnde4>jnde5<jnde6>jnde7|ls ls ls > jnde | << a << v | easy | exit
> b
> d
> a
> b
> p
> a
> v
jnde2: No such file or directory
==357920== Invalid read of size 1
==357920==    at 0x40B2E5: ft_strchr (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x406506: execute_cmd_in_pipeline (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x405E98: execute_all_commands (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x4054E3: execute_multiple_cmds (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x405A52: execute_pipeline (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x40AA4A: mira_execution (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x40AB2F: process_input (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x4015BD: main_loop (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x401691: main (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==357920== 
==357920== 
==357920== Process terminating with default action of signal 11 (SIGSEGV)
==357920==  Access not within mapped region at address 0x0
==357920==    at 0x40B2E5: ft_strchr (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x406506: execute_cmd_in_pipeline (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x405E98: execute_all_commands (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x4054E3: execute_multiple_cmds (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x405A52: execute_pipeline (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x40AA4A: mira_execution (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x40AB2F: process_input (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x4015BD: main_loop (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==    by 0x401691: main (in /home/nfakih/Desktop/git/Minishell/minishell)
==357920==  If you believe this happened as a result of a stack
==357920==  overflow in your program's main thread (unlikely but
==357920==  possible), you can try to increase the size of the
==357920==  main thread stack using the --main-stacksize= flag.
==357920==  The main thread stack size used in this run was 8388608.


minishell$ ""
minishell: : Permission denied
minishell$ echo $?
126

NOUR:

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

minishell$ $NONEXISTENT
minishell: : Permission denied

# The program should not accept unexpected arguments when launching, such as ./minishell 123

minishell$ ./test.sh
minishell: ./test.sh: command not found
minishell$ echo $?
127 
(remove permission from sh file, should be permission denied not command not found + exit code 126) done

ls > a << b > c << d < e > f | cat << a << b > c > d >t>f<<p|cat Makefile>jnde1<jnde2>jnde3|ls>jnde4>jnde5<jnde6>jnde7|ls ls ls > jnde | << a << v | easy | exit
(ok lmshkle fiye he <<a <<v | yane lmshkl ben heredoc wl pipe 3am t3tbr awal wehd huwe delm lama ma tshuf pipe ) 
+test cat <<eof>file (3am t3l2)

# Great job, ctrl+c in a cat block is returning 2 (syntax error) instead of 130.

# minishell$ echo $123
# (empty line)
# nfakih@c2r2s4:~/Desktop/git/Minishell$ echo $123
# 23

# minishell$ echo "'$'HOME"
# ''HOME
# nour@nfakih:~/Desktop/myFiles/42/git/Minishell$ echo "'$'HOME"
# '$'HOME

cat: f.txt: Permission denied
minishell$ echo $?
1

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

minishell$ minishell$ echo hi << a << b
> 
hi
ctrl d it should just leave one heredoc


nour:

.export TEST_VAR3="hello world"
echo $TEST_VAR3

.export TEST_VAR4="hello@world#test"
echo $TEST_VAR4

.test leak 
cat << EOF > out1.txt < in.txt > out2.txt(f2se crtl c)

.cat << EOF
$HOME
`pwd`
$(echo test)
EOF


.export TEST=value << EOF
ignored
EOF
echo $TEST

.minishell$ echo "test\$HOME"
test\/home/miwehbe
minishell$ 

.minishell$ echo "test\"quote"
minishell: syntax error near unclosed quote "
minishell$ 


mira:
.mkdir -p /tmp/test_no_perm
chmod 000 /tmp/test_no_perm
cd /tmp/test_no_perm
echo $?


.mkdir -p /tmp/test_pwd_delete
cd /tmp/test_pwd_delete
rm -rf /tmp/test_pwd_delete
pwd

minishell$ echo "hi" | echo  "bye"  << a | pwd
> a
/home/nfakih/Desktop/git/Minishell
minishell: Bad file descriptor

nour@nfakih:~/Desktop/myFiles/42/git/Minishell$ echo "hi" | echo "bye" << a | pwd
> a
/home/nour/Desktop/myFiles/42/git/Minishell

minishell$ << a
minishell$ 
(Is supposed to open a normal heredoc)


	if (current->type == EMPTY)
		r->s = ft_strdup("");
	else if (current->quotes == 1)
	{
		r->s = ft_strtrim(current->s, "'");
		r->quotes = true;
	}
	else if (current->quotes == 2)
 {
	r->quotes = true;
	r->s = ft_strtrim(current->s, "\"");
	 }
	else
		r->s = ft_strdup(current->s);


minishell$ q | a | pwd
minishell: q: command not found
minishell: a: command not found
/home/nfakih/Desktop/git/Minishell

nour@nfakih:~/Desktop/myFiles/42/git/Minishell$ q | a | pwd
/home/nour/Desktop/myFiles/42/git/Minishell
Command 'q' not found
a: command not found