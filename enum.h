/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:23:49 by cdaveux           #+#    #+#             */
/*   Updated: 2022/03/22 15:29:43 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum {
	PIPE = 0,
	DOLLAR_SIGN = 1,
	DOUBLE_QUOTE = 2,
	SIMPLE_QUOTE = 3,
	REDIR_IN = 4,
	REDIR_OUT = 5,
	ASSIGN = 6,
	DOUBLE_GREATER = 7,
	HEREDOC = 8,
	WORD = 9
} token_type;

typedef enum {
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
	OUTFILE_HEREDOC,
	CMD,
	ARG
} token_cmd;

#endif
