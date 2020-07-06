/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:20:55 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/06 16:12:28 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_anim      *create_animation(t_engine *eng, float latency)
{
    t_anim  *anim;

    if (!(anim = malloc(sizeof(t_anim))))
        return (NULL);
    anim->latency = latency;
    anim->frames = NULL;
    anim->curr_lat = 0;
    ft_lstadd_back(&eng->animations, ft_lstnew(anim));
    return (anim);
}

void        set_anim_ptr(t_anim *anim, t_image **tex_ptr)
{
    anim->anim_ptr = tex_ptr;
}

void        add_animation_frame(t_anim *anim, t_image *frame)
{
    t_list  *anim_node;

    anim_node = ft_lstnew(frame);
    anim_node->next = anim->frames;
    ft_lstadd_back(&anim->frames, anim_node);
}

void        perform_animations(t_engine *eng)
{
    t_anim  *anim;

    while (eng->animations)
    {
        anim = (t_anim *)eng->animations->content;
        if (anim->curr_lat < anim->latency)
            anim->curr_lat++;
        else
        {
            *(anim->anim_ptr) = (t_image *)anim->frames->content;
            anim->frames = anim->frames->next;
            anim->curr_lat = 0;
        }
        eng->animations = eng->animations->next;
    }
}