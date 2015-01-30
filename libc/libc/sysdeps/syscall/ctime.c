

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <tzfile.h>
#include <errno.h>
#include <sys/times.h>

/*
** A la X3J11
*/
void localsub(const time_t * const timep, const long offset, struct tm * const tmp);

char* get_timebuf()
{
	static struct tm  tm;
	static char buf[40];
	localsub(NULL,0,&tm);
	sprintf(buf, "%2d:%2d:%2d", tm.tm_hour, tm.tm_min, tm.tm_sec);
	return buf;
}

char* get_datebuf()
{
	static struct tm  tm;
	static char buf[64];
	static const char wday_name[DAYSPERWEEK][3] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };
//wday_name[tm.tm_wday],
	localsub(NULL,0,&tm);
	sprintf(buf, "??? %4d-%2d-%2d",  tm.tm_year+TM_YEAR_BASE+100, tm.tm_mon, tm.tm_mday);
	return buf;
}

char *
asctime1(const struct tm *timeptr)
{
  static const char wday_name[DAYSPERWEEK][3] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };
  static const char mon_name[MONSPERYEAR][3] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };
  static char result[26];

  (void) sprintf(result, "%3s %3s%3d %02d:%02d:%02d %d\n",
		 wday_name[timeptr->tm_wday],
		 mon_name[timeptr->tm_mon],
		 timeptr->tm_mday, timeptr->tm_hour,
		 timeptr->tm_min, timeptr->tm_sec,
		 TM_YEAR_BASE + timeptr->tm_year);
  return result;
}


