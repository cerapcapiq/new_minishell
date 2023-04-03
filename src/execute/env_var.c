#include "../include/minishell.h"

struct node	*display_node(struct node *head_ref)
{
	struct node	*temp;
	
	temp = head_ref;
	while (temp != NULL)
	{
		if (temp->nxtpointer == NULL)
		{
			printf(" %s->NULL\n", temp->data);
		}
		else
		{
			printf("\n%s->", temp->data);
		}
		temp = temp->nxtpointer; // Traversing the List till end
	}
	return (head_ref);
}

char	*get_name(char *linestr)
{
	char	*str;
	char	*cpy;
	int		i;
	
	str = linestr;
	i = 0;
	while (str[i] != '=')
		i++;
	cpy = ft_substr(str, 0, i);
	return (cpy);
}

void	get_arg(char *lineptr)
{
	char	*str;
	char	*arg;
	size_t	j = 0;
	char	after[j];
	size_t	len;

	str = lineptr;
	arg = str;
	if (arg == ft_strchr(str, '='))
	{
		len = ft_strlen (++arg);
		if (len > j - 1)
		{
			printf("error");
		}
		memcpy (after, arg, len + 1);
		printf ("the arg(value) is %s\n", arg);
	}
}

char	*get_arg_content(char *lineptr)
{
	size_t	i;
	char	*interesting_stuff;
	
	i = 0;
	while (i < strlen(lineptr))
	{
		if (lineptr[i] == '=')
		{
			interesting_stuff = lineptr + i + 2;
		}
		i++;
	}
	return (interesting_stuff);
}

struct node	*create_list(struct node **head_ref, char *lineptr)
{
	char		*nodedata;
	struct node	*new;
	struct node	*last;
	
	new = malloc(sizeof(struct node));
	nodedata = lineptr;
	new->data = nodedata;
	new->nxtpointer = NULL;
	if (*head_ref == NULL)
		*head_ref = new;
	else
	{
		last = *head_ref;
		while (last->nxtpointer != NULL)
		{
			last = last->nxtpointer;
		}
		last->nxtpointer = new;
	}
	return (*head_ref);
}
