/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:42:11 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/11 20:42:11 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_env *create_env_node_from_str(char *str)
{
  t_env *node;
  char *equal_sign;
  int name_len;

  node = malloc(sizeof(t_env));
  if (!node)
    return NULL;
  equal_sign = ft_strchr(str, '=');
  if (equal_sign)
  {
    name_len = equal_sign - str;
    node->name = ft_strndup(str, name_len);
    node->val = ft_strdup(equal_sign + 1);
  }
  else
  {
    node->name = ft_strdup(str);
    node->val = ft_strdup("");
  }

  if (!node->name || !node->val)
  {
    free(node->name);
    free(node->val);
    free(node);
    return NULL;
  }
  node->avail = true;
  node->next = NULL;
  return node;
}

t_env *init_env_from_envp(char **envp)
{
  t_env *head = NULL;
  t_env *current = NULL;
  t_env *newnode;
  int i = 0;

  while (envp[i])
  {
    newnode = create_env_node_from_str(envp[i]);
    if (!newnode)
    {
      t_env *tmp;
      while (head)
      {
        tmp = head->next;
        free(head->name);
        free(head->val);
        free(head);
        head = tmp;
      }
      return NULL;
    }
    if (!head)
      head = newnode;
    else
      current->next = newnode;
    current = newnode;
    i++;
  }
  return head;
}


// Find environment variable by name
t_env *find_env_var(t_env *env, const char *name)
{
  t_env *current;

  if (!env || !name)
    return (NULL);
  current = env;
  while (current != NULL)
  {
    if (ft_strcmp(current->name,name) == 0)
      return current;
    current = current->next;
  }
  return NULL;
}

// Get environment variable value
char *get_env_value(t_env *env, const char *name)
{
  t_env *node;

  node = find_env_var(env, name);
  if (!node || node->avail == false)
    return NULL;
  return node->val;
}
