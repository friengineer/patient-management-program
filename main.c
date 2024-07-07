#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 60 patients in waiting room at most
#define queueSize 60
// 10 consulting rooms at most
#define maxRooms 10

// stores the waiting queue of the patients
int queue[queueSize];
// stores whether a doctor is in a room and ready, a doctor is in a room and is not ready
// or there is no doctor in a room. It also stores the number of each patient in each consulting room
int room[maxRooms];
int front=0;
int back=0;
bool empty=false;
bool full=false;
int deq=0;
// administrator commands password
int password=1234;
// stores which consulting rooms doctors are in
int availRoom[maxRooms];

// checks if the waiting queue is empty. True indicates the waiting queue is empty, false indicates the waiting
// queue is not empty
bool IsEmpty(){
  if (front==-1&&back==-1){
    return true;
  }
  else{
    return false;
  }
}

// checks if the waiting queue is full. True indicates the waiting queue is full and false indicates the waiting
// queue is not full
bool IsFull(){
  if (front==0&&back==(queueSize-1)){
    return true;
  }
  else if (front==(back+1)){
    return true;
  }
  else{
    return false;
  }
}

// adds a newly checked in patient number to the queue if all doctors are busy
void enqueue(int n){
  empty=IsEmpty();
  full=IsFull();

  // check if the waiting queue is full and if not the patient number is added to the waiting queue in the correct position
  // in the queue array
  if (full==true){
    printf("Sorry, the waiting queue is full. Please try again later.\n");
  }
  else{
    if (empty==true){
      front+=1;
      back+=1;
      queue[back]=n;
    }
    else{
      if (back==(queueSize-1)){
        back=0;
        queue[back]=n;
      }
      else{
        back+=1;
        queue[back]=n;
      }
    }
  }
}

// removes the first patient number in the queue. Returns -1 if the waiting queue is empty
int dequeue(){
  empty=IsEmpty();
  if (empty==true){
    return -1;
  }
  else{
    if (front==back){
      deq=queue[front];
      front=-1;
      back=-1;
      return deq;
    }
    else if (front==(queueSize-1)){
      deq=queue[front];
      front=0;
      return deq;
    }
    else{
      deq=queue[front];
      front+=1;
      return deq;
    }
  }
}

// returns the first patient number in the waiting queue. Returns -1 if the waiting queue is empty
int first(){
  empty=IsEmpty();
  if (empty==true){
    return -1;
  }
  else{
    return queue[front];
  }
}

// returns the last patient number in the waiting queue. Returns -1 if the waiting queue is empty
int last(){
  empty=IsEmpty();
  if (empty==true){
    return -1;
  }
  else{
    return queue[back];
  }
}

// clears the waiting queue
void clear(){
  front=-1;
  back=-1;
  for (int i=0;i<queueSize;i++){
    queue[i]=0;
  }
}

// displays the waiting queue
void print(){
  empty=IsEmpty();
  if (empty==true){
    printf("There is currently no queue.\n");
  }
  else{
    if (front<back){
      for (int i=front;i<=back;i++){
        printf("%i, ", queue[i]);
      }
      printf("\n");
    }
    else if (front>back){
      for (int i=front;i<queueSize;i++){
        printf("%i, ", queue[i]);
      }

      for (int i=0;i<=back;i++){
        printf("%i, ", queue[i]);
      }

      printf("\n");
    }
    else{
      printf("%i", queue[front]);
      printf("\n");
    }
  }
}

// returns the position the patient number is in in the waiting queue. Returns -2 if the waiting queue is empty and -1
// if the patient number is not in the waiting queue
int position(int n){
  empty=IsEmpty();
  if (empty==true){
    return -2;
  }
  else{
    if ((front<=back)&&front!=-1){
      for (int i=0;i<queueSize;i++){
        if (n==queue[i]){
          return i+1;
        }
      }
    }
    else if (front>back){
      int count=0;
      for (int i=front;i<queueSize;i++){
        count++;
        if (n==queue[i]){
          return count;
        }
      }

      for (int i=0;i<=back;i++){
        count++;
        if (n==queue[i]){
          return count;
        }
      }
    }
    return -1;
  }
}

