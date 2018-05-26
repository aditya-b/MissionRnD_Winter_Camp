/*DB ENGINE for Dynamic Schemas:

Query Formats:
CREATE: create schema s1 8 a:b:c:d:e:f:g:h -- creates schema s1 with 8 columns with the specified column names(a,b,c,d,e,f,g,h)
IMPORT: import filename.csv s1 -- imports file for schema 1 (replace 1 with required schema number)
FLUSH: flush filename.csv s2 -- flushes into file for schema 2 (replace 2 with required schema number)
JOIN: join s1 s2 -- flushes the data in schema-1 and schema-2 (replace 2 with required schema number)
select is of user's choice

NOTE: Column names are case-sensitive.
	  Queries should be of the above format only(no extra spaces)
	  Schema creation should start from s1 and go progressively
*/

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<math.h>

/*Utility Function to Convert String to Float*/
float strtonum(char *str)
{
	int n = 0, i = 0, x = 1;
	float dec = 0;
	while (str[i]!='.'&&str[i] != '\0')
		n = n * 10 + (str[i++] - 48);
	if (str[i] == '.')
	{
		i++;
		while (str[i] != '\0')
		{
			dec += (str[i++] - 48) / pow(10.0, x++);
		}
	}
	dec = n + dec;
	return dec;
}

