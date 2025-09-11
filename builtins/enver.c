/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enver.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:31:29 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/10 19:31:29 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char    *get_env_value(char **envp, const char *key)
{
  size_t len;
  int i;

  if(!envp || !key)
    return NULL;
  len = ft_strlen(key);
  i = 0;
  while(envp[i])//here we do it bcz we want to check if env[i] start with key=
  {
    if(ft_strncmp(envp[i], key, len) == 0 && env[i][len] == '=')
      return (env[i] + len + 1);
    i++;
  }
  return NULL;
}

// Helper: join key + "=" + value safely using ft_strlcat
static char *join_key_value(const char *key, const char *value)
{
  char *temp;
  char *result;

  if (!key || !value)
    return (NULL);
  temp = ft_strjoin(key, "=");
  if (!temp)
    return (NULL); 
  result = ft_strjoin(temp, value);
  free(temp);
  return (result);
}

static int replace_existing_env(char **envp, const char *key, const char *value)
{
  int i;
  size_t key_len;
  char *new_entry;

  if (!envp || !key || !value)
    return (0);
    
  i = 0;
  key_len = ft_strlen(key);
  while (envp[i])
  {
    if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
    {
      new_entry = join_key_value(key, value);
      if (!new_entry)
        return (0);
      free(envp[i]);
      envp[i] = new_entry;
      return (1);  // Successfully replaced
    }
    i++;
  }
  return (0);  // Not found
}
 
static void append_new_env(char ***envp, const char *key, const char *value)
{
  int i ;
  int j;

  i =0;
  j=0;
  while ((*envp)[i])
     i++;
  char **new_env = malloc(sizeof(char *) * (i + 2)); // old + new + NULL
  if (!new_env)
    return;
  while (j < i)
  {
    new_env[j] = (*envp)[j];
    j++;
  }
  new_env[j] = join_key_value(key, value);
  new_env[j + 1] = NULL;
  free(*envp);
  *envp = new_env;
}

void update_env(char ***envp, const char *key, const char *value)
{
  if (!envp || !key || !value)
    return;
  if (!replace_existing_env(*envp, key, value))
     append_new_env(envp, key, value);
}


/*
in get env this mean while(env[i])//here we do it bcz we want to check if env[i] start with key=
key :is the variable name we want for example "home"
we return the value after = exp ("HOME=/Users/mira" we returns "/Users/mira")
*/