// removes the patient number from the waiting queue
void removeID(int n){
  empty=IsEmpty();
  if (empty==true){
    printf("There is currently no queue.\n");
  }
  else{
    bool notIn=false;
    bool defNotIn=false;
    if (front<back){
      for (int i=front;i<=back;i++){
        // checks if the patient number is equal to the queue element being examined
        if (n==queue[i]){
          if (i==front){
            front+=1;
          }
          else if(i==back){
            back-=1;
          }
          else{
            for (int k=i;k<back;k++){
              queue[k]=queue[k+1];
              back-=1;
            }
          }
        notIn=false;
        break;
        }
        else{
          notIn=true;
        }
      }

      if (notIn==true){
        printf("You are not in the queue.\n");
      }
      else{
        printf("You have been removed from the queue. Thank you for your visit.\n");
      }
    }
    else if (front>back){
      for (int i=front;i<queueSize;i++){
        if (n==queue[i]){
          if (i==front){
            if (front==(queueSize-1)){
              front=0;
              notIn=false;
            }
            else{
              front+=1;
              notIn=false;
            }
          }
          else{
            if (i==(queueSize-1)){
              queue[i]=queue[0];
              notIn=false;
            }
            else{
              for (int k=i;k<(queueSize-1);k++){
                queue[k]=queue[k+1];
                queue[(queueSize-1)]=queue[0];
                notIn=false;
              }
            }
          }
          break;
        }
        else{
          notIn=true;
        }
      }

      if (notIn=true){
        for (int i=0;i<=back;i++){
          if (n==queue[i]){
            if (i==back&&back!=0){
              back-=1;
              printf("You have been removed from the queue. Thank you for your visit.\n");
            }
            else if (i==back&&back==0){
              back=(queueSize-1);
              printf("You have been removed from the queue. Thank you for your visit.\n");
            }
            else{
              for (int k=i;k<back;k++){
                queue[k]=queue[k+1];
              }
              back-=1;
              printf("You have been removed from the queue. Thank you for your visit.\n");
            }
            break;
          }
          else{
            defNotIn=true;
          }
        }
      }
      else{
        if (back==0){
          back=(queueSize-1);
          printf("You have been removed from the queue. Thank you for your visit.\n");
        }
        else{
          for (int i=0;i<back;i++){
            queue[i]=queue[i+1];
          }
          back-=1;
          printf("You have been removed from the queue. Thank you for your visit.\n");
        }
      }

      if (defNotIn=true){
        printf("You are not in the queue.\n");
      }
    }
    else{
      if (n==queue[front]){
        front=-1;
        back=-1;
        printf("You have been removed from the queue. Thank you for your visit.\n");
      }
      else{
        printf("You are not in the queue.\n");
      }
    }
  }
}

// clears the consulting rooms
void clearRoom(){
  for (int i=0;i<maxRooms;i++)
  {
    room[i]=-3;
  }
}

// checks to see if a doctor is ready to see a patient and if so returns the room number they are in. Returns 0 if no doctors are ready
int docReady(){
  int roomNum=0;

  for (int i=0;i<maxRooms;i++){
    if (room[i]==-1){
      roomNum=(i+1);
      break;
    }
  }

  return roomNum;
}

// counts how many doctors are in the surgery
int docCount(){

  int count=0;

  for (int i=0;i<maxRooms;i++){
    availRoom[i]=0;
  }

  for (int i=0;i<maxRooms;i++){
    if (room[i]!=-3){
      availRoom[count]=(i+1);
      count+=1;
    }
  }

  return count;
}

// checks if an entered patient number is valid
bool validID(int n){
  if (n<0||n>999){
    return false;
  }
  else{
    return true;
  }
}

// checks if an entered room number is valid
bool validRoom(int n){
  if (n<1||n>10){
    return false;
  }
  else{
    return true;
  }
}

// checks if the patient is in the room and if so returns the room number they are in. Returns -1 if the patient is not
// being seen by a doctor
int inRoom(int n){
  for (int i=0;i<maxRooms;i++){
    if (room[i]==n){
      return i+1;
    }
  }

  return -1;
}

