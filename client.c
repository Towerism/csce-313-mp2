#include <unistd.h>
#include <sys/wait.h>
#include "reqchannel.h"
#include <ctime>
#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "reqchannel.H"

using namespace std;

void startClient();

int main(int argc, char* argv[]) {
    pid_t parent = getpid();
    pid_t pid = fork();
    if (pid > 0) {
        //execv("simpleclient", argv);
        startClient();
    } else {
        printf("Hi from child\n");
        execv("dataserver", argv);
    }
}


string int2string(int number) {
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

string echo(string message){
    return message;
}
void timeFuncVsChannel(RequestChannel& chan){
  std::clock_t    start;
  string request_string = "hello";
  start = std::clock();
  echo(request_string);
  clock_t function_time = (clock() - start);

  start = std::clock();
  string reply1 = chan.send_request("hello");
  clock_t channel_time = (clock() - start);
  clock_t total_time = channel_time + function_time;
  std::cout << endl << "---TIME---" << endl;
  std::cout << "Function Time: " << function_time / (CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
  std::cout << "Channel Time: " << channel_time / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
  std::cout << "Totatl Time: " << total_time / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
}

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

void startClient(){
  cout << "CLIENT STARTED:" << endl;
  string request_string = "hello";
  cout << "Establishing control channel... " << flush;
  RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
  cout << "done." << endl;

  /* -- Start sending a sequence of requests */
  string reply1 = chan.send_request("hello");
  cout << "Reply to request 'hello' is '" << reply1 << "'" << endl;

  string reply2 = chan.send_request("data Joe Smith");
  cout << "Reply to request 'data Joe Smith' is '" << reply2 << "'" << endl;

  string reply3 = chan.send_request("data Jane Smith");
  cout << "Reply to request 'data Jane Smith' is '" << reply3 << "'" << endl;

  for(int i = 0; i < 100; i++) {
    string request_string("data TestPerson" + int2string(i));
    string reply_string = chan.send_request(request_string);
    cout << "reply to request " << i << ":" << reply_string << endl;;
  }
  timeFuncVsChannel(chan);

  string reply4 = chan.send_request("quit");
  cout << "Reply to request 'quit' is '" << reply4 << endl;

  usleep(1000000);
}
