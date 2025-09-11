/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:29:11 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/09 12:29:11 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char *get_target_path(char **args, t_shell *shell)
{
  if( args[0] == NULL)
    return 
}// this fct take the arg after if it is (.. ,~,-),return the malloc of string with the real path env
static int  change_directory(const char *target, t_shell *shell)
{

}// this fct updt the pwd,old pwd 

int         builtin_cd(t_cmd *cmd, t_shell *shell)
{

}//this fct tale full cmnd
