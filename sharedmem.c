#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  int segment_id;
  unsigned short key;
  unsigned short mode;
  unsigned short owner;
  unsigned long size;
  unsigned short attach;
  struct shmid_ds shmbuffer;

  //if there is an argument, assign it to segment id
  if (argc == 2){
    segment_id = atoi(argv[1]);
  }

  //create segment if there is no argument
  else if (argc == 1){
    segment_id = shmget(IPC_PRIVATE, 4*sizeof(int), IPC_CREAT | 0666);
  }

  //end program if there is too many arguments
  else{
    return (0);
  }


  //retrieve information of the segment
  if (shmctl(segment_id, IPC_STAT, &shmbuffer) == -1) {
    printf("Unable to access segment %d\n",segment_id);
    return 0;
  }

  //get the required data from shmbuffer
  mode = shmbuffer.shm_perm.mode;
  owner = shmbuffer.shm_perm.uid;
  key = shmbuffer.shm_perm.__key;
  size = shmbuffer.shm_segsz;
  attach = shmbuffer.shm_nattch;


  printf("ID\t\tKEY\tMODE\t\tOWNER_UID\tSIZE\t\tATTACHES\n");
  printf("--\t\t---\t----\t\t--------\t----\t\t--------\n");


  printf("%d\t\t", segment_id);
  printf("%d\t", key);

  //outputting 'mode' in the correct format
  //Mode Owner
  if (mode & 0400){
    printf("r");
  }
  else{
    printf("-");
  }
  if (mode & 0200){
    printf("w");
  }
  else{
    printf("-");
  }
  if (mode & 0100){
    printf("a");
  }
  else{
    printf("-");
  }

  //Mode group
  if (mode & 0040){
    printf("r");
  }
  else{
    printf("-");
  }
  if (mode & 0020){
    printf("w");
  }
  else{
    printf("-");
  }
  if (mode & 0010){
    printf("a");
  }
  else{
    printf("-");
  }

  //Mode world
  if (mode & 0004){
    printf("r");
  }
  else{
    printf("-");
  }
  if (mode & 0002){
    printf("w");
  }
  else{
    printf("-");
  }
  if (mode & 0001){
    printf("a");
  }
  else{
    printf("-");
  }

  
  printf("\t");
  printf("%d\t\t", owner);
  printf("%ld\t\t", size);
  printf("%d\n", attach);
  return (0);
}
