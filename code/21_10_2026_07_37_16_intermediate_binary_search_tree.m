% Binary Search Tree in MATLAB
classdef BST < handle
    properties
        root
    end
    
    methods
        function this = BST()
            this.root = [];
        end
        
        function insert(this, value)
            if isempty(this.root)
                this.root = Node(value);
            else
                this.root = this._insertRecursive(this.root, value);
            end
        end
        
        function node = _insertRecursive(this, node, value)
            if value < node.value
                if ~isempty(node.left)
                    node.left = this._insertRecursive(node.left, value);
                else
                    node.left = Node(value);
                end
            elseif value > node.value
                if ~isempty(node.right)
                    node.right = this._insertRecursive(node.right, value);
                else
                    node.right = Node(value);
                end
            else
                error('Value already exists in the tree');
            end
            node
        end
        
        function find = search(this, value)
            find = this._searchRecursive(this.root, value);
        end
        
        function result = _searchRecursive(this, node, value)
            if isempty(node) || value == node.value
                result = node;
            elseif value < node.value
                result = this._searchRecursive(node.left, value);
            else
                result = this._searchRecursive(node.right, value);
            end
        end
        
        function delete = _delete(this, node, value)
            if isempty(node) || value ~= node.value
                error('Value not found in the tree');
            elseif isleaf(node)
                delete = [];
                this.root = [];
            else
                node = this._deleteRecursive(node, value);
                this.root = node;
            end
        end
        
        function result = _deleteRecursive(this, node)
            if ~isempty(node.left) && ~isempty(node.right)
                min = this.findMin(node.right);
                node.value = min.value;
                node.right = this._deleteRecursive(node.right, min.value);
            elseif ~isempty(node.left)
                delete = node;
                node = node.left;
            else
                delete = node;
                node = node.right;
            end
            result = node;
        end
        
        function find = findMin(this, node)
            if isempty(node.left) && isempty(node.right)
                find = node;
            else
                find = this.findMin(node.left);
            end
        end
        
        function isleaf = isleaf(this, node)
            isleaf = isempty(node.left) && isempty(node.right);
        end
    end
    
end

classdef Node < handle
    properties
        value
        left
        right
    end
    
    methods
        function this = Node(value)
            this.value = value;
            this.left = [];
            this.right = [];
        end
    end
end

% Example usage
bst = BST();
numbers = [5, 3, 8, 2, 4, 7, 9];
for i = 1:length(numbers)
    bst.insert(numbers(i));
end

find = bst.search(4);
if ~isempty(find)
    fprintf('Value found: %d\n', find.value);
else
    fprintf('Value not found in the tree.\n');
end

bst.delete(bst._deleteRecursive(bst.root, 8));