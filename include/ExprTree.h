#pragma once
#include <iostream>

class IntegerNode;
class BiOperation;

class Visitor {
public:
    virtual int visitNumber(IntegerNode* num) = 0;
    virtual int visitBiOperation(BiOperation* op) = 0;
};

class Expr {
public:
    virtual void accept(Visitor* v) = 0;
    virtual ~Expr() {}
};

class IntegerNode : public Expr {
    int val;
public:
    IntegerNode(int v) : val(v) {}
    int getVal() { return val; }

    void accept(Visitor* v) override {
        v->visitNumber(this);
    }
};

class DoubleNode : public Expr {
    
    
};

class BiOperation : public Expr {
    char op_;
    Expr* left_;
    Expr* right_;
    double result;
public:
    BiOperation(char op, Expr* l, Expr* r)
        : op_(op), left_(l), right_(r) {}

    Expr* left() { return left_; }
    Expr* right() { return right_; }
    char op() { return op_; }
    double res() { return result; }

    void accept(Visitor* v) override {
         result = v->visitBiOperation(this);
    }
};

class WhileNode : public Expr {

};

class SemicolonNode : public Expr {

};

class Variable : public Expr {

};

class Assignment : public Expr {

};

class Condition : public Expr {

};

class CalcVisitor : public Visitor {
public:
    int visitNumber(IntegerNode* num) override {
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
    int visitNumber(IntegerNode* num) override {
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
    int visitNumber(IntegerNode* num) override {
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