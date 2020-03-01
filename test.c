typedef unsigned char      u8;
typedef signed   char      s8;
typedef unsigned short     u16;
typedef signed   short     s16;
typedef unsigned int       u32;
typedef signed   int       s32;
typedef unsigned long long u64;
typedef signed   long long s64;

#define noreturn __attribute__((noreturn)) void

typedef enum bool {
    false,
    true
} bool;

/* Simple math */

/* A very simple and stupid exponentiation algorithm */
static inline double pow(double a, double b)
{
    double result = 1;
    while (b-- > 0)
        result *= a;
    return result;
}

/* Port I/O */

static inline u8 inb(u16 p)
{
    u8 r;
    asm("inb %1, %0" : "=a" (r) : "dN" (p));
    return r;
}

static inline void outb(u16 p, u8 d)
{
    asm("outb %1, %0" : : "dN" (p), "a" (d));
}

/* SCANNING */
/* Keyboard Input */

#define KEY_D     (0x20)
#define KEY_H     (0x23)

#define KEY_R     (0x13)
#define KEY_S     (0x1F)
#define KEY_UP    (0x48)
#define KEY_DOWN  (0x50)
#define KEY_LEFT  (0x4B)
#define KEY_RIGHT (0x4D)
#define KEY_ENTER (0x1C)
#define KEY_SPACE (0x39)

u8 scan(void)
{
    static u8 key = 0;
    u8 scan = inb(0x60);
    if (scan != key)
        return key = scan;
    else return 0;
}


/* Video Output */

/* Seven possible display colors. Bright variations can be used by bitwise OR
 * with BRIGHT (i.e. BRIGHT | BLUE). */
enum color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    YELLOW,
    GRAY,
    BRIGHT,
    WHITE
};

#define COLS (80)
#define ROWS (25)
u16 *const video = (u16*) 0xB8000;

/* Display a character at x, y in fg foreground color and bg background color.
 */
void putc(u8 x, u8 y, enum color fg, enum color bg, char c)
{
    u16 z = (bg << 12) | (fg << 8) | c;
    video[y * COLS + x] = z;
}

/* Display a string starting at x, y in fg foreground color and bg background
 * color. Characters in the string are not interpreted (e.g \n, \b, \t, etc.).
 * */
void puts(u8 x, u8 y, enum color fg, enum color bg, const char *s)
{
    for (; *s; s++, x++)
        putc(x, y, fg, bg, *s);
}

/* Clear the screen to bg backround color. */
void clear(enum color bg)
{
    u8 x, y;
    for (y = 0; y < ROWS; y++)
        for (x = 0; x < COLS; x++)
            putc(x, y, bg, bg, ' ');
}

int gunPosiX;
int gunPosiY;
void dibujarNaveInicio(){
    gunPosiX = 37;
    gunPosiY = 22;
    putc(35,23,BLACK,GREEN,' ');
    putc(36,22,BLACK,GREEN,' ');
    putc(gunPosiX,gunPosiY,BLACK,GREEN,' ');
    putc(38,22,BLACK,GREEN,' ');
    putc(39,23,BLACK,GREEN,' ');
}

void shoot(){
    int tiroX = gunPosiX;
    int tiroY = gunPosiY-2;
    while(tiroY>0){
        putc(tiroX,tiroY,BLACK,RED,' ');
        tiroY = tiroY-3;

    }
}


void main()
{
    clear(BLACK);
    dibujarNaveInicio();
    while(true){
        u8 key;
        if ((key = scan())) {

            switch(key) {

            case KEY_S:
                shoot();
                break;

            case KEY_LEFT:
                //move(-1, 0);
                break;
            case KEY_RIGHT:
                //move(1, 0);
                break;
            case KEY_ENTER:
                //drop();
                break;
            //case KEY_P:
                //if (game_over)
                    //break;
                //clear(BLACK);
                //paused = !paused;
                //break;
            }
        }

    }

}
