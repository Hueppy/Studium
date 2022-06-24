/*
 * override.cpp
 *
 * Author: Carsten Gips
 */

class A {
    void func1();

    virtual void func2(float);

    virtual void func3() const;

    virtual long func4(int);

    virtual void f();

    virtual void h(int) final;
};

class B : public A {
    virtual void fun1() override;

    virtual void func2(double) override;

    virtual void func3() override;

    virtual int func4(int) override;

    virtual void f() override;

    virtual void h(int);

    virtual void h(double);

    virtual void g(long) final;
};

int main() {
    A base;
    B derived;
}
