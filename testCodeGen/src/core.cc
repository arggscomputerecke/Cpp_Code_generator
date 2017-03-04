#include "testCodeGen/core.hh"
#include "code_gen/CClass.hh"
#include <QtTest/QtTest>
#include <iostream>


void test_class_gen::test_constructor()
{

  CClass myClass("testClass");
  QCOMPARE(myClass.toString(), std::string("class testClass{\n};\n"));
}

void test_class_gen::nested_classes()
{
  CClass myClass("testClass");
  myClass.add(Unew CClass("subclass"));
  QCOMPARE(myClass.toString(), std::string("class testClass{\n  class subclass{\n  };\n};\n"));

}
