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




 minishell git:(main) ✗ echo -e "echo hello > out.txt\nexit" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

==12866== Memcheck, a memory error detector
==12866== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==12866== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==12866== Command: ./minishell
==12866==
DEBUG: SHLVL update disabled for testing
minishell$ echo hello > out.txt
==12867== 
==12867== HEAP SUMMARY:
==12867==     in use at exit: 237,407 bytes in 349 blocks
==12867==   total heap usage: 574 allocs, 225 frees, 264,257 bytes allocated
==12867==
==12867== 2 bytes in 1 blocks are still reachable in loss record 1 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10DEAE: set_single (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10EF8F: set_token (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10F150: tokenize_line (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10961F: nour_parsing (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10976A: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 5 bytes in 1 blocks are still reachable in loss record 2 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10FA3F: ft_strdup (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E269: init_cmd (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E6FA: parse (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x109662: nour_parsing (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10976A: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 5 bytes in 1 blocks are still reachable in loss record 3 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10FA3F: ft_strdup (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E288: init_cmd (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E6FA: parse (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x109662: nour_parsing (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10976A: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 6 bytes in 1 blocks are still reachable in loss record 4 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10FA3F: ft_strdup (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E6AA: parse_word (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E736: parse (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x109662: nour_parsing (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10976A: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 8 bytes in 1 blocks are still reachable in loss record 8 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10FA3F: ft_strdup (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E994: fill_r (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E75C: parse (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x109662: nour_parsing (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10976A: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 16 bytes in 1 blocks are still reachable in loss record 19 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10E0D4: init_cmd (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E6FA: parse (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x109662: nour_parsing (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10976A: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 19 bytes in 3 blocks are still reachable in loss record 20 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10EBB3: split_word (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10EFAB: set_token (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10F150: tokenize_line (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10961F: nour_parsing (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10976A: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 21 bytes in 1 blocks are still reachable in loss record 24 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10FA3F: ft_strdup (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10973F: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 32 bytes in 1 blocks are still reachable in loss record 28 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10EFEF: init_token (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10F1B5: tokenize_line (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10961F: nour_parsing (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10976A: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 32 bytes in 1 blocks are still reachable in loss record 29 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10E092: init_cmd (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E6FA: parse (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x109662: nour_parsing (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10976A: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 32 bytes in 1 blocks are still reachable in loss record 30 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10E8B4: init_redir (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E904: fill_r (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E75C: parse (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x109662: nour_parsing (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10976A: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 72 bytes in 1 blocks are still reachable in loss record 34 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10E069: init_cmd (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10E6FA: parse (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x109662: nour_parsing (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10976A: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 128 bytes in 4 blocks are still reachable in loss record 39 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10EFEF: init_token (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10EE55: set_token (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10F150: tokenize_line (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10961F: nour_parsing (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10976A: process_input (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A0D8: main_loop (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1C7: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 304 bytes in 31 blocks are still reachable in loss record 43 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x1109DA: ft_strndup (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10D547: create_env_node_from_str (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10D642: init_env_from_envp (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x109468: init_shell (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1B6: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 992 bytes in 31 blocks are still reachable in loss record 47 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10D4F6: create_env_node_from_str (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10D642: init_env_from_envp (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x109468: init_shell (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1B6: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==
==12867== 2,843 bytes in 31 blocks are still reachable in loss record 63 of 94
==12867==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12867==    by 0x10FA3F: ft_strdup (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10D55E: create_env_node_from_str (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10D642: init_env_from_envp (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x109468: init_shell (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==    by 0x10A1B6: main (in /mnt/c/Users/miraw/Downloads/minishell/minishell)
==12867==