#include "ft_malloc.h"

void	double_free() {
	exit(2);
}

void	pointer_not_allocated() {
	exit(1);
}

bool	is_inside_zone(t_list *l_zone, void *ptr) {
	t_zone_header *zone = (t_zone_header *)l_zone->content;
	return (ptr >= zone && ptr < (zone + zone->zone_size - LL_NODE_SIZE));
}

bool	is_linked_alloc(t_list *l_alloc, void *ptr) {
	return (ptr == (void *)l_alloc->content + ALLOC_HEADER_SIZE);
}

void	free(void *ptr) {
	t_list	*l_zone;

	if (ptr == NULL)
		return ;

	// this is the find pointer link part
	// needs its own function for use in realloc
	l_zone = ft_lstfind_l(g_head, ptr, is_inside_zone());
	if (l_zone == NULL)
		pointer_not_allocated();
	t_zone_header *zone = (t_zone_header *)l_zone->content;
	t_list **pl_alloc = ft_lstfind_pl(&zone->alloc_head, ptr, is_linked_alloc());
	if (pl_alloc == NULL)
		double_free();

	// this is the free part
	*pl_alloc = *pl_alloc->next;
}