// vim: sw=4 ts=4 et :
#ifndef CLIENT_H
#define CLIENT_H

#include "windows.h"
#include "config.h"
#include "keyboard.h"

#include "area.h"
#include "chat.h"
#include "sysmsg.h"

#define CONNECTION_RETRIES_MAX 16

#define CHECK_CONNECTION()                                                  \
    while (server_connected == 0) {                                         \
        strncpy(menu_msg, _("Server connection lost!"), sizeof(menu_msg));  \
        menu(M_MAIN);                                                       \
    }

int last_key;               // keycode of the last pressed key
int end;                    // flag of program termination

int connecting;             // flag of kinda SYN_SENT state
int server_connected;       // connection status
int sock;                   // c2s socket fd
mqueue_t c2s_queue;         // queue for outgoing messages
pthread_t thr_worker;       // pointer to worker thread
struct sockaddr_in srv;     // buffer for srv address
char server_address[8192];  // buffer for srv address in string format

char menu_msg[8192];        // buffer for in-menu messages

// Menus
enum menus {
    M_MAIN,
    M_NEW_GAME,
    M_CONNECT_GAME,
    M_OPTIONS,
    M_HELP,
    M_EXIT_GAME,
    M_SIZE
};

typedef struct menu {
    void (*f)(int id, WINDOW *);
    char *caption;
} menu_t;

int client();
int connect_to_server(char *address);
void speak_with_server();
int color2attr(enum colors color);
void worker_start();

extern void menu(size_t menu_id);
extern void splash_screen();
extern void locale_init(char *file);
extern char *_(char*);

#endif /* CLIENT_H */
