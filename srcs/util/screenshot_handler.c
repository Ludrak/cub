/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:04:24 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/11 14:31:53 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	take_screenshot(t_engine *eng)
{
	int		status;

	eng->first_screen = 0;
	ft_printf("[SCREENSHOT] Taking screenshot...\n");
	status = export_frame(eng, "image.bmp");
	if (status == -1)
		ft_printf("[SCREENSHOT] Unable to take screenshot \
: screenshot folder is missing.\n");
	else if (status == -2)
		ft_printf("[SCREENSHOT] Unable to take screenshot \
: cannot open file ./screenshot/image.bmp\n");
	else
		ft_printf("[SCREENSHOT] Successfully saved screenshot at \
: ./screenshots/image.bmp\n");
}
