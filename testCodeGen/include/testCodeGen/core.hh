#ifndef core_h__
#define core_h__

#include <QtTest/QtTest>

class TestQString : public QObject
{
  Q_OBJECT
    private slots:
  void toUpper();
};

inline void TestQString::toUpper()
{
  QString str = "Hello";
  QCOMPARE(str.toUpper(), QString("HELLO"));
}


class test_class_gen :public QObject {
  Q_OBJECT

    private slots:
  void namespace_with_function_and_body();
  void test_constructor();
  void nested_classes();
  void functions();
  void functions_with_args();
  void function_with_body();
  void function_with_namespace();
  void namespace_test();
  void namespace_with_function();

};
#endif // core_h__
