#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//simple parser
typedef struct expr{
  struct expr* left;
  struct expr* right;
  char operation;
  double leftOperand;
  double rightOperand;
}Expr;

typedef Expr* ExprPtr;
typedef ExprPtr ExprTree;

void error(char* message);

ExprTree maketree();
ExprTree droptree(ExprTree tree);
ExprPtr makeExprPtr(ExprPtr left, ExprPtr right, double leftOperand, double rightOperand, char operation);

double performAddition(double left, double right);
double performSubtraction(double left, double right);
double performMultiplication(double left, double right);
double performDivision(double left, double right);
double evalExprTree(ExprTree tree);

ExprTree add(ExprPtr left, ExprPtr right, double leftOperand, double rightOperand);
ExprTree sub(ExprPtr left, ExprPtr right, double leftOperand, double rightOperand);
ExprTree times(ExprPtr left, ExprPtr right, double leftOperand, double rightOperand);
ExprTree division(ExprPtr left, ExprPtr right, double leftOperand, double rightOperand);

/* the first parameter is the left sub-expression, if we have a leaf on the left the the first parameter is NULL
   the first parameter is the right sub-expression, if we have a leaf on the right the the second parameter is NULL
   the third parameter is the value for the left leaf, if we have a left sub-expression this value can be everything
   the fourth parameter have the same role of the third but he is the right leaf
*/

int main(int argc, char const *argv[]) {
  ExprTree tree = add(times(NULL, NULL, 3, 6), add(NULL, times(NULL, NULL, 2, 9), 6, 0), 0, 0);
  printf("%s%lf\n", "(3*6)+(6+(2*9)) = ", evalExprTree(tree));
  tree = droptree(tree);
  return 0;
}

void error(char* message){
  fprintf(stderr, "%s\n", message);
  exit(1);
}

ExprTree maketree(){
  return NULL;
}

ExprTree droptree(ExprTree tree){
  if(tree){
    tree->left = droptree(tree->left);
    tree->right = droptree(tree->right);
    free(tree);
  }
  return NULL;
}

ExprPtr makeExprPtr(ExprPtr left, ExprPtr right, double leftOperand, double rightOperand, char operation){
  ExprPtr newnode = (ExprPtr) malloc(sizeof(Expr));
  if(!newnode) error("error in function makeExprPtr");
  newnode->left = left;
  newnode->right = right;
  newnode->leftOperand = leftOperand;
  newnode->rightOperand = rightOperand;
  newnode->operation = operation;
  return newnode;
}

double performAddition(double left, double right){
  return left + right;
}

double performSubtraction(double left, double right){
  return left - right;
}

double performMultiplication(double left, double right){
  return left * right;
}

double performDivision(double left, double right){
  if(!right) error("division by 0! ");
  return left/right;
}

double evalExprTree(ExprTree tree){
  double retValue = 0;
  switch (tree->operation) {
    case '+':
      if(tree->left && tree->right){
        retValue = performAddition(evalExprTree(tree->left), evalExprTree(tree->right));
      }else if(tree->left && !tree->right){
        retValue = performAddition(evalExprTree(tree->left), tree->rightOperand);
      }else if(!tree->left && tree->right){
        retValue = performAddition(tree->leftOperand, evalExprTree(tree->right));
      }else{//leaf node
        retValue = performAddition(tree->leftOperand, tree->rightOperand);
      }
      break;
    case '-':
      if(tree->left && tree->right){
        retValue = performSubtraction(evalExprTree(tree->left), evalExprTree(tree->right));
      }else if(tree->left && !tree->right){
        retValue = performSubtraction(evalExprTree(tree->left), tree->rightOperand);
      }else if(!tree->left && tree->right){
        retValue = performSubtraction(tree->leftOperand, evalExprTree(tree->right));
      }else{//leaf node
        retValue = performSubtraction(tree->leftOperand, tree->rightOperand);
      }
      break;
    case '*':
      if(tree->left && tree->right){
        retValue = performMultiplication(evalExprTree(tree->left), evalExprTree(tree->right));
      }else if(tree->left && !tree->right){
        retValue = performMultiplication(evalExprTree(tree->left), tree->rightOperand);
      }else if(!tree->left && tree->right){
        retValue = performMultiplication(tree->leftOperand, evalExprTree(tree->right));
      }else{//leaf node
        retValue = performMultiplication(tree->leftOperand, tree->rightOperand);
      }
      break;
    case '/':
      if(tree->left && tree->right){
        retValue = performDivision(evalExprTree(tree->left), evalExprTree(tree->right));
      }else if(tree->left && !tree->right){
        retValue = performDivision(evalExprTree(tree->left), tree->rightOperand);
      }else if(!tree->left && tree->right){
        retValue = performDivision(tree->leftOperand, evalExprTree(tree->right));
      }else{//leaf node
        retValue = performDivision(tree->leftOperand, tree->rightOperand);
      }
      break;
  }
  return retValue;
}

ExprTree add(ExprPtr left, ExprPtr right, double leftOperand, double rightOperand){
  ExprPtr newnode;
  if(left && right){
    newnode = makeExprPtr(left, right, 0, 0, '+');
  }else if(!left && right){
    newnode = makeExprPtr(NULL, right,  leftOperand, 0, '+');
  }else if(left && !right){
    newnode = makeExprPtr(left, NULL, 0, rightOperand, '+');
  }else{
    newnode = makeExprPtr(NULL, NULL, leftOperand, rightOperand, '+');
  }
  return newnode;
}

ExprTree sub(ExprPtr left, ExprPtr right, double leftOperand, double rightOperand){
  ExprPtr newnode;
  if(left && right){
    newnode = makeExprPtr(left, right, 0, 0, '-');
  }else if(!left && right){
    newnode = makeExprPtr(NULL, right,  leftOperand, 0, '-');
  }else if(left && !right){
    newnode = makeExprPtr(left, NULL, 0, rightOperand, '-');
  }else{
    newnode = makeExprPtr(NULL, NULL, leftOperand, rightOperand, '-');
  }
  return newnode;
}

ExprTree times(ExprPtr left, ExprPtr right, double leftOperand, double rightOperand){
  ExprPtr newnode;
  if(left && right){
    newnode = makeExprPtr(left, right, 0, 0, '*');
  }else if(!left && right){
    newnode = makeExprPtr(NULL, right,  leftOperand, 0, '*');
  }else if(left && !right){
    newnode = makeExprPtr(left, NULL, 0, rightOperand, '*');
  }else{
    newnode = makeExprPtr(NULL, NULL, leftOperand, rightOperand, '*');
  }
  return newnode;
}
ExprTree division(ExprPtr left, ExprPtr right, double leftOperand, double rightOperand){
  ExprPtr newnode;
  if(left && right){
    newnode = makeExprPtr(left, right, 0, 0, '/');
  }else if(!left && right){
    newnode = makeExprPtr(NULL, right,  leftOperand, 0, '/');
  }else if(left && !right){
    newnode = makeExprPtr(left, NULL, 0, rightOperand, '/');
  }else{
    newnode = makeExprPtr(NULL, NULL, leftOperand, rightOperand, '/');
  }
  return newnode;
}
