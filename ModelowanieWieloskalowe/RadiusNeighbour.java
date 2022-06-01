package mod.neighbours;

import java.awt.*;
import java.lang.Integer;
import java.util.*;
import java.util.List;

public class RadiusNeighbour extends NeighbourAlgorithm{
    int radius = 4;
    List<Integer> xPositions = new ArrayList<>();
    List<Integer> yPositions = new ArrayList<>();

    Map<Color, Integer> neighbours = new HashMap();

    public RadiusNeighbour(int w, int h, boolean isPeriod) {
        width = w;
        height = h;
        isPeriodic = isPeriod;
    }

    public void setRadius(int r) {
        radius = r;
    }

    void addPointsInLineToList(int x, int yMax) {
        for(int y = -yMax; y <= yMax; y++) {
            xPositions.add(x);
            yPositions.add(y);
        }
    }

    @Override
    public int getEnergy(int x, int y,Color color) {
        int energy = 0;
        createNeighboursPositionsLists();
        Color myRealColor = colorsTab[y][x];
        colorsTab[y][x] = color;

        // new radius algorithm to check if neighbours are edges
        RadiusNeighbour radiusNeighbour = new RadiusNeighbour(width, height, isPeriodic);
        radiusNeighbour.colorsTab = colorsTab;
        radiusNeighbour.possibleColors = possibleColors;
        radiusNeighbour.setRadius(radius);

        for(int p = 0; p < xPositions.size(); p++) {
            int pointX = x + xPositions.get(p);
            int pointY = y + yPositions.get(p);
            if (isPeriodic) {
                pointX = (pointX + width) % width;
                pointY = (pointY + height) % height;
            }else{
                if(pointX<0||pointX>=width||pointY<0||pointY>=height)
                    continue;
            }
            if(radiusNeighbour.isEdge(pointX, pointY))
                energy++;
        }
        colorsTab[y][x] = myRealColor;
        return energy;
    }

    @Override
    public boolean isEdge(int x, int y, Color color) {
        createNeighboursPositionsLists();
        for(int p = 0; p < xPositions.size(); p++) {
            int pointX = x + xPositions.get(p);
            int pointY = y + yPositions.get(p);
            if (isPeriodic) {
                pointX = (pointX + width) % width;
                pointY = (pointY + height) % height;
            }else{
                if(pointX<0||pointX>=width||pointY<0||pointY>=height)
                    continue;
            }
            if(!color.equals(colorsTab[pointY][pointX]))
                return true;
        }
        return false;
    }


    @Override
    protected Color decideCell(int x, int y) {
        createNeighboursPositionsLists();

        neighbours.clear();
        for(int p = 0; p < xPositions.size(); p++) {
            int pointX = x + xPositions.get(p);
            int pointY = y + yPositions.get(p);

            if (isPeriodic) {
                pointX = (pointX + width) %width;
                pointY = (pointY + height)%height;
                Color neighbour = colorsTab[pointY][pointX];
                if (!neighbour.equals(neutralColor)) {
                    if (neighbours.containsKey(neighbour))
                        neighbours.put(neighbour, neighbours.get(neighbour) + 1);
                    else
                        neighbours.put(neighbour, 1);
                }
            } else {
                if (isInside(pointX, pointY)) {
                    Color neighbour = colorsTab[pointY][pointX];
                    if (!neighbour.equals(neutralColor)) {
                        if (neighbours.containsKey(neighbour))
                            neighbours.put(neighbour, neighbours.get(neighbour) + 1);
                        else
                            neighbours.put(neighbour, 1);
                    }
                }
            }
        }

        if(neighbours.isEmpty())
            return neutralColor;

        Map.Entry<Color, Integer> highestNeighbour = neighbours.entrySet().iterator().next();
        for ( Map.Entry<Color, Integer> neighbour : neighbours.entrySet()) {
            if(neighbour.getValue() > highestNeighbour.getValue()) {
                highestNeighbour = neighbour;
            }
        }
        return highestNeighbour.getKey();
    }

    private void createNeighboursPositionsLists() {
        xPositions.clear();
        yPositions.clear();

        addPointsInLineToList(0, radius);
        for(int ix = 1; ix <= radius; ix++) {
            int yMax = (int) Math.floor(Math.sqrt(radius * radius - ix * ix));
            addPointsInLineToList(ix, yMax);
            addPointsInLineToList(-ix, yMax);
        }
    }

    boolean isInside(int x, int y) {
        return (x >= 0 && x < width && y >= 0 && y < height);
    }

    @Override
    public Color[] getNeighboursColors(int x, int y, Color myColor) {
        Set<Color> colorSet = new HashSet<>();
        createNeighboursPositionsLists();
        return colorSet.toArray(new Color[colorSet.size()]);
    }

    @Override
    public Integer[][] getNeighbours(int x, int y) {
        List<Integer[]> neighbours = new ArrayList<>();
        if (isPeriodic) {
            neighbours.add(new Integer[]{x, (y + 1) % height});
            neighbours.add(new Integer[]{(x + 1) % width, (y + 1) % height});
            neighbours.add(new Integer[]{(x + 1) % width, y});
            neighbours.add(new Integer[]{(x + 1) % width, (y - 1 + height) % height});
            neighbours.add(new Integer[]{x, (y - 1 + height) % height});
            neighbours.add(new Integer[]{(x - 1 + width) % width, (y - 1 + height) % height});
            neighbours.add(new Integer[]{(x - 1 + width) % width, y});
            neighbours.add(new Integer[]{(x - 1 + width) % width, (y + 1) % height});
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
            if ((y - 1 >= 0) && x - 1 >= 0)
                neighbours.add(new Integer[]{x - 1, y - 1});
            if ((x - 1 >= 0))
                neighbours.add(new Integer[]{x - 1, y});
            if ((y + 1 < height && x - 1 >= 0))
                neighbours.add(new Integer[]{x - 1, y + 1});
        }
        return neighbours.toArray(new Integer[neighbours.size()][]);
    }
}
