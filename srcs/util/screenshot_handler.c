/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:04:24 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/08 17:05:11 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	take_screenshot(t_engine *eng)
{
	int		status;

	printf("[SCREENSHOT] Taking screenshot...\n");
	status = export_frame(eng, "image.bmp");
	if (status == -1)
		printf("[SCREENSHOT] Unable to take screenshot \
: screenshot folder is missing.\n");
	else if (status == -2)
		printf("[SCREENSHOT] Unable to take screenshot \
: cannot open file ./screenshot/image.bmp\n");
	else
		printf("[SCREENSHOT] Successfully saved screenshot at \
: ./screenshots/image.bmp\n");
}
