#include <fcntl.h>
#include "egginshell.h"

int
	process_open_o(t_cmd *current, t_charbox *cur_io) // 나눴음
{
	int	mode;

	if (cur_io->type == RD_OO)
		mode = O_RDWR | O_CREAT | O_APPEND;
	else
		mode = O_RDWR | O_CREAT | O_TRUNC;
	if (current->output_fd > 2)
		close(current->output_fd);
	if (try_open(&current->output_fd, cur_io->data, mode, 0644))
		return (1);
	current->last_output = cur_io;
	return (0);
}

int
	process_open(t_cmd *current, t_charbox *cur_io, t_charbox *cur_theredoc)
{
	int	ret;

	ret = 0;
	if (cur_io->type == RD_II)
	{
		current->last_input = cur_theredoc;
		cur_theredoc = cur_theredoc->next;
	}
	else if (cur_io->type == RD_I)
	{
		if (current->input_fd > 2)
			close(current->input_fd);
		if (try_open(&current->input_fd, cur_io->data, O_RDONLY, 0))
			return (1);
		current->last_input = cur_io;
	}
	else
		ret = process_open_o(current, cur_io);
	return (ret);
}
