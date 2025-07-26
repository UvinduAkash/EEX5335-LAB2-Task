class MatrixMultiply {

    static final int SIZE = 3;
    static int[][] A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    static int[][] B = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    static int[][] C = new int[SIZE][SIZE]; // Result

    static class Worker extends Thread {
        int row;

        Worker(int row) {
            this.row = row;
        }

        public void run() {
            for (int col = 0; col < SIZE; col++) {
                C[row][col] = 0;
                for (int k = 0; k < SIZE; k++) {
                    C[row][col] += A[row][k] * B[k][col];
                }
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread[] threads = new Thread[SIZE];

        // Start threads
        for (int i = 0; i < SIZE; i++) {
            threads[i] = new Worker(i);
            threads[i].start();
        }

        // Wait for threads to finish
        for (int i = 0; i < SIZE; i++) {
            threads[i].join();
        }

        // Print result
        System.out.println("Resultant Matrix C = A x B:");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                System.out.printf("%4d", C[i][j]);
            }
            System.out.println();
        }
    }
}
