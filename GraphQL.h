#ifndef GRAPHQL_H
#define GRAPHQL_H

#include <Arduino.h>

class GraphQL {
  private:
    String nodeName;
    String parentName;
    String fullName;
    int id;

  public:
    GraphQL(String node, String parent, int ID);

    void printInfo() const;

    String getNodeName() const;
    String getParentName() const;
    String getFullName() const;
    int getID() const;
};

#endif