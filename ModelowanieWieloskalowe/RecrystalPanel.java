package mod.panels;

import mod.JPane;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RecrystalPanel extends JPanel {
    JPane canvas;

    private JTextArea Atext =new JTextArea("parametr A = 86710969050178.5");
    private JTextArea Btext =new JTextArea("parametr B = 9.41268203527779");
    private JButton REButton = new JButton("Run Rekrystaization!");
    private JRadioButton newBabiesButton = new JRadioButton("Visualize dislocations");
    private JButton działkoButton = new JButton("Ustaw działko");
    private JButton smallDziałkoButton = new JButton("Set mini działo");
    private JSpinner spinDziałko = new JSpinner(
            new SpinnerNumberModel(0.3, 0.1, 1.0, 0.05));
    private JSpinner spinSmallDziałko = new JSpinner(
            new SpinnerNumberModel(0.001, 0.001, 0.5, 0.001));

    public RecrystalPanel(JPane canv) {
        canvas = canv;
        setPreferredSize(new Dimension(200, 500));
        Atext.setSize(new Dimension(190, 200));

        add(Atext);
        add(Btext);
        add(spinDziałko);
        add(działkoButton);
        add(spinSmallDziałko);
        add(smallDziałkoButton);
        add(REButton);
        add(newBabiesButton);

        initControls();
    }

    void initControls() {
        działkoButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                canvas.zad.recrystal.działko = (double) spinDziałko.getValue();
                canvas.repaint();
            }
        });

        smallDziałkoButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                canvas.zad.recrystal.miniDziałko = (double) spinSmallDziałko.getValue();
                canvas.repaint();
            }
        });

        REButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (canvas.debug) {
                    canvas.debug = false;
                    REButton.setText("Play");
                } else {
                    canvas.debug = true;
                    REButton.setText("Stop");
                }
            }
        });

        newBabiesButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(newBabiesButton.isSelected()) {
                    canvas.zad.visualizeBabies = true;
                    canvas.repaint();
                }else {
                    canvas.zad.visualizeBabies = false;
                    canvas.repaint();
                }
            }
        });
    }
}
