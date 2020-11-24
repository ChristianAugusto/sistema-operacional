long long int str_size(char* str) {
    if (str == NULL) {
        return 0;
    }

    long long int size;

    for (size = 0; str[size] != '\0'; size++);

    return size;
}


char* str_copy(char* str) {
    if (str == NULL) {
        return NULL;
    }

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
    if (oldId == NULL) {
        return NULL;
    }


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


bool str_equals(char* str1, char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }


    long long int str1_size = str_size(str1);

    if (str1_size != str_size(str2)) {
        return false;
    }

    for (long long int i = 0; i < str1_size; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }


    return true;
}
