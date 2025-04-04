#ifndef TEAM4OVERDRACHT_SRC_ESP8266DRIVER_MODULES_H_
#define TEAM4OVERDRACHT_SRC_ESP8266DRIVER_MODULES_H_

void reverse(char *str){
    int sizeStr = strlen(str);
    int firstChar,lastChar,temp;
    for(lastChar = (sizeStr - 1),firstChar = 0 ; lastChar > firstChar ; lastChar--, firstChar++){
        temp = str[firstChar];
        str[firstChar] = str[lastChar];
        str[lastChar] = temp;
    }
}

char* intoa(int num, char* str, int base){
    int i = 0;
    bool isNegative = false;

    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
  
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
  
    if (isNegative)
        str[i++] = '-';
  
    str[i] = '\0'; 

    reverse(str);
    return str;
}

#endif // TEAM4OVERDRACHT_SRC_ESP8266-DRIVER_MODULES_H_