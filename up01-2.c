#include <stdio.h>

int
isLetter(int letter)
{
    return letter >= 'a' && letter <= 'z';
}

int
main(void)
{
    int letters_count = 0;
    int word_max_len = 0;
    int input_char;
    int is_Qword = 0;
    while ((input_char = getchar()) != EOF) {
        if (!is_Qword || !isLetter(input_char)) {
            if (!isLetter(input_char)) {
                is_Qword = 0;
                if (word_max_len < letters_count) {
                    word_max_len = letters_count;
                }
                letters_count = 0;
            } else if (input_char == 'q') {
                is_Qword = 1;
                letters_count = 0;
            } else {
                letters_count++;
            }
        }
    }
    if (word_max_len < letters_count) {
        word_max_len = letters_count;
    }
    printf("%d\n", word_max_len);  
}

