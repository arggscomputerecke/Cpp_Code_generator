#ifndef CClass_h__
#define CClass_h__

#include "code_gen/CNode.hh"



class DllExport CClass :public CNode {
public: 
  CClass(const std::string& name);
  CClass(const CClass& node);
  CClass& operator=(const CClass&);
  virtual void getDefinition(std::ostream&, int indentation = 0) const override;
  virtual void getDeclaration(std::ostream&, int  indentation = 0) const override;
  virtual std::unique_ptr<CNode> copy() const  override;


  CClass& add(const CNode& t);
  inline CClass& operator<<(const CNode& n) {
    return add(n);
  }
};

#endif // CClass_h__
