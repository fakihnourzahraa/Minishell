Thanks for the update! Since the commands are being added to the list, but you still don't see the second command after the pipe (`grep .c`), it suggests that the issue might be in how you're handling or displaying the list of commands after parsing, or in how the tokens are processed when the recursion happens.

### Let's break it down:

---

### 1. **Confirm the Command List (`cmds`) Contains Both Commands**:

It seems like the `add_cmd()` function is working since it's printing that the commands are being added. To verify this:

* **Action**: After parsing, traverse the command list (`shell->cmds`) and print all commands to make sure both `ls` and `grep .c` are added properly.

```c
void print_cmds(t_shell *shell) {
    t_cmd *cmd = shell->cmds;
    int i = 0;
    while (cmd) {
        printf("Command %d: %s\n", i++, cmd->cmd);
        for (int j = 0; cmd->args[j]; j++) {
            printf("  Arg %d: %s\n", j, cmd->args[j]);
        }
        cmd = cmd->next;
    }
}
```

Call this function after the parsing loop to verify that all commands are added correctly:

```c
parse(shell, token);
print_cmds(shell);  // Check the added commands
```

### 2. **Ensure Token List Is Not Getting Mixed Up**:

Even if `add_cmd()` is adding the commands correctly, there might still be an issue with how you're handling the `token` list during recursion. You are passing `token` around, and it's important to make sure it's not getting prematurely modified or lost.

* **Action**: Add prints before and after the recursive call to track token changes.

```c
else if (token->type == PIPE) {
    cmd->args[i] = NULL;
    add_cmd(shell, cmd);
    token = token->next;  // Move token to the next one after the pipe
    printf("Parsing next token after pipe: %s\n", token ? token->s : "(null)");
    parse(shell, token);  // Parse the next part after the pipe
    return;
}
```

### 3. **Check for Token Advancing after Pipe**:

Your logic for advancing the token pointer after encountering the `PIPE` token might be causing issues. You’re using `token = token->next;` after `add_cmd()` and before the recursive call to `parse()`. Double-check that this token pointer is being correctly advanced, especially to point to the right token (the command after the pipe).

Make sure that `token = token->next;` **only happens once** after processing a command part before the pipe.

### 4. **Check Recursion Behavior**:

Even though you're adding the second command, the recursive nature of `parse()` might be interfering with how the list is being built. After you process the command (`grep .c`), make sure you're not skipping over any important tokens in subsequent recursive calls.

* **Action**: Instead of recursive calls, you can try an iterative approach to see if that fixes the issue:

```c
void parse_iterative(t_shell *shell, t_token *token) {
    int i = 0;
    t_cmd *cmd = init_cmd(shell, token);
    while (token && token->type != T_EOF) {
        if (token->type == WORD) {
            if (token->quotes == 1)
                cmd->args[i] = ft_strtrim(token->s, "'");
            else if (token->quotes == 2)
                cmd->args[i] = ft_strtrim(token->s, "\"");
            else
                cmd->args[i] = ft_strdup(token->s);
            i++;
        }
        else if (token->type == PIPE) {
            cmd->args[i] = NULL;
            add_cmd(shell, cmd);
            token = token->next;
            cmd = init_cmd(shell, token);  // Start a new command after the pipe
            i = 0;
        }
        else {
            fill_r(token, shell);  // Handle redirection
        }
        token = token->next;  // Move to the next token
    }
    cmd->args[i] = NULL;
    add_cmd(shell, cmd);  // Add the final command
}
```

This method explicitly avoids recursion and processes everything in a single loop, so it's easier to debug and follow the flow.

---

### 5. **Check for Any Errors in `fill_r()`**:

Since you're using `fill_r()` for redirection handling, there might be issues in that function that are causing some tokens to be misprocessed. For example, if `fill_r()` is modifying the `token` list or causing it to skip tokens, it could lead to problems.

* **Action**: Temporarily comment out the call to `fill_r()` in your code to see if the issue persists without redirection processing. This will help isolate whether the problem is related to `fill_r()` or the parsing logic.

```c
else {
    // fill_r(token, shell);  // Comment this out for debugging
}
```

---

### 6. **Look for Unwanted Token Modifications**:

If after the `PIPE`, the second command is still missing, there might be an issue where the token list is being modified or the pointer is advancing incorrectly.

* **Action**: Verify that the tokens are correctly passed and updated without being overwritten or missed. Add a debug print after each modification of the `token` list.

```c
printf("Current token after processing: %s\n", token ? token->s : "(null)");
```

---

### Summary of Debugging Steps:

1. **Verify** the `cmds` list after parsing to ensure both commands are added properly.
2. **Track** the `token` pointer throughout recursion or iteration to ensure it's advancing correctly.
3. **Check** if the second command (`grep .c`) is being processed inside the recursive call or loop.
4. **Temporarily comment out** `fill_r()` to see if it’s causing issues.
5. **Try an iterative approach** to simplify the parsing flow and avoid potential issues with recursion.

Let me know what you find after these checks, and we can dive deeper into any remaining issues!
