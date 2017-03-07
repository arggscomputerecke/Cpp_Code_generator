#ifndef CNamespace_h__
#define CNamespace_h__
#include "code_gen/CNode.hh"

class DllExport CNamespace:public CNode {

public:
  CNamespace(const std::string& name);
  CNamespace(const CNamespace&);
  CNamespace& operator=(const CNamespace&);
  virtual void getDefinition(std::ostream&, int indentation = 0) const override;
  virtual void getDeclaration(std::ostream&, int indentation = 0) const override;
  virtual std::unique_ptr<CNode> copy() const override;
  
  CNamespace& add(const CNode& node_);

};

#endif // CNamespace_h__
