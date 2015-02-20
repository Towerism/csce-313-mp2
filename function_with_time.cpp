/* **********************Author Info************************** */
/* *@author    Christopher Findeisen                         * */
/* *@contact    <cfindeisen7@gmail.com>                      * */
/* *@date     Thu 19 Feb 21:39:43 2015                       * */
/* *********************************************************** */
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;
vector<int> data_table;

//function to measure time
int requestForData(string which_one){
  int passed = atoi(which_one.c_str());
  return data_table[passed];
}
void init_data(){
    data_table.push_back(9);
    data_table.push_back(10);
    data_table.push_back(1);
    data_table.push_back(2);
    data_table.push_back(3);
    data_table.push_back(4);
    data_table.push_back(5);
    data_table.push_back(6);
    data_table.push_back(6);
    data_table.push_back(8);
}

int main() {
  init_data();
  //time
  clock_t start;

#include <ctime>
  start = std::clock();
  requestForData("1");
  std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
  return 1;
}

