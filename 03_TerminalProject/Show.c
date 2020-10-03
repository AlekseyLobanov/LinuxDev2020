#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curses.h>

const int BUF_SIZE = 76;
const int USER_KEY_ESCAPE = 27;
const int WINDOW_COLS = 77;
const int WINDOW_LINES = 19;

void draw_window(WINDOW* scr,
                 const int first_line,
                 const char lines[WINDOW_LINES][BUF_SIZE],
                 const int lines_count,
                 const int shift_x,
                 const int shift_y) {
    wclear(scr);
    box(scr, 0, 0);

    for (int i = 0; i < lines_count; ++i) {
        wmove(scr, i + shift_y, shift_x);
        char out_str[BUF_SIZE];
        snprintf(out_str, BUF_SIZE - 1, "%d: %s", i + first_line, lines[i]);
        out_str[BUF_SIZE - 1] = '\0';
        waddstr(scr, out_str);
    }
    wrefresh(scr);
}

void shift_lines(char lines[WINDOW_LINES][BUF_SIZE]) {
    for (int i = 0; i < WINDOW_LINES - 1; ++i) {
        strncpy(lines[i], lines[i + 1], BUF_SIZE);
    }
}

// returns 1 on success line read, 0 if EOF reached
int read_line(FILE* pFile, char line[BUF_SIZE]) {
    char* res = fgets(line, BUF_SIZE, pFile);
    if (res == NULL)
        return 0;

    char* pch = strchr(line, '\n');
    if (pch != NULL) {
        *pch = '\0';
    } else {
        // we need only first BUF_SIZE chars from each line
        line[BUF_SIZE - 1] = '\0';
        while (pch == NULL) {
            char end_of_string[BUF_SIZE];
            if (fgets(end_of_string, BUF_SIZE, pFile) == NULL)
                break;
            pch = strchr(end_of_string, '\n');
        }
    }
    return 1;
}

int main(int argc, char** argv) {
    FILE* pFile;
    if (argc < 2) {
        printf("You need to choose file to open: show INPUT_FILE\n");
        return EXIT_FAILURE;
    }
    pFile = fopen(argv[1], "r");
    if (pFile == NULL) {
        printf("You need to choose correct file to open: show INPUT_FILE\n");
        return EXIT_FAILURE;
    }

    char cur_lines[WINDOW_LINES][BUF_SIZE];
    int total_lines = 0;
    int current_line = 1;
    int is_eof = 0;

    // we need to read initial lines of file
    for (int i = 0; i < WINDOW_LINES; ++i) {
        char* line_buffer = cur_lines[i];

        if (read_line(pFile, cur_lines[i])) {
            total_lines += 1;
        } else {
            is_eof = 1;
            break;
        }
    }

    WINDOW* mainwin;
    if ((mainwin = initscr()) == NULL) {
        printf("Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
    }
    noecho();

    wmove(mainwin, 0, 10);
    waddstr(mainwin, argv[1]);
    refresh();

    WINDOW* source_window = newwin(WINDOW_LINES + 2, WINDOW_COLS, 2, 2);

    draw_window(source_window, current_line, cur_lines, total_lines, 1, 1);
    wrefresh(mainwin);

    while (1) {
        int ch = getch();
        if (ch == ' ') {
            if (is_eof && total_lines == 1) {
                // last line -> exiting
                break;
            }
            current_line += 1;
            shift_lines(cur_lines);
            total_lines -= 1;

            if (!is_eof && read_line(pFile, cur_lines[WINDOW_LINES - 1])) {
                total_lines += 1;
            } else {
                is_eof = 1;
            }
            wrefresh(mainwin);
            draw_window(source_window, current_line, cur_lines, total_lines, 1,
                        1);
            wrefresh(mainwin);
        } else if (ch == USER_KEY_ESCAPE) {
            break;
        }
        refresh();
    }

    delwin(source_window);
    delwin(mainwin);
    endwin();

    refresh();

    fclose(pFile);

    return EXIT_SUCCESS;
}
