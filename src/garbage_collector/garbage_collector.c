/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:47:46 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/09 11:52:31 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_elem;

	new_elem = (t_list *)malloc(sizeof(t_list));
	if (!new_elem)
		return (0);
	new_elem->content = content;
	new_elem->next = 0;
	return (new_elem);
}

void	*ft_malloc(int len, int size, t_var *pvar)
{
	void	*ptr;
	t_list	*garbage;

	ptr = malloc(len * size);
	if (!ptr)
		ft_lstclear_and_exit(&pvar->garbage_collector, free);
	garbage = ft_lstnew(ptr);
	if (!(garbage))
		ft_lstclear_and_exit(&pvar->garbage_collector, free);
	ft_lstadd_front(&pvar->garbage_collector, garbage);
	return (ptr);
}

void	ft_lst_find_and_free_finisher(t_list_explorer *plst_expl, t_list **lst)
{
	if (!plst_expl->voyager && !plst_expl->found_node)
	{
		ft_putstr_fd("Error: find and freenull ", STDERR_FILENO);
		ft_putstr_fd("lst arg is false or no node was found\n", STDERR_FILENO);
		return ;
	}
	else if (plst_expl->voyager && plst_expl->previous_node == 0)
	{
		*lst = plst_expl->next_node;
		free(plst_expl->voyager);
	}
	else if (plst_expl->voyager)
	{
		(plst_expl->previous_node)->next = plst_expl->next_node;
		free(plst_expl->voyager);
	}
}

void	ft_lst_find_and_free(t_list **lst, void *content_to_find)
{
	t_list_explorer	lst_expl;

	lst_expl.previous_node = 0;
	lst_expl.voyager = *lst;
	lst_expl.found_node = 0;
	while (lst_expl.voyager && !lst_expl.found_node)
	{
		if ((lst_expl.voyager)->content == content_to_find)
		{
			lst_expl.found_node++;
			lst_expl.next_node = (lst_expl.voyager)->next;
			free((lst_expl.voyager)->content);
			(lst_expl.voyager)->content = NULL;
		}
		else
		{
			lst_expl.previous_node = lst_expl.voyager;
			lst_expl.voyager = (lst_expl.voyager)->next;
		}
	}
	ft_lst_find_and_free_finisher(&lst_expl, lst);
}
