/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:22:45 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/25 15:00:27 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Explicación de la idea general del codigo:
//como se puede ver, no está terminado, la idea era guardar todos los datos
//de los jugadores en una estructura, calculando para cada jugador sus
//respectivos puntos. Despues se calcula cual es el equipo ganador y se le
//añade los puntos bonus a los jugadores que hayan ganado. Por ultimo
//se comparan los puntos de todos los jugadores para ver quien es el MVP
//El codigo para handball seria igual que para basketball pero teniendo en
//cuenta el cambio en los datos numericos.

#include "mvp.h"

void	free_data(char **data)
{
	int	i;

	i = 8;
	while (--i >= 0)
		free (data[i]);
	free(data);
}

void	match_data_init(t_match_data *match_data)
{
	match_data->team_one = NULL;
	match_data->team_two = NULL;
}

void	init_bkt_pl(t_bkt_pl *bkt_pl, char **data, t_match_data *match_data)
{
	bkt_pl->player_name = strdup(data[0]);
	bkt_pl->nickname = strdup(data[1]);
	bkt_pl->number = atoi(data[2]);
	bkt_pl->team_name = strdup(data[3]);
	bkt_pl->position = strdup(data[4]);
	bkt_pl->scored_points = atoi(data[5]);
	bkt_pl->rebounds = atoi(data[6]);
	bkt_pl->assists = atoi(data[7]);
	bkt_pl->total_points = 0;
	if (match_data->team_one == NULL)
		match_data->team_one = strdup(bkt_pl->team_name);
	else if (match_data->team_two == NULL)
		match_data->team_two = strdup(bkt_pl->team_name);
	else if (strcmp(match_data->team_one, bkt_pl->team_name)
			&& strcmp(match_data->team_two, bkt_pl->team_name)
			&& (match_data->team_one != NULL && match_data->team_two != NULL))
	{
		write (2, "Error: invalid teams\n", 21);
		exit (1);
	}
}

void	calculate_basket(t_bkt_pl *bkt_pl)
{
	if (bkt_pl->position[0] == 'G')
		bkt_pl->total_points = (bkt_pl->scored_points * 2)
			+ (bkt_pl->rebounds * 3)
			+ (bkt_pl->assists * 1);
	else if (bkt_pl->position[0] == 'F')
		bkt_pl->total_points = (bkt_pl->scored_points * 2)
			+ (bkt_pl->rebounds * 2)
			+ (bkt_pl->assists * 2);
	else if (bkt_pl->position[0] == 'C')
		bkt_pl->total_points = (bkt_pl->scored_points * 2)
			+ (bkt_pl->rebounds * 1)
			+ (bkt_pl->assists * 3);
	else
	{
		write (2, "Error: invalid player position\n", 31);
		exit (1);
	}
}

void	basket_match(char **argv)
{
	int				i;
	int				j;
	char			*split;
	char			**data;
	int				team_one_points;
	int				team_two_points;
	t_match_data	*match_data;
	t_bkt_pl		*bkt_pl;
	t_bkt_pl		*temp;
	t_bkt_pl		*head;

	i = 1;
	team_one_points = 0;
	team_two_points = 0;
	match_data = malloc(sizeof(match_data));
	if (match_data == NULL)
		exit (1);
	match_data_init(match_data);
	bkt_pl = NULL;
	head = bkt_pl;
	while (argv[++i])
	{
		bkt_pl = malloc(sizeof(bkt_pl));
		if (bkt_pl == NULL)
			exit (1);
		data = malloc(sizeof(char *) * 9);
		if (data == NULL)
			exit (1);
		j = 0;
		split = strtok(argv[i], ";");
		while (split != NULL)
		{
			data[j++] = strdup(split);
			split = strtok(NULL, ";");
		}
		data[j] = NULL;
		if (j != 8)
		{
			write (2, "Invalid arguments\n", 18);
			exit (1);
		}
		init_bkt_pl(bkt_pl, data, match_data);
		calculate_basket(bkt_pl);
		if (!strcmp(bkt_pl->team_name, match_data->team_one))
			team_one_points += bkt_pl->scored_points;
		else if (!strcmp(bkt_pl->team_name, match_data->team_two))
			team_two_points += bkt_pl->scored_points;
		temp = bkt_pl;
		bkt_pl = bkt_pl->next;
		temp->next = bkt_pl;
		free_data(data);
	}

}

void	hand_match(char **argv)
{
	int	i;

	i = 1;
	printf("handball\n");
}

int	main(int argc, char **argv)
{
	if (argc >= 3)
	{
		if (!strcmp(argv[1], "basketball"))
			basket_match(argv);
		else if (!strcmp(argv[1], "handball"))
			hand_match(argv);
		else
		{
			write (2, "Error: first argument is not a valid match type\n", 48);
			return (1);
		}
	}
	else
	{
		write (2, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	return (0);
}
