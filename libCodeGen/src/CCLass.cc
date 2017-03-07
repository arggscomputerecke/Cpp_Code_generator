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



void CClass::getDefinition(std::ostream& out, int indentation /*= 0*/) const
{
  out << std::string(indentation, ' ') + "class " + get_name() + "{\n";
  CNode::getDefinition(out ,indentation + 2);
  out << std::string(indentation, ' ') + "};\n";
}

void CClass::getDeclaration(std::ostream& out, int indentation /*= 0*/) const
{
  out << std::string(indentation, ' ') + "class " + get_name() + ";\n";
}

std::unique_ptr<CNode> CClass::copy() const
{
  return Unew CClass(*this);
}
