
char *pint(int integer, char *inbuffer) {
    char buffer[32];
    int i = 0;
    while (integer > 0) {
        buffer[i] = (integer % 10) + 48;
        i++;
        integer = integer / 10;
    }
    int j = 0;
    while (i > 0) {
        inbuffer[j++] = buffer[--i];
        if (i != 0 && (i % 3) == 0) inbuffer[j++] = ',';
    }
    inbuffer[j] = '\0';
    return inbuffer;
}
