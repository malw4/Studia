package mod.neighbours;

import java.awt.*;

public abstract class NeighbourAlgorithm {

    public boolean isPeriodic;
    public Color[] possibleColors;
    public static Color neutralColor = Color.white;
    public Color[][] colorsTab;
    protected int width, height;


    public int getIndexOfMax(int[] arr) throws Exception {
        int sum = 0;
        int maxAt = 0;
        for (int i = 0; i < arr.length; i++) {
            sum += arr[i];
            if (arr[i] > arr[maxAt])
                maxAt = i;
        }
        if (sum == 0)
            throw new Exception();
        return maxAt;
    }

    public Color[][] getNextTab(Color[][] tab) {
        colorsTab = tab;
        height = colorsTab.length;
        width = colorsTab[0].length;
        Color[][] newTab = new Color[height][width];
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                newTab[j][i] = colorsTab[j][i];
            }
        }
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                if (newTab[j][i].equals(neutralColor)) {
                    newTab[j][i] = decideCell(i, j);
                }
            }
        }
        return newTab;
    }

    public boolean[][] getEdges(Color[][] tab) {
        colorsTab = tab;
        height = tab.length;
        width = tab[0].length;
        boolean[][] edgesTab = new boolean[height][width];
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                edgesTab[j][i] = isEdge(i, j);
            }
        }
        return edgesTab;
    }

    public boolean isEdge(int x, int y) {
        return isEdge(x, y, colorsTab[y][x]);
    }

    // returns count of neighbours with color different than color passed in argument
    public abstract int getEnergy(int x, int y, Color color);

    // checks if there are neighbours with color different than color passed in argument
    public abstract boolean isEdge(int x, int y, Color color);

    // returns color which most of neighbours have (but not neutral)
    protected abstract Color decideCell(int x, int y);

    // returns array of colors of all neighbours (without repetitions)
    public abstract Color[] getNeighboursColors(int x, int y, Color myColor);

    public abstract Integer[][] getNeighbours(int x, int y);
}
