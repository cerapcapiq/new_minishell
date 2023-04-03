#include "../include/minishell.h"

struct LinkedList	*display_linked_node(struct LinkedList *head)
{
	struct LinkedList	*temp;
	
	temp = head;
	while (temp != NULL)
	{
		if (temp->next == NULL)
		{
			printf(" %s->NULL\n", temp->data);
		}
		else
		{
			printf("\n%s->", temp->data);
		}
		temp = temp->next;
	}
	return (head);
}

char	*ft_add_var_content(char *lineptr, struct LinkedList *head)
{
	char				*contact;
	char				*new;
	int					i;
	struct LinkedList	*temp = head;
	
	if (*lineptr == '$')
		lineptr++;
	contact = lineptr;
	new = NULL;
	i = 1;
	while (temp != NULL)
	{
		if (strstr(temp->data, contact))
		{
			new = temp->data;
			printf("%s whre is it", new);
		}
		temp = temp->next;
		i++;
	}
	return (new);
}

struct LinkedList	*ft_create_list(struct LinkedList **head, char *str)
{
	char				*nodedata;
	struct LinkedList	*new;
	struct LinkedList	*last;
	
	new = malloc(sizeof(struct LinkedList));
	nodedata = str;
	new->data = nodedata;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		last = *head;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new;
	}
	return (*head); 
}

char	*get_the_new_var(char *lineptr, struct LinkedList *head)
{
	int					i;
	char				*search;
	struct LinkedList	*temp;
	
	i = 1;
	lineptr = ft_delete_quote(lineptr);
	if (*lineptr == '$')
		lineptr++;
	search = lineptr;
	temp = head;
	while (temp != NULL)
	{
		if (strstr(temp->data, search))
		{
			printf("$var saved is : %s\n",temp->data);
			return (temp->data);
		}
		temp = temp->next;
		i++;
	}
	return (NULL);
}

struct LinkedList	*ft_pass_content(char *cpy, struct LinkedList *head)
{
	head = ft_create_list(&head, cpy);
	return (head);
}

struct LinkedList	*add_to_var(char *str, struct LinkedList *head)
{
	head = ft_pass_content(str, head);
	return (head);
}

char	*strremove(char *str, const char *sub)
{
	char	*p;
	char	*q;
	char	*r;
	size_t	len;

	if (*sub && (q = r = strstr(str, sub)) != NULL)
	{
		len = strlen(sub);
		while ((r = strstr(p = r + len, sub)) != NULL)
		{
			while (p < r)
				*q++ = *p++;
		}
		while ((*q++ = *p++) != '\0')
			continue ;
	}
	return (str);
}
