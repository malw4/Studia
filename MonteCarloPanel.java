package mod.panels;

import mod.JPane;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MonteCarloPanel extends JPanel {
    JPane canvas;

    private JButton MCButton = new JButton("Run Monte Carlo!");
    private JRadioButton energyButton = new JRadioButton("Visualize Energy!");
    private JButton ktButton = new JButton("Set KT rate");
    private JSpinner spinKT = new JSpinner(
            new SpinnerNumberModel(0.1, 0.1, 6, 0.1));
    private JSpinner spinMonte = new JSpinner(
            new SpinnerNumberModel(4, 1, 20, 1));

    public MonteCarloPanel(JPane canv) {
        canvas = canv;

        setPreferredSize(new Dimension(200, 500));
        add(spinKT);
        add(ktButton);
        add(spinMonte);
        add(MCButton);
        add(energyButton);

        initControls();
    }

    void initControls() {
        ktButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                canvas.zad.kt = (double) spinKT.getValue();
            }
        });

        MCButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                canvas.zad.remainingMCSteps = (int) spinMonte.getValue();
                canvas.repaint();
            }
        });

        energyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(energyButton.isSelected()) {
                    canvas.zad.visualizeEnergies = true;
                    canvas.repaint();
                }else {
                    canvas.zad.visualizeEnergies = false;
                    canvas.repaint();
                }
            }
        });
    }
}
