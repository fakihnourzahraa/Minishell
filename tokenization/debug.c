/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:12:11 by nour              #+#    #+#             */
/*   Updated: 2025/10/13 11:03:40 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void TT(t_token_type type)
{
    switch(type) {
        case WORD: printf("WORD"); break;
        case PIPE: printf("PIPE"); break;
        case IN: printf("IN"); break;
        case OUT: printf("OUT"); break;
        case APPEND: printf("APPEND"); break;
        case HEREDOC: printf("HEREDOC"); break;
        case T_EOF: printf("T_EOF"); break;
        default: printf("UNKNOWN"); break;
    }
}
void print_toke(t_token *token)
{
    t_token *current = token;
    int i = 0;
    
    printf("\n--- TOKENS ---\n");
    while (current)
    {
        printf("Token %d: ", i++);
        TT(current->type);
        printf(" | Content: '%s' | Quotes: %d\n", 
               current->s ? current->s : "(null)", 
               current->quotes);
        if (current->type == T_EOF)
            break;
        current = current->next;
    }
    printf("--- END TOKENS ---\n\n");
}
void debug_print_tokens(t_token *tokens) {
    t_token *current = tokens;
    printf("=== TOKEN DEBUG ===\n");
    
    while (current) {
        printf("Token: type=%d, value='%s', quotes=%d, space=%d\n", 
               current->type, current->s ? current->s : "NULL", 
               current->quotes, current->space);
        current = current->next;
    }
    printf("=== END TOKENS ===\n");
}

void debug_print_cmds(t_cmd *cmds) {
    t_cmd *current = cmds;
    int cmd_num = 0;
    
    printf("=== COMMAND DEBUG ===\n");
    while (current) {
        printf("Command %d: cmd='%s'\n", cmd_num, current->cmd ? current->cmd : "NULL");
        
        printf("  Args: ");
        if (current->args) {
            for (int i = 0; current->args[i]; i++) {
                printf("'%s' ", current->args[i]);
            }
        }
        printf("\n");
        
        t_redir *redir = current->rd;
        while (redir) {
            printf("  Redir: type=%d, target='%s'\n", redir->type, 
                   redir->s ? redir->s : "NULL");
            redir = redir->next;
        }
        
        current = current->next;
        cmd_num++;
    }
    printf("=== END COMMANDS ===\n");
}

// Add this to your main parsing function to debug
void debug_parse_input(char *input, t_shell *shell) {
    printf("DEBUG: Input = '%s'\n", input);
    
    // After tokenization
    debug_print_tokens(shell->tkns);
    
    // After parsing
    debug_print_cmds(shell->cmds);
}
