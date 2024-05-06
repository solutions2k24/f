public class SortAlgorithms {
    // Heap Sort
    public static class HeapSort {
        public void sort(int arr[]) {
            int n = arr.length;

            // Build heap (rearrange array)
            for (int i = n / 2 - 1; i >= 0; i--)
                heapify(arr, n, i);

            // One by one extract an element from heap
            for (int i = n - 1; i > 0; i--) {
                // Move current root to end
                int temp = arr[0];
                arr[0] = arr[i];
                arr[i] = temp;

                // call max heapify on the reduced heap
                heapify(arr, i, 0);
            }
        }

        // To heapify a subtree rooted with node i which is an index in arr[]
        void heapify(int arr[], int n, int i) {
            int largest = i; // Initialize largest as root
            int l = 2 * i + 1; // left = 2*i + 1
            int r = 2 * i + 2; // right = 2*i + 2

            // If left child is larger than root
            if (l < n && arr[l] > arr[largest])
                largest = l;

            // If right child is larger than largest so far
            if (r < n && arr[r] > arr[largest])
                largest = r;

            // If largest is not root
            if (largest != i) {
                int swap = arr[i];
                arr[i] = arr[largest];
                arr[largest] = swap;

                // Recursively heapify the affected sub-tree
                heapify(arr, n, largest);
            }
        }

        // Function to print array of size n
        public void printArray(int arr[]) {
            int n = arr.length;
            for (int i = 0; i < n; ++i)
                System.out.print(arr[i] + " ");
            System.out.println();
        }
    }

    // Shell Sort
    public static class ShellSort {
        public void sort(int arr[]) {
            int n = arr.length;

            // Start with a big gap, then reduce the gap
            for (int gap = n / 2; gap > 0; gap /= 2) {
                // Do a gapped insertion sort for this gap size.
                // The first gap elements arr[0..gap-1] are already in gapped order
                // keep adding one more element until the entire array is gap sorted
                for (int i = gap; i < n; i += 1) {
                    // add arr[i] to the elements that have been gap sorted
                    // save arr[i] in temp and make a hole at position i
                    int temp = arr[i];

                    // shift earlier gap-sorted elements up until the correct location for arr[i] is found
                    int j;
                    for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                        arr[j] = arr[j - gap];

                    // put temp (the original arr[i]) in its correct location
                    arr[j] = temp;
                }
            }
        }

        // Function to print array of size n
        public void printArray(int arr[]) {
            int n = arr.length;
            for (int i = 0; i < n; ++i)
                System.out.print(arr[i] + " ");
            System.out.println();
        }
    }

    public static void main(String args[]) {
        // Heap Sort
        int arr1[] = {12, 11, 13, 5, 6, 7};
        HeapSort heapSort = new HeapSort();
        System.out.println("Array before sorting:");
        heapSort.printArray(arr1);
        heapSort.sort(arr1);
        System.out.println("Array after Heap Sort:");
        heapSort.printArray(arr1);

        System.out.println();

        // Shell Sort
        int arr2[] = {12, 34, 54, 2, 3};
        ShellSort shellSort = new ShellSort();
        System.out.println("Array before sorting:");
        shellSort.printArray(arr2);
        shellSort.sort(arr2);
        System.out.println("Array after Shell Sort:");
        shellSort.printArray(arr2);
    }
}
