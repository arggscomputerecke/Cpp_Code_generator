#ifndef CEnvironment_h__
#define CEnvironment_h__
#include <string>


enum env_type {
  class_e,
  namespace_e,
  Funct_e
};
class CEnvironment {
public:
  CEnvironment(const std::string& name, env_type env) :m_name(name), m_type(env) {}
  env_type m_type;

  std::string m_name;
};

#endif // CEnvironment_h__
