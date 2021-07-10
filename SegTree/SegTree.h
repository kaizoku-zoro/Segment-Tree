#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H
#define left(i) (2*i + 1)
#define right(i) (2*i + 2)
#define parent(i) ((i-1)/2)
#include <vector>
using namespace std;
template<class T> //data type to be stored in the SegTree

class SegmentTree
{
	public:
		SegmentTree(std::vector<T> data, T value, T (*combine)(T obj1, T obj2));//construct from vector
        SegmentTree(T ar[], int n, T value, T (*combine)(T obj1, T obj2));//construct from array
		
		T query(int l,int r); //returns the answer of a query made on range l to r (zero based indexing)
		
		void update(int idx,T val); //updates the element at index idx in original array to val
		
	private:
		
		T *tree; //pointer to the array which will store our seg tree
		
		void buildTree(vector<T> data); //build tree utility
		
		int TreeSize;
		
		T identityValue; //For the purpose of returning from empty queries
						 //and to fill up the array to make its size a power of 2
						 // depends on the queries to be made on the tree
		
		T (*combine)(T obj1, T obj2); //The function which combines the results of queries made upon the chidren node to
									 //generate the result for the parent node
		
		int calculateSize(int n); //size of the array needed to store the tree
		
		T queryHelper(int l,int r, int st, int ed, int node); //fucntion that answers queries recursively
				
};

template<class T> SegmentTree<T>::SegmentTree(vector<T> data,T value, T (*combine)(T obj1, T obj2)){
	this->combine = combine;
	identityValue = value;
	TreeSize = calculateSize(data.size());
	buildTree(data);
}

template<class T> SegmentTree<T>::SegmentTree(T a[], int n,T value, T (*combine)(T obj1, T obj2)){
	this->combine = combine;
	identityValue = value;
	TreeSize = calculateSize(n);
	std::vector<T> data;
   	for(int i = 0; i < n; i++)
         data.push_back(a[i]);

	buildTree(data);
}

template<class T> int SegmentTree<T>::calculateSize(int n){
	int pow2 = 1;
    while( pow2 < n)
    {
        pow2 = pow2 << 1;
    }
    return 2*pow2 - 1;
}

template<class T> T SegmentTree<T>::query(int l, int r)
{
    int st = 0, ed = TreeSize/2;
    return queryHelper(l, r, st, ed, 0);
}

template<class T> T SegmentTree<T>::queryHelper(int l,int r, int st, int ed, int node){
	//l,r => range over which query is to be performed
	//st,ed => range in the array which the SegTree-Node node contains the answer of
	
	//if the node's range is completely present in the query
	if(l<=st&&ed<=r) return tree[node];
	
	if(r<st || l>ed || l>r)return identityValue;
	
	T leftVal = queryHelper(l,r,st,(st+ed)/2,left(node));
	T rightVal = queryHelper(l,r,(st+ed)/2 + 1,ed,right(node));
	
	return combine(leftVal, rightVal);
	
}

template<class T> void SegmentTree<T>::buildTree(std::vector<T> data){
	int n=data.size();
	tree = new T[TreeSize];
	int extraNodes = (TreeSize/2 + 1) - n;
	for(int i = TreeSize - 1; i >= 0; i--){
       if(extraNodes>0)
           {
               tree[i] = identityValue;
               extraNodes--;
           }
       else if(n>0)
           {
               tree[i] = data[n-1];
               n--;
           }
       else
           tree[i] = combine(tree[left(i)], tree[right(i)]);
   }
   for(int i=0;i<TreeSize;i++){
   	cout<<tree[i]<<" ";
   }
   cout<<endl;
   
}

template<class T> void SegmentTree<T>::update(int idx, T val)
{
    int segTreeIdx = (TreeSize/2) + idx;
    tree[segTreeIdx] = val;
    while(parent(segTreeIdx) >= 0)
    {
        segTreeIdx = parent(segTreeIdx);
        if(right(segTreeIdx) < TreeSize)
          tree[segTreeIdx] = combine(tree[left(segTreeIdx)], tree[right(segTreeIdx)]);
        if(segTreeIdx == 0)
            break;
    }
}

#endif // SEGMENTTREE_H

