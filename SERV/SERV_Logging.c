void SERV_Log(char * message, int type)
{
    (void)(message);

    switch (type)
    {
        case LOGGING_ERROR:
            printf(COLOR_RED "   (ERROR)    " COLOR_WHITE);
            break;
        case LOGGING_SETUP:
            printf(COLOR_GREEN "   (SETUP)    " COLOR_WHITE);
            break;
        case LOGGING_CONNECTION:
            printf(COLOR_BLUE " (CONNECTION) " COLOR_WHITE);
            break;
        case LOGGING_SENDING:
            printf(COLOR_PURPLE "  (SENDING)   " COLOR_WHITE);
            break;
    }

    time_t rawtime;
    struct tm *info;
    char buffer[MAX_BUFFER_SIZE];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, MAX_BUFFER_SIZE, "%H:%M:%S", info);
    printf("[%s] ", buffer);

    printf(COLOR_YELLOW "%s\n" COLOR_WHITE, message);
}