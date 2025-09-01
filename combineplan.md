the plan we want to do to know the error early not in final.

1️⃣ Week 2 – Single Command Execution

Integration Point:

After Nour builds t_cmd for a single command (quotes handled, single command only).

You can immediately connect your execute_single() to shell->cmds.

Why test now:

Detects mismatches between how t_cmd is built and how execution expects args, path, builtin, and redirections.

Checks that single commands run correctly from real parser output rather than manual t_cmd.

Test:

Input: echo hello, pwd, ls.

Check exit status, output, and memory leaks.

2️⃣ Week 3 – Redirections

Integration Point:

After Nour parses redirections into t_redir in t_cmd.

Mira can apply open(), dup2(), close() in execute_single() for redirections.

Heredoc logic can also be tested with child process + pipe/temp file.

Why test now:

Early detection of:

fd bugs (input/output wrong)

improper closing of files/pipes

heredoc hanging or Ctrl+C behavior

Test:

Commands: cat < file.txt, ls > out.txt, echo hi >> log.txt, cat << EOF.

3️⃣ Week 4 – Pipelines

Integration Point:

After Nour parses pipeline commands (cmd1 | cmd2 | cmd3) into linked list of t_cmd.

Mira executes them using pipe(), dup2(), and fork loops.

Why test now:

Pipelines are complex; testing them early ensures:

Child processes are created correctly

Pipes connect commands properly

Builtins inside pipelines are handled

Test:

Commands: ls | grep .c | wc -l, cat file.txt | grep hello.

4️⃣ Week 5 – Full Builtins & Signals

Integration Point:

After builtins are complete and signals in children are handled.

This is final integration to ensure everything works together.

Why test now:

Validate exit codes and signal behavior (Ctrl+C in child vs shell).

Confirm memory cleanup and Norm compliance.