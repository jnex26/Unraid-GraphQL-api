#ifndef GRAPHQL_MANAGER_H
#define GRAPHQL_MANAGER_H

#include "GraphQL.h"

class GraphQLManager {
  private:
    static const int MAX_NODES = 50;
    GraphQL* children[MAX_NODES];
    int count = 0;

  public:
    GraphQLManager();
    ~GraphQLManager();  // clean up dynamically allocated objects

    bool addChild(String nodeName, String parentName, int ID);
    String getRootNode() const ;
    bool addRoot(String nodeName);
    void printAll() const;
};

#endif