// checks if the administrator password entered is correct
bool admin(){
  int pass=0;

  printf("Enter the admininstrator password to execute this command:\n");
  printf(">>> ");
  scanf("%i", &pass);

  if (pass==password){
    printf("\n");
    printf("Password accepted.\n");
    return true;
  }
  else{
    printf("\n");
    printf("Incorrect password.\n");
    return false;
  }
}

void main(){
  char com;
  int num=0;
  int pos=0;
  bool valid=false;
  bool authenticate2=false;

  clear();
  clearRoom();

  // prevents the program from being quit by a normal user by checking if the user has entered option 'x' and if the
  // correct administrator password has been entered
  while (authenticate2!=true){
    bool authenticate=false;

    printf("\n");
    printf("Welcome to the Doctor's Surgery. Please enter a command below. If you do not know how to use this service or enter commands, please enter 'h'.\n");                //these two lines are repeatedly displayed until the program is quit
    printf(">>> ");
    com=getchar();

    // checks if a character requiring a number has been entered and checks for a number if so
    if (com=='i'||com=='p'||com=='q'||com=='o'||com=='r'||com=='a'){
      scanf("%i", &num);
    }

    // checks the character stored in 'com' and executes the corresponding block of code
    switch (com){
      // checks a patient in
      case 'i':
        printf("\n");

        valid=validID(num);

        // checks if a valid patient number has been entered
        if (valid==false){
          printf("Please enter a patient ID number between 0 and 999.\n");
        }
        else{
          int beingSeen=inRoom(num);

          if (beingSeen!=-1){
            printf("Patient %i is already in room %i.\n", num, beingSeen);
          }
          else{
            full=IsFull();

            if (full==true){
              printf("Sorry, the waiting queue is full. Please try again later.\n");
            }
            else{
              pos=position(num);

              // checks if the patient number is already in the waiting queue
              if (pos==-1||pos==-2){
                enqueue(num);

                int roomNum=docReady();

                if (roomNum==0){
                  printf("All doctors are busy right now, please relax in the waiting area. You are number %i in the queue.\n", position(num));
                }
                else{
                  deq=dequeue();

                  printf("Please proceed to room %i.\n", roomNum);
                  room[roomNum-1]=num;
                }
              }
              else{
              printf("You are already checked in.\n");
              }
            }
          }
        }

        break;
      // tells a patient what position they are in in the waiting queue
      case 'p':
        printf("\n");

        valid=validID(num);

        // checks if a valid patient number has been entered
        if (valid==false){
          printf("Please enter a patient ID number between 0 and 999.\n");
        }
        else{
          pos=position(num);

          if (pos==-2){
            printf("There is currently no queue.\n");
          }
          else if (pos==-1){
            printf("You are not in the queue.\n");
          }
          else{
            printf("You are number %i in the queue.\n", pos);
          }
        }

        break;
      // removes a patient from the waiting queue
      case 'q':
        printf("\n");

        valid=validID(num);

        // checks if a valid patient number has been entered
        if (valid==false){
          printf("Please enter a patient ID number between 0 and 999.\n");
        }
        else{
          removeID(num);
        }

        break;
      // tells the patient how many doctors are in the surgery and what rooms they are in
      case 'd':
        printf("\n");

        int numDoc=docCount();

        if (numDoc==0){
          printf("There are currently no doctors in the surgery. Please wait and a doctor will be along shortly.\n");
        }
        else if (numDoc==1){
          printf("There is currently 1 doctor in the surgery. They are in room %i.\n", availRoom[0]);
        }
        else{
          printf("There are currently %i doctors in the surgery. They are in rooms ", numDoc);

          // displays the room numbers the present doctors are in
          for (int i=0;;i++){
            if (availRoom[i]!=0){
              printf("%i, ", availRoom[i]);
            }
            else{
              break;
            }
          }

          printf("\n");
        }

        break;
      // displays a list of the commands that can be entered and what they do
      case 'h':
        printf("\n");

        printf("You can enter the following commands into the the console:\n");
        printf("\n");
        printf("  For patients:\n");
        printf("    i ### - Allows patients to check themselves in. Replace the hashtags with your patient ID number (maximum 3 numbers).\n");
        printf("    p ### - Allows patients to check what position they are in in the queue. Replace the hashtags with your patient ID number (maximum 3 numbers).\n");
        printf("    q ### - Allows patients to remove themselves from the queue if they no longer wish to be seen by a doctor. Replace the hashtags with your patient ID number (maximum 3 numbers).\n");
        printf("    d - Allows patients to check how many doctors are in the surgery and which rooms they are in.\n");
        printf("    h - Displays a list of all of the commands that can be entered into the console.\n");
        printf("\n");
        printf("  For staff (requires verification):\n");
        printf("    o ### - Allows doctors to check patients out of the surgery once they have been seen. Replace the hashtags with the patient's ID number (maximum 3 numbers).\n");
        printf("    r ## - Allows doctors to indicate that they are ready to see patients in their room. Replace the hashtags with your room number (maximum 2 numbers).\n");
        printf("    a ## - Allows doctors to indicate that they are leaving their room. Replace the hashtags with your room number (maximum 2 numbers).\n");
        printf("    w - Allows staff to see what patients are still in the waiting queue.\n");
        printf("    x - Allows staff to exit the program.\n");

        break;
      // discharges a patient from a consulting room
      case 'o':
        printf("\n");

        valid=validID(num);

        // checks if a valid patient number has been entered
        if (valid==false){
          printf("Please enter a patient ID number between 0 and 999.\n");
        }
        else{
          authenticate=admin();

          // checks if the adminisrator password has been entered correctly
          if (authenticate==true){
            printf("\n");
            bool notIn=false;

            // checks if the patient is in one of the consulting rooms
            for (int i=0;i<maxRooms;i++){
              if (room[i]==num){
                room[i]=-2;
                printf("Patient %i has been successfully discharged.\n", num);
                notIn=false;
                break;
              }
              else{
                notIn=true;
              }
            }

            if (notIn==true){
              printf("Patient %i is not in any room.\n", num);
            }
          }
        }

        break;
      // indicates that a doctor is ready to see a patient
      case 'r':
        printf("\n");

        valid=validRoom(num);

        // checks if a valid room number has been entered
        if (valid==false){
          printf("Please enter a room number between 1 and 10.\n");
        }
        else{
          authenticate=admin();

          // checks if the administrator password has been entered correctly
          if (authenticate==true){
            printf("\n");
            empty=IsEmpty();

            // checks if the waiting queue is empty
            if (empty==true){
              if (room[num-1]>=0){
               printf("Patient %i is still in the room. Please discharge them first.\n", room[num-1]);
              }
              else{
                printf("There are no more patients in the waiting queue.\n");
                room[num-1]=-1;
              }
            }
            else{
              if (room[num-1]==-2||room[num-1]==-3){
                room[num-1]=dequeue();
                printf("Patient %i, please go to room %i.\n", room[num-1], num);
              }
              else{
                printf("Patient %i is still in the room. Please discharge them first.\n", room[num-1]);
              }
            }
          }
        }

        break;
      // indicates that a doctor is leaving a consulting room
      case 'a':
        printf("\n");

        valid=validRoom(num);

        // checks if a valid room number has been entered
        if (valid==false){
          printf("Please enter a room number between 1 and 10.\n");
        }
        else{
          authenticate=admin();

          // checks if the administrator password has been entered correctly
          if (authenticate==true){
            printf("\n");

            if (room[num-1]==-2||room[num-1]==-1){
              room[num-1]=-3;
            }
            else{
              printf("Patient %i is still in the room. Please discharge them first.\n", room[num-1]);
            }
          }
        }

        break;
      // displays the waiting queue
      case 'w':
        printf("\n");

        authenticate=admin();

        // checks if the administrator password has been entered correctly
        if (authenticate==true){
          printf("\n");
          printf("The following patients are still waiting to be seen by a doctor:\n");
          print();
        }

        break;
      // stops execution of the program
      case 'x':
        printf("\n");

        authenticate=admin();

        // checks if the administrator password has been entered correctly
        if (authenticate==true){
          printf("\n");
          authenticate2=true;
        }

        break;
      // executed if an invalid command has been entered
      default:
        printf("\n");
        printf("Please enter a valid command letter.\n");
    }

    getchar();
  }

  printf("You have exited the program.\n");
  exit(0);
}
