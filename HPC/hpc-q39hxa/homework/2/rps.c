#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char * argv[])
{
    int numtasks, rank, dest, sender, rc, count, tag = 1;
    int my_choice,rival_choice=1;  // 0: rock, 1: paper, 2:scisor
    int finish = 0;
    MPI_Status Stat;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank ==0)
    {
        dest = 1;
        srand( time(NULL));

        
        while(finish != 1){
            
            rand();
            my_choice = (rand() % (2 + 1)+1);
            
            rc = MPI_Sendrecv(&my_choice,1,MPI_CHAR,dest,tag
                            ,&rival_choice,1,MPI_CHAR,dest,tag
                            ,MPI_COMM_WORLD,&Stat);
            printf("R%d received %d from %d\n",rank,rival_choice,dest);
            
            //game logic
            if (my_choice == 0){// I use  rock
                if (rival_choice == 0){ //Rival use rock
                printf("R%d (me) I used rock, R%d (rival) used rock, Draw\n",rank,dest);
                }
                else if (rival_choice == 1){ //Rival use paper
                    printf("R%d (me) I used rock, R%d (rival) used paper,R%d lost\n",rank,dest,rank);
                    finish = 1;
                }
                else{ //Rival use scisor
                    printf("R%d (me) I used rock, R%d (rival) used scissor,R%d won\n",rank,dest,rank);
                    finish = 1;
                }
            }
            else if (my_choice == 1){// I use paper
                if (rival_choice == 0){ //Rival use rock
                    printf("R%d (me) I used paper, R%d (rival) used rock,R%d won\n",rank,dest,rank);
                    finish = 1;
                }
                else if (rival_choice == 1){ //Rival use paper
                    printf("R%d (me) I used paper, R%d (rival) used paper,Draw\n",rank,dest);
                }
                else{ //Rival use scisor
                    printf("R%d (me) I used paper, R%d (rival) used scissor,R%d lost\n",rank,dest,rank);
                    finish = 1;
                }
            }
            else{// I use scisor
                if (rival_choice == 0){ //Rival use rock
                    printf("R%d (me) I used scissor, R%d (rival) used rock,R%d lost\n",rank,dest,rank);
                    finish = 1;
                }
                else if (rival_choice == 1){ //Rival use paper
                    printf("R%d (me) I used scissor, R%d (rival) used paper,R%d won\n",rank,dest,rank);
                    finish = 1;
                }
                else{ //Rival use scisor
                    printf("R%d (me) I used scissor, R%d (rival) used scissor,Draw\n",rank,dest);
                }
            }
        }
    }
    else if (rank == 1)
    {
        dest = 0;

        srand( time(NULL));
        
        while(finish != 1){
            my_choice = (rand() % (2 + 1)); //Logic to choose rock,paper or scisor

            rc = MPI_Sendrecv(&my_choice,1,MPI_CHAR,dest,tag
                            ,&rival_choice,1,MPI_CHAR,dest,tag
                            ,MPI_COMM_WORLD,&Stat);
            printf("R%d received %d from %d\n",rank,rival_choice,dest);
        
            //game logic
            if (my_choice == 0){// I use  rock
                if (rival_choice == 0){ //Rival use rock
                    printf("R%d (me) I used rock, R%d (rival) used rock, Draw\n",rank,dest);
                }
                else if (rival_choice == 1){ //Rival use paper
                    printf("R%d (me) I used rock, R%d (rival) used paper,R%d lost\n",rank,dest,rank);
                    finish = 1;
                }
                else{ //Rival use scisor
                  printf("R%d (me) I used rock, R%d (rival) used scissor,R%d won\n",rank,dest,rank);
                  finish = 1;
                }
            }
            else if (my_choice == 1){// I use paper
                if (rival_choice == 0){ //Rival use rock
                  printf("R%d (me) I used paper, R%d (rival) used rock,R%d won\n",rank,dest,rank);
                  finish = 1;
                }
                else if (rival_choice == 1){ //Rival use paper
                  printf("R%d (me) I used paper, R%d (rival) used paper,Draw\n",rank,dest);
                }
                else{ //Rival use scisor
                  printf("R%d (me) I used paper, R%d (rival) used scissor,R%d lost\n",rank,dest,rank);
                  finish = 1;
                }
           }
           else{// I use scisor
               if (rival_choice == 0){ //Rival use rock
                  printf("R%d (me) I used scissor, R%d (rival) used rock,R%d lost\n",rank,dest,rank);
                  finish = 1;
              }
              else if (rival_choice == 1){ //Rival use paper
                  printf("R%d (me) I used scissor, R%d (rival) used paper,R%d won\n",rank,dest,rank);
                  finish = 1;
              }
              else{ //Rival use scisor
                  printf("R%d (me) I used scissor, R%d (rival) used scissor,Draw\n",rank,dest);
              }
          }
        }

    }
    MPI_Finalize();
    return 0;
}