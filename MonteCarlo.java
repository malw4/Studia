package mod.neighbours;

import java.awt.*;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Random;

public class MonteCarlo {
    int width, height;
    public NeighbourAlgorithm neighbourAlgorithm;
    ArrayList<Integer> randX = new ArrayList<>();
    ArrayList<Integer> randY = new ArrayList<>();
    public boolean[][] edges;
    Random rand = new Random();

    public MonteCarlo(NeighbourAlgorithm neigh, int width, int height) {
        this.width = width;
        this.height = height;
        neighbourAlgorithm = neigh;
    }

    public void makeEdgesTab(Color[][] tab) {
        edges = neighbourAlgorithm.getEdges(tab);
    }

    public Color[][] doMonteCarlo(Color[][] tab, double kt) {
        Color[][] newTab = new Color[height][width];
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                newTab[j][i] = tab[j][i];
            }
        }
        makeRandomPositions();
        while (!randX.isEmpty()) {
            int randomIndex = rand.nextInt(randX.size());
            int x = randX.get(randomIndex);
            int y = randY.get(randomIndex);
            randX.remove(randomIndex);
            randY.remove(randomIndex);
            if (edges[y][x]) {
                int energyNOW = calculateEnergy(x, y, tab[y][x]);
                Color bestColor = tab[y][x];
                int lowestEnergy = energyNOW;
                Color[] nc = neighbourAlgorithm.getNeighboursColors(x, y, tab[y][x]);
                if(nc.length > 0) {
                    Color col = nc[rand.nextInt(nc.length)];
                    int hypotheticalEnergy = calculateEnergy(x, y, col);
                    if (hypotheticalEnergy <= lowestEnergy) {
                        bestColor = col;
                    } else {
                        double p = Math.exp((-1 * (hypotheticalEnergy - energyNOW)) / kt);
                        if (rand.nextDouble() <= p)
                            bestColor = col;
                    }
                    tab[y][x] = bestColor;
                }
            }
        }
        return tab;
    }

    private int calculateEnergy(int x, int y, Color col) {
        return neighbourAlgorithm.getEnergy(x, y, col);
    }

    void makeRandomPositions() {
        randX.clear();
        randY.clear();
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                randX.add(i);
                randY.add(j);
            }
        }
    }
}
