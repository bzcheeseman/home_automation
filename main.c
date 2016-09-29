//
// Created by Aman LaChapelle on 8/19/16.
//

#include "include/slackInterface.h"
#include "include/commandsParsing.h"
#include "include/classificationMachine.h"
#include "include/vectorOps.h"
#include "include/hashTable.h"
#include "include/plotting.h"

int main(){
//  interface_t *in = malloc(sizeof(interface_t));
//  in->initialized = 0;
//  in->current_term = 0;
//  in->interface = NULL;
//
//  importInterface(in);
//  sendMessage(in, "Hi there from C!");
//  handleRequests(in, 3);
//
//
//  command_t *cmd  = getTermCommands(NULL, in->current_term);
//  commitToLog(cmd, NULL);
//
//  shutdownInterface(in);
//  discardCommands(cmd);
//
//  free(in);
//
//  char phrase[] = "hi there hi there hi there ben"; //test phrase
//
//  map_t *bag = mapBigrams(phrase, NULL);
//
//  addPhrase("well hi there", bag); //add a test phrase with a bigram already in the bag
//
//  logtoFile(bag, NULL); //log to file to see what we get

  int len = 10000;

  vector_t **S = malloc(sizeof(vector_t *) * len);

  double xd[len];
  double yd[len];

  double y[len];

  for (int i = 0; i < len; i++){
    double r1 = (double)rand()/(double)RAND_MAX;
    double r2 = (double)rand()/(double)RAND_MAX;

    double pt[2] = {r1, r2};

    xd[i] = r1;
    yd[i] = r2;

    S[i] = newVector(2, pt);

    double m = 1.0;
    double b = 0.0;

    if (r2 >= (m * r1 + b)){
      y[i] = 1.0;
    }
    else if (r2 < (m * r1 + b)){
      y[i] = -1.0;
    }

  }

  printf("Starting SVM computation\n");


  clock_t t = clock();

  svm_t *svmparams = coordDescent(S, y, len, 1e-7, 0.1, innerProduct, identity);
  t = clock() - t;
  double time_taken = (double)t/CLOCKS_PER_SEC;
  printf("Done with SVM, took %lf seconds\n", time_taken);

  int testlen = 219;

  double testpts[(testlen+1)*(testlen+1)];

  for (int j = 0; j <= testlen; j++){
    for (int k = 0; k <= testlen; k++){
      double test[2] = {1.*(double)j/(double)testlen, 1.*(double)k/(double)testlen};
      testpts[(testlen+1) * (j) + (k)] = (double)prediction(svmparams, newVector(2, test));

    }

  }
  vector_t *array = newVector((size_t)(testlen+1)*(testlen+1), testpts);


  plotArray(array, (testlen+1));


  return 0;
}