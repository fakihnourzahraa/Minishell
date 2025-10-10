
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


minishell$ $k
==11864== Syscall param execve(argv[0]) points to uninitialised byte(s)
==11864==    at 0x49ADF3B: execve (syscall-template.S:120)
==11864==    by 0x10B59B: exec_external_child (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x10B6A1: execute_external_command (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x10B8AA: execute_single (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x1097CC: mira_execution (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x109875: process_input (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x10999F: main_loop (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x109A60: main (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==  Address 0x4b4ede0 is 0 bytes inside a block of size 1 alloc'd
==11864==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==11864==    by 0x110E4C: ft_calloc (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x10E4D3: trim (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x10E671: remove_quotes (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x10E80B: iterate_expansion (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x1096CB: nour_parsing (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x10981C: process_input (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x10999F: main_loop (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)
==11864==    by 0x109A60: main (in /home/nour/Desktop/myFiles/42/git/Minishell/minishell)


j
minishell$ export 'H'=j
export: not a valid identifier: 'H'=j
minishell$ VAR=hii
minishell: VAR=hii: command not found


h
nfakih@c1r7s3:~/Desktop/git/Minishell$ export V="              h        '$HOME'   "
nfakih@c1r7s3:~/Desktop/git/Minishell$ echo $V
h '/home/nfakih'
nfakih@c1r7s3:~/Desktop/git/Minishell$ export V="              h        "$HOME"   "
nfakih@c1r7s3:~/Desktop/git/Minishell$ echo $V
h /home/nfakih
nfakih@c1r7s3:~/Desktop/git/Minishell$ 


minishell$ echo $123
z1�


-> remove spaces from expansion vars
->