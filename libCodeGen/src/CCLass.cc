#include "code_gen/CClass.hh"

CClass::CClass(const CClass& node) :CNode(node)
{

}

CClass::CClass(const std::string& name) : CNode(name)
{

}

CClass& CClass::operator=(const CClass&)
{
  
  
  return *this;
}

std::string CClass::toString() const
{
  std::string ret;
  ret += "class " + get_name() + "{ \n \n }";
  return ret;
}

std::unique_ptr<CNode> CClass::copy() const
{
  return Unew CClass(*this);
}
