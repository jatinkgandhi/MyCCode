/* Courtecy: https://blog.habets.se/2010/09/gettimeofday-should-never-be-used-to-measure-time.html */

#if 0
Descriptoin:
gettimeofday() should never be used to measure time
gettimeofday() and time() should only be used to get the current time if the current wall-clock time is actually what you want. They should never be used to measure time or schedule an event X time into the future.
What’s the problem?

gettimeofday() returns the current wall clock time and timezone. time() returns a subset of this info (only whole seconds, and not timezone).

Using these functions in order to measure the passage of time (how long an operation took) therefore seems like a no-brainer. After all, in real life you measure by checking your watch before and after the operation. The differences are:
1. Nobody sneaks in and changes your wristwatch when you’re not looking

You usually aren’t running NTP on your wristwatch, so it probably won’t jump a second or two (or 15 minutes) in a random direction because it happened to sync up against a proper clock at that point.

Good NTP implementations try to not make the time jump like this. They instead make the clock go faster or slower so that it will drift to the correct time. But while it’s drifting you either have a clock that’s going too fast or too slow. It’s not measuring the passage of time properly.
2. You’re not stupid, the computer is

Doing something doesn’t take less than 0 time. If you get <0 when you measure time, you’ll realize something is wrong. A program will happily print that a ping reply came back before you sent it. Even if you check for time < 0, the program that uses gettimeofday() still can’t tell the difference between a 2 second delay and 3 seconds plus a time adjustment.
3. You are the limiting factor

In real life you are not expected to measure sub-second times. You can’t measure the difference between 1.08 seconds and 1.03 seconds. This problem is mostly (but far from entirely) in the small scale.
What to use instead

The most portable way to measure time correctly seems to be clock_gettime(CLOCK_MONOTONIC, ...). It’s not stable across reboots, but we don’t care about that. We just want a timer that goes up by one second for each second that passes in the physical world.

So if you want to wait 10 seconds, then check the monotonic clock, add 10 seconds and wait until that time has come.

#endif

/* Code begins...,  */
#include <time.h>
#include <stdio.h>

/**
 * sleep for `sec' seconds, without relying on the wall clock of time(2)
 * or gettimeofday(2).
 *
 * under ideal conditions is accurate to one microsecond. To get nanosecond
 * accuracy, replace sleep()/usleep() with something with higher resolution
 * like nanosleep() or ppoll().
 */
void
true_sleep(int sec)
{
        struct timespec ts_start;
        struct timespec ts_end;

        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        ts_end = ts_start;
        ts_end.tv_sec += sec;

        for(;;) {
                struct timespec ts_current;
                struct timespec ts_remaining;

                clock_gettime(CLOCK_MONOTONIC, &ts_current);

                ts_remaining.tv_sec = ts_end.tv_sec - ts_current.tv_sec;
                ts_remaining.tv_nsec = ts_end.tv_nsec - ts_current.tv_nsec;
                while (ts_remaining.tv_nsec > 1000000000) {
                        ts_remaining.tv_sec++;
                        ts_remaining.tv_nsec -= 1000000000;
                }
                while (ts_remaining.tv_nsec < 0) {
                        ts_remaining.tv_sec--;
                        ts_remaining.tv_nsec += 1000000000;
                }

                if (ts_remaining.tv_sec < 0) {
                        break;
                }

                if (ts_remaining.tv_sec > 0) {
                        sleep(ts_remaining.tv_sec);
                } else {
                        usleep(ts_remaining.tv_nsec / 1000);
                }
        }
}

int
main()
{
        true_sleep(10);
}

