#include "code_gen/CClass.hh"
#include "code_gen/CNode.hh"
#include "code_gen/platform.hh"


CClass::CClass(const CClass& node) :CNode(node)
{

}

CClass::CClass(const std::string& name) : CNode(name)
{

}

CClass& CClass::operator=(const CClass& node)
{
  CNode::operator=(node);
  
  return *this;
}

std::string CClass::toString(int indentation ) const
{
  std::string ret;
  ret += std::string(indentation, ' ') + "class " + get_name() + "{\n";
  ret += CNode::toString(indentation + 2);
  ret += std::string(indentation, ' ') + "};\n";
  return ret;
}

std::unique_ptr<CNode> CClass::copy() const
{
  return Unew CClass(*this);
}
