#define clear_screen() puts("\x1B[2J")
#define move_cursor(row, col) printf("\x1B[%d;%dH", row, col)
