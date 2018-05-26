#include<stdio.h>
#include<malloc.h>
#include<string.h>
/*int strtonum(char *str)
{
	int n = 0, i = 0;
	while (str[i] != '\0')
		n = n * 10 + (str[i++] - 48);
	return n;
}
char*** import(FILE*fp,char ***ss,int *maxrows,int *maxcols)
{
	char ***s1,string[60];
	int n = 0, flag = 0, i = 0, x,buff=0;
	char *line = (char*)malloc(sizeof(char) * 100);
	fgets(line, 100, fp);
	while (fgets(line, 100, fp))
	{
		n++;
	}
	buff = *maxrows;
	*maxrows =n+*maxrows;
	ss = (char***)realloc(ss,*maxrows*sizeof(char***));
	s1 = ss;
	fseek(fp, 0, SEEK_SET);
	flag = 0;
	int z = buff;
	for (i = buff; i < *maxrows; i++)
	{
		s1[i] = (char**)malloc((*maxcols)*sizeof(char**));
	}
	fgets(line, 100, fp);
	while (z<*maxrows&&fgets(line, 100, fp))
	{
		i = 0;
		while (i<strlen(line) && line[i] != '\0')
		{
			x = 0;
			while (i<strlen(line)&&line[i] != ','&&line[i] != '\0'&&line[i]!='\n')
				string[x++] = line[i++];
			string[x] = '\0';
			s1[z][flag%*maxcols] = (char*)malloc(strlen(string)*sizeof(char));
			strcpy(s1[z][flag % (*maxcols)], string);
			flag++;
			i++;
		}
			z++;
	}
	return s1;
}
void flush(FILE*fp, char ***ss, int *maxrows, int *maxcols)
{
	for (int i = 0; i < *maxrows; i++)
	{
		for (int j = 0; j < *maxcols; j++)
		{
			fputs(ss[i][j], fp);
			fputc(',', fp);
		}
		fputc('\n', fp);
	}
}
char*** create(char* columns,int *maxrows,int *maxcols,int n)
{
	*maxcols = n;
	*maxrows = 1;
	int i = 0,x,z=0;
	char colname[20];
	char ***s = (char***)malloc(sizeof(char***));
	*s = (char**)malloc(sizeof(char**)*n);
	while (i<strlen(columns)&&columns[i] != '\0')
	{
		x = 0;
		while (columns[i] != ':'&&columns[i]!='\0')
			colname[x++] = columns[i++];
		colname[x] = '\0';
		s[0][z] = (char*)malloc(sizeof(char)*strlen(colname));
		strcpy(s[0][z], colname);
		i++;
		z++;
	}
	return s;
}
char*** join(char ***s1, char ***s2, int *mr1, int *mc1, int *mr2, int *mc2, int *mr3, int *mc3)
{
	int rows = *mr1>*mr2?*mr1:*mr2;
	int cols = *mc1 + *mc2-1;
	char val[100];
	printf("[%d %d]", *mr1, *mr2);
	char ***s3 = (char***)malloc(rows*sizeof(char***));
	for (int i = 0; i < rows; i++)
		s3[i] = (char**)malloc(cols*sizeof(char**));
	for (int j = 0; j < cols; j++)
	{
		if (j < *mc1)
		{
			s3[0][j] = (char*)malloc(sizeof(char)*strlen(s1[0][j]));
			strcpy(s3[0][j], s1[0][j]);
		}
		else
		{
			s3[0][j] = (char*)malloc(sizeof(char)*strlen(s2[0][j+1-*mc1]));
			strcpy(s3[0][j], s2[0][j+1 - *mc1]);
		}
	}
	for (int i = 1; i < *mr1; i++)
	{
		strcpy(val, s1[i][0]); 
		for (int j = 0; j < *mr2; j++)
		{
			if (!strcmp(val, s2[j][0]))
			{
				int z = 0;
				for (int k = 0; k < *mc1; k++)
				{
					s3[i][z] = (char*)malloc(sizeof(char)*strlen(s1[i][k]));
					strcpy(s3[i][z++], s1[i][k]);
				}
				for (int k = 1; k < *mc2; k++)
				{
					s3[i][z] = (char*)malloc(sizeof(char)*strlen(s2[j][k]));
					strcpy(s3[i][z++], s2[j][k]);
				}
				break;
			}
		}
	}
	*mr3 = rows;
	*mc3 = cols;
	return s3;
}
void query(char ***s, char *required, int *mr, int *mc, char *condition)
{
	int *flag = (int*)malloc(sizeof(int)*(*mc));
	for (int i = 0; i < *mc; i++)
		flag[i] = 0;
	char op[4], val[10], name[20];
	name[0] = '\0';
	int i = 0, x = 0, stat = 0;
	if (strstr(condition, "contains") || strstr(condition, "matches"))
	{
		i = 0; x = 0;
		while (condition[i] != '"')
			i++;
		i++;
		while (condition[i] != '"')
			name[x++] = condition[i++];
		name[x] = '\0';
	}
	if (condition[0] != '\0'&&!strstr(condition, "contains") && !strstr(condition, "matches"))
	{
		i = 0;
		while ((condition[i] > 64 && condition[i] < 91) || (condition[i]>96 && condition[i] < 123) || (condition[i] >= 48 && condition[i] <= 57))
			i++;
		printf("%c", condition[i]);
		while (condition[i] < 48 || condition[i]>57)
			op[x++] = condition[i++];
		op[x] = '\0';
		x = 0;
		while (condition[i] != '\0')
			val[x++] = condition[i++];
		val[x] = '\0';
	}
	if (!strcmp(required, "*"))
	{
		for (i = 0; i < *mc; i++)
		{
			flag[i] = 1;
			stat = 1;
		}
		printf("\n");
	}
	else
	{
		for (i = 0; i < *mc; i++)
			if (strstr(required, s[0][i]))
			{
				flag[i] = 1;
				stat = 1;
			}
	}
	if (!stat)
	{
		printf("Invalid Column Name.Column Names are case-sensitive!\nQuery Successful\n");
		return;
	}
	if (condition[0] == '\0')
	{
		if (!stat)
		{
			printf("Invalid Column Name.Column Names are case-sensitive!\nQuery Successful\n");
			return;
		}
		else
		{
			for (x = 0; x < *mr; x++)
			{
				for (i = 0; i < *mc; i++)
					if (flag[i])
						printf("%s\t\t", s[x][i]);
				printf("\n");
			}
		}
	}
	else
	{
		for (int j = 0; j < *mc; j++)
			if (flag[j])
				printf("%s\t\t", s[0][j]);
		printf("\n"); 
		for (i = 0; i < *mc; i++)
		{
			if (strstr(condition, s[0][i]))
			{
				if (name[0] != '\0')
				{
					if (strstr(condition, "contains"))
					{
						for (int j = 1; j < *mr; j++)
						{
							if (strstr(s[j][i], name))
							{
								for (int k = 0; k < *mc; k++)
									if (flag[k])
										printf("%s\t\t", s[j][k]);
								printf("\n");
							}
						}
					}
					else if (strstr(condition, "matches"))
					{
						for (int j = 1; j < *mr; j++)
						{
							if (!strcmp(s[j][i], name))
							{
								for (int k = 0; k < *mc; k++)
									if (flag[k] == 1)
										printf("%s\t\t", s[j][k]);
								printf("\n");
							}
						}
					}
				}
				else
				{
					if (!strcmp(op, "="))
					{
						for (int j = 1; j < *mr; j++)
						{
							if (strtonum(s[j][i]) == strtonum(val))
							{
								for (int k = 0; k < *mc; k++)
									if (flag[k] == 1)
										printf("%s\t\t", s[j][k]);
								printf("\n");
							}
						}
					}
					else if (!strcmp(op, "<="))
					{
						for (int j = 1; j < *mr; j++)
						{
							if (strtonum(s[j][i]) <= strtonum(val))
							{
								for (int k = 0; k < *mc; k++)
									if (flag[k] == 1)
										printf("%s\t\t", s[j][k]);
								printf("\n");
							}
						}
					}
					else if (!strcmp(op, ">="))
					{
						for (int j = 1; j < *mr; j++)
						{
							if (strtonum(s[j][i]) >= strtonum(val))
							{
								for (int k = 0; k < *mc; k++)
									if (flag[k] == 1)
										printf("%s\t\t", s[j][k]);
								printf("\n");
							}
						}
					}
					else if (!strcmp(op, "<"))
					{
						for (int j = 1; j < *mr; j++)
						{
							if (strtonum(s[j][i]) < strtonum(val))
							{
								for (int k = 0; k < *mc; k++)
									if (flag[k] == 1)
										printf("%s\t\t", s[j][k]);
								printf("\n");
							}
						}
					}
					else if (!strcmp(op, ">"))
					{
						for (int j = 1; j < *mr; j++)
						{
							if (strtonum(s[j][i]) > strtonum(val))
							{
								for (int k = 0; k < *mc; k++)
									if (flag[k] == 1)
										printf("%s\t\t", s[j][k]);
								printf("\n");
							}
						}
					}
				}
				break;
			}
		}
	}
	printf("Query Successful!\n");
}
int main()
{
	char command[150],cmd[20],columns[100],filename[30],required[50],condition[60];
	char ***s1, ***s2, ***s3;
	int mr1 = 0, mr2 = 0, mr3 = 0, mc1 = 0, mc2 = 0, mc3 = 0;
	int i=0,x=0;
	while (1)
	{
		printf("\nDB_ENGINE_DYN>");
		gets(command);
		i = 0;
		while (i < strlen(command) && command[i] != '\0')
		{
			x = 0;
			while (command[i] != ' ')
				cmd[x++] = command[i++];
			cmd[x] = '\0';
			i++;
			if (!strcmp(cmd, "create"))
			{
				i += 8;
				int s = command[i] - 48;
				i+=2;
				int n = command[i] - 48;
				i+=2;
				x = 0;
				while (command[i] != '\0')
					columns[x++] = command[i++];
				columns[x] = '\0';
				switch (s)
				{
				case 1:s1 = create(columns,&mr1,&mc1,n); printf("Created Schema S1\n"); break;
				case 2:s2 = create(columns,&mr2,&mc2,n); printf("Created Schema S2\n"); break;
				}
			}
			else if (!strcmp(cmd, "import"))
			{
				x = 0;
				while (command[i] != ' ')
					filename[x++] = command[i++];
				filename[x] = '\0';
				FILE *fp = fopen(filename, "r");
				i = i + 2;
				int schema = command[i] - 48;
				switch (schema)
				{
				case 1:s1 = import(fp,s1, &mr1, &mc1); printf("Import Successful\n"); break;
				case 2:s2 = import(fp,s2, &mr2, &mc2); printf("Import Successful\n"); break;
				default:printf("Invalid Schema\n");
				}
			}
			else if (!strcmp(cmd, "exit"))
				return 1;
			else if (!strcmp(cmd, "flush"))
			{
				x = 0;
				while (command[i] != ' ')
					filename[x++] = command[i++];
				filename[x] = '\0';
				FILE *fp = fopen(filename, "w");
				i = i + 2;
				int schema = command[i] - 48;
				switch (schema)
				{
				case 1:flush(fp, s1, &mr1, &mc1); printf("Flush Successful\n"); break;
				case 2:flush(fp, s2, &mr2, &mc2); printf("Flush Successful\n"); break;
				case 3:flush(fp, s3, &mr3, &mc3); printf("Flush Successful\n"); break;
				default:printf("Invalid Schema\n");
				}
			}
			else if (!strcmp(cmd, "join"))
			{
				s3 = join(s1, s2, &mr1, &mc1, &mr2, &mc2, &mr3, &mc3);
				printf("Join Successful\n");
			}
			else if (!strcmp(cmd, "select"))
			{

				x = 0;
				while (command[i] != ' ')
					required[x++] = command[i++];
				required[x] = '\0';
				i += 7;
				int s = command[i++] - 48;
				x = 0;
				condition[0] = '\0';
				if (command[i] != '\0')
				{
					i += 7;
					while (i < strlen(command) && command[i] != '\0')
						condition[x++] = command[i++];
					condition[x] = '\0';
				}
				if (command[i] == '\0')
				{
					switch (s)
					{
					case 1:query(s1, required, &mr1, &mc1, condition); break;
					case 2:query(s2, required, &mr2,&mc2,condition); break;
					case 3:query(s3, required, &mr3, &mc3, condition); break;
					}
				}
			}
			else
				printf("Invalid Command\n");
			break;
		}
	}
}*/