/*Import function from file */
char*** import(FILE*fp, char ***ss, int *maxrows, int *maxcols)
{
	
	char ***s1=NULL, string[60];
	int n = 0, flag = 0, i = 0, x, buff = 0, stat = 0;
	char *line = (char*)malloc(sizeof(char) * 100);
	fgets(line, 100, fp);
	while (fgets(line, 100, fp))
	{
		n++;
	}
	buff = *maxrows;//store exitsing size in buffer
	*maxrows = n + *maxrows;//update rowsize
	ss = (char***)realloc(ss, *maxrows*sizeof(char***));//allocate memory for extra rows
	s1 = ss;
	fseek(fp, 0, SEEK_SET);
	flag = 0;
	int z = buff;
	for (i = buff; i < *maxrows; i++)
	{
		s1[i] = (char**)malloc((*maxcols)*sizeof(char**));//allocate memory for columns to each row
	}
	fgets(line, 100, fp);
	while (z<*maxrows&&fgets(line, 100, fp))//check for duplicates and then import
	{
		i = 0;
		stat = 0;
		while (i<strlen(line) && line[i] != '\0')
		{
			x = 0;
			while (i<strlen(line) && line[i] != ','&&line[i] != '\0'&&line[i] != '\n')
				string[x++] = line[i++];
			string[x] = '\0';
			if (flag%*maxcols == 0)
			{
				for (int j = 0; j < buff; j++)
				{
					if (!strcmp(string, s1[j][0]))
					{
						stat = 1;
						break;
					}
				}
			}
			if (stat)
				break;
			s1[z][flag%*maxcols] = (char*)malloc(strlen(string)*sizeof(char));
			strcpy(s1[z][flag % (*maxcols)], string);
			flag++;
			i++;
		}
		if (!stat)
			z++;
	}
	ss = (char***)realloc(ss, z*sizeof(char***));//realloc based on the effective number of rows
	*maxrows = z;
	printf("Import Successful\n");
	return s1;
}
/*Flush function to store data to file*/
void flush(FILE*fp, char ***ss, int *maxrows, int *maxcols)
{
	if (fp == NULL)
	{
		printf("File Error!\n");
		return;
	}
	for (int i = 0; i < *maxrows; i++)//flush data row-by-row
	{
		for (int j = 0; j < *maxcols; j++)
		{
			fputs(ss[i][j], fp);
			fputc(',', fp);
		}
		fputc('\n', fp);
	}
	printf("%d rows %d columns\n", *maxrows, *maxcols);
}
/*Create Function to create the Schema*/
char*** create(char* columns, int *maxrows, int *maxcols, int n)
{
	//columns is colon seperated set of column names
	*maxcols = n;//update max number of columns
	*maxrows = 1;//initilize the schema with the column names
	int i = 0, x, z = 0;
	char colname[20];
	char ***s = (char***)malloc(sizeof(char***));//allocate schema its memory
	*s = (char**)malloc(sizeof(char**)*n);
	while (i<strlen(columns) && columns[i] != '\0')//copy all the specified column names
	{
		x = 0;
		while (columns[i] != ':'&&columns[i] != '\0')
			colname[x++] = columns[i++];
		colname[x] = '\0';
		s[0][z] = (char*)malloc(sizeof(char)*strlen(colname));
		strcpy(s[0][z], colname);
		i++;
		z++;
	}
	return s;
}
/*Join Function to join two schemas and store to new schema*/
char*** join(char ***s1, char ***s2, int *mr1, int *mc1, int *mr2, int *mc2, int *mr3, int *mc3)
{
	int rows = *mr1>*mr2 ? *mr1 : *mr2;//choose the total number of rows by comparing the number of rows in the two schemas
	int cols = *mc1 + *mc2 - 1;//add the number of columns in the two schemas
	char val[100];
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
			s3[0][j] = (char*)malloc(sizeof(char)*strlen(s2[0][j + 1 - *mc1]));
			strcpy(s3[0][j], s2[0][j + 1 - *mc1]);
		}
	}
	for (int i = 1; i < *mr1; i++)//compare the value existence and place into memory accordingly
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
	*mr3 = rows;//update rowsize
	*mc3 = cols;//update columnsize
	return s3;

}
/*Query Function to process queries*/
void query(char ***s, char *required, int *mr, int *mc, char *condition)
{
	int *flag = (int*)malloc(sizeof(int)*(*mc));
	for (int i = 0; i < *mc; i++)
		flag[i] = 0;
	char op[4], val[10], name[20];
	name[0] = '\0';
	int i = 0, x = 0, stat = 0;
	if (strstr(condition, "contains") || strstr(condition, "matches"))//block to get value for contains and matches conditions
	{
		i = 0; x = 0;
		while (condition[i] != '"')
			i++;
		i++;
		while (condition[i] != '"')
			name[x++] = condition[i++];
		name[x] = '\0';
	}
	if (condition[0] != '\0'&&!strstr(condition, "contains") && !strstr(condition, "matches"))//block to get vlaue and operator for numeric comparisions
	{
		i = 0;
		while ((condition[i] > 64 && condition[i] < 91) || (condition[i]>96 && condition[i] < 123) || (condition[i] >= 48 && condition[i] <= 57))
			i++;
		//printf("%c", condition[i]);
		while (condition[i] < 48 || condition[i]>57)
			op[x++] = condition[i++];
		op[x] = '\0';
		x = 0;
		while (condition[i] != '\0')
			val[x++] = condition[i++];
		val[x] = '\0';
	}
	if (!strcmp(required, "*"))//mark all columns(flags) if *
	{
		for (i = 0; i < *mc; i++)
		{
			flag[i] = 1;
			stat = 1;
		}
		printf("\n");
	}
	else//mark only required columns
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
	if (condition[0] == '\0')//check if there is any condition
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
			if (strstr(condition, s[0][i]))//check for existence of column name in the specified condition
			{
				if (name[0] != '\0')
				{
					if (strstr(condition, "contains"))//block to handle contains condition
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
					else if (strstr(condition, "matches"))//block to handle matches condition
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
				else//block to handle numeric comparisions
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
/*Console input function*/
int main()
{
	char command[150], cmd[20], columns[100], filename[30], required[50], condition[60];
	char ****schemas =(char****)malloc(sizeof(char***));
	char ***s1, ***s2, ***s3;
	int *src = (int*)malloc(2 * sizeof(int));
	int schemasize=0;
	int i = 0, x = 0;
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
				int s=0;
				while (command[i]>47 && command[i] < 58)
					s = s * 10 + (command[i++] - 48);
				i++;
				int n = 0;
				while (command[i]>47 && command[i] < 58)
					n = n * 10 + (command[i++] - 48);
				i++;
				x = 0;
				while (command[i] != '\0')
					columns[x++] = command[i++];
				columns[x] = '\0';
				schemasize = schemasize + 1;
				schemas = (char****)realloc(schemas, schemasize*(sizeof(char****)));
				src = (int*)realloc(src, schemasize * 2 * sizeof(int));
				src[(schemasize - 1) * 2] = 0;
				src[(schemasize - 1) * 2 + 1] = 0;
				schemas[s - 1] = (char***)malloc(sizeof(char***));
				schemas[s-1] = create(columns, &src[(s-1)*2], &src[(s-1)*2+1], n);
				printf("Created Schema S%d\n", s);
			}
			else if (!strcmp(cmd, "import"))
			{
				x = 0;
				while (command[i] != ' ')
					filename[x++] = command[i++];
				filename[x] = '\0';
				FILE *fp = fopen(filename, "r");
				i = i + 2;
				int s = 0;
				while (i<strlen(command)&&command[i]>47 && command[i] < 58)
					s = s * 10 + (command[i++] - 48);
				schemas[s-1] = import(fp, schemas[s-1], &src[(s - 1) * 2], &src[(s - 1) * 2 + 1]);
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
				int s = 0;
				while (i<strlen(command) && command[i]>47 && command[i] < 58)
					s = s * 10 + (command[i++] - 48);
				flush(fp, schemas[s - 1], &src[(s - 1) * 2], &src[(s - 1) * 2 + 1]);
				printf("Flush Successful!");
			}
			else if (!strcmp(cmd, "join"))
			{
				i++;
				int f1 = 0;
				while (i<strlen(command) && command[i]>47 && command[i] < 58)
					f1 = f1 * 10 + (command[i++] - 48);
				i += 2;
				int f2 = 0;
				while (i<strlen(command) && command[i]>47 && command[i] < 58)
					f2 = f2 * 10 + (command[i++] - 48);
				f1--;
				f2--;
				schemasize = schemasize + 1;
				schemas = (char****)realloc(schemas, schemasize*(sizeof(char****)));
				src = (int*)realloc(src, schemasize * 2 * sizeof(int));
				schemas[schemasize - 1] = (char***)malloc(sizeof(char***));
				src[(schemasize - 1) * 2] = 0;
				src[(schemasize - 1) * 2 + 1] = 0;
				schemas[schemasize - 1] = join(schemas[f1], schemas[f2], &src[f1 * 2], &src[f1 * 2 + 1], &src[f2 * 2], &src[f2 * 2 + 1], &src[(schemasize - 1) * 2], &src[(schemasize - 1) * 2+1]);
				printf("Join Successful as Schema S-%d\n",schemasize);
			}
			else if (!strcmp(cmd, "select"))
			{

				x = 0;
				while (command[i] != ' ')
					required[x++] = command[i++];
				required[x] = '\0';
				i += 7;
				int s = 0;
				while (i<strlen(command) && command[i]>47 && command[i] < 58)
					s = s * 10 + (command[i++] - 48);
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
					query(schemas[s-1], required, &src[(s - 1) * 2], &src[(s - 1) * 2 + 1], condition);
				}
			}
			else
				printf("Invalid Command\n");
			break;
		}
	}
}