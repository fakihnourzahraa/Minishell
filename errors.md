# 1 

mkdir -p dir/dir/dir/dir

rm -rf ../../../../dir

minishell$ cd ..

minishell$ cd ..

minishell$ cd ..

minishell$ cd ..

==141297== Invalid read of size 1
==141297==    at 0x10EB8D: ft_strlen (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10EF6A: ft_strdup (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10CF36: create_env_node (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10D05D: set_env_var (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10A1BC: update_pwd (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10A23A: change_directory (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10A2B5: builtin_cd (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10AF17: execute_builtin (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x1096DF: mira_execution (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x109790: process_input (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x1098AA: main_loop (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x109970: main (in /home/nfakih/Desktop/git/temp/minishell)
==141297==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==141297== 
==141297== 
==141297== Process terminating with default action of signal 11 (SIGSEGV)
==141297==  Access not within mapped region at address 0x0
==141297==    at 0x10EB8D: ft_strlen (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10EF6A: ft_strdup (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10CF36: create_env_node (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10D05D: set_env_var (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10A1BC: update_pwd (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10A23A: change_directory (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10A2B5: builtin_cd (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x10AF17: execute_builtin (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x1096DF: mira_execution (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x109790: process_input (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x1098AA: main_loop (in /home/nfakih/Desktop/git/temp/minishell)
==141297==    by 0x109970: main (in /home/nfakih/Desktop/git/temp/minishell)
==141297==  If you believe this happened as a result of a stack
==141297==  overflow in your program's main thread (unlikely but
==141297==  possible), you can try to increase the size of the
==141297==  main thread stack using the --main-stacksize= flag.
==141297==  The main thread stack size used in this run was 8388608.
 czsh: segmentation fault (core dumped)  valgrind --leak-check=full -q ./minishell

 # 2

minishell$ 
exit
==142264== 2 bytes in 1 blocks are definitely lost in loss record 1 of 67
==142264==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==142264==    by 0x10FAE0: ft_itoa (in /home/nfakih/Desktop/git/temp/minishell)
==142264==    by 0x10A3BC: update_shlvl_on_exit (in /home/nfakih/Desktop/git/temp/minishell)
==142264==    by 0x109823: main_loop (in /home/nfakih/Desktop/git/temp/minishell)
==142264==    by 0x109970: main (in /home/nfakih/Desktop/git/temp/minishell)
==142264== 