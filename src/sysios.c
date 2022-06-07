#include "types.h"
#include "stat.h"
#include "user.h"
#include "iostat.h"
#include "pstat.h"


extern uint rseed;
int main(int argc, char **argv)
{
	char *s = "";
for(int i =0;i<atoi(argv[1]);i++){
	read(-1,s, sizeof(s));
}
for(int i = 0; i<atoi(argv[2]);i++){
	write(-1,s,sizeof(s));
}
  struct iostat* is = malloc(sizeof(struct iostat));
  int a = getiocounts(is);
  printf(1,"%d ",a );
  printf(1,"%d " ,is->readcount );
  printf(1, "%d\n", is->writecount);
  exit();
}
