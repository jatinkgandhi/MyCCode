// HOW TO COMPILE:
// gcc -g -O0 -rdynamic -funwind-tables bt.c -lpthread -o backtraceetest

#define _GNU_SOURCE

#include <signal.h>
#include <execinfo.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BT_BUF_SIZE 100

/* ---------------------------------------------------------
 * Backtrace of current (faulting) thread
 * --------------------------------------------------------- */
void show_backtrace(void)
{
    void *buffer[BT_BUF_SIZE];
    int nptrs;
    char **strings;
    char thrname[16] = {0};

    nptrs = backtrace(buffer, BT_BUF_SIZE);
    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        return;
    }

    pthread_getname_np(pthread_self(), thrname, sizeof(thrname));

    printf("\n============================================\n");
    printf("Thread backtrace\n");
    printf("Thread name: %s\n", thrname[0] ? thrname : "<unnamed>");
    printf("--------------------------------------------\n");

    for (int i = 0; i < nptrs; i++)
        printf("%s\n", strings[i]);

    printf("============================================\n");

    free(strings);
}

/* ---------------------------------------------------------
 * Signal handler
 * --------------------------------------------------------- */
static void crash_signal_handler(int sig, siginfo_t *si, void *ctx)
{
    (void)si;
    (void)ctx;

    const char *sig_name = strsignal(sig);

    write(STDERR_FILENO,
          "\n\n===== SIGNAL RECEIVED =====\n",
          strlen("\n\n===== SIGNAL RECEIVED =====\n"));

    if (sig_name) {
        write(STDERR_FILENO, sig_name, strlen(sig_name));
        write(STDERR_FILENO, "\n", 1);
    }

    /* Per‑thread backtrace */
    show_backtrace();

    write(STDERR_FILENO,
          "===== END BACKTRACE =====\n",
          strlen("===== END BACKTRACE =====\n"));

    /* Re‑raise with default handler */
    signal(sig, SIG_DFL);
    raise(sig);
}

/* ---------------------------------------------------------
 * Install handlers
 * --------------------------------------------------------- */
static void install_signal_handlers(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    sa.sa_sigaction = crash_signal_handler;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sigfillset(&sa.sa_mask);

    int signals[] = {
        SIGABRT,
        SIGFPE,
        SIGILL,
        SIGINT,
        SIGSEGV,
        SIGTERM,
        SIGBUS
        /* SIGKILL cannot be handled */
    };

    for (size_t i = 0; i < sizeof(signals)/sizeof(signals[0]); i++) {
        if (sigaction(signals[i], &sa, NULL) != 0)
            perror("sigaction");
    }
}
void generatefault3(void)
{
    /* Force crash in this thread */
    int *p = NULL;
    *p = 42;   /* SIGSEGV */


}
void generatefault2(void)
{
	generatefault3();
}
void generatefault1(void)
{
	generatefault2();
}
/* ---------------------------------------------------------
 * Example worker thread
 * --------------------------------------------------------- */
void *worker_thread(void *arg)
{
    (void)arg;
    pthread_setname_np(pthread_self(), "worker");

    sleep(5);

    generatefault1();
    return NULL;
}

/* ---------------------------------------------------------
 * main()
 * --------------------------------------------------------- */
int main(void)
{
    pthread_t tid;

    pthread_setname_np(pthread_self(), "main");

    install_signal_handlers();

    printf("PID: %ld\n", (long)getpid());
    printf("Signal handlers installed\n");

    pthread_create(&tid, NULL, worker_thread, NULL);
    pthread_join(tid, NULL);

    return 0;
}


