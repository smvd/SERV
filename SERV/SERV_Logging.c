void SERV_Log(char * message, int type)
{
    switch (type)
    {
        case LOGGING_ERROR:
            printf(COLOR_ERROR "   (ERROR)    " COLOR_RESET);
            break;
        case LOGGING_SETUP:
            printf(COLOR_SETUP "   (SETUP)    " COLOR_RESET);
            break;
        case LOGGING_CONNECTION:
            printf(COLOR_CONNECTION " (CONNECTION) " COLOR_RESET);
            break;
        case LOGGING_SENDING:
            printf(COLOR_SENDING "  (SENDING)   " COLOR_RESET);
            break;
    }

    time_t rawtime;
    struct tm *info;
    char buffer[MAX_BUFFER_SIZE];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, MAX_BUFFER_SIZE, "%H:%M:%S", info);
    printf("[%s] ", buffer);

    printf(COLOR_MESSAGE "%s\n" COLOR_RESET, message);
}