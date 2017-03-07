#include "code_gen/CHeaderStatement.hh"

CHeaderStatement::CHeaderStatement(const std::string& name):CNode(name)
{

}

void CHeaderStatement::getDefinition(std::ostream&, int indentation /*= 0*/) const
{
 
}

void CHeaderStatement::getDeclaration(std::ostream& out, int indentation /*= 0*/) const
{
  out << std::string(indentation, ' ') << get_name() << "\n";
}

std::unique_ptr<CNode> CHeaderStatement::copy() const
{
  return Unew CHeaderStatement(*this);
}
