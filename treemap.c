#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)){
  
  
  
  TreeMap * new = (TreeMap*)malloc(sizeof(TreeMap));
  new->lower_than=lower_than;
  if (new==NULL)return NULL;
  new->root=NULL;
  new->current=NULL;
    //new->lower_than = lower_than;
  return new;

return NULL;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode * new = createTreeNode(key,value);
  
  if(tree->root==NULL)
  {
    tree->root=new;
    tree->current=new;
  }


  TreeNode * aux=tree->root;
  tree->current=aux;
   
  while(aux!=NULL)
  {
    if(tree->lower_than(key,aux->pair->key)==1)
    {
      if(aux->left==NULL)tree->current=aux;  
      aux=aux->left;
      
    }
    else if(tree->lower_than(key,aux->pair->key)==0)
    {
      if(aux->right==NULL)tree->current=aux;
      aux=aux->right;        
    }
  }
  if(is_equal(tree,key,tree->current->pair->key)==1)
  {
    tree->current=aux;
    return;
      
  }
  if(aux==NULL)
  {
    aux=new;
    if(tree->lower_than(key,tree->current->pair->key)==1)
    {
      tree->current->left= aux;
      aux->parent=tree->current;
      tree->current=aux;
    }
    else if(tree->lower_than(key,tree->current->pair->key)==0){
      tree->current->right= aux;
      aux->parent=tree->current;
      tree->current=aux;
    }
  }
}

TreeNode * minimum(TreeNode * x){
  
  if(x==NULL)return NULL;
  while(x->left!=NULL)
    {
      if(x->left!=NULL)
      {
        x=x->left;
      }
    }
  return x;

  
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(tree->root==NULL)return;

  if(node->parent==NULL)
  {
     if (node->left==NULL || node->right==NULL)
    {
      if(node->left!=NULL)
      {
        node->left->parent=node->parent;
        node->parent->left=node->right;
        node=NULL;
      }
      else if(node->right!=NULL)
      {
        node->right->parent=node->parent;
        node->parent->left=node->right;
        node=NULL;
      }
    }else{

      TreeNode* hijo = node->right;
      hijo=minimum(hijo);
      node->parent->left=hijo;
      hijo->parent=node->parent;
      hijo->right=node->right;
    }
  }
  
  if(node->parent->left==node){
    if (node->left==NULL || node->right==NULL)
    {
      if(node->left!=NULL)
      {
        node->left->parent=node->parent;
        node->parent->left=node->right;
        node=NULL;
      }
      else if(node->right!=NULL)
      {
        node->right->parent=node->parent;
        node->parent->left=node->right;
        node=NULL;
      }
    }else{

      TreeNode* hijo = node->right;
      hijo=minimum(hijo);
      node->parent->left=hijo;
      hijo->parent=node->parent;
      hijo->right=node->right;
    }
  }
  else if(node->parent->right==node)
  {
    if (node->left==NULL || node->right==NULL)
    {
      if(node->left!=NULL)
      {
        node->left->parent=node->parent;
        node->parent->left=node->right;
        node=NULL;
      }
      else if(node->right!=NULL)
      {
        node->right->parent=node->parent;
        node->parent->left=node->right;
        node=NULL;
      }
    }else{

      TreeNode* hijo = node->right;
      hijo=minimum(hijo);
      node->parent->left=hijo;
      hijo->parent=node->parent;
      hijo->right=node->right;
    }
  
  }
  
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {

  TreeNode * aux=tree->root;
  while(aux!=NULL)
  {
    if(is_equal(tree,key,aux->pair->key)==1)
    {
      tree->current=aux;
      return aux->pair;
      
    }
    if(tree->lower_than(key,aux->pair->key)==1)
    {
      aux=aux->left;
    }
    else if(tree->lower_than(key,aux->pair->key)==0)
    {
      aux=aux->right;
    }
  }
  
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
  TreeNode *aux = tree->root;
  TreeNode *max = tree->root;
  int a=0;
  while(aux!=NULL)
  {
    if(is_equal(tree,key,aux->pair->key)==1)
    {
      tree->current=aux;
      return aux->pair;
      
    }
    if(tree->lower_than(key,aux->pair->key)==1)
    {
      aux=aux->left;
      
    }
    else if(tree->lower_than(key,aux->pair->key)==0)
    {
      aux=aux->right;
      a++;
      if(a==1)
      {
        max=aux;
      }
    }
  }
  return max->pair;
  
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode *aux = tree->root;
  while(aux->left!=NULL)
    {
      if(aux->left!=NULL)
      {
        aux=aux->left;
      }
    }
  return aux->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
        
  TreeNode *aux=tree->current;
  if(aux->right!=NULL)
  {
    TreeNode* nodo=aux->right;
    tree->current=minimum(nodo);
    return minimum(nodo);
  }
  else
  {
    while(1)
    {
      if(tree->lower_than(aux->parent->pair->key,aux->pair->key)==1)
      {
        tree->current=aux->parent;
        return aux->parent->pair;
      }
      else
      {
        aux=aux->parent;
      }
    }

  }
 return NULL;   
}
