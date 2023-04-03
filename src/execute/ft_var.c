#include "../include/minishell.h"
#include "../libft/libft.h"
#define j 100000000

void	show_var(char *lineptr, struct node *head)
{
	int			i;
	char		*contact;
	struct node	*temp;
	
	i = 1;
	if (*lineptr == '$')
		lineptr++;
	get_name(lineptr);
	contact = lineptr;
	temp = head;
	while (temp != NULL)
	{
		if (strstr(temp->data, contact))
		{
			printf("$var saved is : %s\n", temp->data);
		}
		temp = temp->nxtpointer;
		i++;
	}
}

char	*ft_var_content(char *lineptr, struct node *head)
{
	char		*contact;
	char		*new;
	int			i;
	struct node	*temp;

	if (*lineptr == '$')
		lineptr++;
	contact = lineptr;
	new = NULL;
	i = 1;
	temp = head;
	while (temp != NULL)
	{
		if (strstr(temp->data, contact))
		{
			new = get_arg_content(temp->data);
		}
		temp = temp->nxtpointer;
		i++;
	}
	return (new);
}

char	*get_arg_to_del(char *lineptr)
{
	size_t	i;
	char	*interesting_stuff;

	i = 0;
	while (i < strlen(lineptr))
	{
		if (lineptr[i] == ' ')
		{
			interesting_stuff = lineptr + i + 1;
		}
		i++;
	}
	return (interesting_stuff);
}

char	*ft_remove_value(char* str)
{
	char	*ptr;
	
	ptr = ft_strchr(str, '=');
	if (ptr != NULL)
		*ptr = '\0';
	return (ptr);
}

struct node	*delete_var(char *lineptr, struct node *head_ref)
{
	struct node	*tmp;
    struct node	*temp;
	struct node	*current;	
	char		*p;
	char		*str;
	
	temp = head_ref;
	lineptr = strremove(lineptr, "unset ");
	if (ft_double_detect_quote(lineptr))
	{
		p = ft_delete_quote(lineptr);
		printf("deteletd quote %s", p);
	}
	else
		p = lineptr;
	if (*p == '$')
		p++;
	str = get_name(p);
	if (!ft_strcmp(get_name(head_ref->data), str))
	{
		printf("\nFirst element deleted is : %s\n", temp->data);
		head_ref = temp->nxtpointer; // Advancing the head pointer
		temp->nxtpointer = NULL;
		free(temp);
	}
	else
	{
		current = head_ref;
		while (current->nxtpointer != NULL)
		{
			if (!ft_strcmp(get_name(current->nxtpointer->data), str))
			{
				tmp = current->nxtpointer;
				current->nxtpointer = current->nxtpointer->nxtpointer;
				printf("\nElement deleted is : %s\n", tmp->data);
				free(tmp);
				break ;
			}
			else
				current = current->nxtpointer;
		}
	}
	return (head_ref);
}

struct node	*del_path(char *now)
{
	char	**s;
	int		i;
	size_t	len;
	
	i = 0;
	s = &now;
	while (s[i])
	{
		if (strstr(s[i], "PATH"))
		{
			len = ft_strlen(s[i]);
			memcpy(s[i], now, len);
			printf("%s\n [%d] \n", s[i], i);
		}
		i++;
	}
	return (head_ref);
}

void	ft_add_back(char *cpy)
{
	struct node	*fnode;
	struct node	*tmp;
	
	fnode = (struct node *)malloc(sizeof(struct node));
	if (fnode == NULL)
	{
		printf(" Memory can not be allocated.");
	}
	else
	{
		fnode->data = cpy;
		fnode->nxtpointer = NULL;
		tmp = head_ref;
		while (tmp->nxtpointer != NULL)
			tmp = tmp->nxtpointer;
		tmp->nxtpointer = fnode;
	}
}

void	ft_linked_list(char *cpy)
{
	if (ft_strchr(cpy, '$') && !strstr(cpy, "export $") && !strstr(cpy, "export \"$"))
		show_var(cpy, head_ref);
	else if (!ft_strcmp(cpy, "env"))
		display_node(head_ref);
	else if (ft_strchr(cpy, '=') && !ft_detect_quote(cpy) && !strstr(cpy, "export ") && !strstr(cpy, "unset "))
	{
		head = add_to_var(cpy, head);
		display_linked_node(head);
	}
	ft_export(cpy);
	ft_unset(cpy);
}
