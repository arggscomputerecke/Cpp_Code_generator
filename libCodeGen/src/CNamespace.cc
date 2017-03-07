#include "code_gen/CNamespace.hh"

CNamespace::CNamespace(const std::string& name):CNode(name)
{
  m_env.push_back(CEnvironment(name, namespace_e));
}

CNamespace::CNamespace(const CNamespace& nameSpace_):CNode(nameSpace_)
{
}

CNamespace& CNamespace::operator=(const CNamespace& rhs)
{
  CNode::operator=(rhs);

  return *this;


}

void CNamespace::getDefinition(std::ostream& out, int indentation /*= 0*/) const
{
  CNode::getDefinition(out, indentation);
}

void CNamespace::getDeclaration(std::ostream& out, int indentation /*= 0*/) const
{
  out << std::string(indentation, ' ') << "namespace "<< m_env[0].m_name << "{\n";
  CNode::getDeclaration(out, indentation + 2);
  out << std::string(indentation, ' ')  << "} // end namespace: " << m_env[0].m_name << "\n";
}

std::unique_ptr<CNode> CNamespace::copy() const
{
  return Unew CNamespace(*this);
}

CNamespace& CNamespace::add(const CNode& node_)
{

  CNode::addNode(node_);
  return *this;
}
