public class Heapsort {

    // Function to perform heapsort to sort marks in ascending order
    public static void heapsort(int[] marks) {
        if (marks == null || marks.length <= 1) {
            return;
        }

        // Build max heap
        buildMaxHeap(marks);

        // Perform heapsort
        int n = marks.length;
        for (int i = n - 1; i > 0; i--) {
            // Swap root (maximum element) with the last element
            swap(marks, 0, i);
            // Heapify the reduced heap
            heapify(marks, i, 0);
        }
    }

    // Function to build a max heap
    private static void buildMaxHeap(int[] arr) {
        int n = arr.length;
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
    }

    // Function to heapify a subtree rooted at given index
    private static void heapify(int[] arr, int n, int i) {
        int largest = i; // Initialize largest as root
        int left = 2 * i + 1; // Left child
        int right = 2 * i + 2; // Right child

        // If left child is larger than root
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        // If right child is larger than largest so far
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        // If largest is not root
        if (largest != i) {
            swap(arr, i, largest);
            // Recursively heapify the affected sub-tree
            heapify(arr, n, largest);
        }
    }

    // Function to swap two elements in an array
    private static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    // Function to find the maximum element in an array
    public static int findMax(int[] arr) {
        if (arr == null || arr.length == 0) {
            throw new IllegalArgumentException("Array is empty or null");
        }

        int max = arr[0];
        for (int num : arr) {
            if (num > max) {
                max = num;
            }
        }
        return max;
    }

    // Function to find the minimum element in an array
    public static int findMin(int[] arr) {
        if (arr == null || arr.length == 0) {
            throw new IllegalArgumentException("Array is empty or null");
        }

        int min = arr[0];
        for (int num : arr) {
            if (num < min) {
                min = num;
            }
        }
        return min;
    }

    public static void main(String[] args) {
        int[] marks = {85, 92, 78, 60, 95, 87, 70};

        // Perform heapsort to sort marks in ascending order
        heapsort(marks);

        // Display sorted marks
        System.out.println("Sorted Marks (Ascending Order):");
        for (int mark : marks) {
            System.out.print(mark + " ");
        }
        System.out.println();

        // Find maximum and minimum marks
        int max = findMax(marks);
        int min = findMin(marks);
        System.out.println("Maximum Mark: " + max);
        System.out.println("Minimum Mark: " + min);
    }
}

// Time Complexity: O(n log n)
