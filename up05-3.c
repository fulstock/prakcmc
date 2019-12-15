void normalize_path(char *buf)
{
    char *ptr, *seeker;
    ptr = buf;
    seeker = buf;
    int flag = 0;
    while (*seeker) {
        while (*seeker == '/') {
            seeker++;
            flag = 1;
        }
        if (flag) {
            *ptr = '/';
            ptr++;
            flag = 0;
        }
        while (*seeker && *seeker != '/') {
            *ptr = *seeker;
            ptr++;
            seeker++;
        }
    }
    *ptr = '\0';
}

