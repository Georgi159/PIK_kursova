#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
// #include <wchar.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <errno.h>
#include <locale.h>

#define READ_SIZE 100

#define IS_VAR(var,not_beginig_detection) (( \
				( (var)>='A' && (var)<='Z') || \
				( (var)>='a' && (var)<='z') || \
				( (var)>='0' && (var)<='9' && (not_beginig_detection)) || \
				( (var) == '_' ) \
				)?1:0)

int file_magic(FILE *stream,FILE *output, unsigned char File_in, char *line, unsigned size_of_line  , unsigned char stream_in)
{

	int	sz=0;
	if (!stream_in)
	{
		line = malloc(sizeof(char)*READ_SIZE+2);
		fseek(stream, 0L, SEEK_END);
	  	sz = ftell(stream);
		rewind(stream);
		fseek(stream, 0L, SEEK_SET);
	}
	else
	{
		sz=size_of_line;
	}
	
   
	int read_size=READ_SIZE;

	union 
	{
		uint8_t all_flags;
		struct 
		{
			uint8_t	sigleline_coment:1;
			uint8_t	multiline_coment:1;
			uint8_t	string:1;
			uint8_t	ch:1;
		};
	}flags={0};

	struct
	{
		uint8_t  start;
		uint8_t  couted;
		uint32_t count;
 	}var = {0,0,0};


	int left=0,right=0, pairs=0;
	uint8_t error=0;
	unsigned int num_of_turns=sz/READ_SIZE;
	if (sz%READ_SIZE != 0)
	{
		num_of_turns++;
	}

	for (int i = 0; i < num_of_turns ; ++i)
	{
		
		line[0]=line[read_size-1];

		if (num_of_turns-1 == i && sz%READ_SIZE != 0 )
		{
			read_size=sz%READ_SIZE;
		}


		// if ()
		// {
		// 	 code 
		// }
		fread(line+1, sizeof(char), read_size, stream);

		for (int k = 1; k <= read_size; ++k)
		{
			
			switch(line[k])
			{

				case '\n':
				{
					flags.sigleline_coment=0;
					break;
				}
				

				case '"':
				{

					if (line[k-1]=='\\') break;
					if (line[k-1]=='\'') break;
					if (flags.multiline_coment || flags.sigleline_coment) break;

					flags.string= ! flags.string;
					
					break;
				}

				case '\'':
				{
					if (line[k-1]=='\\') break;
					if (line[k-1]=='\'') break;
					if (flags.multiline_coment || flags.sigleline_coment || flags.string) break;

					flags.ch = !flags.ch;
					break;
				}

				case '*':
				{
					if (line[k-1] == '/' )
					{
						flags.multiline_coment=1;
					}
	
					break;
				}

				case '/':
				{
					if (line[k-1] == '/' )
					{
						flags.sigleline_coment=1;
					}
					

					if (line[k-1] == '*')
					{
						flags.multiline_coment=0;
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
					// printf("%c {\n",line[k]);
				//	line[k]='^';
					//printf("\t%d\n",i*read_size+k );
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

					if (right<left)
					{
						error =1;
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
					if (var.couted == 0)
					{
						var.count++;
						var.couted=1;
						var.start =0;
					}
				}


		}

		//printf("left = %d right =%d \n", left, right);

		// fwrite(line, sizeof(char), read_size,stdout);
		
	}
	if (right!=left)
	{
		error =1;
	}



	// printf("%d\n",sz/READ_SIZE  );
	fprintf(output,"%d %d\n",right , left );
	fprintf(output,"pairs =%d error=%d var.count=%d\n", pairs , error,var.count);


	free(line);

	return 0;
}