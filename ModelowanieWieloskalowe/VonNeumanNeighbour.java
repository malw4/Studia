package mod.neighbours;

import java.awt.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class VonNeumanNeighbour extends NeighbourAlgorithm {

    public VonNeumanNeighbour(int w, int h, boolean isPeriod) {
        width = w;
        height = h;
        isPeriodic = isPeriod;
    }

    @Override
    protected Color decideCell(int x, int y) {
        Color[] neighbours = new Color[4];
        int j = 0;
        if (isPeriodic) {
            neighbours[j++] = colorsTab[(y - 1 + height) % height][x];
            neighbours[j++] = colorsTab[(y + 1) % height][x];
            neighbours[j++] = colorsTab[y][(x - 1 + width) % width];
            neighbours[j++] = colorsTab[y][(x + 1) % width];
        } else {
            neighbours[j++] = (y - 1 < 0) ? neutralColor : colorsTab[y - 1][x];
            neighbours[j++] = (y + 1 < height) ? colorsTab[y + 1][x] : neutralColor;
            neighbours[j++] = (x - 1 < 0) ? neutralColor : colorsTab[y][x - 1];
            neighbours[j++] = (x + 1 < width) ? colorsTab[y][x + 1] : neutralColor;
        }
        int[] colorCounts = new int[possibleColors.length];
        for (Color neighbour : neighbours) {
            for (int i = 0; i < possibleColors.length; i++) {
                if (neighbour.equals(possibleColors[i])) {
                    colorCounts[i]++;
                    break;
                }
            }
        }
        try {
            int maxIndex = getIndexOfMax(colorCounts);
            return possibleColors[maxIndex];
        } catch (Exception e) {
            return neutralColor;
        }
    }

    @Override
    public Color[] getNeighboursColors(int x, int y, Color myColor) {
        Set<Color> colorSet = new HashSet<>();
        if (isPeriodic) {
            if (isEdge(x, (y + 1) % height, myColor) && !myColor.equals(colorsTab[(y + 1) % height][x]))
                colorSet.add(colorsTab[(y + 1) % height][x]);
            if (isEdge((x + 1) % width, y, myColor) && !myColor.equals(colorsTab[y][(x + 1) % width]))
                colorSet.add(colorsTab[y][(x + 1) % width]);
            if (isEdge(x, (y - 1 + height) % height, myColor) && !myColor.equals(colorsTab[(y - 1 + height) % height][x]))
                colorSet.add(colorsTab[(y - 1 + height) % height][x]);
            if (isEdge((x - 1 + width) % width, y, myColor) && !myColor.equals(colorsTab[y][(x - 1 + width) % width]))
                colorSet.add(colorsTab[y][(x - 1+ width) % width]);
        } else {
            if ((y + 1 < height) && isEdge(x, y + 1, myColor) && !myColor.equals(colorsTab[y + 1][x]))
                colorSet.add(colorsTab[y + 1][x]);
            if ((x + 1 < width) && isEdge(x + 1, y, myColor) && !myColor.equals(colorsTab[y][x + 1]))
                colorSet.add(colorsTab[y][x + 1]);
            if ((y - 1 >= 0) && isEdge(x, y - 1, myColor) && !myColor.equals(colorsTab[y - 1][x]))
                colorSet.add(colorsTab[y - 1][x]);
            if ((x - 1 >= 0) && isEdge(x - 1, y, myColor) && !myColor.equals(colorsTab[y][x - 1]))
                colorSet.add(colorsTab[y][x - 1]);
        }
        return colorSet.toArray(new Color[colorSet.size()]);
    }


    @Override
    public int getEnergy(int x, int y, Color color) {
        int energy = 0;
        Color myRealColor = colorsTab[y][x];
        colorsTab[y][x] = color;
        if (isPeriodic) {
            if (isEdge(x, (y + 1) % height))
                energy++;
            if (isEdge((x + 1) % width, y))
                energy++;
            if (isEdge(x, (y - 1 + height) % height))
                energy++;
            if (isEdge((x - 1 + width) % width, y))
                energy++;
        } else {
            if ((y + 1 < height) && isEdge(x, y + 1))
                energy++;
            if ((x + 1 < width) && isEdge(x + 1, y))
                energy++;
            if ((y - 1 >= 0) && isEdge(x, y - 1))
                energy++;
            if ((x - 1 >= 0) && isEdge(x - 1, y))
                energy++;
        }
        colorsTab[y][x] = myRealColor;
        return energy;
    }

    @Override
    public boolean isEdge(int x, int y, Color color) {
        Color thisColor = color;
        if (isPeriodic) {
            if (!thisColor.equals(colorsTab[(y + 1) % height][x]))
                return true;
            if (!thisColor.equals(colorsTab[y][(x + 1) % width]))
                return true;
            if (!thisColor.equals(colorsTab[(y - 1 + height) % height][x]))
                return true;
            if (!thisColor.equals(colorsTab[y][(x - 1 + width) % width]))
                return true;
        } else {
            if ((y + 1 < height) && !thisColor.equals(colorsTab[y + 1][x]))
                return true;
            if ((x + 1 < width) && !thisColor.equals(colorsTab[y][x + 1]))
                return true;
            if ((y - 1 >= 0) && !thisColor.equals(colorsTab[y - 1][x]))
                return true;
            if ((x - 1 >= 0) && !thisColor.equals(colorsTab[y][x - 1]))
                return true;
        }
        return false;
    }

    @Override
    public Integer[][] getNeighbours(int x, int y) {
        List<Integer[]> neighbours=new ArrayList<>();
        if (isPeriodic) {
            neighbours.add(new Integer[]{x, (y + 1) % height});
            neighbours.add(new Integer[]{(x + 1) % width, y});
            neighbours.add(new Integer[]{x, (y - 1 + height) % height});
            neighbours.add(new Integer[]{(x - 1 + width) % width, y});
        } else {
            if ((y + 1 < height) )
                neighbours.add(new Integer[]{x, y + 1});
            if ((x + 1 < width) )
                neighbours.add(new Integer[]{x + 1, y});
            if ((y - 1 >= 0) )
                neighbours.add(new Integer[]{x, y - 1 });
            if ((x - 1 >= 0) )
                neighbours.add(new Integer[]{x - 1 , y});
        }
        return neighbours.toArray(new Integer[neighbours.size()][]);
    }
}
