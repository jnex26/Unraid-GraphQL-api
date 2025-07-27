#include "GraphQL.h"
#include <Arduino.h>  // Needed for Serial

// Constructor implementation
GraphQL::GraphQL(char *NodeName, char *ParentName, int ID) {
  nodeName = NodeName;
  parentName = ParentName;
  id = ID;
  childCount = 0;


  for (int i = 0; i < MAX_CHILDREN; i++) {
    children[i] = nullptr;
  }
}

bool GraphQL::addChild(GraphQL* child) {
  if (childCount < MAX_CHILDREN) {
    children[childCount++] = child;
    return true;
  }
  return false;
}

// Method implementation
void GraphQL::printInfo(int indent) {
  // Indent based on depth
  for (int i = 0; i < indent; i++) {
    Serial.print("  ");
  }
  
  Serial.print("Node: ");
  Serial.print(nodeName);
  Serial.print(", Parent: ");
  Serial.print(parentName);
  Serial.print(", ID: ");
  Serial.println(id);

  // Print children recursively
  for (int i = 0; i < childCount; i++) {
    children[i]->printInfo(indent + 1);
  }
}