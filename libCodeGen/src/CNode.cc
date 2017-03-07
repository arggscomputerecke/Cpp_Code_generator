#include "code_gen/CNode.hh"

void CNode::getDefinition(std::ostream& out, int indentation) const
{
  
  for (auto& e: m_nodes)
  {
    e->getDefinition(out,indentation);
  }
  
}

void CNode::getDeclaration(std::ostream& out, int indentation /*= 0*/) const
{
  for (auto& e : m_nodes)
  {
    e->getDeclaration(out, indentation);
  }

}

void CNode::addNode(std::unique_ptr<CNode> node_)
{
  for (auto&e :m_env){
    node_->add_environment(e);
  }
  m_nodes.push_back(std::move(node_));
}

void CNode::addNode(const CNode& node_)
{
  addNode(node_.copy());
}

CNode::CNode(const CNode& node) :m_name(node.m_name),m_env(node.m_env)
{
  for (auto& e: node.m_nodes){
    m_nodes.push_back(e->copy());
  }

 
}

CNode::CNode(const std::string& name) :m_name(name)
{

}

const std::string& CNode::get_name() const
{
  return m_name;
}

CNode& CNode::operator=(const CNode& node)
{
  m_name = node.m_name;
  m_nodes.clear();
  for (auto& e : node.m_nodes) {
    m_nodes.push_back(e->copy());
  }

  return *this;
}

CNode& CNode::add_environment(const CEnvironment& env_)
{
  m_env.push_back(env_);
  for (auto& e:m_nodes){
    e->add_environment(env_);
  }
  return *this;
}