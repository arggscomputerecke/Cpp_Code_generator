#ifndef CNode_h__
#define CNode_h__



#include <string>
#include <vector>
#include <memory>
#include "code_gen/platform.hh"
#include "code_gen/CEnvironment.hh"

class DllExport CNode {
public:
  using env_list = std::vector<CEnvironment>;
  virtual void getDefinition( std::ostream& , int indentation = 0) const;
  virtual void getDeclaration(std::ostream&, int  indentation = 0) const =0;
  virtual std::unique_ptr<CNode> copy() const = 0;

  void addNode(std::unique_ptr<CNode> node_);
  void addNode(const CNode& node_);
  CNode(const CNode& node);
  CNode(const std::string& name);
  CNode& operator=(const CNode& other);
  const std::string& get_name() const;
  CNode& add_environment(const CEnvironment& env_);
protected:
  std::vector<std::unique_ptr<CNode>> m_nodes;
  std::string m_name;
  env_list m_env;
};

#endif // CNode_h__