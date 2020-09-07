#ifndef __TEARDOWN_H__
#define __TEARDOWN_H__

template <typename T> struct ITeardown
{
  virtual ~ITeardown() {}
  virtual void operator()(T *t) = 0;
};

template <typename T, typename D> class TeardownFunctor : public ITeardown<T>
{
private:
  D method;

public:
  TeardownFunctor(D d) : method(d) {}
  virtual void operator()(T *t) { method(t); }
};

#endif // __TEARDOWN_H__