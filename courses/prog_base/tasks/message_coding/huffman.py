import sys

class TE:
    " " "Huffman tree element" " "
    def __init__(self,val,probability,left,right):
        self.val = val
        self.probability = probability
        self.left = left
        self.right = right

def huffman_encode(message):
    probabilities={}

    if len(message)==1:
        return 0

    for el in message:
        if el in probabilities:
            probabilities[el]+=1
        else:
            probabilities[el]=1

    tree=[]
    for el in probabilities:
        tree.append(TE(el,probabilities[el],None,None))

    tree=sorted(tree,lambda x,y: y.probability - x.probability)

    while(len(tree)!=1):
        left = tree[-1]
        right = tree[-2]
        new_val = left.val+right.val
        new_probability = left.probability+right.probability
        new_el = TE(new_val,new_probability,left,right)

        for x in range(len(tree)):
            if(tree[x].probability<new_probability):
                tree.insert(x,new_el)
                break

        tree.pop()
        tree.pop()

    encode_table={}
    def view_tree(root,appendix):
        if root==None:
            return
        if(len(root.val)==1):
            print(appendix+" is '"+root.val+"'")
            encode_table[root.val]=appendix
        view_tree(root.left,appendix+"1")
        view_tree(root.right, appendix+"0")
    view_tree(tree[0],"")

    encoded_message=""

    for s in message:
        encoded_message+=encode_table[s]

    return encoded_message

print(huffman_encode(sys.argv[1]))
