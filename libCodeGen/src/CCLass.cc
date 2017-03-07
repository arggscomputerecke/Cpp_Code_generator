#include "code_gen/CClass.hh"
#include "code_gen/CNode.hh"
#include "code_gen/platform.hh"


CClass::CClass(const CClass& node) :CNode(node)
{
  
}

CClass::CClass(const std::string& name) : CNode(name)
{
  m_env.push_back(CEnvironment(name,class_e));
}

CClass& CClass::operator=(const CClass& node)
{
  CNode::operator=(node);
  
  return *this;
}



void CClass::getDefinition(std::ostream& out, int indentation /*= 0*/) const
{
  CNode::getDefinition(out, indentation);
}

void CClass::getDeclaration(std::ostream& out, int indentation /*= 0*/) const
{
  out << std::string(indentation, ' ') << "class " << m_env[0].m_name << "{\n";
  CNode::getDeclaration(out, indentation + 2);
  out << std::string(indentation, ' ') << "} // end class: " << m_env[0].m_name << "\n";
}

std::unique_ptr<CNode> CClass::copy() const
{
  return Unew CClass(*this);
}

CClass& CClass::add(const CNode& t)
{

  CNode::addNode(t);
  return *this;
}
