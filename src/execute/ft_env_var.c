#include "../include/minishell.h"

struct node	*ft_var_main(char *argv, struct node *head_ref)
{
	struct node	*temp;
	
	temp = NULL;
	head_ref = create_list(&head_ref, argv);
	temp = head_ref;
	return (temp);
}

struct node	*ft_link_env(void)
{
	char	**s;
	s = environ;
	while (*s)
	{
		head_ref = ft_var_main(*s, head_ref);
		s++;
	}
	return (head_ref);
}

void	get_env(void)
{
	char	**s;
	int		i;
	
	s = environ;
	i = 0;
	while (s[i] != NULL)
	{
		printf("[%d] = %s \n", i, s[i]);
		i++;
	}
	return ;
}
