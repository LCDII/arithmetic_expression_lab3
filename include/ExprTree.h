#pragma once
#include <iostream>

class Number;
class BiOperation;

class Visitor {
public:
    virtual int visitNumber(Number* num) = 0;
    virtual int visitBiOperation(BiOperation* op) = 0;
};

class Expr {
public:
    virtual int accept(Visitor* v) = 0;
    virtual ~Expr() {}
};

class Number : public Expr {
    int val;
public:
    Number(int v) : val(v) {}
    int getVal() { return val; }

    int accept(Visitor* v) override {
        return v->visitNumber(this);
    }
};

class BiOperation : public Expr {
    char op_;
    Expr* left_;
    Expr* right_;

public:
    BiOperation(char op, Expr* l, Expr* r)
        : op_(op), left_(l), right_(r) {}

    Expr* left() { return left_; }
    Expr* right() { return right_; }
    char op() { return op_; }

    int accept(Visitor* v) override {
        return v->visitBiOperation(this);
    }
};

class CalcVisitor : public Visitor {
public:
    int visitNumber(Number* num) override {
        return num->getVal();
    }

    int visitBiOperation(BiOperation* op) override {

        int l = op->left()->accept(this);
        int r = op->right()->accept(this);

        switch (op->op()) {
        case '+': return l + r;
        case '-': return l - r;
        case '*': return l * r;
        case '/': return l / r;
        }

        return 0;
    }
};

class PrintVisitor : public Visitor {
public:
    int visitNumber(Number* num) override {
        std::cout << num->getVal();
        return 0;
    }

    int visitBiOperation(BiOperation* op) override {
        std::cout << "(";
        op->left()->accept(this);
        std::cout << op->op();
        op->right()->accept(this);
        std::cout << ")";
        return 0;
    }
};

class PrintPostfixVisitor : public Visitor {
public:
    int visitNumber(Number* num) override {
        std::cout << num->getVal();
        return 0;
    }

    int visitBiOperation(BiOperation* op) override {
        op->left()->accept(this);
        op->right()->accept(this);
        std::cout << op->op();
        return 0;
    }
};