long long int str_size(char* str) {
    long long int size;

    for (size = 0; str[size] != '\0'; size++);

    return size;
}

char* str_copy(char* str) {
    long long int strSize = str_size(str) + 1;

    char* newStr = (char*)malloc(strSize * sizeof(char));

    newStr[strSize-1] = '\0';

    long long int i;
    for (i = 0; i < strSize-1; i++) {
        newStr[i] = str[i];
    }

    return newStr;
}

int str_charToInt(char c) {
    return c - '0';
}

char* str_incrementIds(char* oldId) {
    long long int oldIdSize = str_size(oldId);

    long long int i;
    for (i = oldIdSize-1; i >= 0; i--) {
        int number = str_charToInt(oldId[i]);

        if (number+1 < 10) {
            oldId[i] = '0' + number + 1;
            return oldId;
        }
        else {
            oldId[i] = '0';
        }
    }


    long long int newIdSize = oldIdSize + 2;

    char* newId = (char*)malloc(newIdSize*sizeof(char));
    newId[newIdSize-1] = '\0';

    long long int j = newIdSize - 2;
    for (i = oldIdSize-1; i >= 0; i--,j--) {
        newId[j] = oldId[i];
    }

    newId[0] = '1';

    free(oldId);

    return newId;
}