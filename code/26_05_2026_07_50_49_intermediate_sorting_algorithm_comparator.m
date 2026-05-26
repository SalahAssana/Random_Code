% Sorting Algorithm Comparator
%
% This script compares the performance of different sorting algorithms on synthetic data.

function sort_times = compare_sorting_algorithms()
    % Initialize variables to store times for each algorithm
    times_quicksort = zeros(10, 1);
    times_mergesort = zeros(10, 1);
    times_insertionsort = zeros(10, 1);

    % Create synthetic data (random integers)
    rand_numbers = randi([0, 10000], [100000, 1]);

    % Loop over the number of elements to sort
    for i = 1:10
        n_elements = i * 10000;
        data = rand_numbers(1:n_elements);

        % Record time taken by quicksort algorithm
        tic; quicksort(data); toc; times_quicksort(i) = toc;

        % Record time taken by mergesort algorithm
        tic; mergesort(data); toc; times_mergesort(i) = toc;

        % Record time taken by insertionsort algorithm
        tic; insertionsort(data); toc; times_insertionsort(i) = toc;
    end

    % Display the results
    fprintf('Algorithm\tTime (seconds)\n');
    fprintf('Quicksort\t%.2f\n', mean(times_quicksort));
    fprintf('Mergesort\t%.2f\n', mean(times_mergesort));
    fprintf('Insertion Sort\t%.2f\n', mean(times_insertionsort));

end

function quicksort(arr)
    if length(arr) > 1
        pivot = arr(1);
        left = arr(2:end);
        right = arr(end:-1:2);

        % Recursively sort the subarrays
        tic; quicksort(left); toc;
        tic; quicksort(right); toc;

        % Combine the sorted subarrays and the pivot element
        [sorted_left, idx] = sort(left);
        arr(1:end-1) = sorted_left;
        arr(end) = pivot;
    end
end

function mergesort(arr)
    if length(arr) > 1
        mid = floor(length(arr)/2);
        left = arr(1:mid);
        right = arr(mid+1:length(arr));

        % Recursively sort the subarrays
        tic; mergesort(left); toc;
        tic; mergesort(right); toc;

        % Merge the sorted subarrays
        [sorted_left, idx] = sort(left);
        [sorted_right, idx] = sort(right);

        arr(1:end) = [sorted_left; sorted_right];
    end
end

function insertionsort(arr)
    for i = 2:length(arr)
        key = arr(i);
        j = i-1;

        % Shift elements to the right of the key until the correct position is found
        while j > 0 && arr(j) > key
            arr(j+1) = arr(j);
            j = j-1;
        end

        arr(j+1) = key;
    end