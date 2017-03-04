#include "code_gen/CNode.hh"

std::string CNode::toString(int indentation /*= 0*/) const
{
  std::string ret;
  for (auto& e: m_nodes)
  {
    ret += e->toString(indentation);
  }
  return ret;
}

void CNode::add(std::unique_ptr<CNode> node_)
{
  m_nodes.push_back(std::move(node_));
}

void CNode::add(const CNode& node_)
{
  add(node_.copy());
}

CNode::CNode(const CNode& node) :m_name(node.m_name)
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

