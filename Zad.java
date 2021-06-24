package mod;

import mod.neighbours.*;

import java.awt.*;
import java.util.*;

public class Zad {
    int height, width, maxCount = 100;
    boolean isFlow;
    Color[][] tab;

    public boolean visualizeEnergies = false;
    public boolean visualizeBabies = false;
    int[][] energies;
    double[][] densities;
    public ArrayList<Color> colors = new ArrayList<Color>();
    Random rand = new Random();
    int colorIndex = 0;
    public NeighbourAlgorithm neighbourAlgorithm;
    MonteCarlo monteCarlo;
    public double kt = 0.1;
    public int remainingMCSteps = 0;
    public REcrystal recrystal;
    boolean[][] isRecrystalizedThen;
    boolean[][] isRecrystalizedNow;

    Zad(int w, int h) {
        width = w;
        height = h;
        neighbourAlgorithm = new VonNeumanNeighbour(width, height, isFlow);
        monteCarlo = new MonteCarlo(neighbourAlgorithm, width, height);
        recrystal = new REcrystal(width, height, monteCarlo);
        ClearTabs();
    }

    private void ClearTabs() {
        tab = new Color[height][width];
        energies = new int[height][width];
        densities = new double[height][width];
        isRecrystalizedThen = new boolean[height][width];
        isRecrystalizedNow = new boolean[height][width];
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                tab[j][i] = NeighbourAlgorithm.neutralColor;
            }
        }
        colorIndex = 0;
        neighbourAlgorithm.isPeriodic = isFlow;
        colors.clear();
        monteCarlo = new MonteCarlo(neighbourAlgorithm, width, height);
        recrystal = new REcrystal(width, height, monteCarlo);
    }

    void createColoredBud(int x, int y) {
        Color col;
        do {
            int r = rand.nextInt(256);
            int g = rand.nextInt(256);
            int b = rand.nextInt(256);
            col = new Color(r, g, b);
        } while (colors.indexOf(col) >= 0 || col.equals(NeighbourAlgorithm.neutralColor));
        colors.add(col);
        tab[y][x] = col;
    }

    public void generateUniform(int row, int col) {
        int odlX = width / row;
        int odlY = height / col;
        for (int j = odlY / 2; j < height; j += odlY) {
            for (int i = odlX / 2; i < width; i += odlX) {
                createColoredBud(i, j);
            }
        }
    }

    public void generateRadius(int n, int radius) {
        int[] tabX = new int[n];
        int[] tabY = new int[n];
        int randX = rand.nextInt(width);
        int randY = rand.nextInt(height);
        createColoredBud(randX, randY);
        tabX[0] = randX;
        tabY[0] = randY;
        for (int i = 1; i < n; i++) {
            int count = 0;
            while (true) {
                randX = rand.nextInt(width);
                randY = rand.nextInt(height);
                boolean isOK = true;
                for (int j = 0; j < i; j++) {
                    if (Math.hypot(randX - tabX[j], randY - tabY[j]) < radius) {
                        isOK = false;
                        count++;
                        break;
                    }
                }
                if (isOK)
                    break;
                if (count > maxCount) {
                    System.out.println("Za duzo punktow");
                    return;
                }
            }
            tabX[i] = randX;
            tabY[i] = randY;
            createColoredBud(randX, randY);
        }
    }

    public void generateRandom(int n) {
        ClearTabs();
        n = Math.min(n, width * height);
        int i = 0;
        while (i < n) {
            int randX = rand.nextInt(width);
            int randY = rand.nextInt(height);
            createColoredBud(randX, randY);
            i++;
        }
    }

    public void changeAlgorithm(int alg) {
        switch (alg) {
            case 0:
                neighbourAlgorithm = new VonNeumanNeighbour(width, height, isFlow);
                break;
            case 1:
                neighbourAlgorithm = new MooreNeighbour(width, height, isFlow);
                break;
            case 2:
                neighbourAlgorithm = new PentagonalNeighbour(width, height, isFlow);
                break;
            case 3:
                neighbourAlgorithm = new HexagonalNeighbour(width, height, isFlow);
                break;
            case 4:
                neighbourAlgorithm = new RadiusNeighbour(width, height, isFlow);
                break;
        }
        //monteCarlo.neighbourAlgorithm = neighbourAlgorithm;
        System.out.println();
    }


    public void generateMyself(int x, int y) {
        createColoredBud(x, y);
    }

    public void stepNeighbour() {
        tab = neighbourAlgorithm.getNextTab(tab);
    }

    public void makeEdgesTab() {
        monteCarlo.makeEdgesTab(tab);
    }

    public void doMonteCarlo() {
        neighbourAlgorithm.colorsTab = tab;
        monteCarlo.makeEdgesTab(tab);
        tab = monteCarlo.doMonteCarlo(tab, kt);
    }

    void _DRX() {
        densities = recrystal.getRecrystalizedDensities();
        //zarodkowanie
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                if (densities[j][i] > (REcrystal.criticalDensity/(width*height)) && monteCarlo.edges[j][i] && !isRecrystalizedThen[j][i]) {
                    createColoredBud(i, j);
                    densities[j][i] = 0;
                    isRecrystalizedNow[j][i] = true;
                }
            }
        }

        //reguły przejscia
        if (recrystal.time > 0) {
            Color colRecrystal=null;
            for (int j = 0; j < height; j++) {
                for (int i = 0; i < width; i++) {
                    Integer[][] neighbours = neighbourAlgorithm.getNeighbours(i, j);
                    boolean someoneISRecrystalized = false;
                    boolean allAreSmaller = true;
                    for (var p : neighbours) {
                        if (isRecrystalizedThen[p[1]][p[0]]) {
                            someoneISRecrystalized = true;
                            colRecrystal = tab[p[1]][p[0]];
                        }
                        if (densities[p[1]][p[0]] >= densities[j][i])
                            allAreSmaller = false;
                    }
                    if (someoneISRecrystalized && allAreSmaller) {
                        tab[j][i]=colRecrystal;
                        densities[j][i] = 0;
                        isRecrystalizedNow[j][i] = true;
                    }
                }
            }
            isRecrystalizedThen = isRecrystalizedNow;
            isRecrystalizedNow = new boolean[height][width];
            densities = new double[height][width];
        }
    }
}