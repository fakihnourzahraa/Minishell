/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:45:04 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/11 20:45:04 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_env *create_env_node(const char *name, const char *value, bool available)
{
  t_env *node; 
  
  node= malloc(sizeof(t_env));
  if (!node)
    return NULL;
  node->name = ft_strdup(name);
  node->val = ft_strdup(value);
  if (!node->name || !node->val)
  {
    free(node->name);
    free(node->val);
    free(node);
    return NULL;
  }
  node->avail = available;
  node->next = NULL;
  return node;
}

// Set/update environment variable
int set_env_var(t_env **env, const char *name, const char *value, bool available)
{
  t_env *node;

  if (!env || !name)
    return 1;
  node = find_env_var(*env, name);
  if (node)
  {
    free(node->val);
    node->val = ft_strdup(value);
    if (!node->val)
      return 1;
    node->avail = available;
    return 0;
  }
  node = create_env_node(name, value, available); // create new
  if (!node)
    return 1;
  node->next = *env; // insert at head
  *env = node;
  return 0;
}

static void remove_head(t_env **env)
{
  t_env *to_remove;

  to_remove = *env;
  *env = (*env)->next;
  free(to_remove->name);
  free(to_remove->val);
  free(to_remove);
}

static void remove_next_node(t_env *current)
{
  t_env *tmp;
  
  tmp = current->next;
  current->next = tmp->next;
  free(tmp->name);
  free(tmp->val);
  free(tmp);
}

int unset_env_var(t_env **env, const char *name)
{
  t_env *current;

  if (!env || !name || !*env)
    return 1;
  if (ft_strcmp((*env)->name, name) == 0)
  {
    remove_head(env);
    return 0;
  }
  current = *env;
  while (current->next)
  {
    if (ft_strcmp(current->next->name, name) == 0)
    {
      remove_next_node(current);
      return 0;
    }
    current = current->next;
  }
  return (0);
}
