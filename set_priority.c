#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  int priority, pid;
  if(argc < 3){
    printf(2,"Enter priority <space> pid\n");
    exit();
  }
  priority = atoi(argv[1]);
  pid = atoi(argv[2]);
  if (priority < 0 || priority > 100){
    printf(2,"Invalid priority\n");
    exit();
  }
  set_priority(priority, pid);
  exit();
}