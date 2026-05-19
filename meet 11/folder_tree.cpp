#include <bits/stdc++.h>
using namespace std;

struct Node{
    string name;
    vector<Node*> children;

    Node(string folderName){
        name = folderName;
    }
};

class FolderTree{
private:
    Node* root;

public:

    FolderTree(){
        root = new Node("Root");
    }

    Node* getRoot(){
        return root;
    }

    void addFolder(Node* parent, string folderName){
        Node* newFolder = new Node(folderName);
        parent->children.push_back(newFolder);
    }

    void display(Node* node, int level = 0){

        if(node == NULL)
            return;

        for(int i = 0; i < level; i++){
            cout << "   ";
        }

        cout << "|-- " << node->name << endl;

        for(Node* child : node->children){
            display(child, level + 1);
        }
    }

    void preorder(Node* node){

        if(node == NULL)
            return;

        cout << node->name << endl;

        for(Node* child : node->children){
            preorder(child);
        }
    }

    void postorder(Node* node){

        if(node == NULL)
            return;

        for(Node* child : node->children){
            postorder(child);
        }

        cout << node->name << endl;
    }

    bool search(Node* node, string target){

        if(node == NULL)
            return false;

        if(node->name == target)
            return true;

        for(Node* child : node->children){
            if(search(child, target))
                return true;
        }

        return false;
    }

    int countFolder(Node* node){

        if(node == NULL)
            return 0;

        int total = 1;

        for(Node* child : node->children){
            total += countFolder(child);
        }

        return total;
    }

    bool showPath(Node* node, string target){

        if(node == NULL)
            return false;

        cout << "/" << node->name;

        if(node->name == target)
            return true;

        for(Node* child : node->children){
            if(showPath(child, target))
                return true;
        }

        return false;
    }
};

int main(){

    FolderTree ft;

    Node* root = ft.getRoot();

    ft.addFolder(root, "Documents");
    ft.addFolder(root, "Pictures");
    ft.addFolder(root, "Music");

    ft.addFolder(root->children[0], "Kuliah");
    ft.addFolder(root->children[0], "Tugas");

    cout << "Struktur Folder\n";
    ft.display(root);

    cout << "\nPreorder Traversal\n";
    ft.preorder(root);

    cout << "\nPostorder Traversal\n";
    ft.postorder(root);

    cout << "\nJumlah Folder: ";
    cout << ft.countFolder(root) << endl;

    cout << "\nSearch Folder 'Tugas'\n";

    if(ft.search(root, "Tugas")){
        cout << "Folder ditemukan\n";
    }else{
        cout << "Folder tidak ditemukan\n";
    }

    cout << "\nPath Folder:\n";

    ft.showPath(root, "Tugas");

    return 0;
}
