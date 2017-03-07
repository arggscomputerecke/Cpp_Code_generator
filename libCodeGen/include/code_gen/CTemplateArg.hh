#ifndef CTemplateArg_h__
#define CTemplateArg_h__
#include <string>

class CTemplateArg {

  CTemplateArg(const std::string& typename_, const std::string& type_, const std::string& value__ = "");

  std::string m_typeName, m_type, m_value;
};

#endif // CTemplateArg_h__
