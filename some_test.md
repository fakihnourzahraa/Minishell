echo "cd" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 2: pwd command
echo "pwd" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 3: echo command
echo "echo hello world" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 4: ls command
echo "ls" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 5: env command
echo "env" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 6: export command
echo "export TEST=hello" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 7: unset command
echo -e "export TEST=hello\nunset TEST" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 8: Simple pipe
echo "ls | cat" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 9: Multiple pipes
echo "ls | grep .c | wc -l" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 10: Input redirection
echo "cat < Makefile" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 11: Output redirection
echo "echo hello > test_output.txt" | valgrind --leak-check=full --show-leak-kinds=all -s --suppclearressions=readline.supp ./minishell

# Test 12: Append redirection
echo "echo world >> test_output.txt" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 13: Heredoc
echo -e "cat << EOF\nhello\nworld\nEOF" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 14: Environment variable expansion
echo -e "export NAME=minishell\necho Hello \$NAME" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 15: Exit status variable
echo -e "false\necho \$?" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 16: cd with path
echo "cd .." | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 17: cd home
echo "cd ~" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 18: Nonexistent command
echo "nonexistent_command_test" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 19: Multiple commands with variables
echo -e "export A=1\nexport B=2\necho \$A \$B\nunset A\nunset B" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 20: Complex pipeline with redirections
echo "ls | grep .c > c_files.txt" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 21: Exit command
echo "exit" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 22: Exit with code
echo "exit 42" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 23: Echo with -n flag
echo "echo -n hello" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 24: Empty command
echo "" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 25: Quoted strings
echo "echo 'hello world'" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 26: Double quoted strings with variables
echo -e "export NAME=test\necho \"Hello \$NAME\"" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 27: Multiple redirections
echo "echo hello > file1.txt 2> file2.txt" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 28: Pipeline with builtins
echo "export | grep PATH" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 29: Long pipeline
echo "echo hello | cat | cat | cat | wc -l" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Test 30: Stress test with multiple operations
echo -e "pwd\nls\necho test\nexport VAR=value\necho \$VAR\nunset VAR\nls | head -3\nexit" | valgrind --leak-check=full --show-leak-kinds=all -s --suppressions=readline.supp ./minishell

# Clean up test files (run this after testing)
# rm -f test_output.txt c_files.txt file1.txt file2.txt