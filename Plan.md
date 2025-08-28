
# Week 1 – Setup & Shared Structs
Goal: Prepare shell foundation and define shared structs so you can work independently
later.
Shared Structs (Done by Nour)
•Why: These are the “contract” between parsing and execution. Once frozen, you can
code independently.
•Structs to define in minishell.h:
ot_token → store tokens (words, operators)
ot_redir → store redirection info (<, >, >>, <<)
ot_cmd → store commands with args, redirections, next command (pipeline)
ot_env → environment variables (name/value)
ot_shell → global shell state: env, exit_code, cmds

Nour (Parsing)
•Focus: Basic tokenization
•Split input string by spaces → create t_token linked list
•Function examples:
•t_token *tokenize(char *input);
•void print_tokens(t_token *list); // for testing
•Why: Starting with basic tokenization allows Mira to execute commands using
dummy tokens while full parsing isn’t ready.
Mira (Execution)
•Focus: Shell loop + prompt + history + signals
•Implement:•
oMain loop while(1)
oPrompt: minishell$
oInput reading using readline()
oHistory using add_history()
oSignal handling for Ctrl+C, Ctrl+D, Ctrl+\
oMakefile with all, clean, fclean, re
oUtility functions from libft (ft_strcmp, ft_strdup)
Why: Ensures you have a working shell interface, independent of parsing.

End of Week 1:
•Structs frozen → independent work possible
•Shell loop, prompt, history, signals working


# Week 2 – Quotes & Basic Parsing / Single Command Execution
Goal: Recognize commands and arguments, handle quotes, and execute a single
command.

Nour (Parsing)
•Focus: Quotes + Basic Parser
•Extend tokenizer to handle:
•
oSingle quotes ' ' → literal string
oDouble quotes " " → allow expansion later, but keep as one token
oSpecial operators: <, >, >>, |
Build parser: tokens → t_cmd linked list
o
Fill: cmd, args (array), empty redir, next (NULL)
•Why: Correct parsing is necessary before Mira can execute commands with
arguments or quotes.
•Test: "echo 'hello world'" → single argument 'hello world'

Mira (Execution)
•Focus: Execute single external commands
•Implement:
•
oPATH lookup
ofork + execve for command execution
Create builtin skeleton: echo, pwd, exit
o
Just recognition & call functions, not full implementation
•Why: Allows you to test execution of commands without waiting for full parsing or
pipelines.
•Test: "ls -l" runs correctly
End of Week 2:
•Parser handles quotes
•Single command execution works
•Builtin recognition skeleton exists

# Week 3 – Redirections
Goal: Parse and execute input/output redirections.

Nour (Parsing)
•Focus: Redirection parsing
•Identify <, >, >> in token list
•Fill t_redir in t_cmd:
•
otype → REDIR_IN / REDIR_OUT / REDIR_APP
ofile → target filename
Handle errors (e.g., missing filename)
Mira (Execution)
•
Focus: Apply redirections during command execution•Use open(), dup2(), close() for stdin/stdout redirection
•Test:
ols > out.txt
ocat < in.txt
oecho hi >> log.txt
End of Week 3:
•Redirections fully functional
•Parser correctly populates t_redir

# Week 4 – Pipes & Variable Expansion
Goal: Handle command pipelines and environment variable expansion.

Nour (Parsing)
•Focus: Pipelines & expansion
•Parse pipelines: "ls | grep .c | wc -l" → linked list of t_cmd
•Variable expansion:
•
o$VAR → from t_env
o$? → from t_shell->exit_code
Quotes handled correctly with expansion
Mira (Execution)
•Focus: Execute pipelines
•Use pipe(), fork(), dup2() for multiple commands
•Combine pipes + redirections
•Test:
oecho hello | grep h
ols | wc -l > count.txt

End of Week 4:•Pipelines work correctly
•Variables expanded correctly
•Commands with pipes + redirection execute

# Week 5 – Builtins & Finalization
Goal: Complete builtins and polish shell.

Nour (Parsing)
Handle edge cases:
oUnclosed quotes → error
oDisallowed special characters: ;, \
Free memory → no leaks

Mira (Execution)
•Implement heredoc (<<)
•Full builtins:
cd, export, unset, env, exit
Handle signals in child processes

Both
•Test all commands against bash behavior
•Norminette fixes
•README + final project checks

End of Week 5:
•Fully working minishell
•Parsing & execution separated and synchronized via shared structs

Key Notes / Why Tasks Are Split
1. Week 1 structs: frozen → independent work possible2. Week 2 quotes: early handling allows execution tests with arguments
3. Skeleton builtins in Week 2: allows Mira to test execution
4. Full builtins in Week 5: after parsing, pipelines, redirections, and expansions are
ready
5. Step-by-step progression avoids being blocked or overwhelmed