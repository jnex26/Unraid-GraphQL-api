#ifndef GRAPHQL_H
#define GRAPHQL_H

class GraphQL {
  private:
    char* nodeName;
    char* parentName;
    int id;

    static const int MAX_CHILDREN = 50;
    GraphQL* children[MAX_CHILDREN];
    int childCount;

  public:
    // Constructor
    GraphQL(char *NodeName, char *ParentName, int ID);

    // Method to print info
    void printInfo(int indent = 0);
    bool addChild(GraphQL* child);
};

#endif