package mod;

import mod.panels.*;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class MainWind extends JFrame {
    int initialWidth = 180, initialHeight = 150;
    String[] modeDescriptions = {
            " Set Width & Height (max. 1000x1000) ",
            " Choose seed generation type ",
            " Choose neighbourhood type ",
            " Choose parameters \n for Monte Carlo",
            " Create new seeds and watch \n them grow to be grains"};

    private JPane canvas;

    private JPanel mainPanel;
    private JPanel generalPanel;
    private FieldSizePanel fieldSizePanel;
    private GeneratePanel generatePanel;
    private SimulationPanel simulationPanel;
    private MonteCarloPanel monteCarloPanel;
    private RecrystalPanel recrystalPanel;

    private JPanel[] panels;

    private JComboBox modeChoice = new JComboBox(new String[]{"Tworzenie", "Zarodkowanie", "Sąsiedztwo", "Monte Carlo",
    "Rekrystalizacja"});
    private JTextArea modeDescriptionText = new JTextArea("");


    public MainWind(String title) {
        super(title);
        BufferedImage image = null;
        try {
            image = ImageIO.read(new File(("im.jpg")));
        } catch (IOException e) {
            e.printStackTrace();
        }
        canvas = new JPane(image, initialWidth, initialHeight);
        modeChoice.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int mode = modeChoice.getSelectedIndex();
                modeDescriptionText.setText(modeDescriptions[mode]);
                if (mode == 3 && canvas.zad.tab != null) {
                    canvas.zad.makeEdgesTab();
                }
                setVisiblePanel(mode);
                repaint();
            }
        });

        //==============================================================================================================


        mainPanel = new JPanel();
        mainPanel.setLayout(new BorderLayout());
        mainPanel.add(BorderLayout.CENTER, canvas);

        generalPanel = new JPanel();
        generalPanel.setPreferredSize(new Dimension(200, 250));

        fieldSizePanel = new FieldSizePanel(canvas);
        fieldSizePanel.initialWidth = initialWidth;
        fieldSizePanel.initialHeight = initialHeight;
        generatePanel = new GeneratePanel(canvas);
        simulationPanel = new SimulationPanel(canvas);
        monteCarloPanel = new MonteCarloPanel(canvas);
        recrystalPanel = new RecrystalPanel(canvas);


        mainPanel.add(BorderLayout.EAST, generalPanel);
        generalPanel.add(modeChoice);
        generalPanel.add(modeDescriptionText);
        modeDescriptionText.setText(modeDescriptions[0]);
        generalPanel.add(fieldSizePanel);
        generalPanel.add(generatePanel);
        generalPanel.add(simulationPanel);
        generalPanel.add(monteCarloPanel);
        generalPanel.add(recrystalPanel);

        panels = new JPanel[]{
                fieldSizePanel,
                generatePanel,
                simulationPanel,
                monteCarloPanel,
                recrystalPanel
        };


        setVisiblePanel(0);
        //==============================================================================================================

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setContentPane(mainPanel);

        this.setSize(new Dimension(1300, 1000));
        this.setLocationRelativeTo(null);
    }


    void setVisiblePanel(int panelIndex) {
        for (int i = 0; i < panels.length; i++) {
            panels[i].setVisible(false);
        }
        panels[panelIndex].setVisible(true);
    }

    public static void main(String[] args) {
        MainWind window = new MainWind("ZIARNA");
        window.setVisible(true);
    }
}
