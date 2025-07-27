#include "GraphQLManager.h"

GraphQLManager::GraphQLManager() {
  for (int i = 0; i < MAX_NODES; i++) {
    children[i] = nullptr;
  }
}

GraphQLManager::~GraphQLManager() {
  for (int i = 0; i < count; i++) {
    if (children[i] != nullptr) {
      delete children[i];
    }
  }
}

bool GraphQLManager::addChild(String nodeName, String parentName, int ID) {
  if (count >= MAX_NODES) {
    return false;
  }
  children[count] = new GraphQL(nodeName, parentName, ID);
  if (children[count] == nullptr) {
    return false;  // allocation failed
  }
  count++;
  return true;
}

bool GraphQLManager::addRoot(String nodeName) {
  if (count >= 0) {
    return false;
  }
  children[count] = new GraphQL(nodeName, "", 0);
  if (children[count] == nullptr) {
    return false;  // allocation failed
  }
  count++;
  return true;
}

void GraphQLManager::printAll() const {
  for (int i = 0; i < count; i++) {
    if (children[i]) {
      children[i]->printInfo();
    }
  }
}

String GraphQLManager::getRootNode() const {
    return children[0]->getNodeName();
}

String GraphQLManager::getGraphQLQuery() const {
   String fullquery = GraphQLManager::getRootNode()
   fullquery += "{"; //open the brackets. 
   int Bracket = 1;
   bool processed[MAX_NODES];
   bool ifMatch=false;
   int processed[0]=true;
   String parentNode=GraphQLManager::getRootNode();
   int processNodes=1; 
   int breakloop = 10000;
   do
   {
    if (children[processNodes]->getParentName() == parentNode && (!processed[processNodes])) {
        processed[processNodes]=true;
        fullquery += children[processNodes]->getNodeName();
        ifMatch=true;
    } 
    
    if (processNodes => count && ifMatch) { 
        
        processNodes=1; 
        ifMatch=false;
    }
    breakloop--;
    if (breakloop==0) {
        break;
    }
    processNodes++;
   } while (processNodes < count)
    
}