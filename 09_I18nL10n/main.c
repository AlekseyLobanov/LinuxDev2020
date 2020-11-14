#include <stdio.h>
#include <stdlib.h>

#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main() {
    setlocale (LC_ALL, "");
    bindtextdomain ("al_main", "."
    //getenv("PWD")
    );
    textdomain ("al_main");

    printf(_("Choose integer x that 1 <= x <= 100\n"));
    int begin = 1;
    int end = 100 + 1;
    while (end - begin > 1)
    {
        int cur = (begin + end) / 2;
        printf(_("Please choose correct statement:\n"));
        printf("1: x < %d\n", cur);
        printf("2: x >= %d\n", cur);
        int user_input;
        scanf("%d", &user_input);
        if ( user_input == 1 ){
            end = cur;
        } else {
            begin = cur;
        }
    }
    printf(_("Your number is: %d\n"), begin);
    return 0;
}