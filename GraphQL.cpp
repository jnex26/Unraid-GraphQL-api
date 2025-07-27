#include "GraphQL.h"

GraphQL::GraphQL(String node, String parent, int ID) {
  nodeName = node;
  parentName = parent;
  id = ID;
  fullName = parent + "_" + node;
}

String GraphQL::getNodeName() const {
  return nodeName;
}

String GraphQL::getParentName() const {
  return parentName;
}

String GraphQL::getFullName() const {
  return fullName;
}

int GraphQL::getID() const {
  return id;
}

void GraphQL::printInfo() const {
  Serial.print("Full Name: ");
  Serial.print(fullName);
  Serial.print(", ID: ");
  Serial.println(id);
}
