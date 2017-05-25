class Logic {
    public:
        static int[] getNeighbors(int row, int col) {
            return {
                {row-1, col},
                {row-1, col+1},
                {row, col-1},
                {row, col+1},
                {row+1, col-1},
                {row+1, col}
            };
        }
};
