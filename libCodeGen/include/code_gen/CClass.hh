#ifndef CClass_h__
#define CClass_h__

#include "code_gen/CNode.hh"


class DllExport CClass :public CNode {
public: 
  CClass(const std::string& name);
  CClass(const CClass& node);
  CClass& operator=(const CClass&);
  virtual std::string toString(int indentation = 0) const override;
  virtual std::unique_ptr<CNode> copy() const  override;

  
};

#endif // CClass_h__
