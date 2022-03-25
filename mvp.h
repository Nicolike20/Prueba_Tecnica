/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:29:09 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/25 14:55:09 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MVP_H
# define MVP_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_match_data
{
	char	*team_one;
	char	*team_two;
}t_match_data;

typedef struct s_bkt_pl
{
	char			*player_name;
	char			*nickname;
	int				number;
	char			*team_name;
	char			*position;
	int				scored_points;
	int				rebounds;
	int				assists;
	int				total_points;
	struct s_bkt_pl	*next;
}t_bkt_pl;

typedef struct s_hnd_pl
{
	char			*player_name;
	char			*nickname;
	int				number;
	char			*team_name;
	char			position;
	int				goals_made;
	int				goals_received;
	struct s_hnd_pl	*next;
}t_hnd_pl;

#endif
