#ifndef TREENODE_H
#define TREENODE_H

class TreeNode {
private:
    char *buffPage;
public:
    TreeNode(char *buffPage);
    char *getBuffPage() {return buffPage;}
    int isLeaf();
    int getNoPairs();
	void setIsLeaf(int value);
    void setNoPairs(int noPairs);
	/**
	  * returns child pointer if present node is not leaf
	  * returns rid if present node is a leaf
	  */
	int getChildPointer(int key);
};

#endif

#ifndef BPLUSTREE_H
#define BPLUSTREE_H

class BPlusTree {
private:
    TreeNode *root;
	char dbName[20]; 
	int maxNoPairs;
public:
    BPlusTree(const char *dbName, const char *indexName, bool create);
    /**
     * Destructor. Just force all the dirty buffer pages to disk.
     */
    ~BPlusTree();
    /**
     * Insert an entry into the index.
     */
    void insertEntry(int key, int rid);
    /**
     * This recursive function is called when a node at some level is
     * split and the new node id along with its first key is to be 
     * inserted in its parent  
     */
	void insertInParent(TreeNode *node, 
						int startKeyInSplitNode, 
						int splitNodeId, 
						TreeNode** trace, int level );
    /**
     * Base case, where a pointer,key pair is inserted into 
     * leaf knowing that the leaf is not full
     */
    void insertInLeaf(TreeNode *leafNode,int key,int rid);
    /**
     * Delete an entry from the index. For now, assume the index
     * to be on a candidate key.
     */
    void deleteEntry(int key);
	/**
     * This recursive function is called when a node at some level is
     * deleted due to insufficient number of entries after deletion, 
     * which needs its deletion along with its first key from 
     * the parent 
     */
    void recursiveDeleteEntry(TreeNode *node,
    							int key,
    							int pointer, 
    							TreeNode** trace, 
    							int level);
	/**
     * This is just same as the above look up
   	 * The only difference is here we dont unpin the trace nodes 
   	 * which will be used in the calling function to insert or 
     * deletion. Index lookup for a key. Returns the rid if found, 
     * else -1. Assuming the index on a candidate key.
     */ 
	int lookUpWithoutUnpin(int key,TreeNode *leafNode);
    /**
     * Index lookup for a key. Returns the rid if found, else -1.
     * Assuming the index on a candidate key.
     */ 
    int lookUp(int key);
	/**
     * To get leaf node in which given key would be there
     */ 
	TreeNode *getLeaf(int key, TreeNode *trace[], int *height);
	/**
     * Recursive function which at level finds the
     * child which can hold the key
     */ 
	TreeNode *getToLeaf(TreeNode *curNode, 
						int key, 
						TreeNode *trace[], 
						int *height, 
						int curLevel );
	/**
     * The implementation of finding child node at some 
     * level of the tree given the node and a key
     */
	TreeNode *getChild(TreeNode *curNode, int key);
};

#endif	//BPLUSTREE_H
