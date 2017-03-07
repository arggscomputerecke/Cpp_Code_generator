#include <QtTest/QtTest>
#include <iostream>
#include <sstream>


#include "testCodeGen/core.hh"


#include "code_gen/CClass.hh"
#include "code_gen/CFunction.hh"
#include "code_gen/CNamespace.hh"

void test_class_gen::test_constructor()
{

  CClass myClass("testClass");

  std::stringstream ss;
  myClass.getDefinition(ss);
  QCOMPARE(ss.str(), std::string("class testClass{\n};\n"));
}

void test_class_gen::nested_classes()
{
  CClass myClass("testClass");
  myClass.addNode(Unew CClass("subclass"));
  std::stringstream ss;
  myClass.getDefinition(ss);
  QCOMPARE(ss.str(), std::string("class testClass{\n  class subclass{\n  };\n};\n"));

}

void test_class_gen::functions()
{
  CFunction myFun("myFunc");
  std::stringstream ss;
  myFun.getDeclaration(ss);
  QCOMPARE(ss.str(), std::string("void  myFunc();\n"));
}

void test_class_gen::functions_with_args()
{
  CFunction myFun("int", "myFunc", { {"int", "myInt" }, {"std::string" , "myString"} });
  std::stringstream ss;
  myFun.getDeclaration(ss);
  auto s = ss.str();
  QCOMPARE(ss.str(), std::string("int  myFunc( int  myInt, std::string  myString);\n"));
}

void test_class_gen::function_with_body()
{
  auto myFunc = CFunction("int", "myFunc", { { "int", "myInt" },{ "std::string" , "myString" } })
    .addStatement("return 1;");

  std::stringstream ss;
  myFunc.getDefinition(ss);
  auto s = ss.str();
  QCOMPARE(ss.str(), std::string("int  myFunc( int  myInt, std::string  myString) {\n  return 1;\n}\n"));
}

void test_class_gen::function_with_namespace()
{
  auto myFunc = CFunction("int", "myFunc", { { "int", "myInt" },{ "std::string" , "myString" } })
    .addStatement("return 1;");
    myFunc.add_environment(CEnvironment("myNamespace", namespace_t));
  std::stringstream ss;
  myFunc.getDefinition(ss);
  auto s = ss.str();
  QCOMPARE(ss.str(), std::string("int  myNamespace::myFunc( int  myInt, std::string  myString) {\n  return 1;\n}\n"));
}
namespace  myNamespace{  } // end namespace : myNamespace\n
void test_class_gen::namespace_test()
{
  auto myNamespace = CNamespace("myNamespace");

  std::stringstream ss;
  myNamespace.getDeclaration(ss);
  auto s = ss.str();

  QCOMPARE(ss.str(), std::string("namespace myNamespace{\n} // end namespace: myNamespace\n"));
}

void test_class_gen::namespace_with_function()
{
  CNamespace myNamespace = CNamespace("myNamespace")
    .add(CFunction("myFunc")
         );
  std::stringstream ss;
  myNamespace.getDeclaration(ss);
  auto s = ss.str();
  QCOMPARE(ss.str(), std::string("namespace myNamespace{\n  void  myFunc();\n} // end namespace: myNamespace\n"));
}

void test_class_gen::namespace_with_function_and_body()
{
  CNamespace myNamespace = CNamespace("myNamespace1")
    .add(CNamespace("myNamespace2")
      .add(CFunction("myFunc")
        .addStatement("cout << \"hello world\" << endl;")
        .addStatement("return;")
          )
        );
  {
    std::stringstream ss;
    myNamespace.getDeclaration(ss);
    auto s = ss.str();
    QCOMPARE(ss.str(), std::string("namespace myNamespace1{\n  namespace myNamespace2{\n    void  myFunc();\n  } // end namespace: myNamespace2\n} // end namespace: myNamespace1\n"));
  }
  {
    std::stringstream ss;
    myNamespace.getDefinition(ss);
    auto s = ss.str();
    QCOMPARE(ss.str(), std::string("void  myNamespace1::myNamespace2::myFunc() {\n  cout << \"hello world\" << endl;\n  return;\n}\n"));
  }

}
