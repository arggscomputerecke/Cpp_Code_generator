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
  void test_constructor();
  void nested_classes();
};
#endif // core_h__
