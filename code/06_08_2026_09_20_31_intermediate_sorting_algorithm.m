% Sorting Algorithm
%
% This script demonstrates three sorting algorithms: bubble sort,
% insertion sort, and quicksort.

function s = sortAlgorithms()
    % Synthetic data for testing
    n = 10;
    arr = randi(100, 1, n);
    
    % Bubble Sort
    function s = bubbleSort(arr)
        n = length(arr);
        for i = 1:n-1
            swapped = false;
            for j = 1:n-i
                if arr(j) > arr(j+1)
                    temp = arr(j);
                    arr(j) = arr(j+1);
                    arr(j+1) = temp;
                    swapped = true;
                end
            end
            if ~swapped
                break;
            end
        end
        s = arr;
    end
    
    % Insertion Sort
    function s = insertionSort(arr)
        n = length(arr);
        for i = 2:n
            key = arr(i);
            j = i-1;
            while j >= 1 && arr(j) > key
                arr(j+1) = arr(j);
                j = j-1;
            end
            arr(j+1) = key;
        end
        s = arr;
    end
    
    % Quicksort
    function s = quicksort(arr)
        if length(arr) <= 1
            s = arr;
        else
            pivot = arr(1);
            less = [];
            greater = [];
            for i = 2:length(arr)
                if arr(i) <= pivot
                    less = [less; arr(i)];
                else
                    greater = [greater; arr(i)];
                end
            end
            s = [quicksort(less); pivot; quicksort(greater)];
        end
    end
    
    % Main script
    arr = randi(100, 1, n);
    
    fprintf('Original array: ');
    disp(arr);
    
    bubbleSortArr = bubbleSort(arr);
    fprintf('\nBubble sort result: ');
    disp(bubbleSortArr);
    
    insertionSortArr = insertionSort(arr);
    fprintf('\nInsertion sort result: ');
    disp(insertionSortArr);
    
    quicksortArr = quicksort(arr);
    fprintf('\nQuicksort result: ');
    disp(quicksortArr);
end

s = sortAlgorithms();