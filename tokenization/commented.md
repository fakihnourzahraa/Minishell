
/*int	check_tkns(t_token *tkn)
{
    printf("DEBUG: Checking tokens...\n");
    
    if (tkn->type != WORD && tkn->type != T_EOF)
    {
        printf("ERROR: First token is not WORD or T_EOF, it's type %d\n", tkn->type);
        return (-1);
    }
    
    while (tkn)
    {
        printf("DEBUG: Checking token type %d, content '%s'\n", tkn->type, tkn->s ? tkn->s : "NULL");
        
        if ((is_r(tkn) || tkn->type == PIPE) && tkn->next && (is_r(tkn->next) || tkn->next->type == PIPE))
        {
            printf("ERROR: Two consecutive operators\n");
            return (-1);
        }
        if (tkn->next && tkn->next->type == T_EOF && (tkn->type == PIPE || is_r(tkn)))
        {
            printf("ERROR: Command ends with operator\n");
            return (-1);
        }
        tkn = tkn->next;
    }
    return (1);
}*/
/*void	fill_r(t_token *t, t_cmd *cmd)
{
	t_redir *r;

	r = init_redir();
	if (t->type == IN)
		r->type = R_IN;
	else if (t->type == OUT)
		r->type = R_OUT;
	else if (t->type == APPEND)
		r->type = R_APPEND;
	else if (t->type == HEREDOC)
	{
		r->type = R_HEREDOC;
		printf("DEBUG: Found HEREDOC delimiter='%s'\n", t->next ? t->next->s : "NULL");
	}
	
	if (t->next && t->next->s)
		r->s = ft_strdup(t->next->s);
	else
		r->s = NULL;
	add_redir(cmd, r);
}

// Add this debug after parsing to see all redirections
void debug_print_redirections(t_cmd *cmd)
{
	t_redir *redir = cmd->rd;
	int count = 0;
	
	printf("DEBUG: All redirections for command:\n");
	while (redir)
	{
		printf("  Redir[%d]: type=%d", count, redir->type);
		if (redir->type == R_HEREDOC)
			printf(" (HEREDOC), delimiter='%s'", redir->s ? redir->s : "NULL");
		else if (redir->s)
			printf(", file='%s'", redir->s);
		printf("\n");
		redir = redir->next;
		count++;
	}
	printf("DEBUG: Total redirections: %d\n\n",count);
}*/
// int	word_count_p(t_token *token)
// {
// 	int		i;

// 	i = 0;
// 	while (token && token->type != T_EOF && token->type != PIPE)
// 	{
// 		if (token->type == WORD)
// 		{
// 			if (token->type == WORD && token->space == 0)
// 			{
// 				while (token && token->space == 0)
// 					token = token->next;
// 			}
// 			else
// 				token = token->next;
// 			i++;
// 		}
// 		else if (token->type == EMPTY)
// 		{
// 			i++;
// 			token = token->next;
// 		}
// 		else
// 			token = token->next;
// 	}
// 	return (i);
// }

// void	parse(t_shell *shell, t_token *token)
// {
// 	int		i;
// 	t_cmd	*cmd;

// 	if (!token || token->type != WORD)
// 		return ;
		
// 	cmd = init_cmd(token);
// 	if (!cmd)
// 		return;
		
// 	cmd->cmd = ft_strdup(token->s);
// 	cmd->args[0] = ft_strdup(token->s);
// 	i = 1;
// 	token = token->next;
	
// 	// FIXED: Process tokens for THIS command only (until PIPE or EOF)
// 	while (token && token->type != T_EOF && token->type != PIPE)
// 	{
// 		if (token->type == WORD)
// 		{
// 			if (token->quotes == 1)
// 				cmd->args[i] = ft_strtrim(token->s, "'");
// 			else if (token->quotes == 2)
// 				cmd->args[i] = ft_strtrim(token->s, "\"");
// 			else
// 				cmd->args[i] = ft_strdup(token->s);
// 			i++;
// 			token = token->next;
// 		}
// 		else if (token->type == IN || token->type == OUT || 
// 				 token->type == APPEND || token->type == HEREDOC)
// 		{
// 			// FIXED: Store redirection token and get filename token
// 			t_token *redir_token = token;
// 			token = token->next; // Move to filename token
			
// 			if (token && token->type == WORD)
// 			{
// 				// Add redirection with both tokens
// 				fill_r_for_cmd(redir_token, token, cmd);
// 				token = token->next; // Skip filename token
// 			}
// 			else
// 			{
// 				// Invalid syntax - redirection without filename
// 				// Still need to advance token to avoid infinite loop
// 				if (token)
// 					token = token->next;
// 			}
// 		}
// 		else
// 		{
// 			token = token->next;
// 		}
// 	}
	
// 	cmd->args[i] = NULL;
// 	add_cmd(shell, cmd);
	
// 	// FIXED: If we hit a PIPE, recursively parse the next command
// 	if (token && token->type == PIPE)
// 	{
// 		token = token->next; // Skip the PIPE token
// 		parse(shell, token);  // Parse next command after pipe
// 	}
// }

//extra token.next so it skips filename

//parses till eof only

//should take the first token
// typedef struct s_cmd
// {
// 	char	*cmd;
// 	char	**args;
// 	char	*path;
// 	t_redir	*rd;
// 	int		i_fd;
// 	int		o_fd;
// 	pid_t	pid;
// 	t_builtin builtin;
// 	t_cmd	*next;
// }			t_cmd;
//rd: redirections
//i_fd: input fd
//o_fd: output fd
//pid: so we can wait on it later
// int	split_quote(char *a, int i, t_shell *shell, char n)
// {
// 	char	*b;
// 	int		j;
// 	int		z;
// 	t_token	*t;
	
// 	z = 0;
// 	i++;
// 	while (a[z + i] != n)
// 		z++;
// 	//these are the chars between each quotation mark
// 	b = malloc(sizeof(char) * (z + 2));
// 	j = 1;
// 	b[0] = n;
// 	while ((a[i + j]) != n)
// 	{
// 		b[j] = a[i + j];
// 		j++;
// 	}
// 	b[z] = n;
// 	b[z + 1] = '\0';
// 	t = init_token();
// 	t->s = b;
// 	t->type = WORD;
// 	t->quotes = n % 3 + 1;
// 	add_token(shell, t);
// 	return (z + i);
// }
//takes pos of first " returns pos of last "
// i++ cause i is gonna be " at first
//