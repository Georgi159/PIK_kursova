#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <locale.h>

#define READ_SIZE 500

#define IS_VAR(var,not_beginig_detection) (( \
				( (var)>='A' && (var)<='Z') || \
				( (var)>='a' && (var)<='z') || \
				( (var)>='0' && (var)<='9' && (not_beginig_detection)) || \
				( (var) == '_' ) \
				)?1:0)




int file_magic(FILE *stream, FILE *output)
{

	char line[READ_SIZE + 3] = {0};

	union
	{
		uint8_t all_flags;
		struct
		{
			uint8_t	sigleline_coment: 1;
			uint8_t	multiline_coment: 1;
			uint8_t	string: 1;
			uint8_t	ch: 1;
		};
	} flags = {0};

	struct
	{
		uint8_t  start;
		uint8_t  couted;
		uint32_t count;
	} var = {0, 0, 0};


	int left = 0, right = 0, pairs = 0;
	uint8_t error = 0;


	for (int i = 0; fgets(&line[2], READ_SIZE, stream ) ; ++i)
	{

		for (int k = 2; line[k] != '\0' ; ++k)
		{

			switch (line[k])
			{

			case '\n':
			{
				flags.sigleline_coment = 0;
				break;
			}


			case '"':
			{

				if (line[k - 1] == '\\') break;
				if (line[k - 1] == '\'') break;
				if (flags.multiline_coment || flags.sigleline_coment) break;

				flags.string = ! flags.string;

				break;
			}

			case '\'':
			{
				if (line[k - 1] == '\\'  && line[k - 2] != '\\'  ) break;
				// if (line[k - 1] == '\'') break;
				if (flags.multiline_coment || flags.sigleline_coment || flags.string) break;

				flags.ch = !flags.ch;
				break;
			}

			case '*':
			{
				if (line[k - 1] == '/' )
				{
					flags.multiline_coment = 1;
				}

				break;
			}

			case '/':
			{
				if (line[k - 1] == '/' )
				{
					flags.sigleline_coment = 1;
				}


				if (line[k - 1] == '*')
				{
					flags.multiline_coment = 0;
				}
				break;
			}

			case  '{':
			{
				if (flags.all_flags)
				{
					break;
				}

				right++;
				break;
			}
			case  '}':
			{

				if (flags.all_flags)
				{
					break;
				}

				if (right > left)
				{
					pairs++;
				}

				left++;

				if (right < left)
				{
					error = 1;
				}

				break;
			}

			}


			if (IS_VAR( line[k], var.start ) && !flags.all_flags)
			{
				if (var.start == 0)
				{
					var.start  = 1;
					var.couted = 0;
				}

			}
			else
			{
				if (var.couted == 0 && var.start == 1)
				{
					var.count++;
					var.couted = 1;
					var.start = 0;
				}
			}


		}


	}
	if (right != left)
	{
		error = 1;
	}

	printf("%d %d %d\n", right , left , flags.all_flags );
	fprintf(output, "Блокове код = %d \nгрешки = %s \nброй \"променливи\" = %d\n", pairs , (error)? "има" : "няма", var.count);

	return 0;
}