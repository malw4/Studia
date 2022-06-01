package mod;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;

public class JPane extends JPanel implements ActionListener {

    enum VisualizeMode {
        COLORS, EDGES, ENERGIES, DISLOCATIONS
    }

    int whiteRgb = Color.WHITE.getRGB();
    int darkRgb = Color.black.getRGB();
    public int cellSize;
    private BufferedImage image;
    public Zad zad;
    int change, war2 = 0;
    Timer timer = new Timer(400, (ActionListener) this);
    public boolean czyCzasPlynie = false;
    public boolean debug = false;

    public boolean periodic;
    public int algorithmType;

    public JPane(BufferedImage image, int initialWidth, int initialHeight) {
        this.image = image;
        setNewZad(initialWidth, initialHeight);
        repaint();
        startTime();
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == timer) {
            if (czyCzasPlynie) {
                zad.stepNeighbour();
            } else if (zad.remainingMCSteps > 0) {
                zad.doMonteCarlo();
                System.out.println(zad.remainingMCSteps);
                zad.remainingMCSteps--;
            } else if (debug) {
                zad.DRX();
            }
            repaint();
        }
    }

    public void setNewZad(int width, int height) {
        zad = new Zad(width, height);
        zad.isFlow = periodic;
        zad.changeAlgorithm(algorithmType);
        setCellSize();
        repaint();
    }

    public void startTime() {
        timer.start();
    }

    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;
        if (zad.width > 0 && zad.height > 0)
            g2.drawImage(image, 0, 0, zad.width * cellSize,
                    zad.height * cellSize, Color.black, this);
        else if (zad.width == 0 & zad.height == 0)
            g2.drawImage(image, 0, 0, this);

        for (int j = 0; j < zad.height; j++) {
            for (int i = 0; i < zad.width; i++) {
                if (zad.visualizeEnergies)
                    g2.setColor(zad.monteCarlo.edges[j][i] ? Color.green : Color.blue);
                else if (zad.visualizeBabies) {
                    if (zad.monteCarlo.edges[j][i]) {
                        double density = zad.densities[j][i];
                        if (density <= (zad.recrystal.critical) *0.3) {
                            g2.setColor(new Color(0, 210, 0));
                        }
                        else if (density <= (zad.recrystal.critical)*0.6) {
                            g2.setColor(new Color(0, 100, 0));
                            System.out.println("halo brak");
                        }
                        else if (density <= (zad.recrystal.critical))
                            g2.setColor(new Color(0, 60, 0));
                        } else
                            g2.setColor(Color.blue);
                } else
                    g2.setColor(zad.tab[j][i]);

                g2.fillRect(i * cellSize, j * cellSize, cellSize, cellSize);
            }
        }
    }

    void setCellSize() {
        int max = Math.max(zad.width, zad.height);
        if (max < 1000)
            cellSize = (int) Math.ceil(1000 / max);
        else
            cellSize = 1;
    }

    public void setPeriodic(boolean period) {
        periodic = period;
        zad.isFlow = periodic;
        zad.neighbourAlgorithm.isPeriodic = periodic;
    }

    public void applyReg() {
        if (change >= 0 && change <= 250) {
            if (war2 == 1)
                applyRegPeriodic(image, change);
            else
                image = applyReg(image, change);
        }
        repaint();
    }

    public void applyFrames(boolean make) {
        if (make) {
            makeFrame(image);
        } else
            destroyFrame(image);
        repaint();
    }

    public void repaint() {
        super.repaint();
    }

    void makeFrame(BufferedImage image) {
        for (int i = 0; i < zad.width * cellSize; i++) {
            image.setRGB(i, (zad.height - 1) * cellSize, darkRgb);
            image.setRGB(i, 1, darkRgb);
        }
        for (int j = 0; j < zad.height * cellSize; j++) {
            image.setRGB(1, j, darkRgb);
            image.setRGB((zad.width - 1) * cellSize, j, darkRgb);
        }
    }

    void destroyFrame(BufferedImage image) {
        for (int i = 0; i < image.getWidth(); i++) {
            image.setRGB(i, image.getHeight() - 1, whiteRgb);
            image.setRGB(i, 0, whiteRgb);
        }
        for (int j = 0; j < image.getHeight(); j++) {
            image.setRGB(0, j, whiteRgb);
            image.setRGB(image.getWidth() - 1, j, whiteRgb);
        }
        image.setRGB(image.getWidth() / 2, 0, Color.black.getRGB());
    }

    public BufferedImage applyReg(BufferedImage image, int reg) {
        int width = image.getWidth();
        int height = image.getHeight();

        for (int j = 1; j < height; j++) {
            for (int i = 1; i < width - 1; i++) {
                boolean left, center, right;
                left = (image.getRGB(i - 1, j - 1) & 0xff) < 128;
                center = (image.getRGB(i, j - 1) & 0xff) < 128;
                right = (image.getRGB(i + 1, j - 1) & 0xff) < 128;
                int sum = 0;
                if (left) sum += 4;
                if (center) sum += 2;
                if (right) sum += 1;
                image.setRGB(i, j, whiteRgb);
            }
        }
        return image;
    }

    public void applyRegPeriodic(BufferedImage image, int reg) {
        int width = image.getWidth();
        int height = image.getHeight();

        for (int j = 1; j < height; j++) {
            for (int i = 0; i < width; i++) {
                boolean left, center, right;
                int leftX = i - 1;
                if (leftX < 0) leftX += width;
                int rightX = i + 1;
                if (rightX >= width) rightX -= width;
                left = (image.getRGB(leftX, j - 1) & 0xff) < 128;
                center = (image.getRGB(i, j - 1) & 0xff) < 128;
                right = (image.getRGB(rightX, j - 1) & 0xff) < 128;
                int sum = 0;
                if (left) sum += 4;
                if (center) sum += 2;
                if (right) sum += 1;
                image.setRGB(i, j, whiteRgb);
            }
        }
    }

    public void setAlgorithm(int alg) {
        algorithmType = alg;
        zad.changeAlgorithm(alg);
    }
}
