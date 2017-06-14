#include "SocketServer.h"

void Utilities::CharArrayMAlloc(char *arr[], int size, int max_length)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = (char*)malloc(max_length * sizeof(char)); //*** IMPORTANT ***
		char *p = arr[i];
		p[0] = '\0';
	}
}

void Utilities::SplitString(char *str, char dem, char *arr[], int size, int max_length)
{
	CharArrayMAlloc(arr, size, max_length);

	int j = 0, k = 0;
	for (int i = 0; i < (int)strlen(str); i++)
	{
		if (str[i] == '\n')
			str[i] = '\0';

		if (str[i] != dem)
		{
			char *p = (char*)malloc(2 * sizeof(char));
			p[0] = str[i];
			p[1] = '\0';

			strcat_s(arr[k], max_length, p);

			free(p);
		}
		else
		{
			strcat_s(arr[k], max_length, "\0"); //char *p = arr[k]; p[i] = '\0';
			k++;
		}
		j = k;
	}
}

void Utilities::LowerString(char *str)
{
	for (int i = 0; i < (int)strlen(str); i++)
		str[i] = tolower(str[i]);
}

void Utilities::Trim(char *str)
{
	char *start, *end;

	/* Find first non-whitespace */
	for (start = str; *start; start++)
	{
		if (!isspace((unsigned char)start[0]))
			break;
	}

	/* Find start of last all-whitespace */
	for (end = start + strlen(start); end > start + 1; end--)
	{
		if (!isspace((unsigned char)end[-1]))
			break;
	}

	*end = 0; /* Truncate last whitespace */

			  /* Shift from "start" to the beginning of the string */
	if (start > str)
		memmove(str, start, (end - start) + 1);
}

void Utilities::ReadConfig(const char *file_name, char *config_name, char *config_value)
{
	//config_value[0] = '\0';
	FILE *fp;
	if (fopen_s(&fp, file_name, "r") != 0)
	{
		printf("Cannot open or read file: %s\n", file_name);
		return;
	}

	const int max_str_length = 100;
	char lineText[max_str_length];

	while (fgets(lineText, sizeof(lineText) - 1, fp) != NULL)
	{
		const int size = 2;
		char cfName[max_str_length], *strOut[size];

		strcpy_s(cfName, max_str_length, config_name);

		SplitString(lineText, '=', strOut, size, max_str_length);

		Trim(cfName);
		Trim(strOut[0]);
		LowerString(cfName);
		LowerString(strOut[0]);
		if (strcmp(cfName, strOut[0]) == 0)
		{
			strcpy_s(config_value, max_str_length, strOut[1]);
			break;
		}
	}

	fclose(fp);
}
