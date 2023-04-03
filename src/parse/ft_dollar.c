#include "../include/minishell.h"

int ft_check_dollar(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '$')
            return 1;
        i++;
    }
    return 0;
}


int ft_detect_dub_quote(char *data)
{
	char *arg_letters = data;
 	for (int i = 0, j = ft_strlen(arg_letters); i < j; i++)
   {
      for (int k = i+1; k < j; k++)
      {
         if (arg_letters[i] == arg_letters[k])
         {
			 if (arg_letters[i] == '\"')
            return 1;
         }

      }
   }
   return 0;
}

int ft_dollar_error()
{
    printf("0 for now");
    return 0;
}

int ft_dollar_sign(char *str)
{
    if (ft_check_dollar(str) && ft_detect_dub_quote(str))
        return 1;
    else if (!ft_strcmp(str, "$?"))
        ft_dollar_error();
    return 0;
}


