/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:23:49 by cdaveux           #+#    #+#             */
/*   Updated: 2022/03/22 14:10:36 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum {
	PIPE,
	DOLLAR_SIGN,
	DOUBLE_QUOTE,
	SIMPLE_QUOTE,
	REDIR_IN,
	REDIR_OUT,
	ASSIGN,
	DOUBLE_GREATER,
	HEREDOC,
	WORD
} token_type;

typedef enum {
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
	HEREDOC,
	CMD,
	ARG
}

#endif
