/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:12:11 by nour              #+#    #+#             */
/*   Updated: 2025/09/15 19:12:24 by nour             ###   ########.fr       */
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