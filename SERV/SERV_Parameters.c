int SERV_HexToInt(char c)
{
	int out;

	switch (c)
	{
		case '0':
			out = 0;
			break;
		case '1':
			out = 1;
			break;
		case '2':
			out = 2;
			break;
		case '3':
			out = 3;
			break;
		case '4':
			out = 4;
			break;
		case '5':
			out = 5;
			break;
		case '6':
			out = 6;
			break;
		case '7':
			out = 7;
			break;
		case '8':
			out = 8;
			break;
		case '9':
			out = 9;
			break;
		case 'a':
		case 'A':
			out = 10;
			break;
		case 'b':
		case 'B':
			out = 11;
			break;
		case 'c':
		case 'C':
			out = 12;
			break;
		case 'd':
		case 'D':
			out = 13;
			break;
		case 'e':
		case 'E':
			out = 14;
			break;
		case 'f':
		case 'F':
			out = 15;
			break;
		default:
			out = -1;
	}

	return out;
}

CLIENT SERV_ParseArguments(CLIENT client)
{
	char buffer[MAX_BUFFER_SIZE];

	strcpy(buffer, client.header);	// Make a copy of the header to preserve the original

	char * path = strtok(buffer, " ");	// Split it at the first space

	strcpy(client.method, path);

	path = strtok(NULL, " "); // Split it at the second space

	int IncludesParameters = 0;
	
	// Take everything before the first ? (if it exists)
	for (int i = 0; i < (int)strlen(path); i++)
	{
		if (path[i] == '?')
		{
			path[i] = '\0';
			IncludesParameters = 1;
			break;
		}
	}
	
	strcpy(client.path, path);

	if (IncludesParameters) // If we found a '?' in the path we have to parse the arguments
	{
		strcpy(buffer, client.header); // Reset the copy of the header as strtok will have messed it up
		path = strtok(buffer, " ");
		path = strtok(NULL, " ");

		path = strchr(path, '?'); // Read from the first '?'
		++path; // Shift one character over so we dont include the '?'

		strcpy(buffer, path);

		path = strtok(buffer, "&"); // Split the buffer at '&' (the parameter seperator)

		int i = 0;

		while (path != NULL) // Loop until we have parsed every parameter
		{
			strcpy(client.parameters[i][0], path);
			path = strtok(NULL, "&");
			i++;
		}

		client.parameterCount = i;

		// Loop over all the parameters and cut them at '=' to create the key value pairs
		for (int i = 0; i < client.parameterCount; i++)
		{
			strcpy(buffer, client.parameters[i][0]);

			path = strtok(buffer, "=");
			strcpy(client.parameters[i][0], path);

			path = strtok(NULL, "=");
			strcpy(client.parameters[i][1], path);

			int length = strlen(client.parameters[i][1]);

			// Loop over each parameter and remove the escape characters
			for (int a = 0; a < length; a++)
			{
				if (client.parameters[i][1][a] == '%')
				{
					int converted = 0;
					char total = 0;

					// Convert the escape characters into a single character
					converted = SERV_HexToInt(client.parameters[i][1][a +1]);
					(converted != -1) ? (total += converted * 16) : (0);
					converted = SERV_HexToInt(client.parameters[i][1][a +2]);
					(converted != -1) ? (total += converted) : (0);

					length -= 2;

					// Replace the escape character
					client.parameters[i][1][a +2] = total;
					memmove(&client.parameters[i][1][a], &client.parameters[i][1][a +2], length - a);
					client.parameters[i][1][length] = '\0';
				}
			}
		}
	}

	return client;
}

int SERV_GetParameter(CLIENT client, char key[])
{
	// Loop over each parameter
	for (int i = 0; i < client.parameterCount; i++)
	{
		// If it includes the key
		if (strcasecmp(client.parameters[i][0], key) == 0)
		{
			return i;

			break;
		}
	}

	return -1;
}

int SERV_MatchPath(CLIENT client, char path[])
{
	// Match path with request
	if (strcasecmp(client.path, path) == 0) // Yes it returs 0 when succesfull i swear they where drunk while making the function
	{
		return 1;
	}
	
	return 0;
}