package mod.panels;

import mod.neighbours.HexagonalNeighbour;
import mod.JPane;
import mod.neighbours.PentagonalNeighbour;
import mod.neighbours.RadiusNeighbour;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimulationPanel extends JPanel {
    JPane canvas;

    String[] algoritm = {"Von Neumann", "Moore", "Pentagonal", "Hexagonal", "Radius"};
    String[] pentagonalTypeNames = {"Down", "Left", "Up", "Right", "Random"};
    String[] hexagonalTypeNames = {"\\", "/", "Random"};

    private JComboBox algChoice = new JComboBox(algoritm);
    private JComboBox pentChoice = new JComboBox(pentagonalTypeNames);
    private JComboBox hexChoice = new JComboBox(hexagonalTypeNames);
    private JSpinner radiusSpinner = new JSpinner(
            new SpinnerNumberModel(4, 0, 20, 1));

    private JRadioButton periodicChkBox = new JRadioButton("Periodic");
    private JButton visualiseButton = new JButton("Play");

    public SimulationPanel(JPane canv) {
        canvas = canv;

        setPreferredSize(new Dimension(200, 200));
        add(algChoice);
        add(pentChoice);
        add(hexChoice);
        add(radiusSpinner);
        add(visualiseButton);
        add(periodicChkBox);

        initControls();

        pentChoice.setVisible(false);
        hexChoice.setVisible(false);
        radiusSpinner.setVisible(false);
    }

    void initControls() {
        algChoice.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int alg = algChoice.getSelectedIndex();
                canvas.setAlgorithm(alg);
                pentChoice.setVisible(alg == 2);
                hexChoice.setVisible(alg == 3);
                radiusSpinner.setVisible(alg == 4);
            }
        });

        visualiseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    canvas.applyReg();
                } catch (Exception ex) {
                    System.err.println("Tekst nie jest liczbą!");
                }
            }
        });

        periodicChkBox.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                canvas.setPeriodic(periodicChkBox.isSelected());
                canvas.repaint();
            }
        });

        visualiseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (canvas.czyCzasPlynie) {
                    canvas.czyCzasPlynie = false;
                    visualiseButton.setText("Play");
                } else {
                    canvas.czyCzasPlynie = true;
                    canvas.zad.neighbourAlgorithm.possibleColors =
                            canvas.zad.colors.toArray(new Color[0]);
                    visualiseButton.setText("Stop");
                }
            }
        });

        pentChoice.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ((PentagonalNeighbour) canvas.zad.neighbourAlgorithm).setType(
                        pentChoice.getSelectedIndex());
            }
        });

        hexChoice.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ((HexagonalNeighbour) canvas.zad.neighbourAlgorithm).setType(
                        hexChoice.getSelectedIndex());
            }
        });

        radiusSpinner.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                ((RadiusNeighbour) canvas.zad.neighbourAlgorithm).setRadius(
                        (int) radiusSpinner.getValue());
            }
        });
    }
}
