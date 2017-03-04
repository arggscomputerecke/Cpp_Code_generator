#include <string>
#include <vector>
#include <memory>
#include "code_gen/platform.hh"

class DllExport CNode {
public:
  virtual std::string toString() const = 0;
  virtual std::unique_ptr<CNode> copy() const = 0;

  void add(std::unique_ptr<CNode> node_);
  void add(const CNode& node_);
  CNode(const CNode& node);
  CNode(const std::string& name);
  CNode& operator=(const CNode& other);
  const std::string& get_name() const;
private:
  std::vector<std::unique_ptr<CNode>> m_nodes;
  std::string m_name;
};