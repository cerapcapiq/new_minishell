#include "../include/minishell.h"

void	ft_export(char *str)
{
	if (strstr(str, "export $") || strstr(str, "export ") || strstr(str, "export \"$"))
	{
		str = strremove(str, "export ");
		str = get_the_new_var(str, head);
		if (str != NULL)
			ft_add_back(str);
		else
			printf("non exisxtent");
	}
	else if (!ft_strcmp(str, "export"))
		display_node(head_ref);
}

void	ft_unset(char *str)
{
	if (strstr(str, "unset $") || strstr(str, "unset ") || strstr(str, "unset \"$"))
	{
		str = strremove(str, "unset ");
		delete_var(str, head_ref);
	}
	else
		return ;
}
