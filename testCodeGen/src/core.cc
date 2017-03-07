#include <QtTest/QtTest>
#include <QtCore/QDir>
#include <QtWidgets/QPushButton>
#include <iostream>
#include <sstream>
#include <fstream>


#include "testCodeGen/core.hh"


#include "code_gen/CClass.hh"
#include "code_gen/CFunction.hh"
#include "code_gen/CNamespace.hh"
#include "code_gen/CHeaderFunction.hh"
#include "code_gen/CTemplateFunction.hh"
#include "code_gen/CHeaderStatement.hh"
#include "code_gen/CConstructor.hh"

void test_class_gen::test_constructor()
{

  CClass myClass("testClass");

  std::stringstream ss;
  myClass.getDeclaration(ss);
  auto s = ss.str();
  QCOMPARE(ss.str(), std::string("class testClass{\n} // end class: testClass\n"));
}

void test_class_gen::nested_classes()
{
  CClass myClass("testClass");
  myClass.addNode(Unew CClass("subclass"));
  std::stringstream ss;
  myClass.getDeclaration(ss);
  auto s = ss.str();
  QCOMPARE(ss.str(), std::string("class testClass{\n  class subclass{\n  } // end class: subclass\n} // end class: testClass\n"));

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
    myFunc.add_environment(CEnvironment("myNamespace", namespace_e));
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

void test_class_gen::class_with_constructor()
{
  //auto cl1 = CClass("myClass").add(CConstructor({ {"typename","T"} }));  // this seems to be a bug that this sintax does not work


  auto cl = CClass("myClass")
    << (CConstructor({ std::make_pair("int","myInt") })
    .addMemberInitializers("m_test(myInt)")
    .addMemberInitializers("m_t2(42)")
    .addStatement("int i = 43;")
    << inline_t);

  std::stringstream ss;
  cl.getDeclaration(ss);
  auto s = ss.str();
  QCOMPARE(ss.str(), std::string("class myClass{\n    myClass( int  myInt) : m_test(myInt), m_t2(42){\n    int i = 43;\n  }\n} // end class: myClass\n"));
}

void test_class_gen::headerStatements()
{
  auto myNamespace = CNamespace("myN").add(CHeaderStatement("int i =0;"));
  std::stringstream ss;
  myNamespace.getDeclaration(ss);
  auto s = ss.str();
  QCOMPARE(ss.str(), std::string("namespace myN{\n  int i =0;\n} // end namespace: myN\n"));
}

void test_class_gen::templateFunction()
{
  auto myNamespace = CNamespace("myN")
    .add(CTemplateFunction({ { "typename","T" } }, "T", "myTemplateFunction", { { "T&&", "t" } })
      .addStatement(" return t;")
    );

  std::stringstream ss;
  myNamespace.getDeclaration(ss);
  auto s = ss.str();
  QCOMPARE(ss.str(), std::string("namespace myN{\n  template <typename  T>\n  T  myTemplateFunction( T&&  t){\n     return t;\n  }\n} // end namespace: myN\n"));
}

void test_class_gen::signal_create_function()
{
  

  auto metaObject = QPushButton::staticMetaObject;

  std::string QClassName = metaObject.className();
  std::string className = "Signals_";
  className += QClassName;

  auto cl = CClass(className);

  cl.add(CPublic());
  cl.add(CHeaderStatement(className + "(" + QClassName +"* obj) :m_object(obj) {}"));
  for (int i = 0; i < metaObject.methodCount(); i++) {
    auto method = metaObject.method(i);

    if (method.methodType() == QMetaMethod::Signal) {
     auto methode_name = std::string(method.name());
      std::string statement__ = "return make_signal_slot(m_object, &" + QClassName + "::" + methode_name+ ");";
      auto CF = CHeaderFunction("auto", methode_name, {}).addStatement(statement__);
      cl.add(CF);
    }
  }

  cl.add(CHeaderStatement("private:"))
    .add(CHeaderStatement(QClassName + "* m_object;"));
  std::ofstream out("test.cc");
  cl.getDeclaration(out);


  auto fun = CFunction(className, "_singals", { { QClassName + "*","obj" } })
    .addStatement(std::string("return ") + className + "(obj);") << inline_t;
  
  fun.getDeclaration(out);

 
}

void test_class_gen::class_with_member_functions()
{
  CNamespace myNamespace = CNamespace("myNamespace")
    .add(CClass("MyClass")
      .add(CFunction("myFunc"))
    );
  {
    std::stringstream ss;
    myNamespace.getDefinition(ss);
    auto s = ss.str();
    QCOMPARE(ss.str(), std::string("void  myNamespace::MyClass::myFunc() {\n}\n"));


  }
  {
    std::stringstream ss;
    myNamespace.getDeclaration(ss);
    auto s = ss.str();
    QCOMPARE(ss.str(), std::string("namespace myNamespace{\n  class MyClass{\n    void  myFunc();\n  } // end class: MyClass\n} // end namespace: myNamespace\n"));
  }


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

void test_class_gen::namespace_with_multiple_function_and_body()
{
  CNamespace myNamespace = CNamespace("myNamespace1")
    .add(CNamespace("myNamespace2")
      .add(CFunction("myFunc")
        .addStatement("cout << \"hello world\" << endl;")
        .addStatement("return;")
      )
      .add(CFunction("int", "myFunc", { { "int", "myInt" },{ "std::string" , "myString" } })
        .addStatement("return 1;")
      )
    );
  {
    std::stringstream ss;
    myNamespace.getDeclaration(ss);
    auto s = ss.str();
    QCOMPARE(ss.str(), std::string("namespace myNamespace1{\n  namespace myNamespace2{\n    void  myFunc();\n    int  myFunc( int  myInt, std::string  myString);\n  } // end namespace: myNamespace2\n} // end namespace: myNamespace1\n"));
  }
  {
    std::stringstream ss;
    myNamespace.getDefinition(ss);
    auto s = ss.str();
    QCOMPARE(ss.str(), std::string("void  myNamespace1::myNamespace2::myFunc() {\n  cout << \"hello world\" << endl;\n  return;\n}\nint  myNamespace1::myNamespace2::myFunc( int  myInt, std::string  myString) {\n  return 1;\n}\n"));
  }

}
