# Minishell

Notes:

Working: 
Nour? yes 
Mira? 


# Week 1 – Setup & Shared Structs
Goal: Prepare shell foundation and define shared structs so you can work independently
later.

# Shared Structs (Done by Nour)
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
o Main loop while(1)
o Prompt: minishell$
o Input reading using readline()
o History using add_history()
o Signal handling for Ctrl+C, Ctrl+D, Ctrl+\
o Makefile with all, clean, fclean, re
o Utility functions from libft (ft_strcmp, ft_strdup)
Why: Ensures you have a working shell interface, independent of parsing.

End of Week 1:
•Structs frozen → independent work possible
•Shell loop, prompt, history, signals working
