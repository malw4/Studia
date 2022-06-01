package mod.neighbours;

import java.awt.*;
import java.util.*;
import java.util.List;

public class PentagonalNeighbour extends NeighbourAlgorithm {

    enum PentagonalType {
        up, right, down, left, random
    }

    PentagonalType direction;

    public PentagonalNeighbour(int w, int h, boolean isPeriod) {
        width = w;
        height = h;
        isPeriodic = isPeriod;
        direction = PentagonalType.random;
    }

    public void setType(int num) {
        direction = PentagonalType.values()[num];
    }


    @Override
    protected Color decideCell(int x, int y) {
        Color[] neighbours = new Color[5];
        int dir = (direction.ordinal() < 4) ? direction.ordinal() : new Random().nextInt(4);
        int j = 0;
        switch (dir) {
            case 0: // UP
                if (isPeriodic) {
                    neighbours[j++] = colorsTab[y][(x + 1) % width];
                    neighbours[j++] = colorsTab[(y - 1 + height) % height][(x + 1) % width];
                    neighbours[j++] = colorsTab[(y - 1 + height) % height][x];
                    neighbours[j++] = colorsTab[(y - 1 + height) % height][(x - 1 + width) % width];
                    neighbours[j++] = colorsTab[y][(x - 1 + width) % width];
                } else {
                    neighbours[j++] = (x + 1 < width) ? colorsTab[y][x + 1] : neutralColor;
                    neighbours[j++] = (y - 1 >= 0 && x + 1 < width) ? colorsTab[y - 1][x + 1] : neutralColor;
                    neighbours[j++] = (y - 1 >= 0) ? colorsTab[y - 1][x] : neutralColor;
                    neighbours[j++] = (y - 1 >= 0 && x - 1 >= 0) ? colorsTab[y - 1][x - 1] : neutralColor;
                    neighbours[j++] = (x - 1 >= 0) ? colorsTab[y][x - 1] : neutralColor;
                }
                break;
            case 1: // RIGHT
                if (isPeriodic) {
                    neighbours[j++] = colorsTab[(y + 1) % height][x];
                    neighbours[j++] = colorsTab[(y + 1) % height][(x + 1) % width];
                    neighbours[j++] = colorsTab[y][(x + 1) % width];
                    neighbours[j++] = colorsTab[(y - 1 + height) % height][(x + 1) % width];
                    neighbours[j++] = colorsTab[(y - 1 + height) % height][x];
                } else {
                    neighbours[j++] = (y + 1 < height) ? colorsTab[y + 1][x] : neutralColor;
                    neighbours[j++] = (y + 1 < height && x + 1 < width) ? colorsTab[y + 1][x + 1] : neutralColor;
                    neighbours[j++] = (x + 1 < width) ? colorsTab[y][x + 1] : neutralColor;
                    neighbours[j++] = (y - 1 >= 0 && x + 1 < width) ? colorsTab[y - 1][x + 1] : neutralColor;
                    neighbours[j++] = (y - 1 >= 0) ? colorsTab[y - 1][x] : neutralColor;
                }
                break;
            case 2: // DOWN
                if (isPeriodic) {
                    neighbours[j++] = colorsTab[(y + 1) % height][x];
                    neighbours[j++] = colorsTab[(y + 1) % height][(x + 1) % width];
                    neighbours[j++] = colorsTab[y][(x + 1) % width];
                    neighbours[j++] = colorsTab[y][(x - 1 + width) % width];
                    neighbours[j++] = colorsTab[(y + 1) % height][(x - 1 + width) % width];
                } else {
                    neighbours[j++] = (y + 1 < height) ? colorsTab[y + 1][x] : neutralColor;
                    neighbours[j++] = (y + 1 < height && x + 1 < width) ? colorsTab[y + 1][x + 1] : neutralColor;
                    neighbours[j++] = (x + 1 < width) ? colorsTab[y][x + 1] : neutralColor;
                    neighbours[j++] = (x - 1 >= 0) ? colorsTab[y][x - 1] : neutralColor;
                    neighbours[j++] = (y + 1 < height && x - 1 >= 0) ? colorsTab[y + 1][x - 1] : neutralColor;
                }
                break;
            case 3: // LEFT
                if (isPeriodic) {
                    neighbours[j++] = colorsTab[(y + 1) % height][x];
                    neighbours[j++] = colorsTab[(y - 1 + height) % height][x];
                    neighbours[j++] = colorsTab[(y - 1 + height) % height][(x - 1 + width) % width];
                    neighbours[j++] = colorsTab[y][(x - 1 + width) % width];
                    neighbours[j++] = colorsTab[(y + 1) % height][(x - 1 + width) % width];
                } else {
                    neighbours[j++] = (y + 1 < height) ? colorsTab[y + 1][x] : neutralColor;
                    neighbours[j++] = (y - 1 >= 0) ? colorsTab[y - 1][x] : neutralColor;
                    neighbours[j++] = (y - 1 >= 0 && x - 1 >= 0) ? colorsTab[y - 1][x - 1] : neutralColor;
                    neighbours[j++] = (x - 1 >= 0) ? colorsTab[y][x - 1] : neutralColor;
                    neighbours[j++] = (y + 1 < height && x - 1 >= 0) ? colorsTab[y + 1][x - 1] : neutralColor;
                }
                break;
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
        int dir = (direction.ordinal() < 4) ? direction.ordinal() : new Random().nextInt(4);
        switch (dir) {
            case 0: // UP
                if (isPeriodic) {
                    if (isEdge((x + 1) % width, y, myColor) && !myColor.equals(colorsTab[y][(x + 1) % width]))
                        colorSet.add(colorsTab[y][(x + 1) % width]);
                    if (isEdge((x + 1) % width, (y - 1 + height) % height, myColor) && !myColor.equals(colorsTab[(y - 1 + height) % height][(x + 1) % width]))
                        colorSet.add(colorsTab[(y - 1 + height) % height][(x + 1) % width]);
                    if (isEdge(x, (y - 1 + height) % height, myColor) && !myColor.equals(colorsTab[(y - 1 + height) % height][x]))
                        colorSet.add(colorsTab[(y - 1 + height) % height][x]);
                    if (isEdge((x - 1 + width) % width, (y - 1 + height) % height, myColor) && !myColor.equals(colorsTab[(y - 1 + height) % height][(x - 1 + width) % width]))
                        colorSet.add(colorsTab[(y - 1 + height) % height][(x - 1 + width) % width]);
                    if (isEdge((x + 1 + width) % width, y, myColor) && !myColor.equals(colorsTab[y][(x + 1 + width) % width]))
                        colorSet.add(colorsTab[y][(x + 1 + width) % width]);
                } else {
                    if ((x + 1 < width) && isEdge(x + 1, y, myColor) && !myColor.equals(colorsTab[y][x + 1]))
                        colorSet.add(colorsTab[y][x + 1]);
                    if ((y - 1 >= 0) && isEdge(x, y - 1, myColor) && !myColor.equals(colorsTab[y - 1][x]))
                        colorSet.add(colorsTab[y - 1][x]);
                    if ((y - 1 >= 0) && (x + 1 < width) && isEdge(x + 1, y - 1, myColor) && !myColor.equals(colorsTab[y - 1][x + 1]))
                        colorSet.add(colorsTab[y - 1][x + 1]);
                    if ((y - 1 >= 0) && (x - 1 >= 0) && isEdge(x - 1, y - 1, myColor) && !myColor.equals(colorsTab[y - 1][x - 1]))
                        colorSet.add(colorsTab[y - 1][x - 1]);
                    if ((x - 1 >= 0) && isEdge(x - 1, y, myColor) && !myColor.equals(colorsTab[y][x - 1]))
                        colorSet.add(colorsTab[y][x - 1]);
                }
                break;
            case 1: // RIGHT
                if (isPeriodic) {
                    if (isEdge(x, (y + 1) % height, myColor) && !myColor.equals(colorsTab[(y + 1) % height][x]))
                        colorSet.add(colorsTab[(y + 1) % height][x]);
                    if (isEdge((x + 1) % width, (y + 1) % height, myColor) && !myColor.equals(colorsTab[(y + 1) % height][(x + 1) % width]))
                        colorSet.add(colorsTab[(y + 1) % height][(x + 1) % width]);
                    if (isEdge((x + 1) % width, y, myColor) && !myColor.equals(colorsTab[y][(x + 1) % width]))
                        colorSet.add(colorsTab[y][(x + 1) % width]);
                    if (isEdge((x + 1) % width, (y - 1 + height) % height, myColor) && !myColor.equals(colorsTab[(y - 1 + height) % height][(x + 1) % width]))
                        colorSet.add(colorsTab[(y - 1 + height) % height][(x + 1) % width]);
                    if (isEdge(x, (y - 1 + height) % height, myColor) && !myColor.equals(colorsTab[(y - 1 + height) % height][x]))
                        colorSet.add(colorsTab[(y - 1 + height) % height][x]);
                } else {
                    if ((y + 1 < height) && isEdge(x, y + 1, myColor) && !myColor.equals(colorsTab[y + 1][x]))
                        colorSet.add(colorsTab[y + 1][x]);
                    if ((y + 1 < height) && (x + 1 < width) && isEdge(x + 1, y + 1, myColor) && !myColor.equals(colorsTab[y + 1][x + 1]))
                        colorSet.add(colorsTab[y + 1][x + 1]);
                    if ((x + 1 < width) && isEdge(x + 1, y, myColor) && !myColor.equals(colorsTab[y][x + 1]))
                        colorSet.add(colorsTab[y][x + 1]);
                    if ((y - 1 >= 0) && (x + 1 < width) && isEdge(x + 1, y - 1, myColor) && !myColor.equals(colorsTab[y - 1][x + 1]))
                        colorSet.add(colorsTab[y - 1][x + 1]);
                    if ((y - 1 >= 0) && isEdge(x, y - 1, myColor) && !myColor.equals(colorsTab[y - 1][x]))
                        colorSet.add(colorsTab[y - 1][x]);
                }
                break;
            case 2: // DOWN
                if (isPeriodic) {
                    if (isEdge(x, (y + 1) % height, myColor) && !myColor.equals(colorsTab[(y + 1) % height][x]))
                        colorSet.add(colorsTab[(y + 1) % height][x]);
                    if (isEdge((x + 1) % width, (y + 1) % height, myColor) && !myColor.equals(colorsTab[(y + 1) % height][(x + 1) % width]))
                        colorSet.add(colorsTab[(y + 1) % height][(x + 1) % width]);
                    if (isEdge((x + 1) % width, y, myColor) && !myColor.equals(colorsTab[y][(x + 1) % width]))
                        colorSet.add(colorsTab[y][(x + 1) % width]);
                    if (isEdge((x - 1 + width) % width, y, myColor) && !myColor.equals(colorsTab[y][(x - 1 + width) % width]))
                        colorSet.add(colorsTab[y][(x - 1 + width) % width]);
                    if (isEdge((x - 1 + width) % width, (y + 1) % height, myColor) && !myColor.equals(colorsTab[(y + 1) % height][(x - 1 + width) % width]))
                        colorSet.add(colorsTab[(y + 1) % height][(x - 1 + width) % width]);
                } else {
                    if ((y + 1 < height) && isEdge(x, y + 1, myColor) && !myColor.equals(colorsTab[y + 1][x]))
                        colorSet.add(colorsTab[y + 1][x]);
                    if ((y + 1 < height) && (x + 1 < width) && isEdge(x + 1, y + 1, myColor) && !myColor.equals(colorsTab[y + 1][x + 1]))
                        colorSet.add(colorsTab[y + 1][x + 1]);
                    if ((x + 1 < width) && isEdge(x + 1, y, myColor) && !myColor.equals(colorsTab[y][x + 1]))
                        colorSet.add(colorsTab[y][x + 1]);
                    if ((x - 1 >= 0) && isEdge(x - 1, y, myColor) && !myColor.equals(colorsTab[y][x - 1]))
                        colorSet.add(colorsTab[y][x - 1]);
                    if ((x - 1 >= 0) && (y + 1 < height) && isEdge(x - 1, y + 1, myColor) && !myColor.equals(colorsTab[y + 1][x - 1]))
                        colorSet.add(colorsTab[y + 1][x - 1]);
                }
                break;
            case 3: // LEFT
                if (isPeriodic) {
                    if (isEdge(x, (y + 1) % height, myColor) && !myColor.equals(colorsTab[(y + 1) % height][x]))
                        colorSet.add(colorsTab[(y + 1) % height][x]);
                    if (isEdge(x, (y - 1 + height) % height, myColor) && !myColor.equals(colorsTab[(y - 1 + height) % height][x]))
                        colorSet.add(colorsTab[(y - 1 + height) % height][x]);
                    if (isEdge((x - 1 + width) % width, (y - 1 + height) % height, myColor) && !myColor.equals(colorsTab[(y - 1 + height) % height][(x - 1 + width) % width]))
                        colorSet.add(colorsTab[(y - 1 + height) % height][(x - 1 + width) % width]);
                    if (isEdge((x - 1 + width) % width, y, myColor) && !myColor.equals(colorsTab[y][(x - 1 + width) % width]))
                        colorSet.add(colorsTab[y][(x - 1 + width) % width]);
                    if (isEdge((x - 1 + width) % width, (y + 1) % height, myColor) && !myColor.equals(colorsTab[(y + 1) % height][(x - 1 + width) % width]))
                        colorSet.add(colorsTab[(y + 1) % height][(x - 1 + width) % width]);
                } else {
                    if ((y - 1 >= 0) && isEdge(x, y - 1, myColor) && !myColor.equals(colorsTab[y - 1][x]))
                        colorSet.add(colorsTab[y - 1][x]);
                    if ((y - 1 >= 0) && (x - 1 >= 0) && isEdge(x - 1, y - 1, myColor) && !myColor.equals(colorsTab[y - 1][x - 1]))
                        colorSet.add(colorsTab[y - 1][x - 1]);
                    if ((x + 1 < width) && isEdge(x + 1, y, myColor) && !myColor.equals(colorsTab[y][x + 1]))
                        colorSet.add(colorsTab[y][x + 1]);
                    if ((x - 1 >= 0) && isEdge(x - 1, y, myColor) && !myColor.equals(colorsTab[y][x - 1]))
                        colorSet.add(colorsTab[y][x - 1]);
                    if ((y + 1 < height) && (x - 1 >= 0) && isEdge(x - 1, y + 1, myColor) && !myColor.equals(colorsTab[y + 1][x - 1]))
                        colorSet.add(colorsTab[y + 1][x - 1]);
                }
                break;
        }
        return colorSet.toArray(new Color[colorSet.size()]);
    }

    @Override
    public int getEnergy(int x, int y, Color color) {
        int energy = 0;
        Color myRealColor = colorsTab[y][x];
        colorsTab[y][x] = color;
        int dir = (direction.ordinal() < 4) ? direction.ordinal() : new Random().nextInt(4);
        switch (dir) {
            case 0: // UP
                if (isPeriodic) {
                    if (isEdge((x + 1) % width, y))
                        energy++;
                    if (isEdge((x + 1) % width, (y - 1 + height) % height))
                        energy++;
                    if (isEdge(x, (y - 1 + height) % height))
                        energy++;
                    if (isEdge((x - 1 + width) % width, (y - 1 + height) % height))
                        energy++;
                    if (isEdge((x + 1 + width) % width, y))
                        energy++;
                } else {
                    if ((x + 1 < width) && isEdge(x + 1, y))
                        energy++;
                    if ((y - 1 >= 0) && isEdge(x, y - 1))
                        energy++;
                    if ((x + 1 < width) && (y - 1 >= 0) && isEdge(x + 1, y - 1))
                        energy++;
                    if ((y - 1 >= 0) && (x - 1 >= 0) && isEdge(x - 1, y - 1))
                        energy++;
                    if ((x - 1 >= 0) && isEdge(x - 1, y))
                        energy++;
                }
                break;
            case 1: // RIGHT
                if (isPeriodic) {
                    if (isEdge(x, (y + 1) % height))
                        energy++;
                    if (isEdge((x + 1) % width, (y + 1) % height))
                        energy++;
                    if (isEdge((x + 1) % width, y))
                        energy++;
                    if (isEdge((x + 1) % width, (y - 1 + height) % height))
                        energy++;
                    if (isEdge(x, (y - 1 + height) % height))
                        energy++;
                } else {
                    if ((y + 1 < height) && isEdge(x, y + 1))
                        energy++;
                    if ((y + 1 < height) && (x + 1 < width) && isEdge(x + 1, y + 1))
                        energy++;
                    if ((x + 1 < width) && isEdge(x + 1, y))
                        energy++;
                    if ((y - 1 >= 0) && (x + 1 < width) && isEdge(x + 1, y - 1))
                        energy++;
                    if ((y - 1 >= 0) && isEdge(x, y - 1))
                        energy++;
                }
                break;
            case 2: // DOWN
                if (isPeriodic) {
                    if (isEdge(x, (y + 1) % height))
                        energy++;
                    if (isEdge((x + 1) % width, (y + 1) % height))
                        energy++;
                    if (isEdge((x + 1) % width, y))
                        energy++;
                    if (isEdge((x - 1 + width) % width, y))
                        energy++;
                    if (isEdge((x - 1 + width) % width, (y + 1) % height))
                        energy++;
                } else {
                    if ((y + 1 < height) && isEdge(x, y + 1))
                        energy++;
                    if ((y + 1 < height) && (x + 1 < width) && isEdge(x + 1, y + 1))
                        energy++;
                    if ((x + 1 < width) && isEdge(x + 1, y))
                        energy++;
                    if ((x - 1 >= 0) && isEdge(x - 1, y))
                        energy++;
                    if ((x - 1 >= 0) && (y + 1 < height) && isEdge(x - 1, y + 1))
                        energy++;
                }
                break;
            case 3: // LEFT
                if (isPeriodic) {
                    if (isEdge(x, (y + 1) % height))
                        energy++;
                    if (isEdge(x, (y - 1 + height) % height))
                        energy++;
                    if (isEdge((x - 1 + width) % width, (y - 1 + height) % height))
                        energy++;
                    if (isEdge((x - 1 + width) % width, y))
                        energy++;
                    if (isEdge((x - 1 + width) % width, (y + 1) % height))
                        energy++;
                } else {
                    if ((y - 1 >= 0) && isEdge(x, y - 1))
                        energy++;
                    if ((y - 1 >= 0) && (x - 1 >= 0) && isEdge(x - 1, y - 1))
                        energy++;
                    if ((x + 1 < width) && isEdge(x + 1, y))
                        energy++;
                    if ((x - 1 >= 0) && isEdge(x - 1, y))
                        energy++;
                    if ((x - 1 >= 0) && (y + 1 < height) && isEdge(x - 1, y + 1))
                        energy++;
                }
                break;
        }
        colorsTab[y][x] = myRealColor;
        return energy;
    }

    @Override
    public boolean isEdge(int x, int y, Color color) {
        Color thisColor = color;
        int dir = (direction.ordinal() < 4) ? direction.ordinal() : new Random().nextInt(4);
        switch (dir) {
            case 0: // UP
                if (isPeriodic) {
                    if (!thisColor.equals(colorsTab[y][(x + 1) % width]))
                        return true;
                    if (!thisColor.equals(colorsTab[(y - 1 + height) % height][(x + 1) % width]))
                        return true;
                    if (!thisColor.equals(colorsTab[(y - 1 + height) % height][x]))
                        return true;
                    if (!thisColor.equals(colorsTab[(y - 1 + height) % height][(x - 1 + width) % width]))
                        return true;
                    if (!thisColor.equals(colorsTab[y][(x + 1 + width) % width]))
                        return true;
                } else {
                    if ((x + 1 < width) && !thisColor.equals(colorsTab[y][x + 1]))
                        return true;
                    if ((y - 1 >= 0) && !thisColor.equals(colorsTab[y - 1][x]))
                        return true;
                    if ((x + 1 < width) && (y - 1 >= 0) && !thisColor.equals(colorsTab[y - 1][x + 1]))
                        return true;
                    if ((y - 1 >= 0) && (x - 1 >= 0) && !thisColor.equals(colorsTab[y - 1][x - 1]))
                        return true;
                    if ((x - 1 >= 0) && !thisColor.equals(colorsTab[y][x - 1]))
                        return true;
                }
                break;
            case 1: // RIGHT
                if (isPeriodic) {
                    if (!thisColor.equals(colorsTab[(y + 1) % height][x]))
                        return true;
                    if (!thisColor.equals(colorsTab[(y + 1) % height][(x + 1) % width]))
                        return true;
                    if (!thisColor.equals(colorsTab[y][(x + 1) % width]))
                        return true;
                    if (!thisColor.equals(colorsTab[(y - 1 + height) % height][(x + 1) % width]))
                        return true;
                    if (!thisColor.equals(colorsTab[(y - 1 + height) % height][x]))
                        return true;
                } else {
                    if ((y + 1 < height) && !thisColor.equals(colorsTab[y + 1][x]))
                        return true;
                    if ((y + 1 < height) && (x + 1 < width) && !thisColor.equals(colorsTab[y + 1][x + 1]))
                        return true;
                    if ((x + 1 < width) && !thisColor.equals(colorsTab[y][x + 1]))
                        return true;
                    if ((y - 1 >= 0) && (x + 1 < width) && !thisColor.equals(colorsTab[y - 1][x + 1]))
                        return true;
                    if ((y - 1 >= 0) && !thisColor.equals(colorsTab[y - 1][x]))
                        return true;
                }
                break;
            case 2: // DOWN
                if (isPeriodic) {
                    if (!thisColor.equals(colorsTab[(y + 1) % height][x]))
                        return true;
                    if (!thisColor.equals(colorsTab[(y + 1) % height][(x + 1) % width]))
                        return true;
                    if (!thisColor.equals(colorsTab[y][(x + 1) % width]))
                        return true;
                    if (!thisColor.equals(colorsTab[y][(x - 1 + width) % width]))
                        return true;
                    if (!thisColor.equals(colorsTab[(y + 1) % height][(x - 1 + width) % width]))
                        return true;
                } else {
                    if ((y + 1 < height) && !thisColor.equals(colorsTab[y + 1][x]))
                        return true;
                    if ((y + 1 < height) && (x + 1 < width) && !thisColor.equals(colorsTab[y + 1][x + 1]))
                        return true;
                    if ((x + 1 < width) && !thisColor.equals(colorsTab[y][x + 1]))
                        return true;
                    if ((x - 1 >= 0) && !thisColor.equals(colorsTab[y][x - 1]))
                        return true;
                    if ((x - 1 >= 0) && (y + 1 < height) && !thisColor.equals(colorsTab[y + 1][x - 1]))
                        return true;
                }
                break;
            case 3: // LEFT
                if (isPeriodic) {
                    if (!thisColor.equals(colorsTab[(y + 1) % height][x]))
                        return true;
                    if (!thisColor.equals(colorsTab[(y - 1 + height) % height][x]))
                        return true;
                    if (!thisColor.equals(colorsTab[(y - 1 + height) % height][(x - 1 + width) % width]))
                        return true;
                    if (!thisColor.equals(colorsTab[y][(x - 1 + width) % width]))
                        return true;
                    if (!thisColor.equals(colorsTab[(y + 1) % height][(x - 1 + width) % width]))
                        return true;
                } else {
                    if ((y - 1 >= 0) && !thisColor.equals(colorsTab[y - 1][x]))
                        return true;
                    if ((y - 1 >= 0) && (x - 1 >= 0) && !thisColor.equals(colorsTab[y - 1][x - 1]))
                        return true;
                    if ((x + 1 < width) && !thisColor.equals(colorsTab[y][x + 1]))
                        return true;
                    if ((x - 1 >= 0) && !thisColor.equals(colorsTab[y][x - 1]))
                        return true;
                    if ((x - 1 >= 0) && (y + 1 < height) && !thisColor.equals(colorsTab[y + 1][x - 1]))
                        return true;
                }
                break;
        }
        return false;
    }

    @Override
    public Integer[][] getNeighbours(int x, int y) {
        List<Integer[]> neighbours = new ArrayList<>();
        int dir = (direction.ordinal() < 4) ? direction.ordinal() : new Random().nextInt(4);
        switch (dir) {
            case 0: // UP
                if (isPeriodic) {
                    neighbours.add(new Integer[]{(x + 1) % width, y});
                    neighbours.add(new Integer[]{(x + 1) % width, (y - 1 + height) % height});
                    neighbours.add(new Integer[]{x, (y - 1 + height) % height});
                    neighbours.add(new Integer[]{(x - 1 + width) % width, (y - 1 + height) % height});
                    neighbours.add(new Integer[]{(x + 1 + width) % width, y});
                } else {
                    if ((x + 1 < width))
                        neighbours.add(new Integer[]{x + 1, y});
                    if ((y - 1 >= 0))
                        neighbours.add(new Integer[]{x, y - 1});
                    if ((y - 1 >= 0) && x + 1 < width)
                        neighbours.add(new Integer[]{x + 1, y - 1});
                    if ((y - 1 >= 0) && x - 1 >= 0)
                        neighbours.add(new Integer[]{x - 1, y - 1});
                    if ((x - 1 >= 0))
                        neighbours.add(new Integer[]{x - 1, y});
                }
                break;
            case 1: // RIGHT
                if (isPeriodic) {
                    neighbours.add(new Integer[]{x, (y + 1) % height});
                    neighbours.add(new Integer[]{(x + 1) % width, (y + 1) % height});
                    neighbours.add(new Integer[]{(x + 1) % width, y});
                    neighbours.add(new Integer[]{(x + 1) % width, (y - 1 + height) % height});
                    neighbours.add(new Integer[]{x, (y - 1 + height) % height});
                } else {
                    if ((y + 1 < height))
                        neighbours.add(new Integer[]{x, y + 1});
                    if ((y + 1 < height && x + 1 < width))
                        neighbours.add(new Integer[]{x + 1, y + 1});
                    if ((x + 1 < width))
                        neighbours.add(new Integer[]{x + 1, y});
                    if ((y - 1 >= 0 && x + 1 < width))
                        neighbours.add(new Integer[]{x + 1, y - 1});
                    if ((y - 1 >= 0))
                        neighbours.add(new Integer[]{x, y - 1});
                }
                break;

            case 2: // DOWN
                if (isPeriodic) {
                    neighbours.add(new Integer[]{x, (y + 1) % height});
                    neighbours.add(new Integer[]{(x + 1) % width, (y + 1) % height});
                    neighbours.add(new Integer[]{(x + 1) % width, y});
                    neighbours.add(new Integer[]{(x - 1 + width) % width, y});
                    neighbours.add(new Integer[]{(x - 1 + width) % width, (y + 1) % height});
                } else {
                    if ((y + 1 < height))
                        neighbours.add(new Integer[]{x, y + 1});
                    if ((y + 1 < height && x + 1 < width))
                        neighbours.add(new Integer[]{x + 1, y + 1});
                    if ((x + 1 < width))
                        neighbours.add(new Integer[]{x + 1, y});
                    if ((x - 1 >= 0))
                        neighbours.add(new Integer[]{x - 1, y});
                    if ((y + 1 < height && x - 1 >= 0))
                        neighbours.add(new Integer[]{x - 1, y + 1});
                }
                break;
            case 3: // LEFT
                if (isPeriodic) {
                    neighbours.add(new Integer[]{x, (y + 1) % height});
                    neighbours.add(new Integer[]{x, (y - 1 + height) % height});
                    neighbours.add(new Integer[]{(x - 1 + width) % width, (y - 1 + height) % height});
                    neighbours.add(new Integer[]{(x - 1 + width) % width, y});
                    neighbours.add(new Integer[]{(x - 1 + width) % width, (y + 1) % height});
                } else {
                    if ((y - 1 >= 0))
                    neighbours.add(new Integer[]{x, y - 1});
                    if ((y - 1 >= 0) && x - 1 >= 0)
                        neighbours.add(new Integer[]{x - 1, y - 1});
                    if ((x + 1 < width))
                        neighbours.add(new Integer[]{x + 1, y});
                    if ((x - 1 >= 0))
                        neighbours.add(new Integer[]{x - 1, y});
                    if ((y + 1 < height && x - 1 >= 0))
                        neighbours.add(new Integer[]{x - 1, y + 1});
                }
                break;
        }
        return neighbours.toArray(new Integer[neighbours.size()][]);
    }
}